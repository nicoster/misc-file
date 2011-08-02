package org.mfn.dishes.vo;

import java.sql.Date;

import org.mfn.dishes.Constants;

public class ImageInfo {
	private String mImageName;
	private long mImageSize;
	private Date mImageModifyDate;
	private String mSmallImageName;
	private long mSmallImageSize;
	private Date mSmallImageModifyDate;
	
	public ImageInfo(String imageName, long size, Date modifyDate, String smalllImageName, long smallImageSize, Date smallImageModifyDate){
		this.mImageName = imageName;
		this.mImageSize = size;
		this.mImageModifyDate = modifyDate;
		this.mSmallImageName = smalllImageName;
		this.mSmallImageSize = smallImageSize;
		this.mSmallImageModifyDate = smallImageModifyDate;
	}

	public String getImageName() {
		return mImageName;
	}

	public void setImageName(String mImageName) {
		this.mImageName = mImageName;
	}

	public long getImageSize() {
		return mImageSize;
	}

	public void setImageSize(long mImageSize) {
		this.mImageSize = mImageSize;
	}

	public Date getImageModifyDate() {
		return mImageModifyDate;
	}

	public void setImageModifyDate(Date mImageModifyDate) {
		this.mImageModifyDate = mImageModifyDate;
	}

	public String getSmallImageName() {
		return mSmallImageName;
	}

	public void setSmallImageName(String mSmallImageName) {
		this.mSmallImageName = mSmallImageName;
	}

	public long getSmallImageSize() {
		return mSmallImageSize;
	}

	public void setSmallImageSize(long mSmallImageSize) {
		this.mSmallImageSize = mSmallImageSize;
	}

	public Date getSmallImageModifyDate() {
		return mSmallImageModifyDate;
	}

	public void setSmallImageModifyDate(Date mSmallImageModifyDate) {
		this.mSmallImageModifyDate = mSmallImageModifyDate;
	}
	
	public String getImagePath(){
		return Constants.DISHES_IMAGE_PATH + mImageName;
	}
	
	public String getSmallImagePath(){
		return Constants.DISHES_IMAGE_PATH + mSmallImageName;
	}

}
