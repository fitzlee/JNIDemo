#include "jni.h"
#include "stdio.h"
#include "string.h"
#include "JniUtil.h"
#include "JniUtil_Del.h"
#include "JniUtil_IO.h"
/* Source for class cn_dcs_leef_jni_NativeTool */



#ifndef _Included_cn_dcs_leef_jni_NativeTool
#define _Included_cn_dcs_leef_jni_NativeTool
#ifdef __cplusplus
extern "C" {
#endif

/*
static jclass simpleCls;

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIEnv* env = NULL;
     if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    } else {
        //simpleCls = (jclass) env->NewGlobalRef(localSimpleCls);
    } 
    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv* env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        // Something is wrong but nothing we can do about this :(
        return;
    } else {
        if (0 != NULL){
            //env->DeleteGlobalRef(env, simpleCls);
        }
    }
}

*/




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
	sprintf(result,"boolean->bool:%d,byte->uchar:%02x,byte->char:%02x,char->ushort:%04x,short->short:%04x,int->long:%08x,long->llong:%016x,float->float:%f,double->double:%e",
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
		printJbyteArray(env, "array test: ", jbyArray);

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
		printJstring(env, "string test in=", jstr);

		char *result = "from native stringTest";
		jstring str = env->NewStringUTF(result);// pCharToJstring(env,result);
		return str;

		/* //Another method utf-8
		const char *chars = env->GetStringUTFChars(jstr, 0);
		int charsLen = env->GetStringUTFLength(jstr);
		printf("%s\n", chars);
		env->ReleaseStringUTFChars(jstr, chars); 

		char *result = "from native stringTest";
		jstring str = env->NewStringUTF(result);
		*/
}


/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    classTest
 * Signature: (Lcn/dcs/leef/bean/User;)Lcn/dcs/leef/bean/User;
 */
JNIEXPORT jobject JNICALL Java_cn_dcs_leef_jni_NativeTool_classTest
	(JNIEnv *env, jclass cls, jobject obj){

	printf("---class Test:\n");

	//class
	jclass cls_Book = env->FindClass("cn/dcs/leef/bean/Book");
	jclass cls_User = env->FindClass("cn/dcs/leef/bean/User");
	jclass cls_List = env->FindClass("java/util/ArrayList");  
	
	//id & method
	jmethodID m_construct_User = env->GetMethodID(cls_User, "<init>", "()V");
	jfieldID id_userName = env->GetFieldID(cls_User, "name", "Ljava/lang/String;");
	jfieldID id_userId = env->GetFieldID(cls_User, "id", "I");
	jfieldID id_userPubKey = env->GetFieldID(cls_User, "pubKey", "[B");
	jfieldID id_userBooks = env->GetFieldID(cls_User, "books", "Ljava/util/List;");

	jmethodID m_construct_Book = env->GetMethodID(cls_Book,"<init>","()V");  
	jfieldID id_bookId = env->GetFieldID(cls_Book, "id", "I");
	jfieldID id_bookTitle = env->GetFieldID(cls_Book, "title", "Ljava/lang/String;");
	
	jmethodID m_construct_List = env->GetMethodID(cls_List,"<init>","()V");  
	jmethodID arrayList_add = env->GetMethodID(cls_List,"add","(Ljava/lang/Object;)Z"); 
	jmethodID m_list_get = env->GetMethodID(cls_List, "get", "(I)Ljava/lang/Object;");  
	jmethodID m_list_size = env->GetMethodID(cls_List, "size", "()I");  

	//in  getIntField getObjectField
	jstring userName = (jstring)env->GetObjectField(obj, id_userName);
	long userId = 0; getIntValue(userId, env, cls_User, obj, "id");
	jbyteArray userPubKey = (jbyteArray) env->GetObjectField(obj, id_userPubKey);								
	jobject userBooks = env->GetObjectField(obj, id_userBooks);		
	jint len = env->CallIntMethod(userBooks, m_list_size);  

	/*  //Another method List Acess
	jmethodID mToArray = env->GetMethodID(cls_List, "toArray", "()[Ljava/lang/Object;");
	jobjectArray array = (jobjectArray)env->CallObjectMethod(userBooks, mToArray);
	for(int i=0;i<env->GetArrayLength(array);i++) {
		 jobject book = env->GetObjectArrayElement(array, i);
	}
	*/

	for(int i=0; i < len; i++){  
		jobject book = env->CallObjectMethod(userBooks, m_list_get, i); 

		//make your own copy  http://stackoverflow.com/questions/17519116/how-to-release-jstring-in-a-loop-correctly
		long bookId = env->GetIntField(book, id_bookId);
		printf("book id=%ld\n", bookId);
		jstring bookTitle = (jstring)env->GetObjectField(book, id_bookTitle);
		printJstring(env, "book Title=", bookTitle);

		env->DeleteLocalRef(bookTitle);
		env->DeleteLocalRef(book);
	}

	// in output
	printJstring(env,"user Name=", userName);
	printf("user Id=%ld\n", userId);
	printJbyteArray(env, "user pubKey= ", userPubKey);
	

	//do something

	//out setIntField setObjectField
	jobject userNew = env->NewObject(cls_User, m_construct_User);
	jstring userNameNew = env->NewStringUTF("nativeUser");  env->SetObjectField(userNew, id_userName, userNameNew);
	setIntValue(env, cls_User, userNew, "id", 100033);
	unsigned char pRandomUser[32]={0x39,0x45,0x20,0x8F,0x7B,0x21,0x44,0xB1,0x3F,0x36,0xE3,0x8A,0xC6,0xD3,0x9F,0x95,0x88,0x93,0x93,0x69,0x28,0x60,0xB5,0x1A,0x42,0xFB,0x81,0xEF,0x4D,0xF7,0xC5,0xB8};
	jbyteArray userPubKeyNew = env->NewByteArray(32); 
	env->GetByteArrayRegion(userPubKeyNew, 0, 32, (jbyte *)pRandomUser);
	env->SetObjectField(userNew, id_userPubKey, userPubKey);
    jobject userBookList = env->NewObject(cls_List, m_construct_List);  
	for(int i=0; i<2; i++){
		 jobject obj_book = env->NewObject(cls_Book, m_construct_Book); 
		 setIntValue(env, cls_Book, obj_book, "id", i);
		 char pChar[100];
		 sprintf(pChar,"java%i",i);
		 jstring str = env->NewStringUTF(pChar);
		 env->SetObjectField(obj_book, id_bookTitle, str);
		 env->CallObjectMethod(userBookList,arrayList_add,obj_book); 
		 env->DeleteLocalRef(str);
	}
	env->SetObjectField(userNew, id_userBooks, userBookList);

	printf("---class Test END\n");

	//delete&release
	env->DeleteLocalRef(cls_User);
	env->DeleteLocalRef(cls_Book);
	env->DeleteLocalRef(cls_List);
	env->DeleteLocalRef(userName);
	env->DeleteLocalRef(userPubKey);
	env->DeleteLocalRef(userBooks);
	env->DeleteLocalRef(userNameNew);
	env->DeleteLocalRef(userPubKeyNew);

	//return
	return userNew;

}


/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    staticTest
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cn_dcs_leef_jni_NativeTool_staticTest
	(JNIEnv *env, jclass cls){
		jclass cls_User = env->FindClass("cn/dcs/leef/bean/User");
		jmethodID m_GetCount = env->GetStaticMethodID(cls_User, "getTotal", "()I");
		int count = env->CallStaticIntMethod(cls_User,m_GetCount);
		printf("static Method count=%d\n", count);

		jfieldID id_count = env->GetStaticFieldID(cls_User, "count", "I");
		int count1 = env->GetStaticIntField(cls_User, id_count);
		printf("static Variable count=%d\n", count1);
		//delete
		env->DeleteLocalRef(cls_User);
}

/*
 * Class:     cn_dcs_leef_jni_NativeTool
 * Method:    objectMethodTest
 * Signature: (Lcn/dcs/leef/bean/User;)V
 */
JNIEXPORT void JNICALL Java_cn_dcs_leef_jni_NativeTool_objectMethodTest
	(JNIEnv *env, jclass cls, jobject obj){
	//in & methods
	jclass cls_User = env->FindClass("cn/dcs/leef/bean/User");
	jmethodID m_GetId = env->GetMethodID(cls_User, "getId", "()I");
	int id = env->CallIntMethod(obj, m_GetId);
	printf("object Method getId=%d\n", id);

	jmethodID m_Calc = env->GetMethodID(cls_User, "calc", "(I)I");
	int calc = env->CallIntMethod(obj, m_Calc, 3);
	printf("object Method calc=%d\n", calc);

	//set obj
	jfieldID id_userId = env->GetFieldID(cls_User, "id", "I");
	env->SetIntField(obj, id_userId, id+10);

	//delete & release
	env->DeleteLocalRef(cls_User);
}

#ifdef __cplusplus
}
#endif
#endif
