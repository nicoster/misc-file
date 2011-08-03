package org.mfn.wap.group;

import java.util.*;

import android.content.Context;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;

public class WapIconAdapter extends BaseAdapter {
	
	private int num = 9;
	
	public WapIconAdapter(Context c) {
		mContext = c;
		
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
		ImageView imageView;
		if (convertView == null) {
			imageView = new ImageView(mContext);
			imageView.setLayoutParams(new GridView.LayoutParams(120, 120));
			imageView.setAdjustViewBounds(false);
			imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
			imageView.setPadding(8, 8, 8, 8);
		} else {
			imageView = (ImageView) convertView;
		}

		imageView.setImageResource(mThumbIds.get(position).getmIcon());

		return imageView;
	}

	private Context mContext;

	private List<WapItem> mThumbIds = new ArrayList<WapItem>();

}
