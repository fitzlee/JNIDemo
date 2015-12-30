package cn.dcs.leef.jni;

import cn.dcs.leef.bean.User;

public class NativeTool {
	private static final String LIB_NAME="tool";
	static{
		System.loadLibrary(LIB_NAME);
	}
	
	public static native String basicTest(boolean bo, byte by, char ch, short sh, int in, long l, float f, double d);
	public static native int[] arrayTest(byte[] byteArray);
	public static native String stringTest(String str);
	public static native User classTest(User user); //return new User
	public static native int methodTest(int a);  //C++ -> BaxUtil
}
