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

#JNI_OnLoad()

#�ڴ�й¶����
