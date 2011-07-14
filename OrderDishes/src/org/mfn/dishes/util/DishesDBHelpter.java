package org.mfn.dishes.util;

import org.mfn.dishes.vo.DishesObj;
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

	}

	private void createDishesInfoTable(SQLiteDatabase db) {
		String create_dishes_info_table = "CREATE TABLE " + DishesObj.TABLE_NAME + " (" 
		+ DishesObj.DISHES_ID + " INTEGER PRIMARY KEY," 
		+ DishesObj.DISHES_QUERY_CODE + " TEXT," 
		+ DishesObj.DISHES_QUERY_CODE_2 + " TEXT" 
		+ DishesObj.DISHES_NAME + " TEXT, " 
		+ DishesObj.DISHES_SIZE + " INTEGER,"
		+ DishesObj.DISHES_UNIT + " STRING," 
		+ DishesObj.DISHES_PRICE + " FLOAT," 
		+ DishesObj.DISHES_TYPE	+ " FLOAT," 
		+ DishesObj.DISHES_VARIABLE_PRICE + " FLOAT," 
		+ DishesObj.DISHES_COOK_TYPE + " FLOAT,"
		+ DishesObj.DISHES_FLAG + " FLOAT," 
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
