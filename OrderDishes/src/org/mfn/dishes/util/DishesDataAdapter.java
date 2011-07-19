package org.mfn.dishes.util;

import java.util.ArrayList;
import java.util.List;

import org.mfn.dishes.vo.DishObj;
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
	
	public void syncDishesInfo(DishObj[] objs){
		helper.myDB.delete(DishObj.TABLE_NAME, null, null);
		for (DishObj obj: objs){
			addDishInfo(obj);
		}
	}
	
	public long addDishInfo(DishObj obj){
		ContentValues initialValues = new ContentValues();
        initialValues.put(DishObj.DISH_ID, obj.id);
        initialValues.put(DishObj.DISH_QUERY_CODE, obj.query_code);
        initialValues.put(DishObj.DISH_QUERY_CODE_2, obj.query_code2);
        initialValues.put(DishObj.DISH_NAME, obj.name);
        initialValues.put(DishObj.DISH_SIZE, obj.size);
        initialValues.put(DishObj.DISH_UNIT, obj.unit);
        initialValues.put(DishObj.DISH_PRICE, obj.price);
        initialValues.put(DishObj.DISH_TYPE, obj.type);
        initialValues.put(DishObj.DISH_VARIABLE_PRICE, obj.variable_price);
        initialValues.put(DishObj.DISH_SIZE, obj.size);
		//TODO: cooking style
//       initialValues.put(DishObj.DISH_COOK_TYPE, obj.cook_style);
        initialValues.put(DishObj.DISH_FLAG, obj.flag);
        initialValues.put(DishObj.DISH_COST, obj.cost);
        initialValues.put(DishObj.DISH_IMAGE, obj.image);

        return helper.myDB.insert(DishObj.TABLE_NAME, DishObj.DISH_ID, initialValues);			
	}
	
	public DishObj[] listDishesInfo(int type){
		Cursor mCursor = helper.myDB.query(true, DishObj.TABLE_NAME, new String[]{DishObj.DISH_ID,
				DishObj.DISH_QUERY_CODE, DishObj.DISH_QUERY_CODE_2, DishObj.DISH_NAME,
				DishObj.DISH_SIZE, DishObj.DISH_UNIT, DishObj.DISH_PRICE, DishObj.DISH_TYPE,
				DishObj.DISH_VARIABLE_PRICE, DishObj.DISH_SIZE, DishObj.DISH_COOK_TYPE,
				DishObj.DISH_FLAG, DishObj.DISH_COST, DishObj.DISH_IMAGE}, null, null, null, null, null,
				null);

		List<DishObj> list = new ArrayList<DishObj>();
		if (mCursor != null) {

			while (mCursor.moveToNext()) {

				DishObj obj = new DishObj();
				obj.id = mCursor.getString(mCursor.getColumnIndex(DishObj.DISH_ID));
				obj.query_code = mCursor.getString(mCursor.getColumnIndex(DishObj.DISH_QUERY_CODE));
				obj.query_code2 = mCursor.getString(mCursor.getColumnIndex(DishObj.DISH_QUERY_CODE_2));
				obj.name = mCursor.getString(mCursor.getColumnIndex(DishObj.DISH_NAME));
				obj.size = mCursor.getString(mCursor.getColumnIndex(DishObj.DISH_SIZE));
				obj.unit = mCursor.getString(mCursor.getColumnIndex(DishObj.DISH_UNIT));
				obj.price = mCursor.getFloat(mCursor.getColumnIndex(DishObj.DISH_PRICE));
				obj.type = mCursor.getString(mCursor.getColumnIndex(DishObj.DISH_TYPE));
				obj.variable_price = mCursor.getInt(mCursor.getColumnIndex(DishObj.DISH_VARIABLE_PRICE)) == 1;
				//TODO: cooking style
//				obj.cook_style = mCursor.getString(mCursor.getColumnIndex(DishObj.DISH_COOK_TYPE));
				obj.flag = mCursor.getInt(mCursor.getColumnIndex(DishObj.DISH_FLAG));
				obj.cost = mCursor.getInt(mCursor.getColumnIndex(DishObj.DISH_COST));
				obj.image = mCursor.getString(mCursor.getColumnIndex(DishObj.DISH_IMAGE));

				list.add(obj);
			}
			mCursor.close();
		}

		return list.toArray(new DishObj[0]);
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
