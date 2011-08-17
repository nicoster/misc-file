package org.mfn.dishes.vo;

public class FlavorInfo {	
	private String mId;
	private String mName;
	private boolean mIsCookStyle;
	
	public FlavorInfo(String id, String name, boolean isCookStyle){
		this.mId = id;
		this.mName = name;
		this.mIsCookStyle = isCookStyle;
	}

	public String getId() {
		return mId;
	}

	public void setId(String mId) {
		this.mId = mId;
	}

	public String getName() {
		return mName;
	}

	public void setName(String mName) {
		this.mName = mName;
	}

	public boolean isIsCookStyle() {
		return mIsCookStyle;
	}

	public void setIsCookStyle(boolean mIsCookStyle) {
		this.mIsCookStyle = mIsCookStyle;
	}
	
	
}
