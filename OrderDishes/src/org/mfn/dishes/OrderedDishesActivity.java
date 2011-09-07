package org.mfn.dishes;

import org.mfn.dishes.adapter.OrderedDishesAdapter;

import android.app.Activity;
import android.os.Bundle;
import android.widget.ListView;

public class OrderedDishesActivity extends Activity {
	private ListView orderedDishesListView;
	private OrderedDishesAdapter mAdapter;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.ordered_dishes);
		
		orderedDishesListView = (ListView) findViewById(R.id.ordered_dishes_listview);
		mAdapter = new OrderedDishesAdapter(this);
		orderedDishesListView.setAdapter(mAdapter);		
		
	}
}
