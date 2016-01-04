package cn.dcs.leef.tool;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Random;

/**
 * Created by Madoll on 2015/11/24.
 */

public class Util {
    private final static char[] HEX = { '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    public static byte[] toBytes(String str)
    {
        int len = str.length() / 2;
        byte[] result = new byte[len];
        int cnt = 0;
        while (cnt < len)
        {
            String s=str.substring(cnt*2,cnt*2+2);
            result[cnt]=(byte) Integer.parseInt(s, 16);
            cnt++;
        }
        return result;
    }
    
    public static String getCharSetString(String msg, String charset){
    	String str=null;
    	try {
			str = new String(msg.getBytes(), charset);
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		return str;
    }

    
    public static String toHexString(byte[] d, int s, int len) {
        final char[] ret = new char[len * 2];
        final int e = s + len;

        int x = 0;
        for (int i = s; i < e; ++i) {
            final byte v = d[i];
            ret[x++] = HEX[0x0F & (v >> 4)];
            ret[x++] = HEX[0x0F & v];
        }
        return new String(ret);
    }

    public static String toHexString(byte[] d)
    {
        return toHexString(d,0,d.length);
    }

    public static String toHexString(byte[] d, int offset)
    {
        return toHexString(d,offset,d.length-offset);
    }

    public static short ByteArrayToShort(byte[] buf,int offset) {
        short value = 0;
        for (int i = 0; i < 2; i++) {
            value = (short) (value << 8);
            value |= buf[1+offset-i] & 0xff;
        }
        return value;
    }

    public static short ByteArrayToShort(byte[] buf) {
        return ByteArrayToShort(buf,0);
    }

    public static byte[] ShortToByteArray(short r){
        byte[] buf=new byte[2];
        for (int i = 0; i < 2; i++) {
            buf[i] = (byte) (r >>> (i * 8));
        }
        return buf;
    }

    public static int ByteArrayToInt(byte[] buf,int offset) {
        int value = 0;
        for (int i = 0; i < 4; i++) {
            value = value << 8;
            value |= buf[3+offset-i] & 0xff;
        }
        return value;
    }

    public static int ByteArrayToInt(byte[] buf) {
        return ByteArrayToInt(buf,0);
    }

    public static byte[] IntToByteArray(int r) {
        byte[] buf=new byte[4];
        for (int i = 0; i < 4; i++) {
            buf[i] = (byte) (r >>> (i * 8));
        }
        return buf;
    }

    public static void IntToByteArray(int r, byte[] buf, int offset) {
        for (int i = 0; i < 4; i++) {
            buf[offset + i] = (byte) (r >>> (i * 8));
        }
    }

    public static long ByteArrayToLong(byte[] buf, int offset) {
        long value = 0;
        for (int i = 0; i < 8; i++) {
            value = value << 8;
            value |= buf[7+offset-i] & 0xff;
        }
        return value;
    }

    public static long ByteArrayToLong(byte[] buf) {
        return ByteArrayToLong(buf,0);
    }

    public static byte[] LongToByteArray(long r) {
        byte[] buf=new byte[8];
        for (int i = 0; i < 8; i++) {
            buf[i] = (byte) (r >>> (i * 8));
        }
        return buf;
    }

    public static void LongToByteArray(long r, byte[] buf, int offset) {
        for (int i = 0; i < 8; i++) {
            buf[offset + i] = (byte) (r >>> (i * 8));
        }
    }

    public static byte[] join(byte[] ...bs) {
        ByteArrayOutputStream bos=new ByteArrayOutputStream();
        byte[] buf=null;
        try {
            for (byte[] b:bs) {
                bos.write(b);
            }
            buf=bos.toByteArray();
            bos.close();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return buf;
    }

    public static byte[] sub(byte[] source,int offset,final int len) {
        byte[] r=new byte[len];
        System.arraycopy(source, offset, r, 0, len);
        return r;
    }

    public static int parseInt(String txt, int radix, int def) {
        int ret;
        try {
            ret = Integer.valueOf(txt, radix);
        } catch (Exception e) {
            ret = def;
        }

        return ret;
    }


    public static String GenRandomBytes(int len) {
        byte[] buf=new byte[len];
        Random rnd=new Random();
        rnd.nextBytes(buf);
        return toHexString(buf);
    }

    /**
     * 字节数组转为普�?�字符串（ASCII对应的字符） by tianwei
     *
     * @param bytearray
     *             byte[]
     * @return String
     */
    public static String BytetoString(byte[] bytearray) {
        String result = "";
        char temp;

        int length = bytearray.length;
        for (int i = 0; i < length; i++) {
            temp = (char) bytearray[i];
            result += temp;
        }
        return result;
    }

}

