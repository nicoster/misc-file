package org.mfn.dishes;

import org.mfn.dishes.adapter.DishesGridAdapter;
import org.mfn.dishes.animation.Rotate3dAnimation;
import org.mfn.dishes.view.DishesGridView;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.view.animation.AccelerateInterpolator;
import android.view.animation.Animation;
import android.view.animation.DecelerateInterpolator;
import android.widget.ImageButton;
import android.widget.RelativeLayout;
import android.widget.ViewFlipper;

public class InitActivity extends Activity implements OnClickListener{
	private ImageButton mStartBtn;
	private ViewGroup mContainer;
	private RelativeLayout mEntry;
	private ViewFlipper mMenuFlipper;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.init);
		
		mStartBtn = (ImageButton)findViewById(R.id.startbtn);
		mContainer = (ViewGroup) findViewById(R.id.container);
        mEntry = (RelativeLayout) findViewById(R.id.entry);
        mMenuFlipper = (ViewFlipper) findViewById(R.id.menuflipper);
        
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
        dishesGridView.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
//        DishesGridAdapter adapter = new DishesGridAdapter(this);
//        dishesGridView.setAdapter(adapter);
        mMenuFlipper.addView(dishesGridView);		
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
            
            mEntry.setVisibility(View.GONE);
            mMenuFlipper.setVisibility(View.VISIBLE);
            
            rotation = new Rotate3dAnimation(90, 0, centerX, centerY, 310.0f, false);
            rotation.setDuration(500);
            rotation.setFillAfter(true);
            rotation.setInterpolator(new DecelerateInterpolator());

            mContainer.startAnimation(rotation);
    	}
    }
	
}
