package org.mfn.dishes.adapter;

import java.util.List;

import org.mfn.dishes.R;
import org.mfn.dishes.datastore.PageGridDishesInfo;
import org.mfn.dishes.vo.DishInfo;
import org.mfn.dishes.vo.DishInfoObj;

import android.app.Activity;
import android.content.Context;
import android.graphics.drawable.Drawable;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

public class DishesGridAdapter extends BaseAdapter {
	private List<DishInfoObj> mDishesList;
	private List<DishInfo> mDishInfos;
//	private DishInfoObj dishesInfo = null;
	private DishInfo dishInfo = null;
	private LayoutInflater mInflater = null;
	private Activity mContext = null;
	private ViewHolder holder = null;
	private IDishesGridAdapterCallBack mCallBack;
	PageGridDishesInfo mPageInfo;
	
	public DishesGridAdapter(Context context, PageGridDishesInfo pageInfo) {
		mContext = (Activity) context;
		mInflater = mContext.getLayoutInflater();
		mPageInfo = pageInfo;
		mDishesList = pageInfo.dishesList;
		
		Log.w("DishesGridAdapter", "type="+mPageInfo.dish_type_name+" dish number="+mDishesList.size());
		for (DishInfoObj obj: mDishesList){
			Log.i("DishesGridAdapter", "*name="+obj.name+" img="+obj.img.getImgUrl(true));
		}
	}
	
	public DishesGridAdapter(Context context, List<DishInfo> dishInfos) {
		mContext = (Activity) context;
		mInflater = mContext.getLayoutInflater();
		mDishInfos = dishInfos;
//		for(DishInfo dishInfo : mDishInfos){
//			Log.d("DishesGridAdapter", "name = " + dishInfo.getName() + ", code = " + dishInfo.getCode() + ", type = " + dishInfo.getCategoryCodes().get(0));
//		}
	} 

	@Override
	public int getCount() {
//		Log.d("DishesGridAdapter", "getCount ======");
		if(mDishInfos != null){
			return mDishInfos.size();
		}
		return 0;
	}

	@Override
	public DishInfo getItem(int position) {
//		Log.d("DishesGridAdapter", "getItem ====");
		return mDishInfos.get(position);
	}

	@Override
	public long getItemId(int position) {
//		Log.d("DishesGridAdapter", "getItemId  ===");
		return position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
//		Log.d("DishesGridAdapter", "getView ===");
		if(convertView == null || convertView.getTag() == null){
			convertView = this.mInflater.inflate(R.layout.grid_dish_item, parent, false);
			holder = new ViewHolder(convertView);
			convertView.setTag(holder);
		}else{
			holder = (ViewHolder)convertView.getTag();
		}
		dishInfo = mDishInfos.get(position);
		if(dishInfo != null){
			String imgSrc = dishInfo.getImageInfo() == null ? null : dishInfo.getImageInfo().getSmallImagePath();
			String dishName = dishInfo.getName();
			String dishComments = dishInfo.getName();
			String price = String.valueOf(dishInfo.getPrice()) + "/" + dishInfo.getUnit();
			
			Drawable imageDrawable = null;
			if(imgSrc == null){
				holder.imageView.setImageResource(R.drawable.a00010001);
			}else{
				Log.d("Dishes", "image path = " + imgSrc);
				imageDrawable = Drawable.createFromPath(imgSrc);
				holder.imageView.setImageDrawable(imageDrawable);
			}
			
			holder.dishName.setText(dishName);
			holder.dishComments.setText(dishComments);
			holder.price.setText(price);
			
			final int pos = position;
			holder.imageView.setOnClickListener(new View.OnClickListener() {
				public void onClick(View v) {
					mCallBack.onImageClick(pos);
				}
			});
			holder.orderBtn.setOnClickListener(new View.OnClickListener() {
				
				@Override
				public void onClick(View v) {
					mCallBack.onBtnClick(pos);
					
				}
			});
		}
		
//		dishesInfo = mDishInfos.get(position);
//		if(dishesInfo != null){
//			String imgSrc = dishesInfo.img.getImgUrl(true);
//			String dishName = dishesInfo.name;
//			String dishComments = dishesInfo.unit;
//			String price = String.valueOf(dishesInfo.price);
//			
//			Drawable imageDrawable = null;
//			if(imgSrc == null){
//				holder.imageView.setImageResource(R.drawable.a00010001);
//			}else{
//				imageDrawable = Drawable.createFromPath(imgSrc);
//				holder.imageView.setImageDrawable(imageDrawable);
//			}
//			
//			holder.dishName.setText(dishName);
//			holder.dishComments.setText(dishComments);
//			holder.price.setText(price);
//			final int pos = position;
//			holder.imageView.setOnClickListener(new View.OnClickListener() {
//				public void onClick(View v) {
//					mCallBack.onImageClick(pos);
//				}
//			});
//			holder.orderBtn.setOnClickListener(new View.OnClickListener() {
//				
//				@Override
//				public void onClick(View v) {
//					mCallBack.onBtnClick(pos);
//					
//				}
//			});
//		}
		
		return convertView;
	}
	

	public void setCallBack(IDishesGridAdapterCallBack callBack){
		mCallBack = callBack;
	}
	
	public interface IDishesGridAdapterCallBack{
		public void onImageClick(int position);
		public void onBtnClick(int position);
	}
	
	private class ViewHolder{
		ImageView imageView;
		TextView dishName;
		TextView dishComments;
		TextView price;
		ImageButton orderBtn;
		
		public ViewHolder(View base){
			imageView = (ImageView) base.findViewById(R.id.dish_item_image);
			dishName = (TextView) base.findViewById(R.id.dish_item_name);
			dishComments = (TextView) base.findViewById(R.id.dish_item_comments);
			price = (TextView) base.findViewById(R.id.dish_item_price);
			orderBtn = (ImageButton) base.findViewById(R.id.dish_item_order_btn);
		}
	}

}
