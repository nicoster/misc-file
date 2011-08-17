package org.mfn.dishes.vo;

public class DeskState {
	
	public static final String TABLE_NAME = "desk_status_info";
	public static final String TYPE_ID = "type_id";
	public static final String TYPE_NAME = "type_name";
	public static final String PARENT_TYPE_ID = "parent_type_id";
	public static final String TYPE_INDEX = "type_index";
	
	public int id;
	public int state;
	public int orderId;
	public String memo;
	
	public DeskState(){
		
	}
	
}
