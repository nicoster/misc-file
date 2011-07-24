package org.mfn.dishes.adapter;

import org.mfn.dishes.R;
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

	private DishTypeObj[] mDishTypes;

	private LayoutInflater mInflater = null;
	private Activity mContext = null;
	private ViewHolder holder = null;
	private DishTypeObj dishType = null;

	public DishTypeGridAdapter(Context context){
		mContext = (Activity) context;
		mInflater = mContext.getLayoutInflater();
		mDishTypes = getData();
	}
	
	private DishTypeObj[] getData(){
		return DishesDataAdapter.getInstance().listDishTypes();
	}
	
	@Override
	public int getCount() {
		if (mDishTypes != null) {
			return mDishTypes.length;
		}
		return 0;
	}

	@Override
	public DishTypeObj getItem(int position) {
		
		return mDishTypes[position];
	}

	@Override
	public long getItemId(int position) {
		return position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		if(convertView == null || convertView.getTag() == null){
			convertView = this.mInflater.inflate(R.layout.grid_dishtype_item, parent, false);
			holder = new ViewHolder(convertView);
			convertView.setTag(holder);
		}else{
			holder = (ViewHolder)convertView.getTag();
		}
		dishType = mDishTypes[position];
		if(dishType != null){
			String imgSrc = null;
			String dishName = dishType.name;
			
			Drawable imageDrawable = null;
			if(imgSrc == null){
				holder.imageView.setImageResource(R.drawable.a00010001);
			}else{
				imageDrawable = Drawable.createFromPath(imgSrc);
				holder.imageView.setImageDrawable(imageDrawable);
			}
			
			holder.dishTypeName.setText(dishName);
			holder.imageView.setOnClickListener(imageViewClickListener);
		}
		
		return convertView;
	}

	private View.OnClickListener imageViewClickListener = new View.OnClickListener() {		
		@Override
		public void onClick(View v) {
			
		}
	};
	
	private class ViewHolder{
		ImageView imageView;
		TextView dishTypeName;
		
		public ViewHolder(View base){
			imageView = (ImageView) base.findViewById(R.id.dishtype_item_image);
			dishTypeName = (TextView) base.findViewById(R.id.dishtype_item_name);
		}
	}
}
