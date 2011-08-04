package org.mfn.dishes.adapter;

import java.util.List;

import org.mfn.dishes.R;
import org.mfn.dishes.vo.DishCategoryInfo;
import org.mfn.dishes.vo.DishInfo;

import android.app.Activity;
import android.content.Context;
import android.graphics.drawable.Drawable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

public class DishesCategoryAdapter extends BaseAdapter {
	private List<DishCategoryInfo> mCategoryInfos = null;
	private Activity mContext = null;
	private LayoutInflater inflater;
	private ViewHolder holder;
	private DishCategoryInfo categoryInfo;
	private IDishesCategoryAdapterCallback mCallback;
	
	
	public DishesCategoryAdapter(Context context, List<DishCategoryInfo> dishCategoryInfos) {
		this.mCategoryInfos = dishCategoryInfos;
		this.mContext = (Activity) context;
		inflater = mContext.getLayoutInflater();
	}

	@Override
	public int getCount() {
		if(this.mCategoryInfos != null){
			return this.mCategoryInfos.size();
		}
		return 0;
	}

	@Override
	public DishCategoryInfo getItem(int position) {
		if(this.mCategoryInfos != null){
			return this.mCategoryInfos.get(position);
		}
		return null;
	}

	@Override
	public long getItemId(int position) {
		return position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		if(convertView == null || convertView.getTag() == null){
			convertView = inflater.inflate(R.layout.grid_dishtype_item, parent, false);
			holder = new ViewHolder(convertView);
			convertView.setTag(holder);
		}else{
			holder = (ViewHolder) convertView.getTag();
		}
		
		categoryInfo = this.mCategoryInfos.get(position);
		if(categoryInfo != null){
			String imagePath = getDefaultImgUrl(categoryInfo);
			if(imagePath == null){
				holder.imageView.setImageResource(R.drawable.a00010001);
			}else{
				Drawable drawable = Drawable.createFromPath(imagePath);
				holder.imageView.setImageDrawable(drawable);
			}
			holder.categoryName.setText(categoryInfo.getDishCategoryName());
		}
		final int pos = position;
		holder.imageView.setOnClickListener(new View.OnClickListener() {			
			@Override
			public void onClick(View v) {
				mCallback.onCatagoryImgClicked(pos);				
			}
		});
		return convertView;
	}
	
	public void setCallback(IDishesCategoryAdapterCallback callback){
		mCallback = callback;
	}
	
	public interface IDishesCategoryAdapterCallback{
		void onCatagoryImgClicked(int position);
	}
	
	private String getDefaultImgUrl(DishCategoryInfo dishCategoryInfo){
		if (dishCategoryInfo.getAllDishInfos().size()>0){
			DishInfo dishInfo = dishCategoryInfo.getAllDishInfos().get(0);
			if(dishInfo == null || dishInfo.getImageInfo() == null || dishInfo.getImageInfo().getSmallImageName() == null){
				return null;
			}
			return dishCategoryInfo.getAllDishInfos().get(0).getImageInfo().getSmallImagePath();
		}
		return null;
	}
	
	private class ViewHolder{
		ImageView imageView;
		TextView categoryName;
		
		public ViewHolder(View base){
			imageView = (ImageView) base.findViewById(R.id.dishtype_item_image);
			categoryName = (TextView) base.findViewById(R.id.dishtype_item_name);
		}
	}

}
