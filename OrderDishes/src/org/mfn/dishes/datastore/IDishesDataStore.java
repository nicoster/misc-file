package org.mfn.dishes.datastore;

import java.util.List;

import org.mfn.dishes.vo.DishCategoryInfo;
import org.mfn.dishes.vo.DishInfo;
import org.mfn.dishes.vo.FlavorInfo;

public interface IDishesDataStore {
	
	/**
	 * add a dish category to data store
	 * @param categoryInfo
	 */
	public void addDishCategory(DishCategoryInfo categoryInfo);
	
	/**
	 * delete a dish category from data store
	 * @param categoryInfo
	 */
	public void delDishCategory(DishCategoryInfo categoryInfo);
	
	/**
	 * edit a dish category from data store
	 * @param oldDishCategoryInfo
	 * @param newDishCategoryInfo
	 */
	public void editDishCategory(DishCategoryInfo oldDishCategoryInfo, DishCategoryInfo newDishCategoryInfo);
	
	/**
	 * check whether category exist
	 * @param categoryCode
	 * @return
	 */
	public boolean isCategoryExists(String categoryCode);
	
	/**
	 * get a dish category by category code
	 * @param categoryCode
	 * @return
	 */
	public DishCategoryInfo getDishCategoryInfo(String categoryCode);
	
	/**
	 * get all the dish category
	 * @return
	 */
	public List<DishCategoryInfo> getAllDishCategoryInfos();
	
	/**
	 * get the dishes number of this category
	 * @return
	 */
	public int getDishesCategoryNumber();
	
	/**
	 * get page number of all the dishes
	 * @return
	 */
	public int getAllDishesPages();
	
	/**
	 * get the dish info on the specified page
	 * @param page page number of all the dishes, start from 0
	 * @return
	 */
	public List<DishInfo> getDishInfosByPage(int page);
	
	/**
	 * get all the dish info of the specified category
	 * @param categoryCode index of the category
	 * @return
	 */
	public List<DishInfo> getDishInfosByCategory(String categoryCode);
	
	/**
	 * get the first
	 * @param categoryCode
	 * @return
	 */
	public int getFirstPageByCategory(String categoryCode);
	
	/**
	 * add a dish info to a category
	 * @param dishCode
	 * @param dishInfo
	 */
	public void addDishInfo(String categoryCode, DishInfo dishInfo);
	
	/**
	 * delete a dish info from a category
	 * @param dishCode
	 */
	public void delDishInfoFromCategory(String categoryCode, String dishCode);
	
	/**
	 * delete a dish info from all the category
	 * @param dishCode
	 */
	public void delDishInfoFromAllCategory(String dishCode);
	
	/**
	 * edit a dish info
	 * @param dishCode
	 * @param newDishInfo
	 */
	public void editDishInfo(String dishCode, DishInfo newDishInfo);
	
	/**
	 * check whether dish info exists in the category
	 * @param dishCode
	 * @param categoryCode
	 */
	public boolean isDishInCategory(String dishCode, String categoryCode);
	
	/**
	 * check whether dish info exist
	 * @param dishCode
	 * @return
	 */
	public boolean isDishInfoExist(String dishCode);
	
	/**
	 * get a dish info
	 * @param dishCode
	 * @return
	 */
	public DishInfo getDishInfo(String dishCode);
	
	/**
	 * get all dish infos
	 * @return
	 */
	public List<DishInfo> getAllDishInfos();
	
	/**
	 * add a flavor info
	 * @param flavorId
	 * @param flavorInfo
	 */
	public void addFlavorInfo(String flavorId, FlavorInfo flavorInfo);
	
	/**
	 * remove a flavor info
	 * @param flavorId
	 */
	public void delFlavorInfo(String flavorId);
	
	/**
	 * edit a flavor info
	 * @param oldFlavorInfo
	 * @param newFlavorInfo
	 */
	public void editFlavorInfo(FlavorInfo oldFlavorInfo, FlavorInfo newFlavorInfo);
	
	/**
	 * check whether flavor info exist
	 * @param flavorId
	 * @return
	 */
	public boolean isFlavorInfoExist(String flavorId);
	
	/**
	 * get a flavor info
	 * @param flavorId
	 * @return
	 */
	public FlavorInfo getFlavorInfo(String flavorId);
	
	/**
	 * get all flavor infos
	 * @return
	 */
	public List<FlavorInfo> getAllFlavorInfos();	
	
	/**
	 * clear all dishes data
	 */
	public void clearDishesData();
}
