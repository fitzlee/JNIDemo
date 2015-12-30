//Object Delete & Release Too Much ...  Just For Test & Learn 

#include "jni.h"
#include <stdlib.h>
#include <cstring>
#include "jniUtil.h"


//Object Next
/**
 * FUN: Get char[] from java byte[] 
 * NOTE: 使用后需要释放空间，delete(arr)
**/
void getByteArray(char *arr, unsigned int &arrLen, JNIEnv *env, jclass cls, jobject obj, const char *fieldName)
{
	jfieldID id = env->GetFieldID(cls, fieldName, "[B");
	jbyteArray array = (jbyteArray) env->GetObjectField(obj, id);
	if (array)
	{
		char *ary = (char *)env->GetByteArrayElements(array, 0);
		arrLen = env->GetArrayLength(array);
		arr = new char[arrLen];
		memcpy(arr,ary,arrLen);
		env->ReleaseByteArrayElements(array, (jbyte*)ary, 0);
	}
	else
	{
		arr = NULL;
		arrLen = 0;
	}
	env->DeleteLocalRef(array);
}


void setByteArray(JNIEnv *env, jclass cls, jobject obj, const char *fieldName, char *arr, int len)
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


//String Next

/**
 * 使用后必须释放jstring，除了返回给java层的
**/
jstring pCharToJstring(JNIEnv *env, const char *pat)
{
	jclass strClass = env->FindClass("Ljava/lang/String;");
	//获取java String类方法String(byte[],String)的构造器
	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = env->NewByteArray((jsize)strlen(pat));
	(env)->SetByteArrayRegion(bytes, 0, (jsize)strlen(pat), (jbyte*)pat);
	jstring encoding = env->NewStringUTF("utf-8");   //GB2312 
	jstring str = (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
	env->DeleteLocalRef(strClass);
	env->DeleteLocalRef(bytes);
	env->DeleteLocalRef(encoding);
	return str;
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
	env->DeleteLocalRef(clsstring);
	env->DeleteLocalRef(strencode);
	env->ReleaseByteArrayElements(barr, ba, 0);  
	return rtn;
}


void jstringToPchar(char *pOut, int &iLenOfOut, JNIEnv *env, jstring jstr){
	pOut =(char *)env->GetStringUTFChars(jstr,0);
	iLenOfOut = env->GetStringUTFLength(jstr);

	env->ReleaseStringUTFChars(jstr,pOut);
}

void pCharToJstring(jstring &jstr, char *pIn, int iLenOfIn, JNIEnv *env){
	jstr = env->NewStringUTF(pIn);
		
	env->DeleteLocalRef(jstr);
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


//Object Method 

