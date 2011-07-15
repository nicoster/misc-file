package org.mfn.dishes.util;

import java.util.ArrayList;
import java.util.List;

import org.mfn.dishes.vo.DishesObj;
import org.mfn.dishes.vo.DishesTypeObj;
import org.mfn.dishes.vo.UserInfoObj;


import android.content.ContentValues;
import android.database.Cursor;

public class DishesDataAdapter {
	
	private DishesDBHelpter helper = DishesDBHelpter.getInstance();
	
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
	
	
	public UserInfoObj[] listUserInfos(int level) {
		Cursor mCursor = helper.myDB.query(true, UserInfoObj.TABLE_NAME, new String[]{UserInfoObj.USER_ID,
				UserInfoObj.USER_NAME, UserInfoObj.USER_LEVEL}, null, null, null, null, null, null);

		List<UserInfoObj> list = new ArrayList<UserInfoObj>();
		if (mCursor != null) {

			while (mCursor.moveToNext()) {

				UserInfoObj obj = new UserInfoObj();
				obj.id = mCursor.getInt(mCursor.getColumnIndex(UserInfoObj.USER_ID));
				obj.name = mCursor.getString(mCursor.getColumnIndex(UserInfoObj.USER_NAME));
				obj.level = mCursor.getInt(mCursor.getColumnIndex(UserInfoObj.USER_LEVEL));

				list.add(obj);
			}
		}

		return list.toArray(new UserInfoObj[0]);
	}
	
	public void syncDishesInfo(DishesObj[] objs){
		helper.myDB.delete(DishesObj.TABLE_NAME, null, null);
		for (DishesObj obj: objs){
			addDishesInfo(obj);
		}
	}
	
	public long addDishesInfo(DishesObj obj){
		ContentValues initialValues = new ContentValues();
        initialValues.put(DishesObj.DISHES_ID, obj.id);
        initialValues.put(DishesObj.DISHES_QUERY_CODE, obj.query_code);
        initialValues.put(DishesObj.DISHES_QUERY_CODE_2, obj.query_code2);
        initialValues.put(DishesObj.DISHES_NAME, obj.name);
        initialValues.put(DishesObj.DISHES_SIZE, obj.size);
        initialValues.put(DishesObj.DISHES_UNIT, obj.unit);
        initialValues.put(DishesObj.DISHES_PRICE, obj.price);
        initialValues.put(DishesObj.DISHES_TYPE, obj.type);
        initialValues.put(DishesObj.DISHES_VARIABLE_PRICE, obj.variable_price);
        initialValues.put(DishesObj.DISHES_SIZE, obj.size);
        initialValues.put(DishesObj.DISHES_COOK_TYPE, obj.cook_type);
        initialValues.put(DishesObj.DISHES_FLAG, obj.flag);
        initialValues.put(DishesObj.DISHES_COST, obj.cost);
        initialValues.put(DishesObj.DISHES_IMAGE, obj.image);

        return helper.myDB.insert(DishesObj.TABLE_NAME, DishesObj.DISHES_ID, initialValues);			
	}
	
	public DishesObj[] listDishesInfo(int type){
		Cursor mCursor = helper.myDB.query(true, DishesObj.TABLE_NAME, new String[]{DishesObj.DISHES_ID,
				DishesObj.DISHES_QUERY_CODE, DishesObj.DISHES_QUERY_CODE_2, DishesObj.DISHES_NAME,
				DishesObj.DISHES_SIZE, DishesObj.DISHES_UNIT, DishesObj.DISHES_PRICE, DishesObj.DISHES_TYPE,
				DishesObj.DISHES_VARIABLE_PRICE, DishesObj.DISHES_SIZE, DishesObj.DISHES_COOK_TYPE,
				DishesObj.DISHES_FLAG, DishesObj.DISHES_COST, DishesObj.DISHES_IMAGE}, null, null, null, null, null,
				null);

		List<DishesObj> list = new ArrayList<DishesObj>();
		if (mCursor != null) {

			while (mCursor.moveToNext()) {

				DishesObj obj = new DishesObj();
				obj.id = mCursor.getInt(mCursor.getColumnIndex(DishesObj.DISHES_ID));
				obj.query_code = mCursor.getString(mCursor.getColumnIndex(DishesObj.DISHES_QUERY_CODE));
				obj.query_code2 = mCursor.getString(mCursor.getColumnIndex(DishesObj.DISHES_QUERY_CODE_2));
				obj.name = mCursor.getString(mCursor.getColumnIndex(DishesObj.DISHES_NAME));
				obj.size = mCursor.getInt(mCursor.getColumnIndex(DishesObj.DISHES_SIZE));
				obj.unit = mCursor.getString(mCursor.getColumnIndex(DishesObj.DISHES_UNIT));
				obj.price = mCursor.getInt(mCursor.getColumnIndex(DishesObj.DISHES_PRICE));
				obj.type = mCursor.getInt(mCursor.getColumnIndex(DishesObj.DISHES_TYPE));
				obj.variable_price = mCursor.getInt(mCursor.getColumnIndex(DishesObj.DISHES_VARIABLE_PRICE)) == 1;
				obj.size = mCursor.getInt(mCursor.getColumnIndex(DishesObj.DISHES_SIZE));
				obj.cook_type = mCursor.getString(mCursor.getColumnIndex(DishesObj.DISHES_COOK_TYPE));
				obj.flag = mCursor.getInt(mCursor.getColumnIndex(DishesObj.DISHES_FLAG));
				obj.cost = mCursor.getInt(mCursor.getColumnIndex(DishesObj.DISHES_COST));
				obj.image = mCursor.getString(mCursor.getColumnIndex(DishesObj.DISHES_IMAGE));

				list.add(obj);
			}
		}

		return list.toArray(new DishesObj[0]);
	}
	
	public void addDishesType(DishesTypeObj obj){
		
	}
	
	public DishesTypeObj[] listDishesTypes(){
		return null;
	}
}
