package org.mfn.dishes.datastore;

import org.mfn.dishes.DishesApp;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DishesDBHelper extends SQLiteOpenHelper{
	private static final String DB_NAME = "OrderDishes.db";
	private static final int DB_VERSION = 1;
	private static DishesDBHelper helper = null;
	public static String TAG = "DishesDBHelpter";
	
	public static DishesDBHelper getInstance() {
		if(helper == null){
			helper = new DishesDBHelper(DishesApp.getInstance());
		}
		return helper;
	}

	private DishesDBHelper(Context context) {
		super(context, DB_NAME, null, DB_VERSION);
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		createDishInfoTable(db);
		createUserInfoTable(db);
		createDishTypeInfoTable(db);
		createRoomInfoTable(db);
		createFlavorInfoTable(db);
		createImageInfoTable(db);
	}

	private void createDishInfoTable(SQLiteDatabase db) {
		String create_dish_info_table = "CREATE TABLE dish_info (" 
		+ "dish_id INTEGER PRIMARY KEY," //0
		+ "query_code TEXT," //1
		+ "query_code_2 TEXT," //2
		+ "dish_name TEXT, " //3
		+ "dish_size INTEGER,"//4
		+ "dish_unit STRING," //5
		+ "dish_price FLOAT," //6
		+ "dish_type INTEGER," //7
		+ "dish_variable_price BOOLEAN,"//8 
		+ "dish_cook_type STRING,"//9
		+ "dish_flag INTEGER," //10
		+ "dish_cost FLOAT" //11
		+ ")";

		db.execSQL(create_dish_info_table);
	}

	private void createUserInfoTable(SQLiteDatabase db) {
		String create_dish_info_table = "CREATE TABLE user_info (" 
		+ "user_id STRING PRIMARY KEY," 
		+ "user_name TEXT," 
		+ "user_level STRING" 
		+ ")";

		db.execSQL(create_dish_info_table);
	}
	
	private void createDishTypeInfoTable(SQLiteDatabase db) {
		String create_dish_info_table = "CREATE TABLE dishes_type_info (" 
		+ "type_id STRING PRIMARY KEY," 
		+ "type_name TEXT," 
		+ "parent_type_id STRING," 
		+ "type_index INTEGER" 
		+ ")";

		db.execSQL(create_dish_info_table);
	}
	
	private void createRoomInfoTable(SQLiteDatabase db) {
		String create_dish_info_table = "CREATE TABLE room_info (" 
		+ "room_id INTEGER PRIMARY KEY," 
		+ "room_name TEXT" 
		+ ")";

		db.execSQL(create_dish_info_table);
	}

	private void createFlavorInfoTable(SQLiteDatabase db) {
		String create_dish_info_table = "CREATE TABLE flavor_info (" 
		+ "flavor_id STRING PRIMARY KEY," 
		+ "flavor_name TEXT," 
		+ "is_cook_style BOOLEAN" 
		+ ")";

		db.execSQL(create_dish_info_table);
	}

	private void createImageInfoTable(SQLiteDatabase db) {
		String create_dish_info_table = "CREATE TABLE image_info (" 
		+ "image_id STRING PRIMARY KEY," //0
		+ "image_name TEXT," //1
		+ "samll_image_name TEXT,"//2
		+ "video_image_name TEXT,"//3
		+ "image_size LONG," //4
		+ "small_image_size LONG,"//5
		+ "video_image_size LONG,"//6
		+ "image_modify_time LONG," //7
		+ "small_image_modify_time LONG,"//8
		+ "video_image_modify_time LONG"//9
		+ ")";

		db.execSQL(create_dish_info_table);
	}
	
	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		db.execSQL("DROP TABLE IF EXISTS notes");
		onCreate(db);

	}
}
