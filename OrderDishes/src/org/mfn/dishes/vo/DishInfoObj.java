package org.mfn.dishes.vo;

public class DishInfoObj {
	
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
	
	public static class CookingInfo
	{
		String style;
		float price;
	};
	
	public String id;
	public String query_code;
	public String query_code2;
	public String name;
	public String size;
	public String unit;
	public float price;
	public String type;
	public boolean variable_price;
	CookingInfo[] cooking_info;
	public int flag;
	public float cost;
	public float gross_profit;
	public String name_en, name_jp;
	public String image;
	public boolean isPackage(){return (flag & 0x0001) != 0;} //是否套餐
	public boolean isCustom(){return (flag & 0x0002) != 0;} //自定义菜品
	public boolean isByQuantity(){return (flag & 0x0004) != 0;} //称重菜品
	public boolean isPackage2() {return (flag & 0x0020) != 0;} //200904 拼菜套餐标志. 不是很确定这个标志位的意思. 先用这个函数名
	//Note: 该函数的定义是 是否可打折, 和协议中的定义相反. 协议中的定义是 "不可打折标志" true 表示不可打折
	public boolean isDiscountable() {return (flag & 0x0040) == 0;} //2010 可打折标志 true 表示可打折
	public boolean isNew(){ return (flag & 0x0080) != 0;}	// 新菜
	public boolean isSpecial() {return (flag & 0x0100) != 0;} // 特色菜
	public boolean hasMultiCookingStyle() {return cooking_info != null && cooking_info.length > 1;}	// 是否多做法
	public boolean setCookingInfo(String styles, String prices)
	{
		// styles, prices are all delimited by comma.
		//TODO: parse and set cooking_info
		return false;
	}
}
