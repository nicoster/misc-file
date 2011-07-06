package org.mfn.dishes;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;




public class DishesAdapter extends BaseAdapter {
	
	public DishesAdapter(Context c){
		mContext = c;
	}
	
	public int getCount() {
		return mThumbIds.length;
	}

	public Object getItem(int position) {
		return position;
	}

	public long getItemId(int position) {
		return position;
	}

	public View getView(int position, View convertView, ViewGroup parent) {
		ImageView imageView;
		if (convertView == null) {
			imageView = new ImageView(mContext);
			imageView.setLayoutParams(new GridView.LayoutParams(240, 180));
			imageView.setAdjustViewBounds(false);
			imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
			imageView.setPadding(8, 8, 8, 8);
		} else {
			imageView = (ImageView) convertView;
		}

		imageView.setImageResource(mThumbIds[position]);

		return imageView;
	}

	private Context mContext;

	private Integer[] mThumbIds = { R.drawable.a00010001, R.drawable.a00010002, R.drawable.a00010003,
            R.drawable.a00010004, R.drawable.a00010005, R.drawable.a00010006, R.drawable.a00010007,
            R.drawable.a00010008, R.drawable.a00010009, R.drawable.a00010010 };


}
