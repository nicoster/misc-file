package org.mfn.dishes.vo;

public class UserInfo {
	
	public static final String TABLE_NAME = "user_info";
	public static final String USER_ID = "user_ID";
	public static final String USER_NAME = "user_name";
	public static final String USER_LEVEL = "user_level";
	
	private String mId;
	private String mName;
	//FIXME: better to be integer instead of string when it comes to authorization.
	private String mLevel;
	
	public UserInfo(String id, String name, String level){
		this.mId = id;
		this.mName = name;
		this.mLevel = level;
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

	public String getLevel() {
		return mLevel;
	}

	public void setLevel(String mLevel) {
		this.mLevel = mLevel;
	}
	
}
