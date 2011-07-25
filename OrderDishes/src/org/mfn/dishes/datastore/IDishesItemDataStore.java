package org.mfn.dishes.datastore;

import java.util.List;

public interface IDishesItemDataStore {
	
	public List<PageGridDishesInfo> getPageDishesInfos();
	
	public List<TypeGridDishesInfo> getDisheTypePageList();

}
