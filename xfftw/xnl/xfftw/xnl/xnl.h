#pragma once


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

#if  defined(_WIN32)||defined(_DRIVER)
typedef 	__int32				xint;
typedef 	signed __int64		xlong;
typedef		unsigned char		xbyte;
typedef 	unsigned short 		xchar;
#elif defined(__linux__) || defined(__APPLE__) || defined(__unix__)
typedef 	int32_t				xint;
typedef 	signed	long long   xlong;
typedef		unsigned char		xbyte;
typedef 	unsigned short		xchar;
#endif

class XNLEnv {
public:
	enum XDataType {
		t_nilptr = 0,//�ǿ�ָ��
		t_byte = 1,
		t_char = 2,
		t_short = 3,
		t_int = 4,
		t_long = 5,
		t_double = 6,
		t_bool = 7,
		t_string = 8,
		t_type = 9,
		t_object = 10,
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

	//���ö����ֵ
	virtual void setValue(XObject * object, xbyte byteValue) = 0;
	virtual void setValue(XObject * object, xchar charValue) = 0;
	virtual void setValue(XObject * object, short shortValue) = 0;
	virtual void setValue(XObject * object, xint intValue) = 0;
	virtual void setValue(XObject * object, xlong longValue) = 0;
	virtual void setValue(XObject * object, double doubleValue) = 0;
	virtual void setValue(XObject * object, bool boolValue) = 0;
	virtual void setValue(XContext * context, XObject * object, const char * stringValue, int length) = 0;
	virtual void setValue(XObject * object, XObject * value) = 0;

	//��ȡ�����ֵ
	virtual bool getByteValue(XObject * object, xbyte * byteValue) = 0;
	virtual bool getCharValue(XObject * object, xchar * charValue) = 0;
	virtual bool getShortValue(XObject * object, short * shortValue) = 0;
	virtual bool getIntValue(XObject * object, xint * intValue) = 0;
	virtual bool getLongValue(XObject * object, xlong * longValue) = 0;
	virtual bool getDoubleValue(XObject * object, double * doubleValue) = 0;
	virtual bool getBoolValue(XObject * object, bool * boolValue) = 0;
	virtual bool getStringValue(XObject * object, const char * * stringValue, int * length) = 0;

	virtual bool isArray(XObject * object) = 0;
	virtual xlong getLengthOfArray(XObject * object) = 0;
	//����һ������
	virtual XObject * createObject() = 0;

	//����һ������
	virtual XObject * createByteArray(int length) = 0;
	virtual XObject * createCharArray(int length) = 0;
	virtual XObject * createShortArray(int length) = 0;
	virtual XObject * createIntArray(int length) = 0;
	virtual XObject * createLongArray(int length) = 0;
	virtual XObject * createDoubleArray(int length) = 0;
	virtual XObject * createBoolArray(int length) = 0;
	virtual XObject * createStringArray(int length) = 0;
	virtual XObject * createObjectArray(int length) = 0;

	virtual bool setElementValue(XObject * object, size_t index, xbyte *byteValue, size_t length) = 0;
	virtual bool setElementValue(XObject * object, size_t index, xchar *charValue, size_t length) = 0;
	virtual bool setElementValue(XObject * object, size_t index, short *shortValue, size_t length) = 0;
	virtual bool setElementValue(XObject * object, size_t index, xint *intValue, size_t length) = 0;
	virtual bool setElementValue(XObject * object, size_t index, xlong *longValue, size_t length) = 0;
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
	virtual bool getElementValue(XObject * object, size_t index, bool * boolValue, size_t length) = 0;
	virtual bool getElementValue(XObject * object, size_t index, xstring * stringValue, size_t * strlength, size_t length) = 0;
	virtual bool getElementValue(XContext * context, XObject * object, size_t index, XObject ** value, size_t length) = 0;


	virtual void throwNativeException(XContext * context, const char * message) = 0;

	//�ж϶����ǲ���һ����(����ʵ��)
	virtual bool isClass(XObject * object) = 0;

	//�ж�һ�������ǲ���ָ�����ʵ��
	virtual bool isInstanceOf(XObject * object, XObject * _class, bool allowExtends) = 0;

	//�ж�һ�������ǲ���ָ�����������
	virtual bool isExtendsOf(XObject * _class, XObject * _baseclass) = 0;

	//��ȡ���������  ��Ҫ������
	virtual XDataType getObjectType(XObject * object) = 0;

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
			return;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			return;
		}
		XObject * ret = invoke(context, pthis, m, push_Args(context, _Var, arg...));
		if (ret){
			dereferenceObject(ret);
		}
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
			return;
		}
		XMethod * m = getVirtualMethod(pthis, virtualMethodId);
		if (m == 0) {
			return;
		}
		XObject * ret = invoke(context, pthis, m, 0);
		if (ret){
			dereferenceObject(ret);
		}
	}
private:
    int push_Args(XContext * ) {
		return 0;
	}

};
