package org.mfn.dishes.datastore;

public class DataStore {
	private static DataStore mInstance;
	private IDishesDataStore mDishesDataStore = null;
	private IOrderedDishesDataStore mOrderedDishesDataStore = null;
	private IUserDataStore mUserDataStore = null;
	
	public static DataStore getInstance(){
		if(mInstance == null){
			mInstance = new DataStore();
		}
		return mInstance;
	}
	
	public DataStore(){
	}
	
	/**
	 * initiate data from DB
	 */
	public void initDishesData(){
		DBOperator.getInstance().loadDataFromDB();
		
	}

	public IDishesDataStore getDishesDataStore(){
		if(mDishesDataStore == null){
			mDishesDataStore = new DishesDataStore();
		}
		return mDishesDataStore;
	}
	
	public IOrderedDishesDataStore getOrderedDishesDataStore(){
		if(mOrderedDishesDataStore == null){
			mOrderedDishesDataStore = new OrderedDishInfoDataStore();
		}
		return mOrderedDishesDataStore;
	}
	
	public IUserDataStore getUserDataStore(){
		if(mUserDataStore == null){
			mUserDataStore = new UserDataStore();
		}
		return mUserDataStore;
	}
	
	public void clearAllData(){
		if(mDishesDataStore != null) {
			mDishesDataStore.clearDishesData();
		}
		if(mOrderedDishesDataStore != null) {
			mOrderedDishesDataStore.clearOrderedDishesData();
		}
		if(mUserDataStore != null) {
			mUserDataStore.clearUserData();
		}		
	}
	
}
