package org.mfn.dishes;

import org.mfn.dishes.util.DishesDataAdapter;
import org.mfn.dishes.vo.DishObj;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.GridView;

public class AllDishesActivity extends Activity {
	
	public static final String TAG = "AllDishesActivity";
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.all_dishes);

		GridView g = (GridView) findViewById(R.id.allDishesGrid);
		g.setAdapter(new DishesAdapter(this));
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
