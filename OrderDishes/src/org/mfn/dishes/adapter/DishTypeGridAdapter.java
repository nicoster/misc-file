package org.mfn.dishes.adapter;

import java.util.List;

import org.mfn.dishes.R;
import org.mfn.dishes.datastore.TypeGridDishesInfo;
import org.mfn.dishes.util.DishesDataAdapter;
import org.mfn.dishes.vo.DishTypeObj;

import android.app.Activity;
import android.content.Context;
import android.graphics.drawable.Drawable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

public class DishTypeGridAdapter extends BaseAdapter {

	private LayoutInflater mInflater = null;
	private Activity mContext = null;
	private ViewHolder mHolder = null;
	private TypeGridDishesInfo mGridDishType = null;
	
	private List<TypeGridDishesInfo> mDishTypeList = null;

	public DishTypeGridAdapter(Context context, List dishTypeList){
		mContext = (Activity) context;
		mInflater = mContext.getLayoutInflater();
		mDishTypeList = dishTypeList;
	}
	
	private DishTypeObj[] getData(){
		return DishesDataAdapter.getInstance().listDishTypes();
	}
	
	@Override
	public int getCount() {
		if (mDishTypeList != null) {
			return mDishTypeList.size();
		}
		return 0;
	}

	@Override
	public TypeGridDishesInfo getItem(int position) {
		
		return mDishTypeList.get(position);
	}

	@Override
	public long getItemId(int position) {
		return position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		if(convertView == null || convertView.getTag() == null){
			convertView = this.mInflater.inflate(R.layout.grid_dishtype_item, parent, false);
			mHolder = new ViewHolder(convertView);
			convertView.setTag(mHolder);
		}else{
			mHolder = (ViewHolder)convertView.getTag();
		}
		mGridDishType = mDishTypeList.get(position);
		if(mGridDishType != null){
			String imgSrc = getDefaultImgUrl();
			String dishName = mGridDishType.dish_type_name;
			
			Drawable imageDrawable = null;
			if(imgSrc == null){
				mHolder.imageView.setImageResource(R.drawable.a00010001);
			}else{
				imageDrawable = Drawable.createFromPath(imgSrc);
				mHolder.imageView.setImageDrawable(imageDrawable);
			}
			
			mHolder.dishTypeName.setText(dishName);
			mHolder.imageView.setOnClickListener(imageViewClickListener);
		}
		
		return convertView;
	}

	private View.OnClickListener imageViewClickListener = new View.OnClickListener() {		
		@Override
		public void onClick(View v) {
			
		}
	};
	
	private String getDefaultImgUrl(){
		if (mGridDishType.dishesList.size()>0){
			return mGridDishType.dishesList.get(0).img.getImgUrl(true);
		}
		return null;
	}
	
	private class ViewHolder{
		ImageView imageView;
		TextView dishTypeName;
		
		public ViewHolder(View base){
			imageView = (ImageView) base.findViewById(R.id.dishtype_item_image);
			dishTypeName = (TextView) base.findViewById(R.id.dishtype_item_name);
		}
	}
}
