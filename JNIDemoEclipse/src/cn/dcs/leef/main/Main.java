package cn.dcs.leef.main;

import cn.dcs.leef.jni.NativeTool;
import cn.dcs.leef.tool.Util;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String priKey="3945208f7b2144b13f36e38ac6d39f95889393692860b51a42fb81ef4df7c5b8";
		String basicString = NativeTool.basicTest(false, (byte)0x7f, (char)0xffff, (short)0x7fff, 0x11112222, 1111222233334444l, 3.5f, 6.7d);
		System.out.println(basicString);
		
		int[] arrayByte = NativeTool.arrayTest(Util.toBytes(priKey));
		for (int j = 0; j < arrayByte.length; j++) {
			System.out.print(arrayByte[j]);
		}
		System.out.println();
		
		
		
		String msg = Util.getCharSetString("abcÖÐ","UTF-8");
		String testString = NativeTool.stringTest(msg);
		System.out.println(testString);
		
		System.out.println("\n\nnative:");
		
	}

}
