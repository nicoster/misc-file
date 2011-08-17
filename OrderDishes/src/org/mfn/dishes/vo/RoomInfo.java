package org.mfn.dishes.vo;

public class RoomInfo {
	
	public static final String TABLE_NAME = "room_info";
	public static final String ROOM_ID = "room_id";
	public static final String ROOM_NAME = "room_name";
	
	private int mId;
	private String mName;
	
	public RoomInfo(int id, String name){
		this.mId = id;
		this.mName = name;		
	}

	public int getmId() {
		return mId;
	}

	public void setmId(int mId) {
		this.mId = mId;
	}

	public String getmName() {
		return mName;
	}

	public void setmName(String mName) {
		this.mName = mName;
	}
	
}
