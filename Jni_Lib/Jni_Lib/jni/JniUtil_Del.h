//Object Delete & Release Too Much ...  Just For Test & Learn 
#include "jni.h"

#ifndef JNIUTIL_H
#define JNIUTIL_H

//#define ARM
#if defined(ARM) 
	#include <android/log.h>
	#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
	#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
	#define LOGI(message...) __android_log_print(ANDROID_LOG_INFO,"JNILog",message)
	#define LOGW(TAG,message) __android_log_print(ANDROID_LOG_WARN,TAG,message)
	#define LOGE(TAG,message) __android_log_print(ANDROID_LOG_ERROR,TAG,message)
#endif

#define LOGI printf

//String Next 
jstring pCharToJstring( JNIEnv *env, const char *pat);
//NOTE: after using, free(ptr) 
char * jstringToPchar(JNIEnv *env, jstring jstr);
void jstringToPchar(char *pOut, int &iLenOfOut, JNIEnv *env, jstring jstr);
void pCharToJstring(jstring &jstr, char *pIn, int iLenOfIn, JNIEnv *env);


//Object Array
void getByteArray(unsigned char arr[], unsigned int arrLen, JNIEnv *env, jclass cls, jobject obj, const char* fieldName);
void setByteArray(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, unsigned char *arr, int len);
//Object String
void getStringValue(char *pChar, JNIEnv *env, jclass cls, jobject obj, const char *fieldName);
void setStringValue(JNIEnv *env, jclass cls, jobject obj, const char *fieldName,const char *pChar);
void setStringValue(JNIEnv *env, jclass cls, jobject obj, const char *fieldName, jstring jstr);
void getStringValue(jstring &jstr, JNIEnv *env, jclass cls, jobject obj, const char *fieldName);


//Object List


#endif