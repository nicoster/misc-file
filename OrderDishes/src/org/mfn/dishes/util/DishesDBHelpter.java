package org.mfn.dishes.util;

import org.mfn.dishes.vo.DishesObj;
import org.mfn.dishes.vo.DishesTypeObj;
import org.mfn.dishes.vo.RoomInfoObj;
import org.mfn.dishes.vo.UserInfoObj;

import android.content.Context;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

public class DishesDBHelpter extends SQLiteOpenHelper {

	private static final String DB_NAME = "OrderDishes.db";
	private static final int DB_VERSION = 1;
	private static DishesDBHelpter helper;
	private static Context mContext = null;
	public static String TAG = "DishesDBHelpter";
	
	public SQLiteDatabase myDB = null;

	public static void init(Context context) {
		Log.i(TAG, "Init DishesDBHelpter.....");
		mContext = context;
		helper = new DishesDBHelpter(mContext);
	}

	public static DishesDBHelpter getInstance() {
		return helper;
	}

	private DishesDBHelpter(Context context) {
		super(context, DB_NAME, null, DB_VERSION);
	}

	@Override
	public void onCreate(SQLiteDatabase db) {

		createDishesInfoTable(db);
		createUserInfoTable(db);
		createDishesTypeInfoTable(db);
		createRoomInfoTable(db);

	}

	private void createDishesInfoTable(SQLiteDatabase db) {
		String create_dishes_info_table = "CREATE TABLE " + DishesObj.TABLE_NAME + " (" 
		+ DishesObj.DISHES_ID + " INTEGER PRIMARY KEY," 
		+ DishesObj.DISHES_QUERY_CODE + " TEXT," 
		+ DishesObj.DISHES_QUERY_CODE_2 + " TEXT," 
		+ DishesObj.DISHES_NAME + " TEXT, " 
		+ DishesObj.DISHES_SIZE + " INTEGER,"
		+ DishesObj.DISHES_UNIT + " STRING," 
		+ DishesObj.DISHES_PRICE + " FLOAT," 
		+ DishesObj.DISHES_TYPE	+ " INTEGER," 
		+ DishesObj.DISHES_VARIABLE_PRICE + " BOOLEAN," 
		+ DishesObj.DISHES_COOK_TYPE + " STRING,"
		+ DishesObj.DISHES_FLAG + " INTEGER," 
		+ DishesObj.DISHES_COST + " FLOAT," 
		+ DishesObj.DISHES_IMAGE + " TEXT" 
		+ ")";

		db.execSQL(create_dishes_info_table);
	}

	private void createUserInfoTable(SQLiteDatabase db) {
		String create_dishes_info_table = "CREATE TABLE " + UserInfoObj.TABLE_NAME + " (" 
		+ UserInfoObj.USER_ID + " INTEGER PRIMARY KEY," 
		+ UserInfoObj.USER_NAME + " TEXT," 
		+ UserInfoObj.USER_LEVEL + " INTEGER" 
		+ ")";

		db.execSQL(create_dishes_info_table);
	}
	
	private void createDishesTypeInfoTable(SQLiteDatabase db) {
		String create_dishes_info_table = "CREATE TABLE " + DishesTypeObj.TABLE_NAME + " (" 
		+ DishesTypeObj.TYPE_ID + " INTEGER PRIMARY KEY," 
		+ DishesTypeObj.TYPE_NAME + " TEXT," 
		+ DishesTypeObj.PARENT_TYPE_ID + " INTEGER," 
		+ DishesTypeObj.TYPE_INDEX + " INTEGER" 
		+ ")";

		db.execSQL(create_dishes_info_table);
	}
	
	private void createRoomInfoTable(SQLiteDatabase db) {
		String create_dishes_info_table = "CREATE TABLE " + RoomInfoObj.TABLE_NAME + " (" 
		+ RoomInfoObj.ROOM_ID + " INTEGER PRIMARY KEY," 
		+ RoomInfoObj.ROOM_NAME + " TEXT" 
		+ ")";

		db.execSQL(create_dishes_info_table);
	}
	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		db.execSQL("DROP TABLE IF EXISTS notes");
		onCreate(db);

	}

	public void open() throws SQLException {
		myDB = helper.getWritableDatabase();
	}

	public void close() {
		helper.close();
	}
}
