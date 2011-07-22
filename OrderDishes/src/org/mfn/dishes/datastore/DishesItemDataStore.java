package org.mfn.dishes.datastore;

import java.util.ArrayList;
import java.util.List;

import org.mfn.dishes.Constants;
import org.mfn.dishes.util.DishesDataAdapter;
import org.mfn.dishes.vo.DishInfoObj;
import org.mfn.dishes.vo.GridDishesInfo;

import android.util.Log;

public class DishesItemDataStore implements IDishesItemDataStore{
	private List<GridDishesInfo> mGridDishesInfos;
	
	public List<GridDishesInfo> getDishesInfos(){
		return mGridDishesInfos;
	}
	
	public DishesItemDataStore(){
		this.mGridDishesInfos = new ArrayList<GridDishesInfo>();
		this.initData();
	}
	private void initData(){
		
		DishesDataAdapter adapter = DishesDataAdapter.getInstance();

		DishInfoObj[] objs = adapter.listDishesInfo(-1);

		for (DishInfoObj obj : objs) {
			Log.i(Constants.APP_TAG, obj.id + "\t" + obj.name + "\t" + obj.price);
			GridDishesInfo dishesInfo = new GridDishesInfo(obj.id, obj.name, "", obj.price, obj.unit,
					Constants.DISHES_IMAGE_PATH + "000" + obj.id + "t.bmp");
			mGridDishesInfos.add(dishesInfo);
		}
	}
	
	
}
