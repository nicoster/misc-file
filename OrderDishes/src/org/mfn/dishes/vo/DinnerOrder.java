package org.mfn.dishes.vo;

import java.util.Date;

//订单
public class DinnerOrder {
	
	public static final String TABLE_NAME = "dinner_order";
	public static final String ORDER_ID = "order_id";
	public static final String ROOM_ID = "order_room_id";
	public static final String DESK_ID = "order_desk_id";
	public static final String USER_ID = "order_user_id";
	public static final String ORDER_TIME = "order_time";
	public static final String ORDER_FLAG = "order_flag";
	
	public String id;
	public String room_id;
	public String desk_id;
	public String used_id;
	public Date  orderTime;
	public int flag; //点菜过程 -0 . 已发送-1， 结帐-9
	
}
