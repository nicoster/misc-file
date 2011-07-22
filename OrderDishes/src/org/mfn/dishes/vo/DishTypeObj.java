package org.mfn.dishes.vo;

public class DishTypeObj {
	
	public static final String TABLE_NAME = "dishes_type_info";
	public static final String TYPE_ID = "type_id";
	public static final String TYPE_NAME = "type_name";
	public static final String PARENT_TYPE_ID = "parent_type_id";
	public static final String TYPE_INDEX = "type_index";
	
	public String id;
	public String name;
	public String parentId;
	public int index;
	
	public String toString()
	{
		return "{id:" + id + ", name:" + name + ", index:" + index + "}";
	}
}
