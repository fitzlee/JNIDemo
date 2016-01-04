#include "JniUtil_Del.h"

#ifndef JNIUTIL_IO_H
#define JNIUTIL_IO_H


void printCharArray(unsigned char *k, char *msg, int len){
	printf("%s", msg);
	for(int i=0;i<len;i++){
		printf("%02X",k[i]);
	}
	printf("\n");
}


void printJbyteArray(JNIEnv *env, char *msg, jbyteArray array){
	unsigned char *cByte = (unsigned char *)env->GetByteArrayElements(array, NULL);
	int Len = env->GetArrayLength(array);
	printCharArray(cByte, msg, Len);
	env->ReleaseByteArrayElements(array, (jbyte *)cByte, 0);
}

void printJstring(JNIEnv *env, char *msg, jstring jstr){
	char *pChar = NULL; int iLenOfChar=0;
	jstringToPchar(pChar, iLenOfChar, env, jstr);
	printf("%s%s\n", msg, pChar);
	delete(pChar);
}

#endif