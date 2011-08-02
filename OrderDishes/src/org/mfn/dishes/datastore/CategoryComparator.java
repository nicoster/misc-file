package org.mfn.dishes.datastore;

import java.util.Comparator;

import org.mfn.dishes.vo.DishCategoryInfo;

public class CategoryComparator implements Comparator<DishCategoryInfo> {
	public int compare(DishCategoryInfo categoryInfo1, DishCategoryInfo categoryInfo2){
		return categoryInfo1.getIndex() - categoryInfo2.getIndex();
	}
}
