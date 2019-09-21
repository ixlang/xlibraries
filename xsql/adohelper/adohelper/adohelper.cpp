// adohelper.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <sstream>   

XNLEnv * gs_env = 0;

XNLEXPORT xint XI_STDCALL XNLMain(XNLEnv * env, xint version){
	//CoInitialize(NULL);
	CoInitializeEx(0, COINIT_MULTITHREADED);
	gs_env = env->getEnv();
	return 0;
}

XNLEXPORT xint XI_STDCALL XNLExit(XNLEnv * env){
	env->releaseEnv(gs_env);
	gs_env = 0;
	CoUninitialize();
	return 0;
}

typedef UINT32 uint32;
typedef UINT16 uint16;

bool utf8_to_utf16le(const char * u8str, size_t len, std::wstring & u16str)
{
	const unsigned char* p = (unsigned char*)(u8str);
	// 判断是否具有BOM(判断长度小于3字节的情况)
	if (len > 3 && p[0] == 0xEF && p[1] == 0xBB && p[2] == 0xBF){
		p += 3;
		len -= 3;
	}

	bool is_ok = true;
	// 开始转换
	for (size_t i = 0; i < len; ++i) {
		uint32  ch = p[i]; // 取出UTF8序列首字节
		if ((ch & 0x80) == 0) {
			// 最高位为0，只有1字节表示UNICODE代码点
			u16str.push_back((uint16)ch);
			continue;
		}
		switch (ch & 0xF0)
		{
		case 0xF0: // 4 字节字符, 0x10000 到 0x10FFFF
		{
			uint32 c2 = p[++i];
			uint32 c3 = p[++i];
			uint32 c4 = p[++i];
			// 计算UNICODE代码点值(第一个字节取低3bit，其余取6bit)
			uint32 codePoint = ((ch & 0x07U) << 18) | ((c2 & 0x3FU) << 12) | ((c3 & 0x3FU) << 6) | (c4 & 0x3FU);
			if (codePoint >= 0x10000)
			{
				// 在UTF-16中 U+10000 到 U+10FFFF 用两个16bit单元表示, 代理项对.
				// 1、将代码点减去0x10000(得到长度为20bit的值)
				// 2、high 代理项 是将那20bit中的高10bit加上0xD800(110110 00 00000000)
				// 3、low  代理项 是将那20bit中的低10bit加上0xDC00(110111 00 00000000)
				codePoint -= 0x10000;
				u16str.push_back((uint16)((codePoint >> 10) | 0xD800U));
				u16str.push_back((uint16)((codePoint & 0x03FFU) | 0xDC00U));
			}
			else
			{
				// 在UTF-16中 U+0000 到 U+D7FF 以及 U+E000 到 U+FFFF 与Unicode代码点值相同.
				// U+D800 到 U+DFFF 是无效字符, 为了简单起见，这里假设它不存在(如果有则不编码)
				u16str.push_back((uint16)codePoint);
			}
		}
		break;
		case 0xE0: // 3 字节字符, 0x800 到 0xFFFF
		{
			uint32 c2 = p[++i];
			uint32 c3 = p[++i];
			// 计算UNICODE代码点值(第一个字节取低4bit，其余取6bit)
			uint32 codePoint = ((ch & 0x0FU) << 12) | ((c2 & 0x3FU) << 6) | (c3 & 0x3FU);
			u16str.push_back((uint16)codePoint);
		}
		break;
		case 0xD0: // 2 字节字符, 0x80 到 0x7FF
		case 0xC0:
		{
			uint32 c2 = p[++i];
			// 计算UNICODE代码点值(第一个字节取低5bit，其余取6bit)
			uint32 codePoint = ((ch & 0x1FU) << 12) | ((c2 & 0x3FU) << 6);
			u16str.push_back((uint16)codePoint);
		}
		break;
		default:    // 单字节部分(前面已经处理，所以不应该进来)
			is_ok = false;
			break;
		}
	}

	return is_ok;
}

std::string utf16le_to_utf8(const WCHAR * u16str)
{
	if (u16str == 0){ return std::string(); }
	const WCHAR* p = u16str;
	std::u16string::size_type len = wcslen(u16str);
	if (p[0] == 0xFEFF){
		p += 1; //带有bom标记，后移
		len -= 1;
	}

	// 开始转换
	std::string u8str;
	u8str.reserve(len * 3);

	char16_t u16char;
	for (std::u16string::size_type i = 0; i < len; ++i){
		// 这里假设是在小端序下(大端序不适用)
		u16char = p[i];

		// 1字节表示部分
		if (u16char < 0x0080){
			// u16char <= 0x007f
			// U- 0000 0000 ~ 0000 07ff : 0xxx xxxx
			u8str.push_back((char)(u16char & 0x00FF));  // 取低8bit
			continue;
		}
		// 2 字节能表示部分
		if (u16char >= 0x0080 && u16char <= 0x07FF){
			// * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
			u8str.push_back((char)(((u16char >> 6) & 0x1F) | 0xC0));
			u8str.push_back((char)((u16char & 0x3F) | 0x80));
			continue;
		}
		// 代理项对部分(4字节表示)
		if (u16char >= 0xD800 && u16char <= 0xDBFF) {
			// * U-00010000 - U-001FFFFF: 1111 0xxx 10xxxxxx 10xxxxxx 10xxxxxx
			UINT32 highSur = u16char;
			UINT32 lowSur = p[++i];
			// 从代理项对到UNICODE代码点转换
			// 1、从高代理项减去0xD800，获取有效10bit
			// 2、从低代理项减去0xDC00，获取有效10bit
			// 3、加上0x10000，获取UNICODE代码点值
			UINT32 codePoint = highSur - 0xD800;
			codePoint <<= 10;
			codePoint |= lowSur - 0xDC00;
			codePoint += 0x10000;
			// 转为4字节UTF8编码表示
			u8str.push_back((char)((codePoint >> 18) | 0xF0));
			u8str.push_back((char)(((codePoint >> 12) & 0x3F) | 0x80));
			u8str.push_back((char)(((codePoint >> 06) & 0x3F) | 0x80));
			u8str.push_back((char)((codePoint & 0x3F) | 0x80));
			continue;
		}
		// 3 字节表示部分
		{
			// * U-0000E000 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
			u8str.push_back((char)(((u16char >> 12) & 0x0F) | 0xE0));
			u8str.push_back((char)(((u16char >> 6) & 0x3F) | 0x80));
			u8str.push_back((char)((u16char & 0x3F) | 0x80));
			continue;
		}
	}

	return u8str;
}




XObject * variant2String(_variant_t & data) {
	XObject * strobj = gs_env->createObject();
	_bstr_t bstr = data;
	BSTR _bstr = bstr.GetBSTR();
	if (_bstr != 0){
		std::string utf8str = utf16le_to_utf8(_bstr);
		gs_env->setValue(0, strobj, utf8str.c_str(), utf8str.length());
	}
	return strobj;
}

XNLEXPORT void * XI_CDECL ado_alloc(xstring driver, xstring host, int port, xstring name, xstring pwd, xint timeout, xint * errcode, XObject * err){
	_ConnectionPtr * pptr = new _ConnectionPtr();
	try{

		std::ostringstream strstm;
		strstm << "Driver={" << driver << "};server=" << host << "," << port << ";uid=" << name << ";pwd=" << pwd << ";";
		std::string connsql = strstm.str();

		_ConnectionPtr & pConnection = *pptr;
		HRESULT hr = pConnection.CreateInstance(__uuidof(Connection));
		if (FAILED(hr)){
			delete pptr;
			return 0;
		}
		_bstr_t strConnect = connsql.c_str();
		pConnection->ConnectionString = strConnect;
		pConnection->ConnectionTimeout = timeout;
		hr = pConnection->Open("", "", "", NULL);
		_variant_t vAffected;
		if (FAILED(hr)){
			delete pptr;
			pptr = 0;
		}
	}
	catch (_com_error &e){
		*errcode = e.Error();
		std::string errstr = utf16le_to_utf8(e.Description());
		gs_env->setValue(0, err, errstr.c_str(), errstr.length());
		delete pptr;
		pptr = 0;
	}
	//_bstr_t strConnect = "Provider=OraOLEDB.Oracle;Data Source=orcl;User Id=scott;Password=m123;"; //ORACLE

	return pptr;
}

XNLEXPORT void XI_CDECL ado_delloc(void * handle){
	_ConnectionPtr * pptr = (_ConnectionPtr *)handle;
	(*pptr)->Close();
	delete pptr;
}


XNLEXPORT void * XI_CDECL ado_execute(void * handle, const char * sql, bool needRs, xint * err, XObject * errout){
	_ConnectionPtr * pptr = (_ConnectionPtr *)handle;

	_RecordsetPtr * ppRecord = new _RecordsetPtr();// pConnection->Execute(, &vAffected, adCmdText);
	_RecordsetPtr & pRecord = *ppRecord;

	pRecord.CreateInstance(__uuidof(Recordset));
	try{
		std::wstring wstr;
		utf8_to_utf16le(sql, strlen(sql), wstr);
		HRESULT hr = pRecord->Open(_variant_t(wstr.c_str()), (*pptr).GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
		if (FAILED(hr)){
			delete ppRecord;
			ppRecord = 0;
		}
	}catch (_com_error &e){
		*err = e.Error();
		
		std::string errstr = utf16le_to_utf8(e.Description());
		gs_env->setValue(0, errout, errstr.c_str(), errstr.length());

		delete ppRecord;
		ppRecord = 0;
	}

	return ppRecord;
}


XNLEXPORT void XI_CDECL ado_delloc_rs(void * handle){
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)handle;
	
	try{
		(*ppRecord)->Close();
	}catch (_com_error &){
	}
	
	delete ppRecord;
}

XNLEXPORT bool XI_CDECL ado_rs_next(void * handle){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)handle;
	try{
		hr = (*ppRecord)->MoveNext();
	}catch (_com_error &){

	}
	return FAILED(hr) == false;
}

XNLEXPORT bool XI_CDECL ado_rs_prev(void * handle){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)handle;
	try{
		hr = (*ppRecord)->MovePrevious();
	}
	catch (_com_error &){

	}
	return FAILED(hr) == false;
}

XNLEXPORT bool XI_CDECL ado_rs_first(void * handle){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)handle;
	try{
		hr = (*ppRecord)->MoveFirst();
	}
	catch (_com_error &){

	}
	return FAILED(hr) == false;
}

XNLEXPORT bool XI_CDECL ado_rs_last(void * handle){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)handle;
	try{
		hr = (*ppRecord)->MoveLast();
	}
	catch (_com_error &){

	}
	return FAILED(hr) == false;
}

XNLEXPORT xint XI_CDECL ado_rs_count(void * handle){
	int count = 0;
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)handle;
	try{
		count = (*ppRecord)->GetRecordCount();
	}
	catch (_com_error &){

	}
	return count;
}

XNLEXPORT bool XI_CDECL ado_rs_iseof(void * handle){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)handle;
	return !!((*ppRecord)->adoEOF);
}


XNLEXPORT XObject* XI_CDECL ado_rs_getValue(void *rs, const char * key){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)rs;
	_variant_t value; try{ value = (*ppRecord)->GetCollect(key); }catch (_com_error &){}
	return variant2String(value);
}

XNLEXPORT xint XI_CDECL ado_rs_getValueI(void *rs, const char * key){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)rs;
	_variant_t value; try{ value = (*ppRecord)->GetCollect(key); }	catch (_com_error &){}
	return xint(value);
}

XNLEXPORT xlong XI_CDECL ado_rs_getValueL(void *rs, const char * key){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)rs;
	_variant_t value; try{ value = (*ppRecord)->GetCollect(key); }	catch (_com_error &){}
	return xlong(value);
}

XNLEXPORT double XI_CDECL ado_rs_getValueD(void *rs, const char * key){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)rs;
	_variant_t value; try{ value = (*ppRecord)->GetCollect(key); }	catch (_com_error &){}
	return double(value);
}

XNLEXPORT XObject * XI_CDECL ado_rs_getIValue(void *rs, int idx){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)rs;
	_variant_t value; try{ value = (*ppRecord)->GetCollect(idx); }catch (_com_error &){}
	return variant2String(value);
}

XNLEXPORT xint XI_CDECL ado_rs_getIValueI(void *rs, int idx){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)rs;
	_variant_t value; try{ value = (*ppRecord)->GetCollect(idx); }catch (_com_error &){}
	return xint(value);
}

XNLEXPORT xlong XI_CDECL ado_rs_getIValueL(void *rs, int idx){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)rs;
	_variant_t value; try{ value = (*ppRecord)->GetCollect(idx); }catch (_com_error &){}
	return xlong(value);
}

XNLEXPORT double XI_CDECL ado_rs_getIValueD(void *rs, int idx){
	HRESULT hr = E_FAIL;
	_RecordsetPtr * ppRecord = (_RecordsetPtr *)rs;
	_variant_t value; try{ value = (*ppRecord)->GetCollect(idx); }catch (_com_error &){}
	return double(value);
}
