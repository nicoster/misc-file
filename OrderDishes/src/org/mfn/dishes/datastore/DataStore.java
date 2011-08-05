package org.mfn.dishes.datastore;

public class DataStore {
	private static DataStore mInstance;
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
