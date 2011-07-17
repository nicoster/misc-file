package org.mfn.dishes.vo;

public class UserInfoObj {
	
	public static final String TABLE_NAME = "user_info";
	public static final String USER_ID = "user_ID";
	public static final String USER_NAME = "user_name";
	public static final String USER_LEVEL = "user_level";
	
	public String id;
	public String name;
	//FIXME: better to be integer instead of string when it comes to authorization.
	public String level;
	
	public String toString()
	{
		return "{id:" + id + ", name:" + name + ", level:" + level + "}";
	}
}
