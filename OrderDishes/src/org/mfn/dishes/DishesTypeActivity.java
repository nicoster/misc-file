package org.mfn.dishes;

import java.util.List;


import android.app.Activity;
import android.content.Intent;
import android.content.pm.ResolveInfo;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.GridView;
import android.widget.ImageView;

public class DishesTypeActivity extends Activity {

	  protected void onCreate(Bundle savedInstanceState) {
	        super.onCreate(savedInstanceState);

	        loadApps();

	        setContentView(R.layout.layout_animation_1);
	        GridView grid = (GridView) findViewById(R.id.grid);
	        grid.setAdapter(new DishesTypeActivity.AppsAdapter());
	        
			Button b1 = (Button) findViewById(R.id.button1);

			b1.setOnClickListener(new Button.OnClickListener() {
				public void onClick(View v) {
					Intent intent = new Intent();
					intent.setClass(DishesTypeActivity.this, AlreadyOrderedActivity.class);
					startActivity(intent);

				}
			});
			Button b2 = (Button) findViewById(R.id.button2);

			b2.setOnClickListener(new Button.OnClickListener() {
				public void onClick(View v) {
					Intent intent = new Intent();
					intent.setClass(DishesTypeActivity.this, AllDishesActivity.class);
					startActivity(intent);

				}
			});
	    }

	    private List<ResolveInfo> mApps;

	    private void loadApps() {
	        Intent mainIntent = new Intent(Intent.ACTION_MAIN, null);
	        mainIntent.addCategory(Intent.CATEGORY_LAUNCHER);

	        mApps = getPackageManager().queryIntentActivities(mainIntent, 0);
	    }

	    public class AppsAdapter extends BaseAdapter {
	        public View getView(int position, View convertView, ViewGroup parent) {
	            ImageView i = new ImageView(DishesTypeActivity.this);

	            ResolveInfo info = mApps.get(position % mApps.size());

	            i.setImageDrawable(info.activityInfo.loadIcon(getPackageManager()));
	            i.setScaleType(ImageView.ScaleType.FIT_CENTER);
	            final int w = (int) (72 * getResources().getDisplayMetrics().density + 0.5f);
	            i.setLayoutParams(new GridView.LayoutParams(w, w));
	            return i;
	        }


	        public final int getCount() {
	            return Math.min(32, mApps.size());
	        }

	        public final Object getItem(int position) {
	            return mApps.get(position % mApps.size());
	        }

	        public final long getItemId(int position) {
	            return position;
	        }
	    }

	}


