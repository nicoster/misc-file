package org.mfn.dishes;

import org.mfn.dishes.adapter.OrderedDishesAdapter;
import org.mfn.dishes.datastore.DataStore;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ListView;

public class OrderedDishesActivity extends Activity {
	private ListView orderedDishesListView;
	private OrderedDishesAdapter mAdapter;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.ordered_dishes);
		
		orderedDishesListView = (ListView) findViewById(R.id.ordered_dishes_listview);
		View header = (View) getLayoutInflater().inflate(R.layout.ordered_dish_header, orderedDishesListView, false);
		orderedDishesListView.addHeaderView(header);
		mAdapter = new OrderedDishesAdapter(this);
		orderedDishesListView.setAdapter(mAdapter);		
		
		EditText totalPriceText = (EditText) findViewById(R.id.ordered_dishes_total_price_text);
		totalPriceText.setText(String.valueOf(DataStore.getInstance().getOrderedDishesDataStore().getTotlePrice()));
	}
}
