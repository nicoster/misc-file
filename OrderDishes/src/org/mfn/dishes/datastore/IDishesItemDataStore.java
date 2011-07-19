package org.mfn.dishes.datastore;

import java.util.List;

import org.mfn.dishes.vo.GridDishesInfo;

public interface IDishesItemDataStore {
	public List<GridDishesInfo> getDishesInfos();

}
