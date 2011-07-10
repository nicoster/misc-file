package org.mfn.dishes;


import android.app.Activity;
import android.os.Bundle;
import android.widget.GridView;

public class MainActivity extends Activity {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.main);

		GridView g = (GridView) findViewById(R.id.myGrid);
		g.setAdapter(new DishesAdapter(this));
	}

	
}
