package org.mfn.dishes.vo;

public class DishesTypeObj {
	
	public static final String TABLE_NAME = "dishes_type_info";
	public static final String TYPE_ID = "type_id";
	public static final String TYPE_NAME = "type_name";
	public static final String PARENT_TYPE_ID = "parent_type_id";
	public static final String TYPE_INDEX = "type_index";
	
	public int id;
	public String name;
	public int parentId;
	public int index;
	
}
