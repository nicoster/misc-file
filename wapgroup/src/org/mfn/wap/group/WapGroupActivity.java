package org.mfn.wap.group;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AccelerateInterpolator;
import android.view.animation.Animation;
import android.view.animation.DecelerateInterpolator;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.GridView;
import android.widget.Toast;

public class WapGroupActivity extends Activity {

	private static final int DIALOG_CONFIRM_QUIT = 1;
	
	private View mContainer;
	private View mIconPage;
	private View mCoverPage;;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.main);

		mContainer = findViewById(R.id.container);

        mCoverPage = findViewById(R.id.cover_page);
        mIconPage = findViewById(R.id.icon_page);
        
        GridView grid = (GridView) findViewById(R.id.myGrid);
        grid.setAdapter(new WapIconAdapter(this));
        
        
        grid.setOnItemClickListener(new OnItemClickListener() {
            public void onItemClick(AdapterView parent, View v, int position, long id) {
                Toast.makeText(WapGroupActivity.this, "" + position, Toast.LENGTH_SHORT).show();
				Intent intent = new Intent();
				intent.setClass(WapGroupActivity.this, WapPageActivity.class);
				startActivity(intent);
            }
        });

        applyRotation(0, -90);
    }

    public void onBackPressed(){
    	this.showDialog(DIALOG_CONFIRM_QUIT);
    }
    
    protected Dialog onCreateDialog(int id) {
        switch (id) {
        case DIALOG_CONFIRM_QUIT:
            return new AlertDialog.Builder(WapGroupActivity.this)
                .setIcon(R.drawable.alert_dialog_icon)
                .setTitle(R.string.alert_dialog_quit_title)
                .setMessage(R.string.alert_dialog_quit_msg)
                .setPositiveButton(R.string.alert_dialog_yes, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {

                        finish();
                    }
                })
                .setNegativeButton(R.string.alert_dialog_no, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {

                        /* User clicked Cancel so do some stuff */
                    }
                })
                .create();
        }
        return null;
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
            mIconPage.startAnimation(rotation);
            
            mCoverPage.setVisibility(View.GONE);
            mIconPage.setVisibility(View.VISIBLE);
            
            rotation = new Rotate3dAnimation(-90, -180, centerX, centerY, 310.0f, false);
            rotation.setDuration(500);
            rotation.setFillAfter(true);
            rotation.setInterpolator(new DecelerateInterpolator());

            mContainer.startAnimation(rotation);
    	}
    }    
    

}
