#include "jni.h"
#include "string.h"
#include "JniUtil.h"
/* Source for class cn_dcs_leef_jni_NativeTool */



#ifndef _Included_cn_dcs_leef_jni_NativeTool
#define _Included_cn_dcs_leef_jni_NativeTool
#ifdef __cplusplus
extern "C" {
#endif

void printMyCharArray(unsigned char *k,int len){
	for(int i=0;i<len;i++){
		printf("%02X",k[i]);
	}
	printf("\n");
}

void printMyCharArray(const char *k,int len){
	for(int i=0;i<len;i++){
		printf("%02X",k[i]);
	}
	printf("\n");
}

/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    basicTest
 * Signature: (ZBCSIJFD)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_cn_dcs_leef_jni_NativeTool_basicTest
	(JNIEnv *env, jclass cls, jboolean jbo, jbyte jby, jchar jch, jshort jsh, jint ji, jlong jl, jfloat jf, jdouble jd){
	bool cBool = jbo;
	unsigned char cUChar = jby; 
	char cChar = jby;
	unsigned short cUShort = jch;
	short cShort = jsh;
	long cLong = ji;
	long long cLLong = jl;
	float cFloat = jf;
	double cDouble = jd;
	
	int Len=0;
	char result[1024];
	sprintf(result,"boolean->bool:%d,byte->uchar:%02x,byte->char:%02x,char->ushort:%04x,short->short:%04x,int->long:%08x,long->llong:%016x,float->float:%f,double->double:%e",
		 cBool, cUChar, cChar, cUShort, cShort, cLong, cLLong, cFloat, cDouble);
	jstring str = pCharToJstring(env,result);
	return str;
}

/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    arrayTest
 * Signature: ([B)[I
 */
JNIEXPORT jintArray JNICALL Java_cn_dcs_leef_jni_NativeTool_arrayTest
	(JNIEnv *env, jclass cls, jbyteArray jbyArray){
		char *cByte2 = (char *)env->GetByteArrayElements(jbyArray, NULL);
		int Len = env->GetArrayLength(jbyArray);
		unsigned char *cByte = (unsigned char *)env->GetByteArrayElements(jbyArray, NULL);
		printMyCharArray(cByte, Len);
		printMyCharArray(cByte2, Len);
		
		env->ReleaseByteArrayElements(jbyArray, (jbyte *)cByte, NULL);
		env->ReleaseByteArrayElements(jbyArray, (jbyte *)cByte2, NULL);

		char *msg = "from Native arrayTest";
		jbyteArray bytes = env->NewByteArray(strlen(msg));
		env->SetByteArrayRegion(bytes, 0, strlen(msg), (jbyte *)msg);

		long ret[2]={0x1,0x2};
		jintArray ints = env->NewIntArray(2);
		env->SetIntArrayRegion(ints, 0, 2, (jint *)ret);
		return ints;
}

/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    stringTest
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_cn_dcs_leef_jni_NativeTool_stringTest
	(JNIEnv *env, jclass cls, jstring jstr){
		const char *chars = env->GetStringUTFChars(jstr, 0);
		int charsLen = env->GetStringUTFLength(jstr);
		printf("%s\n",chars);
		printMyCharArray(chars, charsLen);
		env->ReleaseStringUTFChars(jstr, chars); 

		char *result = "from native stringTest";
		return pCharToJstring(env, result);
}


/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    classTest
 * Signature: (Lcn/dcs/leef/bean/User;)Lcn/dcs/leef/bean/User;
 */
JNIEXPORT jobject JNICALL Java_cn_dcs_leef_jni_NativeTool_classTest
	(JNIEnv *env, jclass cls, jobject obj){

	//class
	jclass m_cls_Book = env->FindClass("cn/dcs/leef/bean/Book");
	jclass m_cls_User = env->FindClass("cn/dcs/leef/bean/User");
	jclass m_cls_List = env->FindClass("java/util/ArrayList"); 


	//in
	jstring userName = NULL; getStringValue(userName, env, cls, obj, "name");
	long userId = 0; getIntValue(userId, env, cls, obj, "id");
	

	//out
	jclass m_cls = env->FindClass("cn/dcs/leef/bean/");
	jmethodID m_mid = env->GetMethodID(m_cls, "<init>", "()V");
	jobject m_obj = env->NewObject(m_cls, m_mid);

}


/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    methodTest
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_cn_dcs_leef_jni_NativeTool_methodTest
	(JNIEnv *, jclass, jint){
	
}

#ifdef __cplusplus
}
#endif
#endif
