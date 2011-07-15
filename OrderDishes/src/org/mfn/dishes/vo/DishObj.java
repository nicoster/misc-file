package org.mfn.dishes.vo;

public class DishObj {
	
	public static final String TABLE_NAME = "dish_info";
	public static final String DISH_ID = "dish_id";
	public static final String DISH_QUERY_CODE = "query_code";
	public static final String DISH_QUERY_CODE_2 = "query_code_2";
	public static final String DISH_NAME = "dish_name";
	public static final String DISH_SIZE = "dish_size";
	public static final String DISH_UNIT = "dish_unit";
	public static final String DISH_PRICE = "dish_price";
	public static final String DISH_TYPE = "dish_type";
	public static final String DISH_VARIABLE_PRICE = "dish_variable_price";
	public static final String DISH_COOK_TYPE = "dish_cook_type";
	public static final String DISH_FLAG = "dish_flag";
	public static final String DISH_COST = "dish_cost";
	public static final String DISH_IMAGE = "dish_image";
	
	public int id;
	public String query_code;
	public String query_code2;
	public String name;
	public int size;
	public String unit;
	public float price;
	public int type;
	public boolean variable_price;
	public String cook_type;
	public int flag;
	public float cost;
	public String image;
	
}
