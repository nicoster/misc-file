package org.mfn.dishes;


import android.app.Activity;
import android.os.Bundle;
import android.widget.GridView;

public class AllDishesActivity extends Activity {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.all_dishes);

		GridView g = (GridView) findViewById(R.id.allDishesGrid);
		g.setAdapter(new DishesAdapter(this));
	}

	
}
