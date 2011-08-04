package org.mfn.dishes.view;

import java.util.List;

import org.mfn.dishes.adapter.DishTypeGridAdapter;
import org.mfn.dishes.vo.DishCategoryInfo;

import android.content.Context;
import android.widget.GridView;

public class DishTypeGridView extends GridView{

	private Context mContext;
	private DishTypeGridAdapter mAdapter;

	public DishTypeGridView(Context context, List<DishCategoryInfo> dishTypeList) {
		super(context);
		mContext = context;
		this.initView();
		mAdapter = new DishTypeGridAdapter(mContext, dishTypeList);
		this.setAdapter(mAdapter);
		
	}
	
	private void initView(){
		setNumColumns(4);
		setPadding(20, 20, 40, 20);
		setHorizontalSpacing(20);
		setVerticalSpacing(20);
		setFocusable(true);
		setFocusableInTouchMode(true);
		setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
	}
	  
	
}
