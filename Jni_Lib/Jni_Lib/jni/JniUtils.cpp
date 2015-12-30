#include "jni.h"
#include <stdlib.h>
#include <cstring>
#include "jniUtil.h"


//String Next

jstring pCharToJstring(JNIEnv *env, const char *pat)
{
	jclass strClass = env->FindClass("Ljava/lang/String;");
	//获取java String类方法String(byte[],String)的构造器
	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = env->NewByteArray((jsize)strlen(pat));
	(env)->SetByteArrayRegion(bytes, 0, (jsize)strlen(pat), (jbyte*)pat);
	jstring encoding = env->NewStringUTF("utf-8");   //GB2312 
	return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

/**
 * NOTE: after using, free(ptr) 
 */
char * jstringToPchar(JNIEnv *env, jstring jstr)  
{  
	char *rtn = NULL;  
	jclass clsstring = env->FindClass("java/lang/String");   
	jstring strencode = env->NewStringUTF("utf-8");   //GB2312 
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");   
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);  
	jsize alen = env->GetArrayLength(barr);  
	jbyte *ba = env->GetByteArrayElements(barr,NULL);  
	if(alen > 0)  
	{  
		rtn = (char *)malloc(alen+1);         //new char[alen+1];    delete after using
		memcpy(rtn, ba, alen);  
		rtn[alen]=0;  
	}  
	env->ReleaseByteArrayElements(barr, ba, 0);  
	return rtn;
}

void jstringToPchar(char *pOut, int &iLenOfOut, JNIEnv *env, jstring jstr){
	pOut =(char *)env->GetStringUTFChars(jstr,0);
	iLenOfOut = env->GetStringUTFLength(jstr);
}

void pCharToJstring(jstring &jstr, char *pIn, int iLenOfIn, JNIEnv *env){
	jstr = env->NewStringUTF(pIn);
}





//Object Basic Next

void getDoubleValue(double &val, JNIEnv *env, jclass cls, jobject obj, const char *fieldName){
	jfieldID id = env->GetFieldID(cls, fieldName, "D");
	val = env->GetLongField(obj, id);
}

void setDoubleValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName,
		double val) {
	jfieldID id = env->GetFieldID(cls, fieldName, "D");
	env->SetLongField(obj, id, val);
}

void getFloatValue(float &val, JNIEnv *env, jclass cls, jobject obj, const char *fieldName){
	jfieldID id = env->GetFieldID(cls, fieldName, "F");
	val = env->GetLongField(obj, id);
}

void setFloatValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName,
		float val) {
	jfieldID id = env->GetFieldID(cls, fieldName, "F");
	env->SetLongField(obj, id, val);
}

void getLongValue(long long &val, JNIEnv *env, jclass cls, jobject obj,
		const char *fieldName) {
	jfieldID id = env->GetFieldID(cls, fieldName, "J");
	val = env->GetLongField(obj, id);
}

void setLongValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName,
		long long val) {
	jfieldID id = env->GetFieldID(cls, fieldName, "J");
	env->SetLongField(obj, id, val);
}

void getIntValue(long &val, JNIEnv *env, jclass cls, jobject obj,
		const char* fieldName) {
	jfieldID id = env->GetFieldID(cls, fieldName, "I");
	val = env->GetIntField(obj, id);
}

void setIntValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName,
		long val) {
	jfieldID id = env->GetFieldID(cls, fieldName, "I");
	env->SetIntField(obj, id, val);
}

void getShortValue(short &val, JNIEnv *env, jclass cls, jobject obj,
		const char* fieldName)
{
	jfieldID id=env->GetFieldID(cls,fieldName,"S");
	val = env->GetShortField(obj,id);
}

void setShortValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName,
		short val) {
	jfieldID id = env->GetFieldID(cls, fieldName, "S");
	env->SetShortField(obj, id, val);
}


void getCharValue(unsigned short &val, JNIEnv *env, jclass cls, jobject obj,
		const char* fieldName)
{
	jfieldID id=env->GetFieldID(cls,fieldName,"C");
	val = env->GetShortField(obj,id);
}

void setCharValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName,
		unsigned short val) {
	jfieldID id = env->GetFieldID(cls, fieldName, "C");
	env->SetShortField(obj, id, val);
}


void getByteValue(char *val, JNIEnv *env, jclass cls, jobject obj,
		const char* fieldName) {
	jfieldID id = env->GetFieldID(cls, fieldName, "B");
	*val = env->GetByteField(obj, id);
}

void setByteValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, char val) {
	jfieldID id = env->GetFieldID(cls, fieldName, "B");
	env->SetByteField(obj, id, val);
}

void getBoolValue(bool *val, JNIEnv *env, jclass cls, jobject obj,const char *fieldName)
{
	jfieldID id = env->GetFieldID(cls, fieldName, "Z");
	*val = env->GetBooleanField(obj, id);
}

void setBoolValue(JNIEnv *env, jclass cls, jobject obj, const char *fieldName, bool val)
{
	jfieldID id = env->GetFieldID(cls, fieldName, "Z");
	env->SetBooleanField(obj, id, val);
}




//Object Next

void getByteArray(unsigned char arr[], unsigned int arrLen, JNIEnv *env, jclass cls, jobject obj, const char* fieldName)
{
	jfieldID id = env->GetFieldID(cls, fieldName, "[B");
	jbyteArray array = (jbyteArray) env->GetObjectField(obj, id);
	if (array)
	{
		unsigned char *ary = (unsigned char *)env->GetByteArrayElements(array, 0);
		int aryLen = env->GetArrayLength(array);
		unsigned int minLen = arrLen < aryLen ? arrLen : aryLen;
		for (int i = 0; i < minLen; i++) arr[i] = ary[i];
		env->ReleaseByteArrayElements(array, (jbyte*)ary, 0);
	}
	env->DeleteLocalRef(array);
}

void setByteArray(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, unsigned char *arr, int len)
{
	if (len > 0)
	{
		jfieldID id = env->GetFieldID(cls, fieldName, "[B");
		jbyteArray array = env->NewByteArray(len);
		env->SetByteArrayRegion(array, 0, len, (jbyte*)arr);
		env->SetObjectField(obj, id, array);
		env->DeleteLocalRef(array);
	}
}


void getIntArray(unsigned int*& arr, unsigned int *arrCnt, JNIEnv *env, jclass cls, jobject obj, const char* fieldName)
{
	jfieldID id = env->GetFieldID(cls, fieldName, "[I");
	jintArray array = (jintArray)env->GetObjectField(obj, id);
	if (array == NULL) {
		arr = NULL;
		*arrCnt = 0;
	}
	else {
		arr = (unsigned int*)env->GetIntArrayElements(array, 0);
		*arrCnt = (unsigned int)env->GetArrayLength(array);
		env->ReleaseIntArrayElements(array, (jint*)arr, 0);
	}
	env->DeleteLocalRef(array);
}

void setIntArray(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, unsigned int* val, int len) {
	if (len > 0) {
		jfieldID id = env->GetFieldID(cls, fieldName, "[I");
		jintArray array = env->NewIntArray(len);
		env->SetIntArrayRegion(array, 0, len, (jint*) val);
		env->SetObjectField(obj, id, array);
		env->DeleteLocalRef(array);
	} else {
		LOGI("NULL INT ARRAY: %s", fieldName);
	}
}

void setLongArray(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, unsigned long long* val, unsigned int len) {
	//LOGI("LONG ARRAY SIZE %d",len);
	if (len > 0) {
		jfieldID id = env->GetFieldID(cls, fieldName, "[J");
		jlongArray array = env->NewLongArray(len);
		env->SetLongArrayRegion(array, 0, len,(jlong*) val);
		env->SetObjectField(obj, id, array);
		env->DeleteLocalRef(array);
	} else {
		LOGI("NULL LONG ARRAY: %s", fieldName);
	}
}





//Object String

void getStringValue(char *pChar, JNIEnv *env, jclass cls, jobject obj, const char *fieldName){
	jfieldID id = env->GetFieldID(cls, fieldName, "Ljava/lang/String;");
	jstring jstr = (jstring)env->GetObjectField(obj,id);
	pChar = (char*)env->GetStringUTFChars(jstr, 0);
} 

void setStringValue(JNIEnv *env, jclass cls, jobject obj, const char *fieldName,const char *pChar){
	jfieldID id = env->GetFieldID(cls, fieldName, "Ljava/lang/String;");   
	jstring jstr = env->NewStringUTF(pChar);
	env->SetObjectField(obj, id, jstr);
}

void getStringValue(jstring &jstr, JNIEnv *env, jclass cls, jobject obj, const char *fieldName){
	jfieldID id = env->GetFieldID(cls, fieldName, "Ljava/lang/String;");
	jstr = (jstring)env->GetObjectField(obj,id);
} 

void setStringValue(JNIEnv *env, jclass cls, jobject obj, const char *fieldName, jstring jstr){
	jfieldID id = env->GetFieldID(cls, fieldName, "Ljava/lang/String;");   
	env->SetObjectField(obj, id, jstr);
}

void getStringArray(){

}

void setStringArray(){

}

//Object Method 

