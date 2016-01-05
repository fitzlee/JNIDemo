#include "jni.h"
#include <stdlib.h>
#include <cstring>
#include "jniUtil.h"


//Object Basic Next

void getDoubleValue(double &val, JNIEnv *env, jclass cls, jobject obj, const char *fieldName){
	jfieldID id = env->GetFieldID(cls, fieldName, "D");
	val = env->GetDoubleField(obj, id);
}

void setDoubleValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName,
		double val) {
	jfieldID id = env->GetFieldID(cls, fieldName, "D");
	env->SetDoubleField(obj, id, val);
}

void getFloatValue(float &val, JNIEnv *env, jclass cls, jobject obj, const char *fieldName){
	jfieldID id = env->GetFieldID(cls, fieldName, "F");
	val = env->GetFloatField(obj, id);
}

void setFloatValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName,
		float val) {
	jfieldID id = env->GetFieldID(cls, fieldName, "F");
	env->SetFloatField(obj, id, val);
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
	env->SetIntField(obj, id, (jint)val);
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
	val = env->GetCharField(obj,id);
}

void setCharValue(JNIEnv *env, jclass cls, jobject obj, const char* fieldName,
		unsigned short val) {
	jfieldID id = env->GetFieldID(cls, fieldName, "C");
	env->SetCharField(obj, id, val);
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

void getBoolValue(bool &flag, JNIEnv *env, jclass cls, jobject obj,const char *fieldName)
{
	jfieldID id = env->GetFieldID(cls, fieldName, "Z");
	int val = env->GetBooleanField(obj, id);
	flag = (val==0?false:true);
}

void setBoolValue(JNIEnv *env, jclass cls, jobject obj, const char *fieldName, bool val)
{
	jfieldID id = env->GetFieldID(cls, fieldName, "Z");
	env->SetBooleanField(obj, id, val);
}