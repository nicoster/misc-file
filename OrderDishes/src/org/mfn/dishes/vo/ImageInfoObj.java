package org.mfn.dishes.vo;

import java.util.Date;

import org.mfn.dishes.util.FunctionUtil;

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
		id = FunctionUtil.formatNum(sObj.name);
		if (sObj.name.toLowerCase().indexOf("t.bmp") > 0) {
			small_name = sObj.name;
			small_size = sObj.size;
			small_modified_time = sObj.modified_time;
		} else {
			name = sObj.name;
			size = sObj.size;
			modified_time = sObj.modified_time;
		}
	}

}
