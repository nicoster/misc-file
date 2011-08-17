package org.mfn.dishes.vo;

import java.util.Date;

public class DeskDetailInfo {
	private String mId;
	private int mHeadcount;
	private String mOrderId;
	private String mWaiter;
	private Date mOrderTime;
	private DeskDishInfo[] mDeskDishInfos;
	
	public DeskDetailInfo(String id, int headCount, String orderId, String waiter){
		this.mId = id;
		this.mHeadcount = headCount;
		this.mOrderId = orderId;
		this.mWaiter = waiter;		
	}

	public String getId() {
		return mId;
	}

	public void setId(String mId) {
		this.mId = mId;
	}

	public int getHeadcount() {
		return mHeadcount;
	}

	public void setHeadcount(int mHeadcount) {
		this.mHeadcount = mHeadcount;
	}

	public String getOrderId() {
		return mOrderId;
	}

	public void setOrderId(String mOrderId) {
		this.mOrderId = mOrderId;
	}

	public String getWaiter() {
		return mWaiter;
	}

	public void setWaiter(String mWaiter) {
		this.mWaiter = mWaiter;
	}

	public Date getOrderTime() {
		return mOrderTime;
	}

	public void setOrderTime(Date mOrderTime) {
		this.mOrderTime = mOrderTime;
	}

	public DeskDishInfo[] getDeskDishInfos() {
		return mDeskDishInfos;
	}

	public void setDeskDishInfos(DeskDishInfo[] mDeskDishInfos) {
		this.mDeskDishInfos = mDeskDishInfos;
	}
	
}
