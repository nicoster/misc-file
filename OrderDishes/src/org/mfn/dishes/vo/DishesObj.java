package org.mfn.dishes.vo;

public class DishesObj {
	
	public static final String TABLE_NAME = "dishes_info";
	public static final String DISHES_ID = "dishes_id";
	public static final String DISHES_QUERY_CODE = "query_code";
	public static final String DISHES_QUERY_CODE_2 = "query_code_2";
	public static final String DISHES_NAME = "dishes_name";
	public static final String DISHES_SIZE = "dishes_size";
	public static final String DISHES_UNIT = "dishes_unit";
	public static final String DISHES_PRICE = "dishes_price";
	public static final String DISHES_TYPE = "dishes_type";
	public static final String DISHES_VARIABLE_PRICE = "dishes_variable_price";
	public static final String DISHES_COOK_TYPE = "dishes_cook_type";
	public static final String DISHES_FLAG = "dishes_flag";
	public static final String DISHES_COST = "dishes_cost";
	public static final String DISHES_IMAGE = "dishes_image";
	
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
