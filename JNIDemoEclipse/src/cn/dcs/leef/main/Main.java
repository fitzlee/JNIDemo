package cn.dcs.leef.main;

import java.util.ArrayList;

import cn.dcs.leef.bean.Book;
import cn.dcs.leef.bean.User;
import cn.dcs.leef.jni.NativeTool;
import cn.dcs.leef.tool.Util;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String priKey="3945208f7b2144b13f36e38ac6d39f95889393692860b51a42fb81ef4df7c5b8";
		
		//basic test
		String basicString = NativeTool.basicTest(false, (byte)0x7f, (char)0xffff, (short)0x7fff, 0x11112222, 1111222233334444l, 3.5f, 6.7d);
		System.out.println("1 basic test: "+basicString);
		
		//array test
		int[] arrayByte = NativeTool.arrayTest(Util.toBytes(priKey));
		System.out.print("2 array test(byte[]->int[] test): ");
		for (int j = 0; j < arrayByte.length; j++) {
			System.out.print(arrayByte[j]);
		}
		System.out.println();
		
		//string test
		String msg = Util.getCharSetString("abcÖÐ","gbk");
		String testString = NativeTool.stringTest(msg);
		System.out.println("3 String test: "+testString);
		
		//class test
		User user = new User();
		user.id=2;
		user.name="ming";
		user.pubKey = Util.toBytes(priKey);
		ArrayList<Book> list=new ArrayList<>();
		Book book = new Book(); 
		book.id=3; book.title="java";
		list.add(book);
		user.books = list;
		User userNew = NativeTool.classTest(user);
		System.out.println("4 class test: "+ userNew.toString());
		
		//method test
		System.out.println("5 static object Method test:  see in native ");
		NativeTool.staticTest();
		NativeTool.objectMethodTest(user);
		
		//some printf in native 
		System.out.println("\n\nnative:");
		
	}

}
