package org.mfn.dishes.datastore;

import java.util.List;

import org.mfn.dishes.vo.OrderedDishInfo;

public interface IOrderedDishesDataStore {
	/**
	 * add a ordered dish info to data store
	 * @param orderedDishInfo
	 */
	public void addDishesInfo(OrderedDishInfo orderedDishInfo);
	
	/**
	 * delete a ordered dish info from data store
	 * @param orderedDishInfo
	 */
	public void delDishesInfo(OrderedDishInfo orderedDishInfo);
	
	/**
	 * update a ordered dish info
	 * @param oldOrderedDishInfo
	 * @param newOrderedDishInfo
	 */
	public void editDishesInfo(OrderedDishInfo oldOrderedDishInfo, OrderedDishInfo newOrderedDishInfo);
	
	/**
	 * get all the ordered dish info
	 * @return
	 */
	public List<OrderedDishInfo> getOrderedDishInfo();
	
	/**
	 * get the total price ordered
	 * @return
	 */
	public float getTotlePrice();
}
