#JNI DEMO
��Ҫ�ع�jniʹ�����̣�Ϊ�������ٹ��������������ݿ���

#jni����
* ����ת��
	1. ʹ�ù���ͨ����jboolean�������⣬����jni��jbooleanӳ�䵽unsigned char��������Java��Booleanֻ֧�ָ�true/false�����Ի���Ҫ����ӳ��Ϊbool)
	2. Java byte����ӳ��ΪC������char��unsigned char���޷���ȡ����ǿ��ת��һ�¼��ɣ�������ע��Java String str.getBytes("utf-8")����Chaset����ʱ�������jvmĬ����ת������Ҫע���ַ���������
	3. Java char������Jvm��16bit�޷�������������Ҫӳ��Ϊunsigned short
	3. int��������C��ʵ�ֺ�ƽ̨�Ĳ��죬���Է���ʹ�á�����Cӵ��int��long���������ͣ��������ǵ�ʵ��ȴ��ȡ���ھ����ƽ̨����һЩƽ̨�ϣ�int������16λ�ģ���������һЩƽ̨����32λ���������������ԭ��Java���ؽӿڶ�����jint��jlong�ȵ�
	4. Java int������32λ������ӳ��Ϊlong����32bit��java long����ӳ��long long 64bit
	jboolean (1/0) -> bool
	jbyte -> char/unsigned char
	jchar -> unsigned short
	jshort -> short 
	jint -> long 
	jlong -> long long 
	jfloat -> float
	jdouble -> double 
* String char����
	����ת���ο�JniUtil.cpp�з������ɣ���Ҫע�����ת���ַ���������
	��򵥵�ʵ�ַ������ǣ�
		const char *user = env->GetStringUTFChars(userName, 0);
		int userLen = env->GetStringUTFLength(userName);
		env->ReleaseStringUTFChars(userName, user); 
* �ַ�����


#c++����java��

#Java������Ƕ����? c++��ô���ظ���?

#��ģ����� sm2.so sm3.so

#jni��ȫ�ֱ���������ά�֣��������� 

#JNI_OnLoad() JNI_OnUnload()  ->  [cache Ids](http://stackoverflow.com/questions/10617735/in-jni-how-do-i-cache-the-class-methodid-and-fieldids-per-ibms-performance-r)

#java Static����

#�ڴ�й¶����
1. DeleteLocalRef  DeleteGlobalRef
  * FindClass GetObjectField() GetObjectClass()  GetObjectArrayElement()  NewString/ NewStringUTF/NewObject/NewByteArray 
		jclass ref= (env)->FindClass("java/lang/String");
		env->DeleteLocalRef(ref); 
	   
		jclass ref = env->GetObjectClass(robj);
		env->DeleteLocalRef(ref); 
		
		jobject ref= env->NewGlobalRef(customObj);
		env->DeleteGlobalRef(customObj); 
    
2. ReleaseXXX
  *Release is paired with Get  GetStringChars() GetStringUTFChars() GetByteArrayElements()  
	
		const char* input =(*env)->GetStringUTFChars(env,jinput, &isCopy);
		(*env)->ReleaseStringUTFChars(env,jinput,input); 
		
		jbyte* array= (*env)->GetByteArrayElements(env,jarray,&isCopy);
		(*env)->ReleaseByteArrayElements(env,jarray,array,0);
		
		
#��������

    
#REF: (Thanks)
[JNI���ܺ�ע������](http://www.ibm.com/developerworks/library/j-jni/)
[��Ƕ��ת��](http://blog.csdn.net/jinhill/article/details/6918821)
[List����1](http://blog.csdn.net/woshinia/article/details/25132353) [List����2](http://blog.csdn.net/u_xtian/article/details/6033963) [List����3](http://blog.csdn.net/qinjuning/article/details/7607214)
[����](http://blog.csdn.net/qiuxiaolong007/article/details/7554005)
[�ڴ�й©](http://amazontzy.iteye.com/blog/1962367)