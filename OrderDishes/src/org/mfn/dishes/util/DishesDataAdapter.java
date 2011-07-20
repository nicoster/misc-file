package org.mfn.dishes.util;

import java.util.ArrayList;
import java.util.List;

import org.mfn.dishes.vo.DishInfoObj;
import org.mfn.dishes.vo.DishTypeObj;
import org.mfn.dishes.vo.FlavorInfoObj;
import org.mfn.dishes.vo.UserInfoObj;

import android.content.ContentValues;
import android.database.Cursor;

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
	
	public void syncUsersInfo(UserInfoObj[] objs){
		helper.myDB.delete(UserInfoObj.TABLE_NAME, null, null);
		for (UserInfoObj obj: objs){
			addUserInfo(obj);
		}
	}
	
	public long addUserInfo(UserInfoObj obj){
		ContentValues initialValues = new ContentValues();
        initialValues.put(UserInfoObj.USER_ID, obj.id);
        initialValues.put(UserInfoObj.USER_NAME, obj.name);
        initialValues.put(UserInfoObj.USER_LEVEL, obj.level);

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
        initialValues.put(DishInfoObj.DISH_IMAGE, obj.image);

        return helper.myDB.insert(DishInfoObj.TABLE_NAME, DishInfoObj.DISH_ID, initialValues);			
	}
	
	public DishInfoObj[] listDishesInfo(int type){
		Cursor mCursor = helper.myDB.query(true, DishInfoObj.TABLE_NAME, new String[]{DishInfoObj.DISH_ID,
				DishInfoObj.DISH_QUERY_CODE, DishInfoObj.DISH_QUERY_CODE_2, DishInfoObj.DISH_NAME,
				DishInfoObj.DISH_SIZE, DishInfoObj.DISH_UNIT, DishInfoObj.DISH_PRICE, DishInfoObj.DISH_TYPE,
				DishInfoObj.DISH_VARIABLE_PRICE, DishInfoObj.DISH_SIZE, DishInfoObj.DISH_COOK_TYPE,
				DishInfoObj.DISH_FLAG, DishInfoObj.DISH_COST, DishInfoObj.DISH_IMAGE}, null, null, null, null, null,
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
				obj.image = mCursor.getString(mCursor.getColumnIndex(DishInfoObj.DISH_IMAGE));

				list.add(obj);
			}
			mCursor.close();
		}

		return list.toArray(new DishInfoObj[0]);
	}
	
	public void syncDishTypeInfo(DishTypeObj[] objs) {
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

        return helper.myDB.insert(DishTypeObj.TABLE_NAME, DishTypeObj.TYPE_ID, initialValues);		
	}
	
	public DishTypeObj[] listDishTypes(){
		Cursor mCursor = helper.myDB.query(true, DishTypeObj.TABLE_NAME, new String[]{DishTypeObj.TYPE_ID,
				DishTypeObj.TYPE_NAME, DishTypeObj.TYPE_ID}, null, null, null, null, null, null);
		
		List<DishTypeObj> list = new ArrayList<DishTypeObj>();
		if (mCursor != null) {

			while (mCursor.moveToNext()) {

				DishTypeObj obj = new DishTypeObj();
				obj.id = "" + mCursor.getInt(mCursor.getColumnIndex(DishTypeObj.TYPE_ID));
				obj.name = mCursor.getString(mCursor.getColumnIndex(DishTypeObj.TYPE_NAME));
				obj.index = mCursor.getInt(mCursor.getColumnIndex(DishTypeObj.TYPE_NAME));

				list.add(obj);
			}
			mCursor.close();

		}
		return list.toArray(new DishTypeObj[0]);		
	}
	
	public void syncFlavorInfo(FlavorInfoObj[] objs){
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

        return helper.myDB.insert(FlavorInfoObj.TABLE_NAME, FlavorInfoObj.FLAVOR_ID, initialValues);		
	}
	
}
