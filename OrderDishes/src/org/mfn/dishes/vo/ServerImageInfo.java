package org.mfn.dishes.vo;

import java.util.Date;

public class ServerImageInfo {
	private String mName;
	private long mSize;
	private Date mModified_time;
	
	public ServerImageInfo(String name, long size, Date modifyTime){
		this.mName = name;
		this.mSize = size;
		this.mModified_time = modifyTime;
	}

	public String getName() {
		return mName;
	}

	public void setName(String mName) {
		this.mName = mName;
	}

	public long getSize() {
		return mSize;
	}

	public void setSize(long mSize) {
		this.mSize = mSize;
	}

	public Date getModified_time() {
		return mModified_time;
	}

	public void setModified_time(Date mModified_time) {
		this.mModified_time = mModified_time;
	}
	
}
