package org.mfn.dishes.datastore;

public class DataStore {
	private static DataStore mInstance;
	private IDishesItemDataStore mDishesItemDataStore;
	
	public static DataStore getInstance(){
		if(mInstance == null){
			mInstance = new DataStore();
		}
		return mInstance;
	}
	
	public DataStore(){
	}
	
	public IDishesItemDataStore getDishesItemDataStore(){
		if(mDishesItemDataStore == null){
			mDishesItemDataStore = new DishesItemDataStore();
		}
		return mDishesItemDataStore;
	}
	
}
