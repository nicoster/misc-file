package org.mfn.dishes.vo;

import java.util.Date;

public class DishObj {
	public int index;
	public String id;
	public String dishInfoId;
	public String state;		// 菜品状态
	public float count;
	public String flavorIds;	// delimited by comma
	public int servingMode;		// 出菜方式	enum SERVING_MODE{SM_NOW = 0 /*即起*/, SM_ON_DEMAND /*叫起*/}
	public Date start;
	public float price;
	public String waiter;
	public String unit;
	public String operator;
}
