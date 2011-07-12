package org.mfn.dishes;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.GridView;

public class AllDishesActivity extends Activity {

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
	}

}
