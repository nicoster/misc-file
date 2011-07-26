package org.mfn.dishes.util;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.mfn.dishes.Constants;
import org.mfn.dishes.vo.DishInfoObj;
import org.mfn.dishes.vo.DishTypeObj;
import org.mfn.dishes.vo.FlavorInfoObj;
import org.mfn.dishes.vo.ImageInfoObj;
import org.mfn.dishes.vo.ServerImageInfoObj;
import org.mfn.dishes.vo.UserInfoObj;

import android.content.ContentValues;
import android.database.Cursor;
import android.text.TextUtils;
import android.util.Log;

public class DishesDataAdapter {
	
	private DishesDBHelpter helper = DishesDBHelpter.getInstance();
	
	private static DishesDataAdapter dishesAdapter;
	
	private DishesDataAdapter(){
		
	}
	
	public static DishesDataAdapter getInstance() {
		if (dishesAdapter == null) {
			dishesAdapter = new DishesDataAdapter();
		}
		return dishesAdapter;
	}
	
	public void syncUsersInfo(UserInfoObj[] objs) {
		if (objs == null || objs.length == 0) {
			Log.e(Constants.APP_TAG, "syncUsersInfo error, data is null");
			return;
		}
		helper.myDB.delete(UserInfoObj.TABLE_NAME, null, null);

		for (UserInfoObj obj : objs) {
			addUserInfo(obj);
		}
	}
	
	public long addUserInfo(UserInfoObj obj){
		ContentValues initialValues = new ContentValues();
        initialValues.put(UserInfoObj.USER_ID, obj.id);
        initialValues.put(UserInfoObj.USER_NAME, obj.name);
        initialValues.put(UserInfoObj.USER_LEVEL, obj.level);
        
        Log.i(Constants.APP_TAG, "addUserInfo:: "+obj.toString());
        return helper.myDB.insert(UserInfoObj.TABLE_NAME, UserInfoObj.USER_ID, initialValues);		
	}
	
	
	public UserInfoObj[] listUsersInfo(int level) {
		Cursor mCursor = helper.myDB.query(true, UserInfoObj.TABLE_NAME, new String[]{UserInfoObj.USER_ID,
				UserInfoObj.USER_NAME, UserInfoObj.USER_LEVEL}, null, null, null, null, null, null);

		List<UserInfoObj> list = new ArrayList<UserInfoObj>();
		if (mCursor != null) {

			while (mCursor.moveToNext()) {

				UserInfoObj obj = new UserInfoObj();
				obj.id = mCursor.getString(mCursor.getColumnIndex(UserInfoObj.USER_ID));
				obj.name = mCursor.getString(mCursor.getColumnIndex(UserInfoObj.USER_NAME));
				obj.level = mCursor.getString(mCursor.getColumnIndex(UserInfoObj.USER_LEVEL));

				list.add(obj);
			}
			mCursor.close();
		}

		return list.toArray(new UserInfoObj[0]);
	}
	
	public void syncDishesInfo(DishInfoObj[] objs){
		if (objs == null || objs.length == 0) {
			Log.e(Constants.APP_TAG, "syncDishesInfo error, data is null");
			return;
		}
		helper.myDB.delete(DishInfoObj.TABLE_NAME, null, null);
		
		for (DishInfoObj obj: objs){
			addDishInfo(obj);
		}
	}
	
	public long addDishInfo(DishInfoObj obj){
		ContentValues initialValues = new ContentValues();
        initialValues.put(DishInfoObj.DISH_ID, obj.id);
        initialValues.put(DishInfoObj.DISH_QUERY_CODE, obj.query_code);
        initialValues.put(DishInfoObj.DISH_QUERY_CODE_2, obj.query_code2);
        initialValues.put(DishInfoObj.DISH_NAME, obj.name);
        initialValues.put(DishInfoObj.DISH_SIZE, obj.size);
        initialValues.put(DishInfoObj.DISH_UNIT, obj.unit);
        initialValues.put(DishInfoObj.DISH_PRICE, obj.price);
        initialValues.put(DishInfoObj.DISH_TYPE, obj.type);
        initialValues.put(DishInfoObj.DISH_VARIABLE_PRICE, obj.variable_price);
        initialValues.put(DishInfoObj.DISH_SIZE, obj.size);
		//TODO: cooking style
//       initialValues.put(DishObj.DISH_COOK_TYPE, obj.cook_style);
        initialValues.put(DishInfoObj.DISH_FLAG, obj.flag);
        initialValues.put(DishInfoObj.DISH_COST, obj.cost);

        Log.i(Constants.APP_TAG, "addDishInfo:: "+obj.toString());
        return helper.myDB.insert(DishInfoObj.TABLE_NAME, DishInfoObj.DISH_ID, initialValues);			
	}
	
	public DishInfoObj[] listDishesInfo(int type){
		HashMap<String, ImageInfoObj> imgMap = listImageInfo();
		
		Cursor mCursor = helper.myDB.query(true, DishInfoObj.TABLE_NAME, new String[]{DishInfoObj.DISH_ID,
				DishInfoObj.DISH_QUERY_CODE, DishInfoObj.DISH_QUERY_CODE_2, DishInfoObj.DISH_NAME,
				DishInfoObj.DISH_SIZE, DishInfoObj.DISH_UNIT, DishInfoObj.DISH_PRICE, DishInfoObj.DISH_TYPE,
				DishInfoObj.DISH_VARIABLE_PRICE, DishInfoObj.DISH_SIZE, DishInfoObj.DISH_COOK_TYPE,
				DishInfoObj.DISH_FLAG, DishInfoObj.DISH_COST}, null, null, null, null, null,
				null);

		List<DishInfoObj> list = new ArrayList<DishInfoObj>();
		if (mCursor != null) {

			while (mCursor.moveToNext()) {

				DishInfoObj obj = new DishInfoObj();
				obj.id = mCursor.getString(mCursor.getColumnIndex(DishInfoObj.DISH_ID));
				obj.query_code = mCursor.getString(mCursor.getColumnIndex(DishInfoObj.DISH_QUERY_CODE));
				obj.query_code2 = mCursor.getString(mCursor.getColumnIndex(DishInfoObj.DISH_QUERY_CODE_2));
				obj.name = mCursor.getString(mCursor.getColumnIndex(DishInfoObj.DISH_NAME));
				obj.size = mCursor.getString(mCursor.getColumnIndex(DishInfoObj.DISH_SIZE));
				obj.unit = mCursor.getString(mCursor.getColumnIndex(DishInfoObj.DISH_UNIT));
				obj.price = mCursor.getFloat(mCursor.getColumnIndex(DishInfoObj.DISH_PRICE));
				obj.type = mCursor.getString(mCursor.getColumnIndex(DishInfoObj.DISH_TYPE));
				obj.variable_price = mCursor.getInt(mCursor.getColumnIndex(DishInfoObj.DISH_VARIABLE_PRICE)) == 1;
				//TODO: cooking style
//				obj.cook_style = mCursor.getString(mCursor.getColumnIndex(DishObj.DISH_COOK_TYPE));
				obj.flag = mCursor.getInt(mCursor.getColumnIndex(DishInfoObj.DISH_FLAG));
				obj.cost = mCursor.getInt(mCursor.getColumnIndex(DishInfoObj.DISH_COST));
				
				if (obj.type == null || obj.type.trim().equals("0")){
					continue;
				}
				
				ImageInfoObj imgObj = imgMap.get(obj.id);
				if (imgObj == null) {
					continue;
				}
				obj.img = imgObj;
				
				list.add(obj);
			}
			mCursor.close();
		}

		return list.toArray(new DishInfoObj[0]);
	}
	
	public void syncDishTypeInfo(DishTypeObj[] objs) {
		if (objs == null || objs.length == 0) {
			Log.e(Constants.APP_TAG, "syncDishTypeInfo error, data is null");
			return;
		}
		helper.myDB.delete(DishTypeObj.TABLE_NAME, null, null);
		for (DishTypeObj obj : objs) {
			addDishType(obj);
		}
	}
	
	public long addDishType(DishTypeObj obj){
		ContentValues initialValues = new ContentValues();
        initialValues.put(DishTypeObj.TYPE_ID, obj.id);
        initialValues.put(DishTypeObj.TYPE_NAME, obj.name);
        initialValues.put(DishTypeObj.PARENT_TYPE_ID, obj.parentId);
        initialValues.put(DishTypeObj.TYPE_INDEX, obj.index);

        Log.i(Constants.APP_TAG, "addDishType:: "+obj.toString());
        return helper.myDB.insert(DishTypeObj.TABLE_NAME, DishTypeObj.TYPE_ID, initialValues);		
	}
	
	public DishTypeObj[] listDishTypes(){
		Cursor mCursor = helper.myDB.query(true, DishTypeObj.TABLE_NAME, new String[]{DishTypeObj.TYPE_ID,
				DishTypeObj.TYPE_NAME, DishTypeObj.TYPE_ID}, null, null, null, null, null, null);
		
		List<DishTypeObj> list = new ArrayList<DishTypeObj>();
		if (mCursor != null) {

			while (mCursor.moveToNext()) {

				DishTypeObj obj = new DishTypeObj();
				obj.id = mCursor.getString(mCursor.getColumnIndex(DishTypeObj.TYPE_ID));
				obj.name = mCursor.getString(mCursor.getColumnIndex(DishTypeObj.TYPE_NAME));
				obj.index = mCursor.getInt(mCursor.getColumnIndex(DishTypeObj.TYPE_NAME));

				list.add(obj);
			}
			mCursor.close();

		}
		return list.toArray(new DishTypeObj[0]);		
	}
	
	public HashMap<String, DishTypeObj> listDishTypesMap() {
		HashMap<String, DishTypeObj> map = new HashMap<String, DishTypeObj>();
		DishTypeObj[] objs = listDishTypes();
		for (DishTypeObj obj : objs) {
			map.put(obj.id, obj);
		}
		return map;
	}
	
	public void syncFlavorInfo(FlavorInfoObj[] objs){
		if (objs == null || objs.length == 0) {
			Log.e(Constants.APP_TAG, "syncFlavorInfo error, data is null");
			return;
		}
		helper.myDB.delete(FlavorInfoObj.TABLE_NAME, null, null);
		for (FlavorInfoObj obj : objs) {
			addFlavorInfo(obj);
		}
	}
	
	public long addFlavorInfo(FlavorInfoObj obj){
		ContentValues initialValues = new ContentValues();
        initialValues.put(FlavorInfoObj.FLAVOR_ID, obj.id);
        initialValues.put(FlavorInfoObj.FLAVOR_NAME, obj.name);
        initialValues.put(FlavorInfoObj.IS_COOK_STYLE, obj.is_cook_style);

        Log.i(Constants.APP_TAG, "addFlavorInfo:: "+obj.toString());
        return helper.myDB.insert(FlavorInfoObj.TABLE_NAME, FlavorInfoObj.FLAVOR_ID, initialValues);		
	}
	
	public FlavorInfoObj[] listFlavorInfo(){
		Cursor mCursor = helper.myDB.query(true, FlavorInfoObj.TABLE_NAME, new String[]{FlavorInfoObj.FLAVOR_ID,
				FlavorInfoObj.FLAVOR_NAME, FlavorInfoObj.IS_COOK_STYLE}, null, null, null, null, null, null);
		
		List<FlavorInfoObj> list = new ArrayList<FlavorInfoObj>();
		if (mCursor != null) {

			while (mCursor.moveToNext()) {

				FlavorInfoObj obj = new FlavorInfoObj();
				obj.id = mCursor.getString(mCursor.getColumnIndex(FlavorInfoObj.FLAVOR_ID));
				obj.name = mCursor.getString(mCursor.getColumnIndex(FlavorInfoObj.FLAVOR_NAME));
				obj.is_cook_style = mCursor.getInt(mCursor.getColumnIndex(FlavorInfoObj.IS_COOK_STYLE)) == 1;

				list.add(obj);
			}
			mCursor.close();

		}
		return list.toArray(new FlavorInfoObj[0]);		
	}
	
	public void syncImageInfo(ServerImageInfoObj[] objs) {
		if (objs == null || objs.length == 0) {
			Log.e(Constants.APP_TAG, "syncImageInfo error, data is null");
			return;
		}
		helper.myDB.delete(ImageInfoObj.TABLE_NAME, null, null);
		HashMap<String, ImageInfoObj> imageMap = new HashMap<String, ImageInfoObj>();
		for (ServerImageInfoObj sObj : objs) {
			String id = FunctionUtil.formatDishId(sObj.name);
			ImageInfoObj estImgObj = imageMap.get(id);
			if (estImgObj == null) {
				ImageInfoObj mObj = new ImageInfoObj();
				mObj.set(sObj);
				imageMap.put(id, mObj);
			} else {
				estImgObj.set(sObj);
			}
		}
		
		Iterator it = imageMap.values().iterator();
		while (it.hasNext()) {
			ImageInfoObj obj = (ImageInfoObj) it.next();
			if (FunctionUtil.isImageFile(obj.name)) {
				Log.i(Constants.APP_TAG, "addImageInfo:: "+obj.toString());
				addImageInfo(obj);
			}
		}
	}
	
	public long addImageInfo(ImageInfoObj obj) {
		ContentValues initialValues = new ContentValues();
		initialValues.put(ImageInfoObj.IMAGE_ID, obj.id);
		
		if (TextUtils.isEmpty(obj.name) || obj.size<=0 || obj.modified_time == null){
			Log.w(Constants.APP_TAG, "addImageInfo:: invalid image info data "+obj.id);
			return -1;
		}
		
		initialValues.put(ImageInfoObj.IMAGE_NAME, obj.name);
		initialValues.put(ImageInfoObj.IMAGE_SIZE, obj.size);
		initialValues.put(ImageInfoObj.IMAGE_MODIFY_TIME, obj.modified_time.getTime());

		if (TextUtils.isEmpty(obj.small_name)) {
			initialValues.put(ImageInfoObj.SMALL_IMAGE_NAME, obj.name);
		} else {
			initialValues.put(ImageInfoObj.SMALL_IMAGE_NAME, obj.small_name);
		}
		if (obj.small_size > 0) {
			initialValues.put(ImageInfoObj.SMALL_IMAGE_SIZE, obj.small_size);
		} else {
			initialValues.put(ImageInfoObj.SMALL_IMAGE_SIZE, obj.size);
		}
		if (obj.small_modified_time != null) {
			initialValues.put(ImageInfoObj.SMALL_IMAGE_MODIFY_TIME, obj.small_modified_time.getTime());
		} else {
			initialValues.put(ImageInfoObj.SMALL_IMAGE_MODIFY_TIME, obj.modified_time.getTime());
		}
        
		if (!TextUtils.isEmpty(obj.video_name) && obj.video_size > 0 && obj.video_modified_time != null) {
			initialValues.put(ImageInfoObj.VIDEO_IMAGE_NAME, obj.video_name);
			initialValues.put(ImageInfoObj.VIDEO_IMAGE_SIZE, obj.video_size);
			initialValues.put(ImageInfoObj.VIDEO_IMAGE_MODIFY_TIME, obj.video_modified_time.getTime());
		}
		
        return helper.myDB.insert(ImageInfoObj.TABLE_NAME, ImageInfoObj.IMAGE_ID, initialValues);		
	}
		
	
	public HashMap<String, ImageInfoObj> listImageInfo(){
		Cursor mCursor = helper.myDB.query(true, ImageInfoObj.TABLE_NAME, new String[]{ImageInfoObj.IMAGE_ID,
				ImageInfoObj.IMAGE_NAME, ImageInfoObj.IMAGE_SIZE, ImageInfoObj.IMAGE_MODIFY_TIME,
				ImageInfoObj.SMALL_IMAGE_NAME, ImageInfoObj.SMALL_IMAGE_SIZE, ImageInfoObj.SMALL_IMAGE_MODIFY_TIME,
				}, null, null, null, null, null, null);
		
		HashMap<String, ImageInfoObj> map = new HashMap<String, ImageInfoObj>();
		if (mCursor != null) {

			while (mCursor.moveToNext()) {

				ImageInfoObj obj = new ImageInfoObj();
				obj.id = mCursor.getString(mCursor.getColumnIndex(ImageInfoObj.IMAGE_ID));
				obj.name = mCursor.getString(mCursor.getColumnIndex(ImageInfoObj.IMAGE_NAME));
				obj.size = mCursor.getLong(mCursor.getColumnIndex(ImageInfoObj.IMAGE_SIZE));
				obj.modified_time = new Date(mCursor.getLong(mCursor.getColumnIndex(ImageInfoObj.IMAGE_MODIFY_TIME)));

				obj.small_name = mCursor.getString(mCursor.getColumnIndex(ImageInfoObj.SMALL_IMAGE_NAME));
				obj.small_size = mCursor.getLong(mCursor.getColumnIndex(ImageInfoObj.SMALL_IMAGE_SIZE));
				obj.small_modified_time = new Date(mCursor.getLong(mCursor.getColumnIndex(ImageInfoObj.SMALL_IMAGE_MODIFY_TIME)));

				map.put(obj.id, obj);
			}
			mCursor.close();

		}
		return map;
	}	
}
