package org.mfn.dishes.datastore;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.mfn.dishes.Constants;
import org.mfn.dishes.util.DishesDataAdapter;
import org.mfn.dishes.vo.DishInfoObj;
import org.mfn.dishes.vo.DishTypeObj;

import android.util.Log;

public class DishesItemDataStore implements IDishesItemDataStore {

	private List<PageGridDishesInfo> mPageGridDishesInfos =null;
	
	private HashMap<String, TypeGridDishesInfo>mTypeGridDishesInfos=null ;
	private List<TypeGridDishesInfo>mTypeGridDishesInfoList=null ;
	
	private DishInfoObj[] allDishInfo = null;
	private Map<String, DishTypeObj> allDishTypeInfo = null;

	public List<PageGridDishesInfo> getPageDishesInfos() {
		return mPageGridDishesInfos;
	}
	
	public List<TypeGridDishesInfo> getDisheTypePageList(){
		return mTypeGridDishesInfoList;
	}
	
	public DishesItemDataStore() {
		this.mPageGridDishesInfos = new ArrayList<PageGridDishesInfo>();
		this.mTypeGridDishesInfos = new HashMap<String, TypeGridDishesInfo>();
		this.mTypeGridDishesInfoList = new ArrayList<TypeGridDishesInfo>();
		
		this.initData();
	}
	
	private void initData() {

		DishesDataAdapter adapter = DishesDataAdapter.getInstance();
		if (allDishInfo == null) {
			allDishInfo = adapter.listDishesInfo(-1);
		}

		if (allDishTypeInfo == null) {
			allDishTypeInfo = adapter.listDishTypesMap();
		}
		
		for (DishInfoObj obj : allDishInfo) {
			String dish_type_id = obj.type;
			
			if (dish_type_id != null && dish_type_id.equals("0")){
				continue;
			}
			
			DishTypeObj dishTypeObj = allDishTypeInfo.get(dish_type_id);
			if (dishTypeObj == null){
				continue;
			}
			
			TypeGridDishesInfo typeInfo = mTypeGridDishesInfos.get(dish_type_id);
			if (typeInfo == null){
				typeInfo = new TypeGridDishesInfo();
				typeInfo.dish_type_id =dish_type_id;
				typeInfo.dish_type_name = dishTypeObj.name;
				typeInfo.addDishes(obj);
				mTypeGridDishesInfos.put(dish_type_id, typeInfo);
				mTypeGridDishesInfoList.add(typeInfo);
			}else{
				typeInfo.addDishes(obj);
			}
		}
		
		setGridDeshesInfoToPages();
	}
	
	private int countPages(int allNumber) {
		int pageNum = allNumber / PageGridDishesInfo.PAGE_DISH_NUM;
		if (allNumber % PageGridDishesInfo.PAGE_DISH_NUM > 0) {
			pageNum++;
		}
		return pageNum;
	}
	
	private void setGridDeshesInfoToPages() {
		int current_page = 0;
		for (TypeGridDishesInfo typeInfo : mTypeGridDishesInfoList) {
			List list = typeInfo.dishesList;
			int allTypeDishesNum = list.size();
			
			int typePages =countPages(allTypeDishesNum);
					
			typeInfo.pages = typePages;
			typeInfo.first_page = current_page;

			for (int i = 0; i < typePages; i++) {
				PageGridDishesInfo pageInfo = new PageGridDishesInfo();
				pageInfo.page = current_page;
				current_page++;

				pageInfo.dish_type_id = typeInfo.dish_type_id;
				pageInfo.dish_type_name = typeInfo.dish_type_name;
				pageInfo.page_in_type = i;

				for (int j = 0; j < PageGridDishesInfo.PAGE_DISH_NUM; j++) {
					int index = i * PageGridDishesInfo.PAGE_DISH_NUM + j;
					if (index < typeInfo.dishesList.size()) {
						pageInfo.addDishes(typeInfo.dishesList.get(index));
					}
				}

				mPageGridDishesInfos.add(pageInfo);
				Log.w(Constants.APP_TAG, "Page:" + pageInfo.page + " Page in Type:" + pageInfo.page_in_type + " ID="
						+ pageInfo.dish_type_id + " Name:" + pageInfo.dish_type_name+" bumber="+pageInfo.dishesList.size());
			}

		}
	}
	
}
