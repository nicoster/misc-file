package org.mfn.dishes.vo;

public class FlavorInfoObj {
	
	public static final String TABLE_NAME = "flavor_info";
	public static final String FLAVOR_ID = "flavor_id";
	public static final String FLAVOR_NAME = "flavor_name";
	public static final String IS_COOK_STYLE = "is_cook_style";
	
	public String id;
	public String name;
	public boolean is_cook_style;
	
	public String toString()
	{
		return "{id:" + id + ", name:" + name + ", is_cook_style:" + is_cook_style + "}";
	}
}
