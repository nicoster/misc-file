package org.mfn.dishes.sync.syncadapter;

import java.sql.Date;
import java.util.HashMap;
import java.util.Iterator;

import org.mfn.dishes.Constants;
import org.mfn.dishes.datastore.DishesDBHelper;
import org.mfn.dishes.util.FunctionUtil;
import org.mfn.dishes.vo.DishCategoryInfo;
import org.mfn.dishes.vo.DishInfo;
import org.mfn.dishes.vo.FlavorInfo;
import org.mfn.dishes.vo.ImageInfo;
import org.mfn.dishes.vo.ServerImageInfo;
import org.mfn.dishes.vo.UserInfo;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.text.TextUtils;
import android.util.Log;

public class SyncDBOperator {
	private static SyncDBOperator mInstance = null;
	private DishesDBHelper mDbHelper = null;
	
	public SyncDBOperator(){
		mDbHelper = DishesDBHelper.getInstance();
	}
	
	public static SyncDBOperator getInstance(){
		if(mInstance == null){
			mInstance = new SyncDBOperator();
		}
		return mInstance;
	}
	
	/**
	 * save user info to DB
	 * @param userInfos
	 */
	public void saveUserInfo(UserInfo[] userInfos){
		if(userInfos == null || userInfos.length == 0){
			Log.e(Constants.APP_TAG, "syncUsersInfo error, data is null");
			return;
		}
		SQLiteDatabase db = mDbHelper.getWritableDatabase();
		db.delete("user_info", null, null);
		for(UserInfo userInfo : userInfos){
			ContentValues values = new ContentValues();
			values.put("user_ID", userInfo.getId());
			values.put("user_name", userInfo.getName());
			values.put("user_level", userInfo.getLevel());
			db.insert("user_info", "user_ID", values);
		}
		db.close();
	}
	
	/**
	 * save dish category info to DB
	 * @param dishCategoryInfos
	 */
	public void saveDishCategoryInfo(DishCategoryInfo[] dishCategoryInfos) {
		if(dishCategoryInfos == null || dishCategoryInfos.length == 0){
			Log.e(Constants.APP_TAG, "saveDishCategoryInfo error, data is null");
			return;
		}
		SQLiteDatabase db = mDbHelper.getWritableDatabase();
		db.delete("dishes_type_info", null, null);
		for(DishCategoryInfo dishCategoryInfo : dishCategoryInfos){
			ContentValues values = new ContentValues();
			values.put("type_id", dishCategoryInfo.getDishCategoryCode());
			values.put("type_name", dishCategoryInfo.getDishCategoryName());
			values.put("parent_type_id", dishCategoryInfo.getParentCode());
			values.put("type_index", dishCategoryInfo.getIndex());
			db.insert("dishes_type_info", null, values);
		}
		db.close();
	}

	/**
	 * save dish info to DB
	 * @param dishInfos
	 */
	public void saveDishInfo(DishInfo[] dishInfos) {
		if(dishInfos == null || dishInfos.length == 0){
			Log.e(Constants.APP_TAG, "saveDishInfo error, data is null");
			return;
		}
		SQLiteDatabase db = mDbHelper.getWritableDatabase();
		db.delete("dish_info", null, null);
		for(DishInfo dishInfo : dishInfos){
			ContentValues values = new ContentValues();
			values.put("dish_id", dishInfo.getId());
			values.put("query_code", dishInfo.getCode());
			values.put("query_code_2", dishInfo.getPinyinCode());
			values.put("dish_name", dishInfo.getName());
			values.put("dish_size", dishInfo.getSize());
			values.put("dish_unit", dishInfo.getUnit());
			values.put("dish_price", dishInfo.getPrice());
			values.put("dish_type", dishInfo.getCategoryCodes().get(0));
			values.put("dish_variable_price", dishInfo.isVariablePrice() ? 1 : 0);
			values.put("dish_cook_type", "");
			values.put("dish_flag", dishInfo.getFlag());
			values.put("dish_cost", dishInfo.getCost());
			db.insert("dish_info", null, values);
		}
		db.close();
	}
	
	/**
	 * save flavor info to DB
	 * @param flavorInfos
	 */
	public void saveFlavorInfo(FlavorInfo[] flavorInfos){
		if(flavorInfos == null || flavorInfos.length == 0){
			Log.e(Constants.APP_TAG, "saveFlavorInfo error, data is null");
			return;
		}
		SQLiteDatabase db = mDbHelper.getWritableDatabase();
		db.delete("flavor_info", null, null);
		for(FlavorInfo flavorInfo : flavorInfos){
			ContentValues values = new ContentValues();
			values.put("flavor_id", flavorInfo.getId());
			values.put("flavor_name", flavorInfo.getName());
			values.put("is_cook_style", flavorInfo.isIsCookStyle());
	        db.insert("flavor_info", null, values);
		}
		db.close();
	}
	
	public void saveImageInfo(ServerImageInfo[] serverImageInfos){
		if (serverImageInfos == null || serverImageInfos.length == 0) {
			Log.e(Constants.APP_TAG, "syncImageInfo error, data is null");
			return;
		}
		SQLiteDatabase db = mDbHelper.getWritableDatabase();
		db.delete("image_info", null, null);
		HashMap<String, ImageInfo> imageMap = new HashMap<String, ImageInfo>();
		for (ServerImageInfo serverImageInfo : serverImageInfos) {
			String id = FunctionUtil.formatDishId(serverImageInfo.getName());
			ImageInfo estImgObj = imageMap.get(id);
			if (estImgObj == null) {
				ImageInfo imageInfo = new ImageInfo();
				imageInfo.setImageInfo(serverImageInfo);
				imageMap.put(id, imageInfo);
			} else {
				estImgObj.setImageInfo(serverImageInfo);
			}
		}
		
		Iterator<ImageInfo> it = imageMap.values().iterator();
		while (it.hasNext()) {
			ImageInfo imageInfo = (ImageInfo) it.next();
			if (FunctionUtil.isImageFile(imageInfo.getImageName())) {
				ContentValues values = new ContentValues();
				values.put("image_id", imageInfo.getId());
				
				if (TextUtils.isEmpty(imageInfo.getImageName()) || imageInfo.getImageSize() <= 0 || imageInfo.getImageModifyTime() == null){
					Log.w(Constants.APP_TAG, "addImageInfo:: invalid image info data " + imageInfo.getImageName());
					continue;
				}
				
				values.put("image_name", imageInfo.getImageName());
				values.put("image_size", imageInfo.getImageSize());
				values.put("image_modify_time", imageInfo.getImageModifyTime().getTime());

				if (TextUtils.isEmpty(imageInfo.getSmallImageName())) {
					values.put("samll_image_name", imageInfo.getImageName());
				} else {
					values.put("samll_image_name", imageInfo.getSmallImageName());
				}
				if (imageInfo.getSmallImageSize() <= 0) {
					values.put("small_image_size", imageInfo.getImageSize());
				} else {
					values.put("small_image_size", imageInfo.getSmallImageSize());
				}
				if (imageInfo.getSmallImageModifyTime() != null) {
					values.put("small_image_modify_time", imageInfo.getSmallImageModifyTime().getTime());
				} else {
					values.put("small_image_modify_time", imageInfo.getImageModifyTime().getTime());
				}
		        
				if (!TextUtils.isEmpty(imageInfo.getVideoName()) && imageInfo.getVideoSize() > 0 && imageInfo.getVideoModifiedTime() != null) {
					values.put("video_image_name", imageInfo.getVideoName());
					values.put("video_image_size", imageInfo.getVideoSize());
					values.put("video_image_modify_time", imageInfo.getVideoModifiedTime().getTime());
				}
				db.insert("image_info", null, values);
			}
		}
		db.close();
	}
	
	public HashMap<String, ImageInfo> getImageInfos(){
		HashMap<String, ImageInfo> imageInfos = new HashMap<String, ImageInfo>();
		SQLiteDatabase db = mDbHelper.getReadableDatabase();
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
		return imageInfos;
	}

}
