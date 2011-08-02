package org.mfn.wap.group;


import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.Toast;

public class WapGroupActivity extends Activity {

	private static final int DIALOG_CONFIRM_QUIT = 1;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.main);

        GridView g = (GridView) findViewById(R.id.myGrid);
        g.setAdapter(new ImageAdapter(this));
        
        g.setOnItemClickListener(new OnItemClickListener() {
            public void onItemClick(AdapterView parent, View v, int position, long id) {
                Toast.makeText(WapGroupActivity.this, "" + position, Toast.LENGTH_SHORT).show();
				Intent intent = new Intent();
				intent.setClass(WapGroupActivity.this, WapPageActivity.class);
				startActivity(intent);
            }
        });


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
    
    public class ImageAdapter extends BaseAdapter {
        public ImageAdapter(Context c) {
            mContext = c;
        }

        public int getCount() {
            return mThumbIds.length;
        }

        public Object getItem(int position) {
            return position;
        }

        public long getItemId(int position) {
            return position;
        }

        public View getView(int position, View convertView, ViewGroup parent) {
            ImageView imageView;
            if (convertView == null) {
                imageView = new ImageView(mContext);
                imageView.setLayoutParams(new GridView.LayoutParams(120, 120));
                imageView.setAdjustViewBounds(false);
                imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
                imageView.setPadding(8, 8, 8, 8);
            } else {
                imageView = (ImageView) convertView;
            }

            imageView.setImageResource(mThumbIds[position]);

            return imageView;
        }

        private Context mContext;

		private Integer[] mThumbIds = { R.drawable.a1, R.drawable.a2,
				R.drawable.a3, R.drawable.a4, R.drawable.a5, R.drawable.a6,
				R.drawable.a7, R.drawable.a8, R.drawable.a9 };
    }

}
