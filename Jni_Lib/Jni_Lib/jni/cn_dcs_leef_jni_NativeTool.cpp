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
	//jclass m_cls_List = env->FindClass("java/util/ArrayList"); 


	//in
	jfieldID id_userName = env->GetFieldID(cls_User, "name", "Ljava/lang/String;");
	jstring userName = (jstring)env->GetObjectField(obj, id_userName);
	long userId = 0; getIntValue(userId, env, cls_User, obj, "id");
	jfieldID id_userPubKey = env->GetFieldID(cls_User, "pubKey", "[B");
	jbyteArray userPubKey = (jbyteArray) env->GetObjectField(obj, id_userPubKey);
	jfieldID id_userBooks = env->GetFieldID(cls_User, "books", "Ljava/lang/Object;");
	jobject userBooks = env->GetObjectField(obj, id_userBooks);

	jclass cls_arraylist = env->GetObjectClass(userBooks);  // ?==ArrayList  ?==ArrayList<Book>
	jmethodID arraylist_get = env->GetMethodID(cls_arraylist, "get", "(I)Ljava/lang/Object;");  
	jmethodID arraylist_size = env->GetMethodID(cls_arraylist, "size", "()I");  
	jint len = env->CallIntMethod(userBooks, arraylist_size);  
	for(int i=0;i<len;i++){  
		jobject book = env->CallObjectMethod(userBooks, arraylist_get, i); 
		jfieldID id_bookTitle = env->GetFieldID(cls_Book, "title", "Ljava/lang/String;");
		jstring bookTitle = (jstring)env->GetObjectField(book, id_bookTitle);
		jfieldID id_bookId = env->GetFieldID(cls_Book, "id", "I");
		jint bookId = env->GetIntField(book, id_bookId);
	}

	//out
	jmethodID m_userInit = env->GetMethodID(cls_User, "<init>", "()V");
	jobject userNew = env->NewObject(cls_User, m_userInit);
	jmethodID userMethod = env->GetMethodID(cls_User,"<init>","()V");  
	jfieldID mId = env->GetFieldID(userClass,"id","J");  
        jfieldID mUserName = env->GetFieldID(userClass,"userName","Ljava/lang/String;");  
        jfieldID mIsMan = env->GetFieldID(userClass,"isMan","Z");  
        jfieldID mAge = env->GetFieldID(userClass,"age","I");  
        jobject userObject = env->NewObject(userClass,userMethod);  
        env->SetObjectField(userObject,mUserName,name);  
        env->SetLongField(userObject,mId,1001);  
        env->SetBooleanField(userObject,mIsMan,1);  
        env->SetIntField(userObject,mAge,21);  

	//delete&release


	//return

}



/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    methodTest
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_cn_dcs_leef_jni_NativeTool_methodTest
	(JNIEnv *, jclass, jint){

				jobject obj_user = env->CallObjectMethod(userList,arraylist_get,i);  
                jclass cls_user = env->GetObjectClass(obj_user);  
                jmethodID user_getId = env->GetMethodID(cls_user,"getId","()J");  
                jmethodID user_getUserName = env->GetMethodID(cls_user,"getUserName","()Ljava/lang/String;");  
                jmethodID user_isMan = env->GetMethodID(cls_user,"isMan","()Z");  
                jmethodID user_getAge = env->GetMethodID(cls_user,"getAge","()I");  
                jstring name = (jstring)env->CallObjectMethod(obj_user,user_getUserName);  
                jboolean b = true;  
                const char *namePtr = env->GetStringUTFChars(name,&b);  
                jlong id = env->CallLongMethod(obj_user,user_getId);  
                jboolean sex = env->CallBooleanMethod(obj_user,user_isMan);  
                jint age = env->CallIntMethod(obj_user,user_getAge);  
                printf("Id:%d; ",id);  
                printf("Name:%s; ",namePtr);  
                printf("isMan? %d; ",sex);  
                printf("Age:%d /n ",age);  
	
}

#ifdef __cplusplus
}
#endif
#endif
