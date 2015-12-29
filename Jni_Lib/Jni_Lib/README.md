#JNI DEMO
主要回顾jni使用流程，为将来减少工作量，快速敏捷开发

#jni基础
* 类型转换
	1. 使用过程通常，jboolean类型特殊，尽管jni中jboolean映射到unsigned char，但由于Java中Boolean只支持赋true/false，所以还是要最终映射为bool)
	2. Java byte可以映射为C语言中char或unsigned char，无非是取补或强制转换一下即可，另外需注意Java String str.getBytes("utf-8")不加Chaset参数时，会根据jvm默认来转换，需要注意字符编码问题
	3. Java char类型在Jvm是16bit无符号数，所以需要映射为unsigned short
	3. int类型由于C中实现和平台的差异，所以放弃使用。尽管C拥有int和long的数据类型，但是他们的实现却是取决于具体的平台。在一些平台上，int类型是16位的，而在另外一些平台上市32位的整数。基于这个原因，Java本地接口定义了jint，jlong等等
	4. Java int类型是32位，所以映射为long类型32bit，java long类型映射long long 64bit
	jboolean (1/0) -> bool
	jbyte -> char/unsigned char
	jchar -> unsigned short
	jshort -> short 
	jint -> long 
	jlong -> long long 
	jfloat -> float
	jdouble -> double 
* String char类型
	具体转换参考JniUtil.cpp中方法即可，需要注意的是转换字符编码问题
	最简单的实现方法就是：
		const char *user = env->GetStringUTFChars(userName, 0);
		int userLen = env->GetStringUTFLength(userName);
		env->ReleaseStringUTFChars(userName, user); 
* 字符编码


#c++调用java类

#Java类中有嵌套类? c++怎么返回该类?

#多模块调用 sm2.so sm3.so

#jni中全局变量，变量维持，生命周期 

#JNI_OnLoad()

#内存泄露风险
