package org.mfn.dishes.datastore;

import java.sql.Date;
import java.util.HashMap;

import org.mfn.dishes.vo.DishCategoryInfo;
import org.mfn.dishes.vo.DishInfo;
import org.mfn.dishes.vo.FlavorInfo;
import org.mfn.dishes.vo.ImageInfo;
import org.mfn.dishes.vo.UserInfo;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

public class DBOperator {
	private IDishesDataStore dishesDataStore = DataStore.getInstance().getDishesDataStore();
	private IUserDataStore userDataStore = DataStore.getInstance().getUserDataStore();
	private HashMap<String, ImageInfo> imageInfos = null;
	private DishesDBHelper dbHelpter = null;
	
	private static DBOperator mInstance = null;
	
	public DBOperator(){
		this.imageInfos = new HashMap<String, ImageInfo>();
		dbHelpter = DishesDBHelper.getInstance();
	}
	
	public static DBOperator getInstance(){
		if(mInstance == null){
			mInstance = new DBOperator();
		}
		return mInstance;
	}
	
	public void loadDataFromDB(){
		loadCategoryData();
		loadFlavorsData();
		loadDishesData();
		loadUserData();
	}
	
	public HashMap<String, ImageInfo> getImageInfoHashMap(){
		if (imageInfos == null || imageInfos.size() == 0) {
			loadImageData();
		}
		return imageInfos;
	}
	
	/**
	 * load category data from DB to data store
	 */
	private void loadCategoryData(){
		SQLiteDatabase db = dbHelpter.getReadableDatabase();
		Cursor cursor = db.query("dishes_type_info", null, null, null, null, null, null);
		if(cursor.moveToFirst()){
			do {
				DishCategoryInfo categoryInfo = new DishCategoryInfo(cursor.getString(0), 
						cursor.getString(1), 
						cursor.getString(2), 
						cursor.getInt(3));
				dishesDataStore.addDishCategory(categoryInfo);
			} while (cursor.moveToNext());
		}
		cursor.close();
		db.close();
	}
	
	/**
	 * load image data from DB to data store
	 */
	private void loadImageData(){
		SQLiteDatabase db = dbHelpter.getReadableDatabase();
		Cursor cursor = db.query("image_info", null, null, null, null, null, null);
		String dishId = null;
		if(cursor.moveToFirst()){
			do {
				dishId = cursor.getString(0);
				ImageInfo imageInfo = new ImageInfo(cursor.getString(0),
								cursor.getString(1), 
								cursor.getLong(3), 
								new Date(cursor.getLong(7)), 
								cursor.getString(2), 
								cursor.getLong(5), 
								new Date(cursor.getLong(8)));
				imageInfos.put(dishId, imageInfo);
			} while (cursor.moveToNext());			
		}
		cursor.close();
		db.close();
	}
	
	/**
	 * load dish info from DB to data store
	 */
	private void loadDishesData(){
		loadImageData();
		SQLiteDatabase db = dbHelpter.getReadableDatabase();
		Cursor cursor = db.query("dish_info", null, null, null, null, null, null);
		String dishId = null;
		ImageInfo imageInfo = null;
		String categoryCode = null;
		if(cursor.moveToFirst()){
			do {
				dishId = cursor.getString(0);
				imageInfo = imageInfos.get(dishId);
				categoryCode = cursor.getString(7);
				DishInfo dishInfo = new DishInfo(cursor.getString(0), 
						cursor.getString(1), 
						cursor.getString(2), 
						cursor.getString(3), 
						cursor.getInt(4), 
						cursor.getString(5), 
						cursor.getFloat(6),  
						cursor.getInt(8) == 1,
						cursor.getFloat(11),
						cursor.getInt(10), 
						imageInfo);
				dishesDataStore.addDishInfo(categoryCode, dishInfo);
			} while (cursor.moveToNext());
		}
		cursor.close();
		db.close();
	}	
	
	/**
	 * load user info from DB to data store
	 */
	private void loadUserData(){
		SQLiteDatabase db = dbHelpter.getReadableDatabase();
		Cursor cursor = db.query("user_info", null, null, null, null, null, null);
		if(cursor.moveToFirst()){
			do{
				UserInfo userInfo = new UserInfo(cursor.getString(0), cursor.getString(1), cursor.getString(2));
				userDataStore.addUserInfo(cursor.getString(0), userInfo);
			}while(cursor.moveToNext());
		}
		cursor.close();
		db.close();
	}
	
	/**
	 * load flavor info from DB to data store
	 */
	private void loadFlavorsData(){
		SQLiteDatabase db = dbHelpter.getReadableDatabase();
		Cursor cursor = db.query("flavor_info", null, null, null, null, null, null);
		if(cursor.moveToFirst()){
			do{
				FlavorInfo flavorInfo = new FlavorInfo(cursor.getString(0), cursor.getString(1), cursor.getInt(2) == 1);
				dishesDataStore.addFlavorInfo(cursor.getString(0), flavorInfo);
			}while(cursor.moveToNext());
		}
		cursor.close();
		db.close();
	}

}
