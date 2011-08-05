package org.mfn.dishes.view;

import java.util.List;

import org.mfn.dishes.InitActivity;
import org.mfn.dishes.R;
import org.mfn.dishes.adapter.DishesCategoryAdapter;
import org.mfn.dishes.adapter.DishesCategoryAdapter.IDishesCategoryAdapterCallback;
import org.mfn.dishes.vo.DishCategoryInfo;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;

public class DishesCategoryView extends GridView implements IDishesCategoryAdapterCallback{
	private InitActivity mContext;
	private DishesCategoryAdapter mAdapter;
	
	public DishesCategoryView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		this.setBackgroundResource(R.drawable.default_bg);

	}

	public DishesCategoryView(Context context, AttributeSet attrs) {
		super(context, attrs);
		// TODO Auto-generated constructor stub
	}

	public DishesCategoryView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		// TODO Auto-generated constructor stub
	}
	
	public DishesCategoryView(Context context, List<DishCategoryInfo> dishCategoryInfos){		
		super(context);
		mContext = (InitActivity) context;
		this.initView();
		mAdapter = new DishesCategoryAdapter(context, dishCategoryInfos);
		this.setAdapter(mAdapter);
		mAdapter.setCallback(this);
//		this.setOnItemClickListener(listener);
		this.setBackgroundResource(R.drawable.default_bg);
	}
	
	private void initView(){
		setNumColumns(4);
		setPadding(20, 20, 20, 20);
		setStretchMode(STRETCH_COLUMN_WIDTH);
		setFocusable(true);
		setFocusableInTouchMode(true);
		setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
	}
	
	private OnItemClickListener listener = new OnItemClickListener() {
		public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
			String categoryCode = mAdapter.getItem(position).getDishCategoryCode();
			mContext.onCategoryClicked(categoryCode);
		}
	};
	
	public void onCatagoryImgClicked(int position){
		String categoryCode = mAdapter.getItem(position).getDishCategoryCode();
		mContext.onCategoryClicked(categoryCode);
	}
	

}
