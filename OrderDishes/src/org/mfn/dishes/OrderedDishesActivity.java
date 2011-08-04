package org.mfn.dishes;

import org.mfn.dishes.adapter.OrderedDishesAdapter;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ListView;

public class OrderedDishesActivity extends Activity {
	private ListView orderedDishesListView;
	private OrderedDishesAdapter mAdapter;
	private Button mReload;

	public OrderedDishesActivity() {
		// TODO Auto-generated constructor stub
	}

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.ordered_dishes);
		
		orderedDishesListView = (ListView) findViewById(R.id.ordered_dishes_listview);
		mAdapter = new OrderedDishesAdapter(this);
		orderedDishesListView.setAdapter(mAdapter);		
		
		mReload = (Button) findViewById(R.id.ordered_dishes_reload);
		mReload.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				OrderedDishesActivity.this.reloadData();
				
			}
		});
	}
	
	private void reloadData(){
		mAdapter.notifyDataSetChanged();
	}
}
