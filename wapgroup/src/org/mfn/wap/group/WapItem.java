package org.mfn.wap.group;

public class WapItem {

	private int mIcon;
	private String wapUrl;
	private String wapName;
	private boolean avaiable;

	public WapItem() {
	}
	
	public WapItem(int mIcon, String wapUrl, String wapName, boolean avaiable) {
		this.mIcon = mIcon;
		this.wapUrl = wapUrl;
		this.wapName = wapName;
		this.avaiable = avaiable;
	}

	public int getmIcon() {
		return mIcon;
	}

	public boolean isAvaiable() {
		return avaiable;
	}

	public void setAvaiable(boolean avaiable) {
		this.avaiable = avaiable;
	}

	public void setmIcon(int mIcon) {
		this.mIcon = mIcon;
	}

	public String getWapUrl() {
		return wapUrl;
	}

	public void setWapUrl(String wapUrl) {
		this.wapUrl = wapUrl;
	}

	public String getWapName() {
		return wapName;
	}

	public void setWapName(String wapName) {
		this.wapName = wapName;
	}

}
