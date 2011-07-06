package org.mfn.dishes;


import android.app.Activity;
import android.os.Bundle;
import android.widget.GridView;

public class OrderDishes3Activity extends Activity {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.grid_2);

		GridView g = (GridView) findViewById(R.id.myGrid);
		g.setAdapter(new DishesAdapter(this));
	}

	
}
