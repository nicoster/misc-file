package org.mfn.dishes.datastore;

public class DataStore {
	private static DataStore mInstance;
	private IDishesItemDataStore mDishesItemDataStore = null;
	private IDishesDataStore mDishesDataStore = null;
	private IOrderedDishesDataStore mOrderedDishesDataStore = null;
	
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
	
	public IDishesItemDataStore getDishesItemDataStore(){
		if(mDishesItemDataStore == null){
			mDishesItemDataStore = new DishesItemDataStore();
		}
		return mDishesItemDataStore;
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
	
}
