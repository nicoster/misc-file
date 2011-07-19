package org.mfn.dishes.adapter;

import java.util.List;

import org.mfn.dishes.R;
import org.mfn.dishes.datastore.DataStore;
import org.mfn.dishes.vo.GridDishesInfo;

import android.app.Activity;
import android.content.Context;
import android.graphics.drawable.Drawable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

public class DishesGridAdapter extends BaseAdapter {
	private List<GridDishesInfo> mDishesList;
	private GridDishesInfo dishesInfo = null;
	private LayoutInflater mInflater = null;
	private Activity mContext = null;
	private ViewHolder holder = null;
	private IDishesGridAdapterCallBack mCallBack;
	
	public DishesGridAdapter(Context context) {
		mContext = (Activity) context;
		mInflater = mContext.getLayoutInflater();
		mDishesList = this.getData();
	}
	
	private List<GridDishesInfo> getData(){
		return DataStore.getInstance().getDishesItemDataStore().getDishesInfos();
	}

	@Override
	public int getCount() {
		if(mDishesList != null){
			return mDishesList.size();
		}
		return 0;
	}

	@Override
	public GridDishesInfo getItem(int position) {
		return mDishesList.get(position);
	}

	@Override
	public long getItemId(int position) {
		return position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		if(convertView == null || convertView.getTag() == null){
			convertView = this.mInflater.inflate(R.layout.grid_dish_item, parent, false);
			holder = new ViewHolder(convertView);
			convertView.setTag(holder);
		}else{
			holder = (ViewHolder)convertView.getTag();
		}
		dishesInfo = mDishesList.get(position);
		if(dishesInfo != null){
			String imgSrc = dishesInfo.getImageSrc();
			String dishName = dishesInfo.getDishName();
			String dishComments = dishesInfo.getComment();
			String price = dishesInfo.getFormatedPrice();
			
			Drawable imageDrawable = null;
			if(imgSrc == null){
				holder.imageView.setImageResource(R.drawable.a00010001);
			}else{
				imageDrawable = Drawable.createFromPath(imgSrc);
				holder.imageView.setImageDrawable(imageDrawable);
			}
			
			holder.dishName.setText(dishName);
			holder.dishComments.setText(dishComments);
			holder.price.setText(price);
			
			holder.imageView.setOnClickListener(imageViewClickListener);
			holder.orderBtn.setOnClickListener(orderBtnClickListener);
		}
		
		return convertView;
	}
	
	private View.OnClickListener imageViewClickListener = new View.OnClickListener() {		
		@Override
		public void onClick(View v) {
			mCallBack.onImageClick(v);			
		}
	};
	
	private View.OnClickListener orderBtnClickListener = new View.OnClickListener() {		
		@Override
		public void onClick(View v) {
			mCallBack.onBtnClick(v);
		}
	};
	
	public void setCallBack(IDishesGridAdapterCallBack callBack){
		mCallBack = callBack;
	}
	
	public interface IDishesGridAdapterCallBack{
		public void onImageClick(View v);
		public void onBtnClick(View v);
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
