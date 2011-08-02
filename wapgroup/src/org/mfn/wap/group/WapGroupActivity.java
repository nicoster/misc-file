package org.mfn.wap.group;

import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.ResolveInfo;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemClickListener;

public class WapGroupActivity extends Activity {

    GridView mGrid;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        loadApps(); // do this in onresume?

        setContentView(R.layout.main);
        mGrid = (GridView) findViewById(R.id.myGrid);
        mGrid.setAdapter(new AppsAdapter());
        
        mGrid.setOnItemClickListener(new OnItemClickListener() {
            public void onItemClick(AdapterView parent, View v, int position, long id) {
                Toast.makeText(WapGroupActivity.this, "" + position, Toast.LENGTH_SHORT).show();
				Intent intent = new Intent();
				intent.setClass(WapGroupActivity.this, WapPageActivity.class);
				startActivity(intent);
            }
        });
    }

    private List<ResolveInfo> mApps;

    private void loadApps() {
        Intent mainIntent = new Intent(Intent.ACTION_MAIN, null);
        mainIntent.addCategory(Intent.CATEGORY_LAUNCHER);

        mApps = getPackageManager().queryIntentActivities(mainIntent, 0);
    }

    public class AppsAdapter extends BaseAdapter {
        public AppsAdapter() {
        }

        public View getView(int position, View convertView, ViewGroup parent) {
            ImageView i;

            if (convertView == null) {
                i = new ImageView(WapGroupActivity.this);
                i.setScaleType(ImageView.ScaleType.FIT_CENTER);
                i.setLayoutParams(new GridView.LayoutParams(50, 50));
            } else {
                i = (ImageView) convertView;
            }

            ResolveInfo info = mApps.get(position);
            i.setImageDrawable(info.activityInfo.loadIcon(getPackageManager()));

            return i;
        }


        public final int getCount() {
            return mApps.size();
        }

        public final Object getItem(int position) {
            return mApps.get(position);
        }

        public final long getItemId(int position) {
            return position;
        }
    }

}
