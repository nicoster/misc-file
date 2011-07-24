package org.mfn.dishes;

import org.mfn.dishes.animation.Rotate3dAnimation;
import org.mfn.dishes.view.DishTypeGridView;
import org.mfn.dishes.view.DishesGridView;
import org.mfn.dishes.view.ScrollLayout;

import android.app.Activity;
import android.os.Bundle;
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
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.init);
		
		mStartBtn = (ImageButton)findViewById(R.id.startbtn);
		mContainer = (ViewGroup) findViewById(R.id.container);
        mEntry = (RelativeLayout) findViewById(R.id.entry);
        mDishesMenus = (RelativeLayout) findViewById(R.id.dishes_menus);
        mScrollLayout = (ScrollLayout) findViewById(R.id.scroll_layout);
        
        mStartBtn.setOnClickListener(this);
//		mStartBtn.setOnClickListener(new Button.OnClickListener() {
//            public void onClick(View v) {
//            	Intent intent = new Intent();
//                intent.setClass(InitActivity.this, AllDishesActivity.class);
//                startActivity(intent);
//                InitActivity.this.finish();
//            }
//        });
        DishesGridView dishesGridView = new DishesGridView(this);
//        DishesGridAdapter adapter = new DishesGridAdapter(this);
//        dishesGridView.setAdapter(adapter);
        mScrollLayout.addView(dishesGridView);
        mScrollLayout.addView(new DishesGridView(this));
        mScrollLayout.addView(new DishesGridView(this));
        mScrollLayout.addView(new DishesGridView(this));
        
        mScrollLayout.addView(new DishTypeGridView(this));
        
	}
	public void onClick(View v){
    	applyRotation(0, 90);
    }
    
    private void applyRotation(float start, float end){
		// Find the center of the container
		final float centerX = mContainer.getWidth() / 2.0f;
		final float centerY = mContainer.getHeight() / 2.0f;

		// Create a new 3D rotation with the supplied parameter
		// The animation listener is used to trigger the next animation
		final Rotate3dAnimation rotation = new Rotate3dAnimation(start, end, centerX, centerY, 310.0f, true);
		rotation.setDuration(500);
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
            
            rotation = new Rotate3dAnimation(90, 180, centerX, centerY, 310.0f, false);
            rotation.setDuration(500);
            rotation.setFillAfter(true);
            rotation.setInterpolator(new DecelerateInterpolator());

            mContainer.startAnimation(rotation);
    	}
    }
	
}
