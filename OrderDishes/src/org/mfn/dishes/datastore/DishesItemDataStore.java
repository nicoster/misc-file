package org.mfn.dishes.datastore;

import java.util.ArrayList;
import java.util.List;

import org.mfn.dishes.vo.GridDishesInfo;

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
		this.mGridDishesInfos.add(new GridDishesInfo(1, "A", "A comment", 100, "yuan/person", null));
		this.mGridDishesInfos.add(new GridDishesInfo(2, "B", "B comment", 200, "yuan/person", null));
		this.mGridDishesInfos.add(new GridDishesInfo(3, "C", "C comment", 120, "yuan/person", null));
		this.mGridDishesInfos.add(new GridDishesInfo(4, "D", "D comment", 140, "yuan/person", null));
		this.mGridDishesInfos.add(new GridDishesInfo(5, "E", "E comment", 160, "yuan/person", null));
	}
}
