package org.mfn.dishes.util;

public class FunctionUtil {

	public static String formatNum(String mixString) {
		StringBuffer sb = new StringBuffer();
		for (int i = 0; i < mixString.length(); i++) {
			int chr = mixString.charAt(i);
			if (chr >= 0x30 && chr <= 0x39) {
				sb.append((char) chr);
			}
		}
		return sb.toString();
	}
}
