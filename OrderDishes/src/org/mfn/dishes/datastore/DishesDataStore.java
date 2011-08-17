package org.mfn.dishes.datastore;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.TreeMap;
import java.util.TreeSet;

import org.mfn.dishes.vo.DishCategoryInfo;
import org.mfn.dishes.vo.DishInfo;
import org.mfn.dishes.vo.FlavorInfo;

public class DishesDataStore implements IDishesDataStore {
	private TreeMap<String, DishInfo> mDishesInfos;
	private TreeSet<DishCategoryInfo> mCategoryInfos;
	private HashMap<String, FlavorInfo> mFlavorInfos;
	
	public DishesDataStore(){
		this.mDishesInfos = new TreeMap<String, DishInfo>();
		this.mCategoryInfos = new TreeSet<DishCategoryInfo>(new CategoryComparator());
		this.mFlavorInfos = new HashMap<String, FlavorInfo>();
	}
	
	/**
	 * add a dish category to data store
	 * @param categoryInfo
	 */
	public void addDishCategory(DishCategoryInfo categoryInfo){
		if(this.mCategoryInfos.contains(categoryInfo)){
			return;
		}
		this.mCategoryInfos.add(categoryInfo);
	}
	
	/**
	 * delete a dish category from data store
	 * @param categoryInfo
	 */
	public void delDishCategory(DishCategoryInfo categoryInfo){
		if(this.mCategoryInfos.contains(categoryInfo)){
			this.mCategoryInfos.remove(categoryInfo);
		}
	}
	
	/**
	 * edit a dish category from data store
	 * @param oldDishCategoryInfo
	 * @param newDishCategoryInfo
	 */
	public void editDishCategory(DishCategoryInfo oldDishCategoryInfo, DishCategoryInfo newDishCategoryInfo){
		if(this.mCategoryInfos.contains(oldDishCategoryInfo)){
			this.mCategoryInfos.remove(oldDishCategoryInfo);
			this.mCategoryInfos.add(newDishCategoryInfo);
		}
	}
	
	/**
	 * check whether category exist
	 * @param categoryCode
	 * @return
	 */
	public boolean isCategoryExists(String categoryCode){
		Iterator<DishCategoryInfo> iterator = this.mCategoryInfos.iterator();
		DishCategoryInfo dishCategoryInfo = null;
		while(iterator.hasNext()){
			dishCategoryInfo = iterator.next();
			if(dishCategoryInfo.getDishCategoryCode().equalsIgnoreCase(categoryCode)){
				return true;
			}
		}
		return false;
	}
	
	/**
	 * get a dish category by category code
	 * @param categoryCode
	 * @return
	 */
	public DishCategoryInfo getDishCategoryInfo(String categoryCode){
		DishCategoryInfo dishCategoryInfo = null;
		Iterator<DishCategoryInfo> iterator = this.mCategoryInfos.iterator();
		while(iterator.hasNext()){
			dishCategoryInfo = iterator.next();
			if(dishCategoryInfo.getDishCategoryCode().equalsIgnoreCase(categoryCode)){
				break;
			}
		}
		return dishCategoryInfo;
	}
	
	/**
	 * get all the dish category
	 * @return
	 */
	public List<DishCategoryInfo> getAllDishCategoryInfos(){
		ArrayList<DishCategoryInfo> categoryInfos = new ArrayList<DishCategoryInfo>();
		Iterator<DishCategoryInfo> iterator = this.mCategoryInfos.iterator();
		while(iterator.hasNext()){
			categoryInfos.add(iterator.next());
		}
		return categoryInfos;
	}
	
	/**
	 * get the dishes number of this category
	 * @return
	 */
	public int getDishesCategoryNumber(){
		if(this.mCategoryInfos == null){
			return 0;
		}
		return this.mCategoryInfos.size();
	}
	
	/**
	 * get page number of all the dishes
	 * @return
	 */
	public int getAllDishesPages(){
		Iterator<DishCategoryInfo> iterator = this.mCategoryInfos.iterator();
		int pages = 0;
		int pagesInCategory = 0;
		DishCategoryInfo categoryInfo = null;
		while(iterator.hasNext()){			
			categoryInfo = iterator.next();
			
			pagesInCategory = categoryInfo.getPages();
			
			if(pagesInCategory == 0){
				categoryInfo.setStartPage(-1);
			}else{
				categoryInfo.setStartPage(pages);
			}			
			pages += pagesInCategory;
		}
		return pages;
	}
	
	/**
	 * get the dish info on the specified page
	 * @param page page number of all the dishes, start from 0
	 * @return
	 */
	public List<DishInfo> getDishInfosByPage(int page){
		List<DishInfo> dishInfos = new ArrayList<DishInfo>();
		Iterator<DishCategoryInfo> iterator = this.mCategoryInfos.iterator();
		DishCategoryInfo categoryInfo = null;
		int startPage = -1;
		while(iterator.hasNext()){
			categoryInfo = iterator.next();			
			startPage = categoryInfo.getStartPage();
			if(startPage <= page && page < startPage + categoryInfo.getPages() && startPage != -1){
				dishInfos = categoryInfo.getDishInfos(page);
				break;
			}
		}
		return dishInfos;
	}
	
	/**
	 * get all the dish info of the specified category
	 * @param categoryCode code of the category
	 * @return
	 */
	public List<DishInfo> getDishInfosByCategory(String categoryCode){
		List<DishInfo> dishInfos = new ArrayList<DishInfo>();
		Iterator<DishCategoryInfo> iterator = this.mCategoryInfos.iterator();
		DishCategoryInfo categoryInfo = null;
		while(iterator.hasNext()){
			categoryInfo = iterator.next();
			if(categoryInfo.getDishCategoryCode().equalsIgnoreCase(categoryCode)){
				dishInfos = categoryInfo.getAllDishInfos();
				break;
			}
		}
		return dishInfos;
	}
	
	/**
	 * get the first
	 * @param categroyName
	 * @return
	 */
	public int getFirstPageByCategory(String categoryCode){
		Iterator<DishCategoryInfo> iterator = this.mCategoryInfos.iterator();
		DishCategoryInfo categoryInfo = null;
		int firstPage = -1;
		while(iterator.hasNext()){
			categoryInfo = iterator.next();
			if(categoryInfo.getDishCategoryCode().equalsIgnoreCase(categoryCode)){
				firstPage = categoryInfo.getStartPage();
				break;
			}
		}
		return firstPage;
	}
	/*================== Below is Dish info ========================================================*/
	/**
	 * add a dish info to data store
	 * @param categoryCode
	 * @param dishInfo
	 */
	public void addDishInfo(String categoryCode, DishInfo dishInfo){
		//add dish info to list
		dishInfo.addCategory(categoryCode);		
		this.mDishesInfos.put(dishInfo.getCode(), dishInfo);		
		
		//add dish info to category info
		DishCategoryInfo categoryInfo = this.getDishCategoryInfo(categoryCode);
		if(categoryInfo != null){
			categoryInfo.addDishInfo(dishInfo);
		}		
	}
	
	/**
	 * delete a dish info from a category
	 * @param dishCode
	 */
	public void delDishInfoFromCategory(String categoryCode, String dishCode){
		//delete dish info from category
		DishCategoryInfo categoryInfo = this.getDishCategoryInfo(categoryCode);
		if(categoryInfo != null){
			categoryInfo.delDishInfo(dishCode);
		}		
		
		DishInfo dishInfo = getDishInfo(dishCode);
		if(dishInfo != null){
			dishInfo.delCategory(categoryCode);
		}
	}
	
	/**
	 * delete a dish info from all the category
	 */
	public void delDishInfoFromAllCategory(String dishCode){
		DishInfo dishInfo = this.getDishInfo(dishCode);
		if(dishInfo != null){
			List<String> categoryList = dishInfo.getCategoryCodes();
			DishCategoryInfo categoryInfo = null;
			for(int i = 0; i < categoryList.size(); i++){
				categoryInfo = getDishCategoryInfo(categoryList.get(i));
				if(categoryInfo != null){
					categoryInfo.delDishInfo(dishCode);
				}
			}
		}		
	}
	
	/**
	 * edit a dish info
	 * @param dishCode
	 * @param newDishInfo
	 */
	public void editDishInfo(String dishCode, DishInfo newDishInfo){
		if(this.mDishesInfos.containsKey(dishCode)){
			//update the dish info in all categories
			this.updateDishinfoForCategory(this.mDishesInfos.get(dishCode), newDishInfo);
			
			this.mDishesInfos.remove(dishCode);
			this.mDishesInfos.put(dishCode, newDishInfo);			
		}
	}
	
	/**
	 * check whether dish info exists in the category
	 * @param dishCode
	 * @param categoryCode
	 */
	public boolean isDishInCategory(String dishCode, String categoryCode){
		DishInfo dishInfo = this.mDishesInfos.get(dishCode);
		if(dishInfo != null && dishInfo.getCategoryCodes().contains(categoryCode)){
			return true;
		}
		return false;
	}
	
	/**
	 * check whether dish info exists
	 * @param dishCode
	 */
	public boolean isDishInfoExist(String dishCode){
		if(this.mDishesInfos.containsKey(dishCode)){
			return true;
		}
		return false;
	}
	
	/**
	 * get a dish info
	 * @param dishCode
	 * @return
	 */
	public DishInfo getDishInfo(String dishCode){
		DishInfo dishInfo = null;
		if(this.mDishesInfos.containsKey(dishCode)){
			dishInfo = this.mDishesInfos.get(dishCode);
		}
		return dishInfo;
	}
	
	/**
	 * get all dish infos
	 * @return
	 */
	public List<DishInfo> getAllDishInfos(){
		ArrayList<DishInfo> dishInfos = new ArrayList<DishInfo>();
		Iterator<DishInfo> iterator = this.mDishesInfos.values().iterator();
		while(iterator.hasNext()){
			dishInfos.add(iterator.next());
		}
		return dishInfos;
	}
	
	/**
	 * update the dish info for category
	 * @param oldDishInfo
	 * @param newDishInfo
	 */
	private void updateDishinfoForCategory(DishInfo oldDishInfo, DishInfo newDishInfo){
		List<String> categoryCodes = newDishInfo.getCategoryCodes();
		DishCategoryInfo categoryInfo = null;
		for(int i = 0; i < categoryCodes.size(); i++){
			categoryInfo = this.getDishCategoryInfo(categoryCodes.get(i));
			if(categoryInfo != null){
				categoryInfo.editDishInfo(oldDishInfo, newDishInfo);
			}			
		}
	}
	
	/**
	 * add a flavor info
	 * @param flavorId
	 * @param flavorInfo
	 */
	public void addFlavorInfo(String flavorId, FlavorInfo flavorInfo){
		if(this.mFlavorInfos.containsKey(flavorId)){
			return;
		}
		this.mFlavorInfos.put(flavorId, flavorInfo);
	}
	
	/**
	 * remove a flavor info
	 * @param flavorId
	 */
	public void delFlavorInfo(String flavorId){
		if(this.mFlavorInfos.containsKey(flavorId)){
			this.mFlavorInfos.remove(flavorId);
		}
	}
	
	/**
	 * edit a flavor info
	 * @param oldFlavorInfo
	 * @param newFlavorInfo
	 */
	public void editFlavorInfo(FlavorInfo oldFlavorInfo, FlavorInfo newFlavorInfo){
		if(this.mFlavorInfos.containsKey(oldFlavorInfo.getId()) && !this.mFlavorInfos.containsKey(newFlavorInfo.getId())){
			this.mFlavorInfos.remove(oldFlavorInfo.getId());
			this.mFlavorInfos.put(newFlavorInfo.getId(), newFlavorInfo);
		}
	}
	
	/**
	 * check whether flavor info exist
	 * @param flavorId
	 * @return
	 */
	public boolean isFlavorInfoExist(String flavorId){
		if(this.mFlavorInfos.containsKey(flavorId)){
			return true;
		}
		return false;
	}
	
	/**
	 * get a flavor info
	 * @param flavorId
	 * @return
	 */
	public FlavorInfo getFlavorInfo(String flavorId){
		if(this.mFlavorInfos.containsKey(flavorId)){
			return this.mFlavorInfos.get(flavorId);
		}
		return null;
	}
	
	/**
	 * get all flavor infos
	 * @return
	 */
	public List<FlavorInfo> getAllFlavorInfos(){
		ArrayList<FlavorInfo> flavorInfos = new ArrayList<FlavorInfo>();
		Iterator<FlavorInfo> iterator = this.mFlavorInfos.values().iterator();
		while (iterator.hasNext()) {
			flavorInfos.add(iterator.next());			
		}
		return flavorInfos;
	}
	
	/**
	 * clear all dishes data
	 */
	public void clearDishesData(){
		this.mCategoryInfos.clear();
		this.mDishesInfos.clear();
		this.mFlavorInfos.clear();
	}
	
}
