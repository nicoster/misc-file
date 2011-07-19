package org.mfn.dishes.util;

import org.mfn.dishes.vo.DishObj;
import org.mfn.dishes.vo.DishTypeObj;
import org.mfn.dishes.vo.FlavorInfoObj;
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

		createDishInfoTable(db);
		createUserInfoTable(db);
		createDishTypeInfoTable(db);
		createRoomInfoTable(db);
		createFlavorInfoTable(db);

	}

	private void createDishInfoTable(SQLiteDatabase db) {
		String create_dish_info_table = "CREATE TABLE " + DishObj.TABLE_NAME + " (" 
		+ DishObj.DISH_ID + " INTEGER PRIMARY KEY," 
		+ DishObj.DISH_QUERY_CODE + " TEXT," 
		+ DishObj.DISH_QUERY_CODE_2 + " TEXT," 
		+ DishObj.DISH_NAME + " TEXT, " 
		+ DishObj.DISH_SIZE + " INTEGER,"
		+ DishObj.DISH_UNIT + " STRING," 
		+ DishObj.DISH_PRICE + " FLOAT," 
		+ DishObj.DISH_TYPE	+ " INTEGER," 
		+ DishObj.DISH_VARIABLE_PRICE + " BOOLEAN," 
		+ DishObj.DISH_COOK_TYPE + " STRING,"
		+ DishObj.DISH_FLAG + " INTEGER," 
		+ DishObj.DISH_COST + " FLOAT," 
		+ DishObj.DISH_IMAGE + " TEXT" 
		+ ")";

		db.execSQL(create_dish_info_table);
	}

	private void createUserInfoTable(SQLiteDatabase db) {
		String create_dish_info_table = "CREATE TABLE " + UserInfoObj.TABLE_NAME + " (" 
		+ UserInfoObj.USER_ID + " STRING PRIMARY KEY," 
		+ UserInfoObj.USER_NAME + " TEXT," 
		+ UserInfoObj.USER_LEVEL + " STRING" 
		+ ")";

		db.execSQL(create_dish_info_table);
	}
	
	private void createDishTypeInfoTable(SQLiteDatabase db) {
		String create_dish_info_table = "CREATE TABLE " + DishTypeObj.TABLE_NAME + " (" 
		+ DishTypeObj.TYPE_ID + " STRING PRIMARY KEY," 
		+ DishTypeObj.TYPE_NAME + " TEXT," 
		+ DishTypeObj.PARENT_TYPE_ID + " STRING," 
		+ DishTypeObj.TYPE_INDEX + " INTEGER" 
		+ ")";

		db.execSQL(create_dish_info_table);
	}
	
	private void createRoomInfoTable(SQLiteDatabase db) {
		String create_dish_info_table = "CREATE TABLE " + RoomInfoObj.TABLE_NAME + " (" 
		+ RoomInfoObj.ROOM_ID + " INTEGER PRIMARY KEY," 
		+ RoomInfoObj.ROOM_NAME + " TEXT" 
		+ ")";

		db.execSQL(create_dish_info_table);
	}

	private void createFlavorInfoTable(SQLiteDatabase db) {
		String create_dish_info_table = "CREATE TABLE " + FlavorInfoObj.TABLE_NAME + " (" 
		+ FlavorInfoObj.FLAVOR_ID + " STRING PRIMARY KEY," 
		+ FlavorInfoObj.FLAVOR_NAME + " TEXT," 
		+ FlavorInfoObj.IS_COOK_STYLE + " BOOLEAN" 
		+ ")";

		db.execSQL(create_dish_info_table);
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
