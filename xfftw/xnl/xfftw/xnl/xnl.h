#pragma once

#include <assert.h>
#include <typeinfo>
#include <cstring>
#ifdef _WIN32
#define XI_STDCALL __stdcall
#define XI_CDECL __cdecl
#define XI_FASTCALL __fastcall
#define XI_PASCAL __pascal
#define XNLEXPORT extern "C"
#else
#define XI_STDCALL __attribute__((__stdcall__))
#define XI_CDECL __attribute__((__cdecl__))
#define XI_FASTCALL __attribute__((regparm(3)))
#define XI_PASCAL
#define XNLEXPORT extern "C" __attribute__ ((visibility("default")))
#endif

typedef int xbool;
typedef const char * xstring;
typedef void* xptr;

class XObject;
class XMethod;
class XContext;
class XObjectId;

#if  defined(_WIN32)||defined(_DRIVER)
typedef 	__int32				xint;
typedef 	signed __int64		xlong;
typedef		unsigned char		xbyte;
typedef 	unsigned short 		xchar;
typedef 	float 				xfloat;
typedef 	double 				xdouble;
#elif defined(__linux__) || defined(__APPLE__) || defined(__unix__)
typedef 	int32_t				xint;
typedef 	signed	long long   xlong;
typedef		unsigned char		xbyte;
typedef 	unsigned short		xchar;
typedef 	float 				xfloat;
typedef 	double 				xdouble;
#endif


class XNLEnv {
public:
	enum XDataType {
		t_nilptr = 0,//���˵���ǿ�ָ��
		t_byte = 1,
		t_char = 2,
		t_short = 3,
		t_int = 4,
		t_long = 5,
		t_float = 6,
		t_double = 7,
		t_bool = 8,
		t_podmax = 9,
		t_string = 9,
		t_type = 10,
		t_object = 11
	};

	/**	ע��XNLMain�еĲ���XNLEnv�������ñ���
	��Ҫʹ�ô˺�����ȡһ��envʵ�������ñ���
	*/
	virtual XNLEnv * getEnv() = 0;

	/**	��������getEnv ��ȡ��ʵ��*/
	virtual void releaseEnv(XNLEnv * env) = 0;

	//������ȡ���Ա����
	virtual int getClassId(const char * path) = 0;

	//ע�� ��ֵ��Ҫ�ͷ�
	virtual XObject * getClass(int id) = 0;

	//������ȡ���Ա����
	virtual int getMethodId(const char * path) = 0;

	//ע��÷���ȡ�õĺ����Ǳ���������д�ĺ���
	virtual XMethod * getVirtualMethod(XObject * object, int id) = 0;

	//ע��÷���ȡ�õĺ�����path����ķ���
	virtual XMethod * getDynamicMethod(XObject * object, int classId, int id) = 0;

	//ע��÷���ȡ�õĺ����Ǿ�̬����
	virtual XMethod * getStaticMethod(XObject * object, int id) = 0;

	//������ȡȫ�ֵı������߷���
	virtual int getObjectId(XObject * object, const char * path) = 0;
	virtual XObject * getObject(XObject * object, int id) = 0;

	//������ȡ���Ա����
	virtual int getFieldId(const char * path) = 0;

	//�����ͷ�, ��ʵ������ǰ��Ч
	virtual XObject * getDynamicField(XObject * object, int id) = 0;
	virtual XObject * getStaticField(XObject * object, int id) = 0;

	//ѹ����� ��invoke֮ǰ
	virtual void pushParam(XContext * context, XObject *) = 0;

	/*** ��ȡ���������ԭʼָ��, 
	ע��: ָ������������xlang�������, ���ɳ��ڱ���, �ϲ�����ͷ�ʱ, ָ��ָ�����ݽ���Ч**/
	virtual void* getArrayOriginalPtr(XObject* object) = 0;
	//����һ��context  ����invoke 
	//ע�� �˶����Ӧ�߳�, ��ͬ�߳�֮�䲻���Թ���һ��context
	//���Գ��ڱ���  ��ֻ����һ���߳�ʹ��
	virtual XContext * getContext(bool * bRelease) = 0;

	//�����ͷ�createContext�����Ķ���
	virtual void  releaseContext(XContext * context) = 0;

	//����һ������ĸ���, 
	//xlang����native�еĲ�������  ��Ҫ���ڱ���,��ʹ�������������һ������
	// ����֮����Ҫʹ��dereferenceObject ������ �������й¶
	virtual XObject * referenceObject( XObject * obj) = 0;
	virtual void dereferenceObject(XObject * obj) = 0;

	// ��ȡxlang�еĶ���ID,��ID��ռ����Դ,�����ͷ�, ����Ҫ�Լ�������Ч, ���ϲ�finalizeʱ Ҫʹ�ö���ʧЧ
	virtual XObjectId*  getObjectId(XObject * _class) = 0;

	//����ID ��ȡxlang�ϲ�Ķ���, ע�� ����ֵ�Ķ���ָ�벻�õ�ʱ����Ҫʹ��dereferenceObject�����ͷ� �����ռ����Դ
	//�÷������˲�id����Ч�ԣ� �����ID����������
	virtual XObject * refObjectById(XObjectId * id) = 0;

	//���ö����ֵ
	virtual void setValue(XObject * object, xbyte byteValue) = 0;
	virtual void setValue(XObject * object, xchar charValue) = 0;
	virtual void setValue(XObject * object, short shortValue) = 0;
	virtual void setValue(XObject * object, xint intValue) = 0;
	virtual void setValue(XObject * object, xlong longValue) = 0;
	virtual void setValue(XObject* object, float floatValue) = 0;
	virtual void setValue(XObject * object, double doubleValue) = 0;
	virtual void setValue(XObject * object, bool boolValue) = 0;
	virtual bool setValue(XContext * context, XObject * object, const char * stringValue, int length) = 0;
	virtual void setValue(XObject * object, XObject * value) = 0;

	//��ȡ�����ֵ
	virtual bool getByteValue(XObject * object, xbyte * byteValue) = 0;
	virtual bool getCharValue(XObject * object, xchar * charValue) = 0;
	virtual bool getShortValue(XObject * object, short * shortValue) = 0;
	virtual bool getIntValue(XObject * object, xint * intValue) = 0;
	virtual bool getLongValue(XObject * object, xlong * longValue) = 0;
	virtual bool getFloatValue(XObject* object, float* floatValue) = 0;
	virtual bool getDoubleValue(XObject * object, double * doubleValue) = 0;
	virtual bool getBoolValue(XObject * object, bool * boolValue) = 0;
	virtual bool getStringValue(XObject * object, const char * * stringValue, int * length) = 0;

	virtual bool isArray(XObject * object) = 0;
	virtual xlong getLengthOfArray(XObject * object) = 0;
	virtual xptr getPointerOfArray(XObject * object) = 0;
	//����һ������
	virtual XObject * createObject() = 0;

	//����һ������
	virtual XObject * createByteArray(int length) = 0;
	virtual XObject * createCharArray(int length) = 0;
	virtual XObject * createShortArray(int length) = 0;
	virtual XObject * createIntArray(int length) = 0;
	virtual XObject * createLongArray(int length) = 0;
	virtual XObject * createFloatArray(int length) = 0;
	virtual XObject * createDoubleArray(int length) = 0;
	virtual XObject * createBoolArray(int length) = 0;
	virtual XObject * createStringArray(int length) = 0;
	virtual XObject * createObjectArray(int length) = 0;

	virtual bool setElementValue(XObject * object, size_t index, xbyte *byteValue, size_t length) = 0;
	virtual bool setElementValue(XObject * object, size_t index, xchar *charValue, size_t length) = 0;
	virtual bool setElementValue(XObject * object, size_t index, short *shortValue, size_t length) = 0;
	virtual bool setElementValue(XObject * object, size_t index, xint *intValue, size_t length) = 0;
	virtual bool setElementValue(XObject * object, size_t index, xlong *longValue, size_t length) = 0;
	virtual bool setElementValue(XObject * object, size_t index, float* floatValue, size_t length) = 0;
	virtual bool setElementValue(XObject * object, size_t index, double *doubleValue, size_t length) = 0;
	virtual bool setElementValue(XObject * object, size_t index, bool *boolValue, size_t length) = 0;
	virtual bool setElementValue(XContext * context, XObject * object, size_t index, xstring* stringValue, int * strslength, size_t length) = 0;
	virtual bool setElementValue(XContext * context, XObject * object, size_t index, XObject ** value, size_t length) = 0;

	virtual bool getElementValue(XObject * object, size_t index, xbyte * byteValue, size_t length) = 0;
	virtual bool getElementValue(XObject * object, size_t index, xchar * charValue, size_t length) = 0;
	virtual bool getElementValue(XObject * object, size_t index, short * shortValue, size_t length) = 0;
	virtual bool getElementValue(XObject * object, size_t index, xint * intValue, size_t length) = 0;
	virtual bool getElementValue(XObject * object, size_t index, xlong * longValue, size_t length) = 0;
	virtual bool getElementValue(XObject * object, size_t index, double * doubleValue, size_t length) = 0;
	virtual bool getElementValue(XObject* object, size_t index, float* floatValue, size_t length) = 0;
	virtual bool getElementValue(XObject * object, size_t index, bool * boolValue, size_t length) = 0;
	virtual bool getElementValue(XObject * object, size_t index, xstring * stringValue, size_t * strlength, size_t length) = 0;
	virtual bool getElementValue(XContext * context, XObject * object, size_t index, XObject ** value, size_t length) = 0;


	virtual void throwNativeException(XContext * context, const char * message) = 0;

	//��������ڴ�ӡ
	virtual void debugOutput(const char* message) = 0;

	//��������ڴ�ӡ
	virtual void log(XContext* context, const char* tag, int level, const char * message, bool bSystem) = 0;

	//�ж϶����ǲ���һ����(����ʵ��)
	virtual bool isClass(XObject * object) = 0;

	//�ж�һ�������ǲ���ָ�����ʵ��
	virtual bool isInstanceOf(XObject * object, XObject * _class, bool allowExtends) = 0;

	//�ж�һ�������ǲ���ָ�����������
	virtual bool isExtendsOf(XObject * _class, XObject * _baseclass) = 0;

	//��ȡ���������  
	virtual XDataType getObjectType(XObject * object) = 0;

	//��ȡ������������  
	virtual XDataType getComponentType(XObject* object) = 0;

	//��ȡһ������������
	virtual XObject * getObjectClass(XObject * object) = 0;

	//��ȡһ����Ļ�����
	virtual XObject * getBaseClass(XObject * _classobject) = 0;

	template<typename _FIRST, typename... _LIST>
	XObject * createInstance(XContext * context/*�߳�*/, XObject * _class/*��*/, XMethod * method/*���췽��*/, _FIRST _Var/*�������*/, _LIST... arg) {
		return createInstance(context, _class, method, push_Args(context, _Var, arg...));
	}

	template<typename _FIRST, typename... _LIST>
	XObject * invoke(XContext * context, XObject * pthis, int virtualMethodId, _FIRST _Var, _LIST... arg) {
		if (virtualMethodId == -1) {
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			return 0;
		}
		return invoke(context, pthis, m, push_Args(context, _Var, arg...));
	}

	template<typename _FIRST, typename... _LIST>
	XObject * invoke(XContext * context, XObject * pthis, XMethod * method, _FIRST _Var, _LIST... arg) {
		return invoke(context, pthis, method, push_Args(context, _Var, arg...));
	}

	template<typename _FIRST, typename... _LIST>
	int push_Args(XContext * context, _FIRST _Var, _LIST... arg) {
		pushParam(context, _Var);
		return  push_Args(context, arg...) + 1;
	}

	XObject * invoke(XContext * context, XObject * pthis, int virtualMethodId) {
		if (virtualMethodId == -1) {
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			return 0;
		}
		return invoke(context, pthis, m, 0);
	}
	//���ú���
	virtual XObject * invoke(XContext * context, XObject * pthis, XMethod * method, int argc) = 0;
	virtual XObject * createInstance(XContext * context, XObject * _class, XMethod * method, int argc) = 0;


	template<typename _FIRST, typename... _LIST>
	void void_invoke(XContext * context, XObject * pthis, int virtualMethodId, _FIRST _Var, _LIST... arg) {
		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return ;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return ;
		}
		XObject * ret = invoke(context, pthis, m, push_Args(context, _Var, arg...));
		if (ret){
			dereferenceObject(ret);
		}
	}

	template<typename _FIRST, typename... _LIST>
	bool bool_invoke(XContext * context, XObject * pthis, int virtualMethodId, _FIRST _Var, _LIST... arg) {
		bool bret = false;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject * ret = invoke(context, pthis, m, push_Args(context, _Var, arg...));
		if (ret) {
			getBoolValue(ret, &bret);
			dereferenceObject(ret);
		}
		return bret;
	}

	bool bool_invoke(XContext * context, XObject * pthis, int virtualMethodId) {
		bool bret = false;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject * ret = invoke(context, pthis, m, 0);
		if (ret) {
			getBoolValue(ret, &bret);
			dereferenceObject(ret);
		}
		return bret;
	}

	template<typename _FIRST, typename... _LIST>
	xint int_invoke(XContext * context, XObject * pthis, int virtualMethodId, _FIRST _Var, _LIST... arg) {
		xint nret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject * ret = invoke(context, pthis, m, push_Args(context, _Var, arg...));
		if (ret) {
			getIntValue(ret, &nret);
			dereferenceObject(ret);
		}
		return nret;
	}

	xint int_invoke(XContext * context, XObject * pthis, int virtualMethodId) {
		xint nret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject * ret = invoke(context, pthis, m, 0);
		if (ret) {
			getIntValue(ret, &nret);
			dereferenceObject(ret);
		}
		return nret;
	}

	template<typename _FIRST, typename... _LIST>
	xchar char_invoke(XContext * context, XObject * pthis, int virtualMethodId, _FIRST _Var, _LIST... arg) {
		xchar cret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject * ret = invoke(context, pthis, m, push_Args(context, _Var, arg...));
		if (ret) {
			getCharValue(ret, &cret);
			dereferenceObject(ret);
		}
		return cret;
	}

	xchar char_invoke(XContext * context, XObject * pthis, int virtualMethodId) {
		xchar cret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject * ret = invoke(context, pthis, m, 0);
		if (ret) {
			getCharValue(ret, &cret);
			dereferenceObject(ret);
		}
		return cret;
	}
	template<typename _FIRST, typename... _LIST>
	xbyte byte_invoke(XContext * context, XObject * pthis, int virtualMethodId, _FIRST _Var, _LIST... arg) {
		xbyte cbret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject * ret = invoke(context, pthis, m, push_Args(context, _Var, arg...));
		if (ret) {
			getByteValue(ret, &cbret);
			dereferenceObject(ret);
		}
		return cbret;
	}

	xbyte byte_invoke(XContext * context, XObject * pthis, int virtualMethodId) {
		xbyte cbret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject * ret = invoke(context, pthis, m, 0);
		if (ret) {
			getByteValue(ret, &cbret);
			dereferenceObject(ret);
		}
		return cbret;
	}

	template<typename _FIRST, typename... _LIST>
	xlong long_invoke(XContext * context, XObject * pthis, int virtualMethodId, _FIRST _Var, _LIST... arg) {
		xlong lret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject * ret = invoke(context, pthis, m, push_Args(context, _Var, arg...));
		if (ret) {
			getLongValue(ret, &lret);
			dereferenceObject(ret);
		}
		return lret;
	}

	xlong long_invoke(XContext * context, XObject * pthis, int virtualMethodId) {
		xlong lret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject * ret = invoke(context, pthis, m, 0);
		if (ret) {
			getLongValue(ret, &lret);
			dereferenceObject(ret);
		}
		return lret;
	}


	template<typename _FIRST, typename... _LIST>
	double double_invoke(XContext* context, XObject* pthis, int virtualMethodId, _FIRST _Var, _LIST... arg) {
		double lret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod* m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject* ret = invoke(context, pthis, m, push_Args(context, _Var, arg...));
		if (ret) {
			getDoubleValue(ret, &lret);
			dereferenceObject(ret);
		}
		return lret;
	}

	double double_invoke(XContext* context, XObject* pthis, int virtualMethodId) {
		double lret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod* m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject* ret = invoke(context, pthis, m, 0);
		if (ret) {
			getDoubleValue(ret, &lret);
			dereferenceObject(ret);
		}
		return lret;
	}

	template<typename _FIRST, typename... _LIST>
	float float_invoke(XContext* context, XObject* pthis, int virtualMethodId, _FIRST _Var, _LIST... arg) {
		float lret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod* m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject* ret = invoke(context, pthis, m, push_Args(context, _Var, arg...));
		if (ret) {
			getFloatValue(ret, &lret);
			dereferenceObject(ret);
		}
		return lret;
	}

	float float_invoke(XContext* context, XObject* pthis, int virtualMethodId) {
		float lret = 0;

		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod* m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		XObject* ret = invoke(context, pthis, m, 0);
		if (ret) {
			getFloatValue(ret, &lret);
			dereferenceObject(ret);
		}
		return lret;
	}

	template<typename _FIRST, typename... _LIST>
	void void_invoke(XContext * context, XObject * pthis, XMethod * method, _FIRST _Var, _LIST... arg) {
		XObject * ret = invoke(context, pthis, method, push_Args(context, _Var, arg...));
		if (ret){
			dereferenceObject(ret);
		}
	}

	void void_invoke(XContext * context, XObject * pthis, int virtualMethodId) {
		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return ;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return ;
		}
		XObject * ret = invoke(context, pthis, m, 0);
		if (ret){
			dereferenceObject(ret);
		}
	}

	template<class _Type>
	XObject * CreateXObject(_Type v) {
		XObject * obj = createObject();
		setValue(obj, v);
		return obj;
	}

	template<typename _FIRST, typename _METHOD, typename... _LIST>
	XObject *Invoke(XContext * context, XObject * pthis, _METHOD method, _FIRST _Var, _LIST... arg) {
		return Invoke_helper(context, pthis, method, 0, _Var, arg...);
	}

	template<typename _FIRST = bool, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, bool _Var, _LIST... arg) {
		XObject * param = CreateXObject((bool)_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = unsigned char, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, unsigned char _Var, _LIST... arg) {
		XObject * param = CreateXObject((xbyte)_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = char, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, char _Var, _LIST... arg) {
		XObject * param = CreateXObject((xchar)_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = wchar_t, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, wchar_t _Var, _LIST... arg) {
		XObject * param = CreateXObject((xchar)_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = unsigned short, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, unsigned short _Var, _LIST... arg) {
		XObject * param = CreateXObject((xchar)_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}


	template<typename _FIRST = signed short, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, signed short _Var, _LIST... arg) {
		XObject * param = CreateXObject((short)_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = signed int, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, signed int _Var, _LIST... arg) {
		XObject * param = CreateXObject((xint)_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = unsigned int, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, unsigned int _Var, _LIST... arg) {
		XObject * param = CreateXObject((xint)_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = signed long long, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, signed long long _Var, _LIST... arg) {
		XObject * param = CreateXObject((xlong)_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = unsigned long long, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, unsigned long long _Var, _LIST... arg) {
		XObject * param = CreateXObject((xlong)_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}


	template<typename _FIRST = float, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, float _Var, _LIST... arg) {
		XObject * param = CreateXObject(_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = double, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, double _Var, _LIST... arg) {
		XObject * param = CreateXObject(_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = long double, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, long double _Var, _LIST... arg) {
		XObject * param = CreateXObject((double)_Var);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}


	template<typename _FIRST = char *, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, char * _Var, _LIST... arg) {
		XObject * param = createObject();
		const char * pstr = (const char *)(_Var);
		setValue(context, param, pstr, strlen(pstr));
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = const char *, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, const char * _Var, _LIST... arg) {
		XObject * param = createObject();
		const char * pstr = (const char *)(_Var);
		setValue(context, param, pstr, strlen(pstr));
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = unsigned char *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, unsigned char * _Var, size_t length, _LIST... arg) {
		XObject * param = createByteArray((unsigned int)length);
		setElementValue(param, 0, (xbyte*)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = const unsigned char *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, const unsigned char * _Var, size_t length, _LIST... arg) {
		XObject * param = createByteArray((unsigned int)length);
		setElementValue(param, 0, (xbyte*)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = wchar_t *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, wchar_t * _Var, size_t length, _LIST... arg) {
		XObject * param = createCharArray((unsigned int)length);
		setElementValue(param, 0, (xchar*)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = const wchar_t *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, const wchar_t * _Var, size_t length, _LIST... arg) {
		XObject * param = createCharArray((unsigned int)length);
		setElementValue(param, 0, (xchar*)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = short *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, short * _Var, size_t length, _LIST... arg) {
		XObject * param = createShortArray((unsigned int)length);
		setElementValue(param, 0, (short *)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = const short *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, const short * _Var, size_t length, _LIST... arg) {
		XObject * param = createShortArray((unsigned int)length);
		setElementValue(param, 0, (short *)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = int *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, int * _Var, size_t length, _LIST... arg) {
		XObject * param = createIntArray((unsigned int)length);
		setElementValue(param, 0, (xint*)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = const int *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, const int * _Var, size_t length, _LIST... arg) {
		XObject * param = createIntArray((unsigned int)length);
		setElementValue(param, 0, (xint*)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = long long *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, long long * _Var, size_t length, _LIST... arg) {
		XObject * param = createLongArray((unsigned int)length);
		setElementValue(param, 0, (xlong*)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = const long long *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, const long long * _Var, size_t length, _LIST... arg) {
		XObject * param = createLongArray((unsigned int)length);
		setElementValue(param, 0, (xlong*)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = double *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, double * _Var, size_t length, _LIST... arg) {
		XObject * param = createDoubleArray((unsigned int)length);
		setElementValue(param, 0, (double *)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = const double *,  typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, const double * _Var, size_t length, _LIST... arg) {
		XObject * param = createDoubleArray((unsigned int)length);
		setElementValue(param, 0, (double *)_Var, length);
		pushParam(context, param);
		XObject *pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = float*, typename _METHOD, typename... _LIST>
	XObject* Invoke_helper(XContext* context, XObject* pthis, _METHOD method, int helper_cnt, float* _Var, size_t length, _LIST... arg) {
		XObject* param = createFloatArray((unsigned int)length);
		setElementValue(param, 0, (float*)_Var, length);
		pushParam(context, param);
		XObject* pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = const float*, typename _METHOD, typename... _LIST>
	XObject* Invoke_helper(XContext* context, XObject* pthis, _METHOD method, int helper_cnt, const float* _Var, size_t length, _LIST... arg) {
		XObject* param = createFloatArray((unsigned int)length);
		setElementValue(param, 0, (float*)_Var, length);
		pushParam(context, param);
		XObject* pret = Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
		dereferenceObject(param);
		return pret;
	}

	template<typename _FIRST = XObject *, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, XObject * _Var, _LIST... arg) {
		pushParam(context, _Var);
		return Invoke_helper(context, pthis, method, helper_cnt + 1, arg...);
	}

	template<typename _FIRST, typename _METHOD, typename... _LIST>
	XObject *Invoke_helper(XContext * context, XObject * pthis, _METHOD method, int helper_cnt, _FIRST _Var, _LIST... arg) {
		assert(0 && "Unsupported type");
		return 0;
	}
	
	XObject *Invoke_helper(XContext * context, XObject * pthis, XMethod * method, int helper_cnt) {
		return invoke(context, pthis, method, helper_cnt);
	}

	XObject *Invoke_helper(XContext * context, XObject * pthis, int virtualMethodId, int helper_cnt) {
		if (virtualMethodId == -1) {
			assert(0 && "invalid MethodId");
			return 0;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			assert(0 && "invalid VirtualMethod");
			return 0;
		}
		return invoke(context, pthis, m, helper_cnt);
	}

	template<typename _FIRST, typename _METHOD, typename... _LIST>
	void void_Invoke(XContext * context, XObject * pthis, _METHOD virtualMethodId, _FIRST _Var, _LIST... arg) {
		XObject * ret = Invoke(context, pthis, virtualMethodId, _Var, arg...);
		if (ret) {
			dereferenceObject(ret);
		}
	}

	template<typename _FIRST, typename _METHOD, typename... _LIST>
	bool bool_Invoke(XContext * context, XObject * pthis, _METHOD virtualMethodId, _FIRST _Var, _LIST... arg) {
		bool bret = false;
		XObject * ret = Invoke(context, pthis, virtualMethodId, _Var, arg...);
		if (ret) {
			getBoolValue(ret, &bret);
			dereferenceObject(ret);
		}
		return bret;
	}

	template<typename _FIRST, typename _METHOD, typename... _LIST>
	xint int_Invoke(XContext * context, XObject * pthis, _METHOD virtualMethodId, _FIRST _Var, _LIST... arg) {
		xint nret = 0;

		XObject * ret = Invoke(context, pthis, virtualMethodId, _Var, arg...);
		if (ret) {
			getIntValue(ret, &nret);
			dereferenceObject(ret);
		}
		return nret;
	}

	template<typename _FIRST, typename _METHOD, typename... _LIST>
	xchar char_Invoke(XContext * context, XObject * pthis, _METHOD virtualMethodId, _FIRST _Var, _LIST... arg) {
		xchar cret = 0;

		XObject * ret = Invoke(context, pthis, virtualMethodId, _Var, arg...);
		if (ret) {
			getCharValue(ret, &cret);
			dereferenceObject(ret);
		}
		return cret;
	}

	template<typename _FIRST, typename _METHOD, typename... _LIST>
	xbyte byte_Invoke(XContext * context, XObject * pthis, _METHOD virtualMethodId, _FIRST _Var, _LIST... arg) {
		xbyte cbret = 0;

		XObject * ret = Invoke(context, pthis, virtualMethodId, _Var, arg...);
		if (ret) {
			getByteValue(ret, &cbret);
			dereferenceObject(ret);
		}
		return cbret;
	}

	template<typename _FIRST, typename _METHOD, typename... _LIST>
	xlong long_Invoke(XContext * context, XObject * pthis, _METHOD virtualMethodId, _FIRST _Var, _LIST... arg) {
		xlong lret = 0;
		XObject * ret = Invoke(context, pthis, virtualMethodId,  _Var, arg...);
		if (ret) {
			getLongValue(ret, &lret);
			dereferenceObject(ret);
		}
		return lret;
	}

	template<typename _FIRST, typename _METHOD, typename... _LIST>
	double double_Invoke(XContext* context, XObject* pthis, _METHOD virtualMethodId, _FIRST _Var, _LIST... arg) {
		double cbret = 0;

		XObject* ret = Invoke(context, pthis, virtualMethodId, _Var, arg...);
		if (ret) {
			getDoubleValue(ret, &cbret);
			dereferenceObject(ret);
		}
		return cbret;
	}

	template<typename _FIRST, typename _METHOD, typename... _LIST>
	float float_Invoke(XContext* context, XObject* pthis, _METHOD virtualMethodId, _FIRST _Var, _LIST... arg) {
		float lret = 0;
		XObject* ret = Invoke(context, pthis, virtualMethodId, _Var, arg...);
		if (ret) {
			getFloatValue(ret, &lret);
			dereferenceObject(ret);
		}
		return lret;
	}
private:
    int push_Args(XContext * ) {
		return 0;
	}

};

/*
entry:
	XNLEXPORT xint XI_STDCALL XNLMain(XNLEnv * env, xint version);
exit:
	XNLEXPORT xint XI_STDCALL XNLExit(XNLEnv * env);
*/
