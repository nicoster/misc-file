package org.mfn.dishes.datastore;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeSet;

import org.mfn.dishes.vo.OrderedDishInfo;

public class OrderedDishInfoDataStore implements IOrderedDishesDataStore {
	private static OrderedDishInfoDataStore mInstance = null;
	private List<OrderedDishInfo> mOrderedDishInfos = null;
	
	public OrderedDishInfoDataStore(){
		this.mOrderedDishInfos = new ArrayList<OrderedDishInfo>();
	}
	
	public static OrderedDishInfoDataStore getInstance(){
		if(mInstance == null){
			mInstance = new OrderedDishInfoDataStore();
		}
		return mInstance;
	}

	/**
	 * add a ordered dish info to data store
	 * @param orderedDishInfo
	 */
	public void addDishesInfo(OrderedDishInfo orderedDishInfo){
		if(this.mOrderedDishInfos.contains(orderedDishInfo)){
			return;
		}
		this.mOrderedDishInfos.add(orderedDishInfo);
	}
	
	/**
	 * delete a ordered dish info from data store
	 * @param orderedDishInfo
	 */
	public void delDishesInfo(OrderedDishInfo orderedDishInfo){
		if(this.mOrderedDishInfos.contains(orderedDishInfo)){
			this.mOrderedDishInfos.remove(orderedDishInfo);
		}
	}
	
	/**
	 * update a ordered dish info
	 * @param oldOrderedDishInfo
	 * @param newOrderedDishInfo
	 */
	public void editDishesInfo(OrderedDishInfo oldOrderedDishInfo, OrderedDishInfo newOrderedDishInfo){
		if(this.mOrderedDishInfos.contains(oldOrderedDishInfo)){
			this.mOrderedDishInfos.remove(oldOrderedDishInfo);
			this.mOrderedDishInfos.add(newOrderedDishInfo);
		}
	}
	
	/**
	 * get all the ordered dish info
	 * @return
	 */
	public List<OrderedDishInfo> getOrderedDishInfo(){
		ArrayList<OrderedDishInfo> orderedDishInfos = new ArrayList<OrderedDishInfo>();
		TreeSet<OrderedDishInfo> orderedDishesSet = new TreeSet<OrderedDishInfo>(new OrderedDishinfoComparator());
		for(OrderedDishInfo orderedDishInfo : this.mOrderedDishInfos){
			orderedDishesSet.add(orderedDishInfo);
		}
		Iterator<OrderedDishInfo> iterator = orderedDishesSet.iterator();
		while (iterator.hasNext()) {
			orderedDishInfos.add(iterator.next());			
		}
		return orderedDishInfos;
	}
	
	/**
	 * get the total price ordered
	 * @return
	 */
	public float getTotlePrice(){
		float totalPrice = 0;
		Iterator<OrderedDishInfo> iterator = this.mOrderedDishInfos.iterator();
		OrderedDishInfo dishInfo = null;
		while(iterator.hasNext()){
			dishInfo = iterator.next();
			totalPrice += dishInfo.getTotalPrice();
		}
		return totalPrice;
	}
	
	/**
	 * clear all ordered dishes data
	 */
	public void clearOrderedDishesData(){
		this.mOrderedDishInfos.clear();
	}

}
