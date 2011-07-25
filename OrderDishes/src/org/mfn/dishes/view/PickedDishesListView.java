package org.mfn.dishes.view;

import org.mfn.dishes.adapter.PickedDishesExpListAdapter;

import android.content.Context;
import android.view.View;
import android.widget.ExpandableListView;

public class PickedDishesListView extends ExpandableListView {

	PickedDishesExpListAdapter mAdapter;
	private Context mContext;

	public PickedDishesListView(Context context) {
		super(context);
		mContext = context;
		mAdapter = new PickedDishesExpListAdapter(context);
		this.setAdapter(mAdapter);

		this.setOnChildClickListener(new OnChildClickListener() {

			@Override
			public boolean onChildClick(ExpandableListView parent, View v, int groupPosition, int childPosition, long id) {
				// TODO Auto-generated method stub
				return false;
			}

		});
	}

}
