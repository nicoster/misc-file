package org.mfn.dishes.view;

import org.mfn.dishes.R;
import org.mfn.dishes.adapter.OrderedDishesAdapter;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;

public class OrderedDishesView extends LinearLayout implements OnItemClickListener{
	private Activity mContext;
	private EditText deskNumber;
	private EditText personNum;
	private ListView orderedDishesListView;
	private OrderedDishesAdapter mAdapter;
	private Button mReload;
	
	public OrderedDishesView(Context context) {
		super(context);
		initView(context);
		// TODO Auto-generated constructor stub
	}

	public OrderedDishesView(Context context, AttributeSet attrs) {
		super(context, attrs);
		initView(context);
		// TODO Auto-generated constructor stub
	}
	
	private void initView(Context context){
		mContext = (Activity)context;
		LayoutInflater inflater = mContext.getLayoutInflater();
		View orderedDishesView = inflater.inflate(R.layout.ordered_dishes, this, true);

		deskNumber = (EditText) orderedDishesView.findViewById(R.id.ordered_dishes_desk_number_text);
		personNum = (EditText) orderedDishesView.findViewById(R.id.ordered_dishes_person_number_text);
		orderedDishesListView = (ListView) orderedDishesView.findViewById(R.id.ordered_dishes_listview);
		mReload = (Button) orderedDishesView.findViewById(R.id.ordered_dishes_reload);
		mReload.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				OrderedDishesView.this.reloadData();
				
			}
		});
		
		mAdapter = new OrderedDishesAdapter(mContext);
		orderedDishesListView.setAdapter(mAdapter);
		orderedDishesListView.setOnItemClickListener(this);
	}
	
	private void reloadData(){
//		mAdapter = new OrderedDishesAdapter(mContext);
//		orderedDishesListView.setAdapter(mAdapter);
		mAdapter.notifyDataSetChanged();
	}
	
	public void updateUI(){
		mAdapter.notifyDataSetChanged();
	}
	
	@Override
	public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
		// TODO Auto-generated method stub
		
	}

}

	
