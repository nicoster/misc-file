package org.mfn.dishes.view;

import org.mfn.dishes.adapter.DishesGridAdapter;
import org.mfn.dishes.adapter.DishesGridAdapter.IDishesGridAdapterCallBack;
import org.mfn.dishes.datastore.PageGridDishesInfo;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.widget.GridView;

public class DishesGridView extends GridView implements IDishesGridAdapterCallBack{
	
	private Context mContext;
	private DishesGridAdapter mAdapter;

	public DishesGridView(Context context, PageGridDishesInfo pageInfo) {		
		super(context);
		mContext = context;
		this.initView();
		this.loadDishes(pageInfo);
	}

	public DishesGridView(Context context, AttributeSet attrs) {
		super(context, attrs);
		// TODO Auto-generated constructor stub
	}

	public DishesGridView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		// TODO Auto-generated constructor stub
	}
	
	private void initView(){
		setNumColumns(2);
		setPadding(40, 20, 40, 20);
		setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT , LayoutParams.MATCH_PARENT));
	}
	
	public void loadDishes(PageGridDishesInfo pageInfo){
		mAdapter = new DishesGridAdapter(mContext,pageInfo);
		mAdapter.setCallBack(this);
		this.setAdapter(mAdapter);
	}
	
	public void onImageClick(View v){
		
	}
	public void onBtnClick(View v){
		
	}
}
