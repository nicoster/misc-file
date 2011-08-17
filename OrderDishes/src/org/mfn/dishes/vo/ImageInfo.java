package org.mfn.dishes.vo;

import java.util.Date;

import org.mfn.dishes.Constants;
import org.mfn.dishes.util.FunctionUtil;

public class ImageInfo {
	private String mId;
	private String mImageName;
	private long mImageSize;
	private Date mImageModifyTime;
	
	private String mSmallImageName;
	private long mSmallImageSize;
	private Date mSmallImageModifyTime;
	
	private String mVideoName;
	private long mVideoSize;
	private Date mVideoModifiedTime;
	
	public ImageInfo() {
	}
	
	public ImageInfo(String id, String imageName, long size, Date modifyDate, String smalllImageName, long smallImageSize, Date smallImageModifyDate){
		this.mId = id;
		this.mImageName = imageName;
		this.mImageSize = size;
		this.mImageModifyTime = modifyDate;
		this.mSmallImageName = smalllImageName;
		this.mSmallImageSize = smallImageSize;
		this.mSmallImageModifyTime = smallImageModifyDate;
	}
	
	public void setImageInfo(ServerImageInfo serverImageInfo) {
		mId = FunctionUtil.formatDishId(serverImageInfo.getName());
		if(FunctionUtil.isVideo(serverImageInfo.getName())){
			this.mVideoName = serverImageInfo.getName();
			this.mVideoSize = serverImageInfo.getSize();
			this.mVideoModifiedTime = serverImageInfo.getModified_time();
		}else if (FunctionUtil.isSmallImage(serverImageInfo.getName())) {
			this.mSmallImageName = serverImageInfo.getName();
			this.mSmallImageSize = serverImageInfo.getSize();
			this.mSmallImageModifyTime = serverImageInfo.getModified_time();
		} else {
			this.mImageName = serverImageInfo.getName();
			this.mImageSize = serverImageInfo.getSize();
			this.mImageModifyTime = serverImageInfo.getModified_time();
		}
	}

	public String getId() {
		return mId;
	}

	public void setId(String mId) {
		this.mId = mId;
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

	public Date getImageModifyTime() {
		return mImageModifyTime;
	}

	public void setImageModifyTime(Date mImageModifyTime) {
		this.mImageModifyTime = mImageModifyTime;
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

	public Date getSmallImageModifyTime() {
		return mSmallImageModifyTime;
	}

	public void setSmallImageModifyTime(Date mSmallImageModifyTime) {
		this.mSmallImageModifyTime = mSmallImageModifyTime;
	}
	
	public String getImagePath(){
		return Constants.DISHES_IMAGE_PATH + mImageName;
	}
	
	public String getSmallImagePath(){
		return Constants.DISHES_IMAGE_PATH + mSmallImageName;
	}

	public String getVideoName() {
		return mVideoName;
	}

	public void setVideoName(String mVideoName) {
		this.mVideoName = mVideoName;
	}

	public long getVideoSize() {
		return mVideoSize;
	}

	public void setVideoSize(long mVideoSize) {
		this.mVideoSize = mVideoSize;
	}

	public Date getVideoModifiedTime() {
		return mVideoModifiedTime;
	}

	public void setVideoModifiedTime(Date mVideoModifiedTime) {
		this.mVideoModifiedTime = mVideoModifiedTime;
	}

}
