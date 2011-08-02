package org.mfn.dishes.datastore;

import java.util.Comparator;

import org.mfn.dishes.vo.OrderedDishInfo;

public class OrderedDishinfoComparator implements Comparator<OrderedDishInfo> {

	public int compare(OrderedDishInfo dishInfo1, OrderedDishInfo dishInfo2){		
//		if((dishInfo1.getCategoryCode().equalsIgnoreCase(dishInfo2.getCategoryCode())) 
//				&& (dishInfo1.getDishInfo().getCode().equalsIgnoreCase(dishInfo2.getDishInfo().getCode()))){
//			return 0;
//		}
		return dishInfo1.getDishInfo().getCode().compareToIgnoreCase(dishInfo2.getDishInfo().getCode());
	}
}
