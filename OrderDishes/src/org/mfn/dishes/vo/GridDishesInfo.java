package org.mfn.dishes.vo;

public class GridDishesInfo {
	private String mCode;
	private String mDishName;
	private String mComment;
	private float mPrice;
	private String mUnit;
	private String mImageSrc;
	private String mFormatedPrice;
	
	public GridDishesInfo(String code, String dishName, String comments, float price, String unit, String imageSrc){
		mCode = code;
		mDishName = dishName;
		mComment = comments;
		mPrice = price;
		mUnit = unit;
		mImageSrc = imageSrc;
		this.formatPrice();
	}
	
	public String getCode() {
		return mCode;
	}
	public void setCode(String mCode) {
		this.mCode = mCode;
	}
	public String getDishName() {
		return mDishName;
	}
	public void setDishName(String mDishName) {
		this.mDishName = mDishName;
	}
	public String getComment() {
		return mComment;
	}
	public void setComment(String mComment) {
		this.mComment = mComment;
	}
	public float getPrice() {
		return mPrice;
	}
	public void setPrice(float mPrice) {
		this.mPrice = mPrice;
	}
	
	public String getUnit() {
		return mUnit;
	}

	public void setUnit(String mUnit) {
		this.mUnit = mUnit;
	}

	public String getImageSrc() {
		return mImageSrc;
	}
	public void setImageSrc(String mImageSrc) {
		this.mImageSrc = mImageSrc;
	}
	
	public String getFormatedPrice(){
		return mFormatedPrice;
	}
	
	private void formatPrice(){
		mFormatedPrice = mPrice + mUnit;
	}
	
}
