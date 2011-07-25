package org.mfn.dishes.datastore;

import java.util.ArrayList;

import org.mfn.dishes.vo.DishInfoObj;

public class TypeGridDishesInfo {

	public int pages;
	public int first_page;

	public String dish_type_id;
	public String dish_type_name;

	public ArrayList<DishInfoObj> dishesList = new ArrayList();

	public void addDishes(DishInfoObj obj) {
		dishesList.add(obj);
		countPages();
	}

	private void countPages() {
		pages = dishesList.size() / PageGridDishesInfo.PAGE_DISH_NUM + 1;
	}
}
