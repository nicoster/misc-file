package org.mfn.dishes.vo;

import java.util.Date;

public class DeskDishInfo {
	private String mId;
	private String mDishInfoId;
	private String mState;		// 菜品状态
	private float mCount;
	private String mFlavorIds;	// delimited by comma
	private int mServingMode;		// 出菜方式	enum SERVING_MODE{SM_NOW = 0 /*即起*/, SM_ON_DEMAND /*叫起*/}
	private Date mStartTime;
	private float mPrice;
	private String mWaiter;
	private String mUnit;
	private String mOperator;
	
	public DeskDishInfo(String id, String dishInfoId, String state, float count, Date startTime,
				float price, String waiter, String unit, String operator){
		this.mId = id;
		this.mDishInfoId = dishInfoId;
		this.mState = state;
		this.mCount = count;
		this.mStartTime = startTime;
		this.mPrice = price;
		this.mWaiter = waiter;
		this.mUnit = unit;
		this.mOperator = operator;
	}

	public String getId() {
		return mId;
	}

	public void setId(String mId) {
		this.mId = mId;
	}

	public String getDishInfoId() {
		return mDishInfoId;
	}

	public void setDishInfoId(String mDishInfoId) {
		this.mDishInfoId = mDishInfoId;
	}

	public String getState() {
		return mState;
	}

	public void setState(String mState) {
		this.mState = mState;
	}

	public float getCount() {
		return mCount;
	}

	public void setCount(float mCount) {
		this.mCount = mCount;
	}

	public String getFlavorIds() {
		return mFlavorIds;
	}

	public void setFlavorIds(String mFlavorIds) {
		this.mFlavorIds = mFlavorIds;
	}

	public int getServingMode() {
		return mServingMode;
	}

	public void setServingMode(int mServingMode) {
		this.mServingMode = mServingMode;
	}

	public Date getStartTime() {
		return mStartTime;
	}

	public void setStartTime(Date mStartTime) {
		this.mStartTime = mStartTime;
	}

	public float getPrice() {
		return mPrice;
	}

	public void setPrice(float mPrice) {
		this.mPrice = mPrice;
	}

	public String getWaiter() {
		return mWaiter;
	}

	public void setWaiter(String mWaiter) {
		this.mWaiter = mWaiter;
	}

	public String getUnit() {
		return mUnit;
	}

	public void setUnit(String mUnit) {
		this.mUnit = mUnit;
	}

	public String getOperator() {
		return mOperator;
	}

	public void setOperator(String mOperator) {
		this.mOperator = mOperator;
	}
	
}
