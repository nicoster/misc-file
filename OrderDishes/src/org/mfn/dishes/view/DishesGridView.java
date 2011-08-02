package org.mfn.dishes.view;

import java.util.List;

import org.mfn.dishes.InitActivity;
import org.mfn.dishes.adapter.DishesGridAdapter;
import org.mfn.dishes.adapter.DishesGridAdapter.IDishesGridAdapterCallBack;
import org.mfn.dishes.datastore.DataStore;
import org.mfn.dishes.datastore.IOrderedDishesDataStore;
import org.mfn.dishes.datastore.PageGridDishesInfo;
import org.mfn.dishes.vo.DishInfo;
import org.mfn.dishes.vo.OrderedDishInfo;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;

public class DishesGridView extends GridView implements IDishesGridAdapterCallBack{
	
	private InitActivity mContext;
	private DishesGridAdapter mAdapter;
	private IOrderedDishesDataStore mOrderedDishesDataStore;

	public DishesGridView(Context context, PageGridDishesInfo pageInfo) {		
		super(context);
		InitDishesGridView(context, pageInfo);
	}
	
	public DishesGridView(Context context, List<DishInfo> dishInfos){
		super(context);
		initGridView(context, dishInfos);
	}

	public DishesGridView(Context context, AttributeSet attrs, PageGridDishesInfo pageInfo) {
		super(context, attrs);
		InitDishesGridView(context, pageInfo);
	}

	public DishesGridView(Context context, AttributeSet attrs, int defStyle, PageGridDishesInfo pageInfo) {
		super(context, attrs, defStyle);
		InitDishesGridView(context, pageInfo);
	}
	
	private void initGridView(Context context, List<DishInfo> dishInfos){
		mContext = (InitActivity) context;
		mOrderedDishesDataStore = DataStore.getInstance().getOrderedDishesDataStore();
		this.initView();
		this.loadDishesItem(dishInfos);
		this.setOnItemClickListener(listener);
	}
	
	private void loadDishesItem(List<DishInfo> dishInfos){
		mAdapter = new DishesGridAdapter(mContext,dishInfos);
		mAdapter.setCallBack(this);
		this.setAdapter(mAdapter);
	}
	
	private void InitDishesGridView(Context context, PageGridDishesInfo pageInfo){
		mContext = (InitActivity) context;
		this.initView();
		this.loadDishes(pageInfo);
		this.setOnItemClickListener(listener);
	}
	
	private void initView(){
		setNumColumns(AUTO_FIT);		
		setPadding(60, 20, 60, 20);
		setHorizontalSpacing(60);
		setVerticalSpacing(20);
		setGravity(Gravity.CENTER);
		setStretchMode(STRETCH_COLUMN_WIDTH);
		setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
	}
	
	public void loadDishes(PageGridDishesInfo pageInfo){
		mAdapter = new DishesGridAdapter(mContext,pageInfo);
		mAdapter.setCallBack(this);
		this.setAdapter(mAdapter);
	}
	
	public void onImageClick(int position){
		Log.d("DishesGridView", "onImageClick position = " + position);
		
	}
	public void onBtnClick(int position){
		Log.d("DishesGridView", "onBtnClick position = " + position);
		DishInfo selectedDishInfo = mAdapter.getItem(position);
		OrderedDishInfo orderedDishInfo = new OrderedDishInfo(selectedDishInfo, 1);
		mOrderedDishesDataStore.addDishesInfo(orderedDishInfo);
		mContext.updateUI();
	}
	
	private OnItemClickListener listener = new OnItemClickListener() {
		public void onItemClick(AdapterView<?> parent, View view, int position, long id){
			
		}
	};
}
