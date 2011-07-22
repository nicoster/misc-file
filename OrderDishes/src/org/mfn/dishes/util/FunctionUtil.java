package org.mfn.dishes.util;

import android.text.TextUtils;

public class FunctionUtil {

	public static String formatDishId(String mixString) {
		StringBuffer sb = new StringBuffer();
		for (int i = 0; i < mixString.length(); i++) {
			int chr = mixString.charAt(i);
			if (chr >= 0x30 && chr <= 0x39) {
				sb.append((char) chr);
			}
		}
		return "" + Long.parseLong(sb.toString());
	}
	
	public static boolean isImageFile(String fileName){
		if (TextUtils.isEmpty(fileName)){
			return false;
		}
		if (fileName.toLowerCase().endsWith(".bmp")){
			return true;
		}
		if (fileName.toLowerCase().endsWith(".png")){
			return true;
		}
		if (fileName.toLowerCase().endsWith(".jpg")){
			return true;
		}
		return false;
	}
}
