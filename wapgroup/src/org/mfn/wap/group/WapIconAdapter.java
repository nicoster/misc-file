package org.mfn.wap.group;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class WapIconAdapter extends BaseAdapter {
	
	private int num = 9;
	private ViewHolder holder = null;
	private LayoutInflater mInflater = null;
	private Activity mContext = null;
	
	public WapIconAdapter(Context c) {
		mContext = (Activity) c;
		
		mInflater = mContext.getLayoutInflater();
		
		String[] wap_names = c.getResources().getStringArray(R.array.wap_item_names);
        String[] wap_urls = c.getResources().getStringArray(R.array.wap_item_urls);
		
		for (int i = 0; i < num; i++) {
			WapItem wapItem = new WapItem();
			wapItem.setmIcon(R.drawable.a1 + i);
			wapItem.setWapName(wap_names[i]);
			wapItem.setWapUrl(wap_urls[i]);
			wapItem.setAvaiable(!TextUtils.isEmpty((wap_urls[i])));
			
			mThumbIds.add(wapItem);
		}
	}

	public int getCount() {
		return mThumbIds.size();
	}

	public WapItem getItem(int position) {
		return mThumbIds.get(position);
	}

	public long getItemId(int position) {
		return position;
	}

	public View getView(int position, View convertView, ViewGroup parent) {

		if(convertView == null || convertView.getTag() == null){
			convertView = this.mInflater.inflate(R.layout.grid_icon_item, parent, false);
			holder = new ViewHolder(convertView);
			convertView.setTag(holder);
//			convertView.setLayoutParams(new GridView.LayoutParams(120, 170));
//			convertView.setPadding(8, 8, 8, 8);			
		}else{
			holder = (ViewHolder)convertView.getTag();
		}
		
		final int pos = position;
		holder.imageView.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				WapItem item = getItem(pos);
				String wapName = item.getWapName();
				String wapUrl = item.getWapUrl();
				if (!item.isAvaiable()) {
					Toast.makeText(mContext, "[" + wapName + " ]功能暂时还未开通...", Toast.LENGTH_LONG).show();
					return;
				}

				Intent intent = new Intent();
				intent.putExtra(Constants.PARAM_WAP_URL, wapUrl);
				intent.setClass(mContext, WapPageActivity.class);
				mContext.startActivity(intent);
			}
		});
		
		WapItem item = this.getItem(position);
		holder.imageView.setImageResource(item.getmIcon());
		holder.wapName.setText(item.getWapName());
		
		return convertView;
	}

	private List<WapItem> mThumbIds = new ArrayList<WapItem>();
	
	private class ViewHolder{
		ImageView imageView;
		TextView wapName;
		
		public ViewHolder(View base){
			imageView = (ImageView) base.findViewById(R.id.wap_item_image);
			wapName = (TextView) base.findViewById(R.id.wap_item_name);
		}
	}

}
