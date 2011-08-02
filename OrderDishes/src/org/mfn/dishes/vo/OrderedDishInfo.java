package org.mfn.dishes.vo;

import org.mfn.dishes.datastore.DataStore;

public class OrderedDishInfo {
	private DishInfo mDishInfo;
	private int mOrderedNumber;
	private float mTotalPrice;
	private String mCategoryCode;
	private String mCategoryName;
	
	public OrderedDishInfo(DishInfo dishInfo, int orderedNumber) {
		this.mDishInfo = dishInfo;
		this.mOrderedNumber = orderedNumber;
		this.mTotalPrice = dishInfo.getPrice() * mOrderedNumber;
		this.mCategoryCode = dishInfo.getCategoryCodes().get(0);
		this.mCategoryName = DataStore.getInstance().getDishesDataStore().getDishCategoryInfo(mCategoryCode).getDishCategoryName();
	}

	public DishInfo getDishInfo() {
		return mDishInfo;
	}

	public void setDishInfo(DishInfo mDishInfo) {
		this.mDishInfo = mDishInfo;
	}

	public int getOrderedNumber() {
		return mOrderedNumber;
	}

	public void setOrderedNumber(int mOrderedNumber) {
		this.mOrderedNumber = mOrderedNumber;
	}

	public float getTotalPrice() {
		return mTotalPrice;
	}

	public void setTotalPrice(float mTotalPrice) {
		this.mTotalPrice = mTotalPrice;
	}

	public String getCategoryCode() {
		return mCategoryCode;
	}

	public void setCategoryCode(String mCategoryCode) {
		this.mCategoryCode = mCategoryCode;
	}

	public String getCategoryName() {
		return mCategoryName;
	}

	public void setCategoryName(String mCategoryName) {
		this.mCategoryName = mCategoryName;
	}
	
}
