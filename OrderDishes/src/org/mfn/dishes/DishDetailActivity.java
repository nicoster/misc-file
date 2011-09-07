package org.mfn.dishes;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.ImageView;

public class DishDetailActivity extends Activity {
	private ImageView mImage = null;
	
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.dish_detail);		
		
		Intent intent = getIntent();
		String dishId = intent.getStringExtra("dishId");
		
		mImage = (ImageView) findViewById(R.id.dish_detail_image);
	}

}
