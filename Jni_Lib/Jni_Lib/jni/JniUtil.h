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
/**
 * NOTE: after using, free(ptr) 
 */
char * jstringToPchar(JNIEnv *env, jstring jstr);
void jstringToPchar(char *pOut, int &iLenOfOut, JNIEnv *env, jstring jstr);
void pCharToJstring(jstring &jstr, char *pIn, int iLenOfIn, JNIEnv *env);

//Object Basic
void getDoubleValue(double &val, JNIEnv *env, jclass cls, jobject obj, const char* fieldName);
void setDoubleValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, double val);
void getFloatValue(float &val, JNIEnv *env, jclass cls, jobject obj, const char* fieldName);
void setFloatValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, float val);
void getLongValue(long long &val, JNIEnv *env, jclass cls, jobject obj, const char* fieldName);
void setLongValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, long long val);
void getIntValue(long &val, JNIEnv *env, jclass cls, jobject obj, const char* fieldName);
void setIntValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, long val);
void getShortValue(short &val, JNIEnv *env, jclass cls, jobject obj, const char* fieldName);
void setShortValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, short val);
void getCharValue(unsigned short &val, JNIEnv *env, jclass cls, jobject obj, const char* fieldName);
void setCharValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, unsigned short val);
void getByteValue(char &val, JNIEnv *env, jclass cls, jobject obj, const char* fieldName);
void setByteValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, char val);
void getBoolValue(bool* val, JNIEnv* env, jclass cls, jobject obj,const char* fieldName);
void setBoolValue(JNIEnv* env, jclass cls, jobject obj, const char* fieldName, bool val);

//Object Array
void getByteArray(unsigned char arr[], unsigned int arrLen, JNIEnv *env, jclass cls, jobject obj, const char* fieldName);
void setByteArray(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, unsigned char *arr, int len);
void getIntArray(unsigned int*& arr, unsigned int *arrCnt, JNIEnv *env, jclass cls, jobject obj, const char* fieldName);
void setIntArray(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, unsigned int* val, int len);
void setLongArray(JNIEnv *env, jclass cls, jobject obj, const char* fieldName, unsigned long long* val, unsigned int len);

//Object String
void getStringValue(char *pChar, JNIEnv *env, jclass cls, jobject obj, const char *fieldName);
void setStringValue(JNIEnv *env, jclass cls, jobject obj, const char *fieldName,const char *pChar);
void setStringValue(JNIEnv *env, jclass cls, jobject obj, const char *fieldName, jstring jstr);
void getStringValue(jstring &jstr, JNIEnv *env, jclass cls, jobject obj, const char *fieldName);

//Object List


#endif