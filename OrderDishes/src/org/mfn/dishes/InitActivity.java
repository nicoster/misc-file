package org.mfn.dishes;

import java.util.List;

import org.mfn.dishes.animation.Rotate3dAnimation;
import org.mfn.dishes.datastore.DataStore;
import org.mfn.dishes.datastore.IDishesDataStore;
import org.mfn.dishes.datastore.IDishesItemDataStore;
import org.mfn.dishes.datastore.TypeGridDishesInfo;
import org.mfn.dishes.view.DishTypeGridView;
import org.mfn.dishes.view.DishesGridView;
import org.mfn.dishes.view.OrderedDishesView;
import org.mfn.dishes.view.ScrollLayout;
import org.mfn.dishes.vo.DishInfo;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.animation.AccelerateInterpolator;
import android.view.animation.Animation;
import android.view.animation.DecelerateInterpolator;
import android.widget.ImageButton;
import android.widget.RelativeLayout;

public class InitActivity extends Activity implements OnClickListener{
	private ImageButton mStartBtn;
	private ViewGroup mContainer;
	private RelativeLayout mEntry;
	private RelativeLayout mDishesMenus;
	private ScrollLayout mScrollLayout;
	
	private ImageButton mOrderedBtn;
	private ImageButton mCategoryBtn;
	
	private IDishesItemDataStore store;
	private IDishesDataStore dishesDataStore;
	
	private OrderedDishesView orderedDishesView;
	
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
        
        mOrderedBtn = (ImageButton)findViewById(R.id.btn_left);
        mCategoryBtn = (ImageButton)findViewById(R.id.btn_right);
        
        mStartBtn.setOnClickListener(this);
        
        store = DataStore.getInstance().getDishesItemDataStore();
        dishesDataStore = DataStore.getInstance().getDishesDataStore();
        
        prepareViews();
//        mEntry.setVisibility(View.GONE);
//        mDishesMenus.setVisibility(View.VISIBLE);
	}
	
	
	private void prepareViews(){
		orderedDishesView = new OrderedDishesView(this);
        mScrollLayout.addView(orderedDishesView);
        
        int dishesItemPages = dishesDataStore.getAllDishesPages();
        
        for(int i = 0; i < dishesItemPages; i++){
        	List<DishInfo> dishInfos = dishesDataStore.getDishInfosByPage(i);
        	if(dishInfos.size() > 0){
        		mScrollLayout.addView(new DishesGridView(this, dishInfos));
        	}
        }
        
        
//        List<PageGridDishesInfo> pageList = store.getPageDishesInfos();
//        for (int i=0;i<pageList.size();i++){
//        	PageGridDishesInfo pageInfo = pageList.get(i);
//            mScrollLayout.addView(new DishesGridView(this, pageInfo));
//        }
//        
        List<TypeGridDishesInfo> dishTypeList = store.getDisheTypePageList();
        mScrollLayout.addView(new DishTypeGridView(this, dishTypeList));
        
        mScrollLayout.snapToScreen(1);

        mOrderedBtn.setOnClickListener(new ImageButton.OnClickListener() {
			public void onClick(View v) {				
				mScrollLayout.setToScreen(3);
				mScrollLayout.snapToScreen(0);
			}
		});
        mCategoryBtn.setOnClickListener(new ImageButton.OnClickListener() {
			public void onClick(View v) {
				int last = mScrollLayout.getChildCount();
				mScrollLayout.setToScreen(last-3);
				mScrollLayout.snapToScreen(last);
			}
		});    
	}
	
	public void onStart(){
		super.onStart();
//		mEntry.setVisibility(View.VISIBLE);
//        mDishesMenus.setVisibility(View.GONE);
		Log.i(Constants.APP_TAG, "InitActivity: onStart");
	
        
        
//        prepareViews();
	}

	public void onStop(){
		Log.i(Constants.APP_TAG, "InitActivity: onStop");
		super.onStop();
	}
	
	public void onDestroy() {
		Log.i(Constants.APP_TAG, "InitActivity: onDestroy");
		super.onDestroy();
	}
	
	public void onClick(View v){
    	applyRotation(0, -90);
    }
	
	public void updateUI(){
		orderedDishesView.updateUI();
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
            rotation.setDuration(500);
            rotation.setFillAfter(true);
            rotation.setInterpolator(new DecelerateInterpolator());

            mContainer.startAnimation(rotation);
    	}
    }
	
}
