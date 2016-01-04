#include "jni.h"
#include "stdio.h"
#include "string.h"
#include "JniUtil.h"
#include "JniUtil_Del.h"
/* Source for class cn_dcs_leef_jni_NativeTool */



#ifndef _Included_cn_dcs_leef_jni_NativeTool
#define _Included_cn_dcs_leef_jni_NativeTool
#ifdef __cplusplus
extern "C" {
#endif

void printMyCharArray(unsigned char *k, int len){
	for(int i=0;i<len;i++){
		printf("%02X",k[i]);
	}
	printf("\n");
}


void printJbyteArray(JNIEnv *env, jbyteArray array){
	unsigned char *cByte = (unsigned char *)env->GetByteArrayElements(array, NULL);
	int Len = env->GetArrayLength(array);
	printMyCharArray(cByte, Len);
	env->ReleaseByteArrayElements(array, (jbyte *)cByte, 0);
}

/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    basicTest
 * Signature: (ZBCSIJFD)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_cn_dcs_leef_jni_NativeTool_basicTest
	(JNIEnv *env, jclass cls, jboolean jbo, jbyte jby, jchar jch, jshort jsh, jint ji, jlong jl, jfloat jf, jdouble jd){
	bool cBool = jbo==0?false:true;
	unsigned char cUChar = jby; 
	char cChar = jby;
	unsigned short cUShort = jch;
	short cShort = jsh;
	long cLong = ji;
	long long cLLong = jl;
	float cFloat = jf;
	double cDouble = jd;
	
	int Len=0;
	char result[1024]; memset(result,0,1024);
	sprintf_s(result,"boolean->bool:%d,byte->uchar:%02x,byte->char:%02x,char->ushort:%04x,short->short:%04x,int->long:%08x,long->llong:%016x,float->float:%f,double->double:%e",
		 cBool, cUChar, cChar, cUShort, cShort, cLong, cLLong, cFloat, cDouble);
	jstring str = env->NewStringUTF(result);
	return str;
}

/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    arrayTest
 * Signature: ([B)[I
 */
JNIEXPORT jintArray JNICALL Java_cn_dcs_leef_jni_NativeTool_arrayTest
	(JNIEnv *env, jclass cls, jbyteArray jbyArray){
		//in 
		printJbyteArray(env, jbyArray);

		//out
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
		char *pChar = NULL; int iLenOfChar=0;
		jstringToPchar(pChar, iLenOfChar, env, jstr);
		printf("%s\n", pChar);
		delete(pChar);

		char *result = "from native stringTest";
		jstring str = env->NewStringUTF(result);// pCharToJstring(env,result);

		/*
		const char *chars = env->GetStringUTFChars(jstr, 0);
		int charsLen = env->GetStringUTFLength(jstr);
		printf("%s\n", chars);
		env->ReleaseStringUTFChars(jstr, chars); 

		char *result = "from native stringTest";
		jstring str = env->NewStringUTF(result);
		*/

		return str;
}


// http://blog.csdn.net/u_xtian/article/details/6033963
// http://blog.csdn.net/woshinia/article/details/25132353
// http://blog.csdn.net/qinjuning/article/details/7607214

/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    classTest
 * Signature: (Lcn/dcs/leef/bean/User;)Lcn/dcs/leef/bean/User;
 */
JNIEXPORT jobject JNICALL Java_cn_dcs_leef_jni_NativeTool_classTest
	(JNIEnv *env, jclass cls, jobject obj){

	//class
	jclass cls_Book = env->FindClass("cn/dcs/leef/bean/Book");
	jclass cls_User = env->FindClass("cn/dcs/leef/bean/User");
	jclass cls_ArrayList = env->FindClass("java/util/ArrayList");  
	

	//id & method
	jmethodID construct_User = env->GetMethodID(cls_User, "<init>", "()V");
	jfieldID id_userName = env->GetFieldID(cls_User, "name", "Ljava/lang/String;");
	jfieldID id_userId = env->GetFieldID(cls_User, "id", "I");
	jfieldID id_userPubKey = env->GetFieldID(cls_User, "pubKey", "[B");
	jfieldID id_userBooks = env->GetFieldID(cls_User, "books", "Ljava/lang/Object;");
	
	jmethodID construct_Book = env->GetMethodID(cls_Book,"<init>","()V");  
	jfieldID id_bookTitle = env->GetFieldID(cls_Book, "title", "Ljava/lang/String;");
	jfieldID id_bookId = env->GetFieldID(cls_Book, "id", "I");
	
	jmethodID construct_List = env->GetMethodID(cls_ArrayList,"<init>","()V");  
	jmethodID arrayList_add = env->GetMethodID(cls_ArrayList,"add","(Ljava/lang/Object;)Z"); 
	jmethodID arraylist_get = env->GetMethodID(cls_ArrayList, "get", "(I)Ljava/lang/Object;");  
	jmethodID arraylist_size = env->GetMethodID(cls_ArrayList, "size", "()I");  

	//in  getIntField getObjectField
	jstring userName = (jstring)env->GetObjectField(obj, id_userName);
	long userId = 0; getIntValue(userId, env, cls_User, obj, "id");
	jbyteArray userPubKey = (jbyteArray) env->GetObjectField(obj, id_userPubKey);
	jobject userBooks = env->GetObjectField(obj, id_userBooks);											
	jint len = env->CallIntMethod(userBooks, arraylist_size);  
	for(int i=0; i < len; i++){  
		jobject book = env->CallObjectMethod(userBooks, arraylist_get, i); 
		jstring bookTitle = (jstring)env->GetObjectField(book, id_bookTitle);
		jint bookId = env->GetIntField(book, id_bookId);
		//make your own copy  http://stackoverflow.com/questions/17519116/how-to-release-jstring-in-a-loop-correctly
		env->DeleteLocalRef(book);
		env->DeleteLocalRef(bookTitle);
	}

	//do something

	//out setIntField setObjectField
	jobject userNew = env->NewObject(cls_User, construct_User);
	jstring userNameNew = env->NewStringUTF("native UserName");  env->SetObjectField(userNew, id_userName, userNameNew);
	setIntValue(env, cls, userNew, "id", 100031);
	unsigned char pRandomUser[32]={0x39,0x45,0x20,0x8F,0x7B,0x21,0x44,0xB1,0x3F,0x36,0xE3,0x8A,0xC6,0xD3,0x9F,0x95,0x88,0x93,0x93,0x69,0x28,0x60,0xB5,0x1A,0x42,0xFB,0x81,0xEF,0x4D,0xF7,0xC5,0xB8};
	jbyteArray userPubKeyNew = env->NewByteArray(32); 
	env->GetByteArrayRegion(userPubKeyNew, 0, 32, (jbyte *)pRandomUser);
	env->SetObjectField(userNew, id_userPubKey,userPubKey);
    jobject userBookList = env->NewObject(cls_ArrayList,construct_List,"");  
	for(int i=0; i<2; i++){
		 jobject obj_book = env->NewObject(cls_Book, construct_Book); 
		 setIntValue(env, cls_Book, obj_book, "id", 10003100+i);
		 jstring str = env->NewStringUTF("book "+i);
		 env->SetObjectField(obj_book, id_bookTitle, str);
		 env->CallObjectMethod(userBookList,arrayList_add,obj_book); 
		 env->DeleteLocalRef(str);
	}
	env->SetObjectField(userNew, id_userBooks, userBookList);

	//delete&release
	env->DeleteLocalRef(cls_User);
	env->DeleteLocalRef(cls_Book);
	env->DeleteLocalRef(cls_ArrayList);
	env->DeleteLocalRef(userName);
	env->DeleteLocalRef(userPubKey);
	env->DeleteLocalRef(userBooks);

	env->DeleteLocalRef(userNameNew);
	env->DeleteLocalRef(userPubKey);

	//return
	return userNew;

}


/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    staticMethodTest
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cn_dcs_leef_jni_NativeTool_staticMethodTest
	(JNIEnv *env, jclass cls){
		jclass cls_User = env->FindClass("cn/dcs/leef/bean/User");
		jmethodID m_GetCount = env->GetStaticMethodID(cls_User, "getCount", "(I)I");
		int count = env->CallStaticIntMethod(cls_User,m_GetCount);
		printf("native count=\n"+count);
}

/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    objectMethodTest
 * Signature: (Lcn/dcs/leef/bean/User;)V
 */
JNIEXPORT void JNICALL Java_cn_dcs_leef_jni_NativeTool_objectMethodTest
	(JNIEnv *env, jclass cls, jobject obj){
	//in
	jclass cls_User = env->FindClass("cn/dcs/leef/bean/User");
	jmethodID m_GetId = env->GetMethodID(cls_User, "getId", "()I");
	int id = env->CallIntMethod(obj, m_GetId);
	printf("native getId=\n"+id);

	//set obj
	jfieldID id_userId = env->GetFieldID(cls_User, "id", "I");
	env->SetIntField(obj, id_userId, id+10);
}

#ifdef __cplusplus
}
#endif
#endif
