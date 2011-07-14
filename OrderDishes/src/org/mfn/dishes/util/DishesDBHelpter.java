package org.mfn.dishes.util;

import android.content.Context;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

public class DishesDBHelpter extends SQLiteOpenHelper {

	private static final String DB_NAME = "OrderDishes.db";

	private static final int DB_VERSION = 1;

	private static DishesDBHelpter helper;

	public SQLiteDatabase myDB = null;

	private static Context mContext = null;
	
	public static String TAG = "DishesDBHelpter";
	
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
		Log.i(TAG, "Create table :" + TableContacts.DISHES_INFO);
		String create_dishes_info_table = "CREATE TABLE " + TableContacts.DISHES_INFO + " (" 
				+ TableContacts.KEY_ID + " INTEGER PRIMARY KEY," 
				+ TableContacts.QUERY_CODE + " TEXT," 
				+ TableContacts.QUERY_CODE_2 + " TEXT"
				+ TableContacts.DISHES_NAME + " TEXT, " 
				+ TableContacts.DISHES_SIZE + " INTEGER," 
				+ TableContacts.DISHES_UNIT + " STRING," 
				+ TableContacts.DISHES_PRICE + " FLOAT," 
				+ TableContacts.DISHES_TYPE + " FLOAT," 
				+ TableContacts.DISHES_VARIABLE_PRICE + " FLOAT," 
				+ TableContacts.DISHES_COOK_TYPE + " FLOAT," 
				+ TableContacts.DISHES_FLAG + " FLOAT," 
				+ TableContacts.DISHES_COST + " FLOAT," 
				+ TableContacts.DISHES_IMAGE + " TEXT" 
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
