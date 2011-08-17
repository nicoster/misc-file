package org.mfn.dishes;

import java.util.List;

import org.mfn.dishes.animation.Rotate3dAnimation;
import org.mfn.dishes.datastore.DataStore;
import org.mfn.dishes.datastore.IDishesDataStore;
import org.mfn.dishes.view.DishesCategoryView;
import org.mfn.dishes.view.DishesGridView;
import org.mfn.dishes.view.ScrollLayout;
import org.mfn.dishes.view.ScrollLayout.IScrollLayoutCallBack;
import org.mfn.dishes.vo.DishCategoryInfo;
import org.mfn.dishes.vo.DishInfo;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.animation.AccelerateInterpolator;
import android.view.animation.Animation;
import android.view.animation.DecelerateInterpolator;
import android.widget.ImageButton;
import android.widget.RelativeLayout;

public class InitActivity extends Activity implements OnClickListener, IScrollLayoutCallBack{
	private ImageButton mStartBtn;
	private ViewGroup mContainer;
	private RelativeLayout mEntry;
	private RelativeLayout mDishesMenus;
	private ScrollLayout mScrollLayout;
	
	private ImageButton mOrderedBtn;
	private ImageButton mCategoryBtn;
	
	private IDishesDataStore dishesDataStore;
	
//	private OrderedDishesView orderedDishesView;
	private int mCurrentPage = 0;
	
	private Handler handler;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		Log.i(Constants.APP_TAG, "InitActivity:onCreate");
		
		setContentView(R.layout.init);
		
		mStartBtn = (ImageButton)findViewById(R.id.startbtn);
		mContainer = (ViewGroup) findViewById(R.id.container);
        mEntry = (RelativeLayout) findViewById(R.id.entry);
        mDishesMenus = (RelativeLayout) findViewById(R.id.dishes_menus);
        mScrollLayout = (ScrollLayout) findViewById(R.id.scroll_layout);
        
        mCategoryBtn = (ImageButton)findViewById(R.id.btn_left);
        mOrderedBtn = (ImageButton)findViewById(R.id.btn_right);
        
        mStartBtn.setOnClickListener(this);
        
        dishesDataStore = DataStore.getInstance().getDishesDataStore();
        
        mScrollLayout.setCallBack(this);
        
        handler = new Handler(){
        	public void handleMessage(Message msg){
        		if(msg.what == 0){
        			updateUI();
        		}
        	}
        };
        
        prepareViews();
	}
	
	public void onPageShown(int page){
		Log.d("InitActivity", "onPageShown page = " + page);
		mCurrentPage = page;
	}
	
	
	
	private void prepareViews(){
		List<DishCategoryInfo> dishCategoryInfos = dishesDataStore.getAllDishCategoryInfos();
        mScrollLayout.addView(new DishesCategoryView(this, dishCategoryInfos));
		
		
        int dishesItemPages = dishesDataStore.getAllDishesPages();
        for(int i = 0; i < dishesItemPages; i++){
        	List<DishInfo> dishInfos = dishesDataStore.getDishInfosByPage(i);
        	if(dishInfos.size() > 0){
        		mScrollLayout.addView(new DishesGridView(this, dishInfos));
        	}
        }
        
        mOrderedBtn.setOnClickListener(new ImageButton.OnClickListener() {
			public void onClick(View v) {
				Intent intent = new Intent(InitActivity.this, OrderedDishesActivity.class);
				startActivity(intent);
			}
		});
        
        mCategoryBtn.setOnClickListener(new ImageButton.OnClickListener() {
			public void onClick(View v) {
				if(mCurrentPage > 2){
					mScrollLayout.setToScreen(2);
				}
				mScrollLayout.snapToScreen(0);
			}
		});

	}
	
	public void onStart(){
		super.onStart();
		Log.i(Constants.APP_TAG, "InitActivity: onStart");
	}

	public void onStop(){
		Log.i(Constants.APP_TAG, "InitActivity: onStop");
		super.onStop();
	}
	
	public void onDestroy() {
		Log.i(Constants.APP_TAG, "InitActivity: onDestroy");
		super.onDestroy();
	}
	
	public void onBackPressed(){
		DataStore.getInstance().clearAllData();
		android.os.Process.killProcess(android.os.Process.myPid());
		finish();		
	}
	
	public void onClick(View v){
    	applyRotation(0, -90);
    }
	
	public void onDishOrdered(){
		handler.sendEmptyMessage(0);
	}
	
	public void onCategoryClicked(String categoryCode){
		int pageNumber = dishesDataStore.getFirstPageByCategory(categoryCode);
		if(pageNumber == -1){
			pageNumber = 0;
		}
		pageNumber++;
		Log.d("InitActivity", "onCategoryClicked pageNumber = " + pageNumber);
		if(pageNumber > 2){
			mScrollLayout.setToScreen(pageNumber - 2);			
		}
		mScrollLayout.snapToScreen(pageNumber);
		
	}
	
	private void updateUI(){
//		orderedDishesView.updateUI();
//		orderedDishesView.invalidate();		
	}
    
    private void applyRotation(float start, float end){
		// Find the center of the container
		final float centerX = mContainer.getWidth() / 2.0f;
		final float centerY = mContainer.getHeight() / 2.0f;

		// Create a new 3D rotation with the supplied parameter
		// The animation listener is used to trigger the next animation
		final Rotate3dAnimation rotation = new Rotate3dAnimation(start, end, centerX, centerY, 310.0f, true);
		rotation.setDuration(800);
		rotation.setFillAfter(true);
		rotation.setInterpolator(new AccelerateInterpolator());
		rotation.setAnimationListener(new DisplayNextView());
		mContainer.startAnimation(rotation);
    }
    
    private final class DisplayNextView implements Animation.AnimationListener{
    	 public void onAnimationStart(Animation animation) {
         }

         public void onAnimationEnd(Animation animation) {
             mContainer.post(new SwapViews());
             mScrollLayout.setToScreen(1);
         }

         public void onAnimationRepeat(Animation animation) {
         }
    }
    
    /**
     * This class is responsible for swapping the views and start the second
     * half of the animation.
     */
    private final class SwapViews implements Runnable{
    	public void run(){
    		final float centerX = mContainer.getWidth() / 2.0f;
            final float centerY = mContainer.getHeight() / 2.0f;
            Rotate3dAnimation rotation;
            
            //rotate menu first
            rotation = new Rotate3dAnimation(0, 180, centerX, centerY, 310.0f, false);
            rotation.setFillAfter(true);
            rotation.setInterpolator(new DecelerateInterpolator());
            mDishesMenus.startAnimation(rotation);
            
            mEntry.setVisibility(View.GONE);
            mDishesMenus.setVisibility(View.VISIBLE);
            
            rotation = new Rotate3dAnimation(-90, -180, centerX, centerY, 310.0f, false);
            rotation.setDuration(600);
            rotation.setFillAfter(true);
            rotation.setInterpolator(new DecelerateInterpolator());

            mContainer.startAnimation(rotation);
    	}
    }
	
}
