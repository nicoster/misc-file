package org.mfn.dishes.adapter;

import java.util.List;

import org.mfn.dishes.R;
import org.mfn.dishes.datastore.DataStore;
import org.mfn.dishes.vo.OrderedDishInfo;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

public class OrderedDishesAdapter extends BaseAdapter {
	private List<OrderedDishInfo> mOrderedDishInfos = null;
	private Activity mContext;
	private LayoutInflater inflater;
	private ViewHolder holder = null;

	public OrderedDishesAdapter(Context context) {
		this.mContext = (Activity) context;
		inflater = mContext.getLayoutInflater();
		this.mOrderedDishInfos = DataStore.getInstance().getOrderedDishesDataStore().getOrderedDishInfo();
	}

	public int getCount() {
		Log.d("OrderedDishesAdapter", "getCount size = " + this.mOrderedDishInfos.size());
		if(this.mOrderedDishInfos == null){
			return 0;
		}
		return this.mOrderedDishInfos.size();
	}

	public OrderedDishInfo getItem(int position) {
//		if(this.mOrderedDishInfos == null){
//			return null;
//		}
		return this.mOrderedDishInfos.get(position);
	}

	public long getItemId(int position) {
		return position;
	}

	public View getView(int position, View convertView, ViewGroup parent) {	
		Log.e("OrderedDishesAdapter", " getView ======");
		if(convertView == null || convertView.getTag() == null){
			convertView = this.inflater.inflate(R.layout.ordered_dish_item, parent, false);
			holder = new ViewHolder(convertView);
			convertView.setTag(holder);
		}else{
			holder = (ViewHolder) convertView.getTag();
		}
		OrderedDishInfo orderedDishInfo = this.mOrderedDishInfos.get(position);
		if(orderedDishInfo != null){
			holder.index.setText(String.valueOf(position));
			holder.dishName.setText(orderedDishInfo.getDishInfo().getName());
			holder.unitPrice.setText(String.valueOf(orderedDishInfo.getDishInfo().getPrice()));
			holder.unit.setText(orderedDishInfo.getDishInfo().getUnit());
			holder.orderedNumber.setText(String.valueOf(orderedDishInfo.getOrderedNumber()));
			holder.totalPrice.setText(String.valueOf(orderedDishInfo.getTotalPrice()));
		}
		
		return convertView;
	}
	
	public void notifyDataSetChanged(){
		Log.d("OrderedDishesAdapter", "updateUI ==================");
		this.mOrderedDishInfos = DataStore.getInstance().getOrderedDishesDataStore().getOrderedDishInfo();
		super.notifyDataSetChanged();
	}
	
	private class ViewHolder{
		TextView index;
		TextView dishName;
		TextView unitPrice;
		TextView unit;
		TextView orderedNumber;
		TextView totalPrice;
		
		public ViewHolder(View view){
			index = (TextView) view.findViewById(R.id.ordered_dish_item_index);
			dishName = (TextView) view.findViewById(R.id.ordered_dish_item_name);
			unitPrice = (TextView) view.findViewById(R.id.order_dish_item_price);
			unit = (TextView) view.findViewById(R.id.ordered_dish_item_unit);
			orderedNumber = (TextView) view.findViewById(R.id.ordered_dish_item_count);
			totalPrice = (TextView) view.findViewById(R.id.ordered_dish_item_total_price);
		}
	}

}
