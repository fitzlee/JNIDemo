package cn.dcs.leef.bean;

import java.util.List;

public class User {
	public int id;
	public String name;
	public byte[] pubKey;
	public List<Book> books;
	
	public User(){
		super();
		count++;
	};
	
	private static int count=0;
	public static int getTotal(){
		return count;
	}
	
	public int getId(){
		return id;
	}
	
	public int calc(int i){
		return i+2;
	}
	
	@Override
	public String toString(){
		String str = "id="+id+",name="+name+",";
		for(Book item:books){
			str+= "bookId="+item.id+",booktitle="+item.title+","; 
		}
		return str;
	}
}
