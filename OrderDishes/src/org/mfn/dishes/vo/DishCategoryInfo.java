package org.mfn.dishes.vo;

import java.util.ArrayList;
import java.util.List;

import org.mfn.dishes.Constants;

import android.util.Log;

public class DishCategoryInfo {
	private String mDishCategoryCode; //type code, use id from DB	
	private String mDishCategoryName; //type name
	private String mParentCode; //the parent type code
	private int mIndex; //the category index, used to order the dishes category
	private int mStartPage; //the first page number in all dishes, for example there are 20 pages, this category is from 12 pages
	private int mItemsPerPage = Constants.DISHES_PER_PAGE; //how many dish item in  a page
	private ArrayList<DishInfo> mDishInfoList = null;
	
	public DishCategoryInfo(String categoryCode, String categoryName, String parentCode, int index){
		this.mDishCategoryCode = categoryCode;
		this.mDishCategoryName = categoryName;
		this.mParentCode = parentCode;
		this.mIndex = index;
		this.mDishInfoList = new ArrayList<DishInfo>();
	}
	
	/**
	 * add a dish info to this category
	 * @param dishCode
	 * @param dishInfo
	 */
	public void addDishInfo(DishInfo dishInfo){
		if(this.mDishInfoList.contains(dishInfo)){
			return;
		}
		this.mDishInfoList.add(dishInfo);
	}
	
	/**
	 * remove a dish info from this category
	 * @param dishInfo
	 */
	public void delDishInfo(String dishCode){
		DishInfo dishInfo = getDishInfo(dishCode);
		if(dishInfo != null){
			this.mDishInfoList.remove(dishInfo);
		}
	}
	
	/**
	 * edit a dish info
	 * @param oldDishInfo
	 * @param newDishInfo
	 */
	public void editDishInfo(DishInfo oldDishInfo, DishInfo newDishInfo){
		if(this.mDishInfoList.contains(oldDishInfo) && !this.mDishInfoList.contains(newDishInfo)){
			this.mDishInfoList.remove(oldDishInfo);
			this.mDishInfoList.add(newDishInfo);
		}
	}
	
	/**
	 * check whether dish in this category
	 * @param dishCode
	 * @return
	 */
	public boolean isDishExists(String dishCode){
		DishInfo dishInfo = getDishInfo(dishCode);
		if(dishInfo == null){
			return false;
		}
		return true;
	}
	
	/**
	 * get dish info by dish code
	 * @param dishCode
	 */
	private DishInfo getDishInfo(String dishCode){
		DishInfo dishInfo = null;
		for(int i = 0; i < this.mDishInfoList.size(); i++){
			dishInfo = this.mDishInfoList.get(i);
			if(dishCode.equals(dishInfo.getCode())){
				break;
			}
		}
		return dishInfo;
	}
	
	/**
	 * get all dishes
	 * @return
	 */
	public List<DishInfo> getAllDishInfos(){
		return this.mDishInfoList;
	}
	
	public int getDishNumber(){
		if(this.mDishInfoList == null){
			return 0;
		}
		return this.mDishInfoList.size();
	}
	
	/**
	 * get how many pages in this category
	 * @param itemsPerPage
	 * @return
	 */
	public int getPages(){
		int dishNumber = this.getDishNumber();		
		int pages = dishNumber / mItemsPerPage;
		if(dishNumber % mItemsPerPage > 0) {
			pages++;
		}
		Log.d("DishCategoryInfo", "getPage items = " + dishNumber + ", page = " + pages);
		return pages;
	}
	
	/**
	 * get dishes of the page
	 * @param page the whole page of all dishes
	 * @return
	 */
	public List<DishInfo> getDishInfos(int page){
		ArrayList<DishInfo> dishInfos = new ArrayList<DishInfo>();
		int dishNumber = getDishNumber();
		int startNumber = (page - mStartPage) * mItemsPerPage; 
		int endNumber = Math.min(startNumber + mItemsPerPage, dishNumber);
		for(int i = startNumber; i < endNumber; i++){
			dishInfos.add(this.mDishInfoList.get(i));
		}
		
		return dishInfos;
	}
	
	
	public String getDishCategoryCode() {
		return mDishCategoryCode;
	}
	public void setDishCategoryCode(String mDishCategoryCode) {
		this.mDishCategoryCode = mDishCategoryCode;
	}
	public String getDishCategoryName() {
		return mDishCategoryName;
	}
	public void setDishCategoryName(String mDishCategoryName) {
		this.mDishCategoryName = mDishCategoryName;
	}
	public String getParentCode() {
		return mParentCode;
	}
	public void setParentCode(String mParentCode) {
		this.mParentCode = mParentCode;
	}
	public int getIndex() {
		return mIndex;
	}
	public void setIndex(int mIndex) {
		this.mIndex = mIndex;
	}

	public int getStartPage() {
		return mStartPage;
	}

	public void setStartPage(int mStartPage) {
		this.mStartPage = mStartPage;
	}

	public int getItemsPerPage() {
		return mItemsPerPage;
	}

	public void setItemsPerPage(int mItemsPerPage) {
		this.mItemsPerPage = mItemsPerPage;
	}
	
}
