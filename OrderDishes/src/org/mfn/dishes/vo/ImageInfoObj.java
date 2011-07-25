package org.mfn.dishes.vo;

import java.util.Date;

import org.mfn.dishes.Constants;
import org.mfn.dishes.util.FunctionUtil;

import android.text.TextUtils;

public class ImageInfoObj {
	public static final String TABLE_NAME = "image_info";
	
	public static final String IMAGE_ID = "image_id";
	
	public static final String IMAGE_NAME = "image_name";
	public static final String IMAGE_SIZE = "image_size";
	public static final String IMAGE_MODIFY_TIME = "image_modify_time";

	public static final String SMALL_IMAGE_NAME = "small_image_name";
	public static final String SMALL_IMAGE_SIZE = "small_image_size";
	public static final String SMALL_IMAGE_MODIFY_TIME = "small_image_modify_time";
	
	public String id;
	public String name;
	public long size;
	public Date modified_time;
	
	public String small_name;
	public long small_size;
	public Date small_modified_time;
	
	public void set(ServerImageInfoObj sObj) {
		id = FunctionUtil.formatDishId(sObj.name);
		if (sObj.name.toLowerCase().endsWith("t.bmp")) {
			small_name = sObj.name;
			small_size = sObj.size;
			small_modified_time = sObj.modified_time;
		} else {
			name = sObj.name;
			size = sObj.size;
			modified_time = sObj.modified_time;
		}
	}

	public String toString() {
		return "{id:" + id + ", name:" + name + ", modified_time:" + modified_time + ", small_name:" + small_name
				+ ", small_modified_time:" + small_modified_time + "}";
	}
	
	public String getImgUrl(boolean isSmall) {
		if (isSmall && !TextUtils.isEmpty(small_name)) {
			return Constants.DISHES_IMAGE_PATH + small_name;
		}
		return Constants.DISHES_IMAGE_PATH + name;
	}
}
