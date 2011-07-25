package org.mfn.dishes.datastore;

import java.util.ArrayList;

import org.mfn.dishes.vo.DishInfoObj;

public class PageGridDishesInfo {
	
	public static final int PAGE_DISH_NUM = 8;
	
	public int page;			//总数第5页
	public int page_in_type;  //热菜第一页
	public String dish_type_id;
	public String dish_type_name;
	
	public ArrayList<DishInfoObj> dishesList = new ArrayList();
	
	public void addDishes(DishInfoObj obj){
		dishesList.add(obj);
	}
	
}
