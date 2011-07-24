package org.mfn.dishes.view;

import org.mfn.dishes.adapter.DishTypeGridAdapter;
import org.mfn.dishes.adapter.DishesGridAdapter;

import android.content.Context;
import android.widget.GridView;
import android.widget.AbsListView.LayoutParams;

public class DishTypeGridView extends GridView{

	private Context mContext;
	private DishTypeGridAdapter mAdapter;

	public DishTypeGridView(Context context) {
		super(context);
		mContext = context;
		this.initView();
		this.loadDishTypes();
	}
	
	private void initView(){
		setNumColumns(4);
		setPadding(20, 20, 40, 20);
		setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
	}
	
	public void loadDishTypes(){
		mAdapter = new DishTypeGridAdapter(mContext);
		//mAdapter.setCallBack(this);
		this.setAdapter(mAdapter);
	}
}
