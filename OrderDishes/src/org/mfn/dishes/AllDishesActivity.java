package org.mfn.dishes;

import java.util.List;

import org.mfn.dishes.util.DishesDataAdapter;
import org.mfn.dishes.view.ScrollLayout;
import org.mfn.dishes.vo.DishObj;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.GridView;

public class AllDishesActivity extends Activity {
	
	public static final String TAG = "AllDishesActivity";
	private ScrollLayout mScrollLayout;
	private static final float APP_PAGE_SIZE = 16.0f;
	private Context mContext;
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		mContext = this;
		setContentView(R.layout.all_dishes);
		
		mScrollLayout = (ScrollLayout)findViewById(R.id.ScrollLayoutAllDishes);
		

//		GridView g = (GridView) findViewById(R.id.allDishesGrid);
//		g.setAdapter(new DishesAdapter(this));
		
		GridView appPage = new GridView(this);
		appPage.setAdapter(new DishesAdapter(this));
		mScrollLayout.addView(appPage);
		
		Button b1 = (Button) findViewById(R.id.button1);

		b1.setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
				Intent intent = new Intent();
				intent.setClass(AllDishesActivity.this, AlreadyOrderedActivity.class);
				startActivity(intent);

			}
		});
		Button b2 = (Button) findViewById(R.id.button2);

		b2.setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
				Intent intent = new Intent();
				intent.setClass(AllDishesActivity.this, DishesTypeActivity.class);
				startActivity(intent);

			}
		});
		
		listAllDishes();
	}


	private void listAllDishes() {
		DishesDataAdapter adapter = DishesDataAdapter.getInstance();

		DishObj[] objs = adapter.listDishesInfo(-1);

		for (DishObj obj : objs) {
			Log.i(TAG, "ID=" + obj.id + "\tName=" + obj.name + "\tPrice=" + obj.price);
		}
	}
	
}
