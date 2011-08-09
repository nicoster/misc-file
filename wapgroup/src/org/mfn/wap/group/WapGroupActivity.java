package org.mfn.wap.group;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;

import org.mfn.wap.group.util.HttpDownloader;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.animation.AccelerateInterpolator;
import android.view.animation.Animation;
import android.view.animation.DecelerateInterpolator;
import android.webkit.URLUtil;
import android.webkit.WebView;
import android.widget.GridView;
import android.widget.TextView;

public class WapGroupActivity extends Activity {

	private static final String TAG = "SUZHOU_ONLINE";

	private static final int DIALOG_CONFIRM_QUIT = 1;
	private static final int DIALOG_CONFIRM_UPDATE = 2;
	private static final int DIALOG_ABOUT = 3;

	private ProgressDialog dialog;

	private String fileEx = "";
	private String fileNa = "";
	private String currentFilePath = "";
	private String currentTempFilePath = "";

	public int versionCode = 0;
	public String versionName = "";
	public String new_apk_url = "";

	private View mContainer;
	private View mIconPage;
	private View mCoverPage;
	private WapIconAdapter mAdapter;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.main);

		mContainer = findViewById(R.id.container);

		mCoverPage = findViewById(R.id.cover_page);
		mIconPage = findViewById(R.id.icon_page);

		GridView grid = (GridView) findViewById(R.id.myGrid);
		mAdapter = new WapIconAdapter(this);
		grid.setAdapter(mAdapter);

		loadLoginPage.start();
		checkAppVersin.start();
	}
	
	public void onStart() {
		WebView  wvMobile = (WebView)findViewById(R.id.wv_mobile_num);
		wvMobile.loadUrl("http://wap.js.ct10000.com/login!tryLogin.action?ENSTR=3840989EA982EF4308270861BEAC341942AB955700336657");
		super.onStart();
	}
	
	public void onPause(){
		super.onPause();
		//this.delFile();
	}
	
	public void onBackPressed() {
		this.showDialog(DIALOG_CONFIRM_QUIT);
	}

	public boolean isVersionUpdated() {
		this.getCurrentVersion();

		HttpDownloader downloader = new HttpDownloader();
		String version_txt = downloader.download(Constants.CONFIG_APP_STATUS_URL);
		
		Log.d(TAG, "Check App Version from " + Constants.CONFIG_APP_STATUS_URL);
		
		int idx2 = version_txt.indexOf("name ");
		int idx3 = version_txt.indexOf("url ");

		String new_ver_name = version_txt.substring(idx2 + 5, idx3);
		String url = version_txt.substring(idx3 + 4);
		
		Log.d(TAG, "Server Side ,versionName=" + new_ver_name);
		
		if (!new_ver_name.equalsIgnoreCase(versionName)) {
			new_apk_url = url;
			return true;
		}

		return false;
	}

	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.menu, menu);
		return true;
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case R.id.menu_exit:
			showDialog(DIALOG_CONFIRM_QUIT);
			return true;
		case R.id.menu_about:
			showDialog(DIALOG_ABOUT);
			return true;
		}
		return false;
	}	
	protected Dialog onCreateDialog(int id) {
		switch (id) {
			case DIALOG_CONFIRM_QUIT :
				return new AlertDialog.Builder(WapGroupActivity.this).setIcon(R.drawable.alert_dialog_icon)
						.setTitle(R.string.alert_dialog_quit_title).setMessage(R.string.alert_dialog_quit_msg)
						.setPositiveButton(R.string.alert_dialog_yes, new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int whichButton) {

								finish();
							}
						}).setNegativeButton(R.string.alert_dialog_no, new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int whichButton) {

								/* User clicked Cancel so do some stuff */
							}
						}).create();
			case DIALOG_CONFIRM_UPDATE :
				return new AlertDialog.Builder(WapGroupActivity.this).setIcon(R.drawable.alert_dialog_icon)
						.setTitle(R.string.alert_dialog_update_title).setMessage(R.string.alert_dialog_update_msg)
						.setPositiveButton(R.string.alert_dialog_yes, new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int whichButton) {
								downloadTheFile(new_apk_url);
								showWaitDialog();
							}
						}).setNegativeButton(R.string.alert_dialog_no, new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int whichButton) {
							}
						}).create();
			case DIALOG_ABOUT:
				return new AlertDialog.Builder(this).setIcon(android.R.drawable.ic_dialog_alert)
						.setTitle(R.string.menu_about)
						.setMessage(R.string.dialog_about_msg)
						.setPositiveButton(android.R.string.ok,new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface Dialog, int whichButton) {
								Dialog.cancel();
							}})
						.create();				
		}
		return null;
	}

	private void applyRotation(float start, float end) {
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

	private final class DisplayNextView implements Animation.AnimationListener {
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
	private final class SwapViews implements Runnable {
		public void run() {
			final float centerX = mContainer.getWidth() / 2.0f;
			final float centerY = mContainer.getHeight() / 2.0f;
			Rotate3dAnimation rotation;

			// rotate menu first
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

	Handler progressHandler = new Handler() {
		public void handleMessage(Message msg) {
			switch (msg.what) {
				case 0 :
					applyRotation(0, -90);
					break;
				case 1 :
					showDialog(DIALOG_CONFIRM_UPDATE);
			}
		}
	};

	public void getCurrentVersion() {
		try {
			PackageInfo info = this.getPackageManager().getPackageInfo(this.getPackageName(), 0);
			this.versionCode = info.versionCode;
			this.versionName = info.versionName;
			
			Log.d(TAG, "Current version_name is " + versionName);
			
			TextView textVersion = (TextView) findViewById(R.id.textVersion);
			textVersion.setText(versionName);

		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
	}

	private Thread loadLoginPage = new Thread() {
		public void run() {
			try {
				progressHandler.sendEmptyMessageDelayed(0, 2000);

			} catch (Exception e) {
				e.printStackTrace();
			} finally {

			}
		}
	};

	private Thread checkAppVersin = new Thread() {
		public void run() {
			try {
				if (isVersionUpdated()) {
					progressHandler.sendEmptyMessage(1);
				}
			} catch (Exception e) {
				e.printStackTrace();
			} finally {

			}
		}
	};

	private void downloadTheFile(final String strPath) {
		fileEx = new_apk_url.substring(new_apk_url.lastIndexOf(".") + 1, new_apk_url.length()).toLowerCase();
		fileNa = new_apk_url.substring(new_apk_url.lastIndexOf("/") + 1, new_apk_url.lastIndexOf("."));
		try {
			if (strPath.equals(currentFilePath)) {
				doDownloadTheFile(strPath);
			}
			currentFilePath = strPath;
			Runnable r = new Runnable() {
				public void run() {
					try {
						doDownloadTheFile(strPath);
					} catch (Exception e) {
						Log.e(TAG, e.getMessage(), e);
					}
				}
			};
			new Thread(r).start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	private void doDownloadTheFile(String strPath) throws Exception {
		Log.i(TAG, "getDataSource()");
		if (!URLUtil.isNetworkUrl(strPath)) {
			Log.i(TAG, "getDataSource() It's a wrong URL!");
		} else {
			URL myURL = new URL(strPath);
			URLConnection conn = myURL.openConnection();
			conn.connect();
			InputStream is = conn.getInputStream();
			if (is == null) {
				throw new RuntimeException("stream is null");
			}
			Log.d(TAG, "Create Temp file "+fileNa+"."+fileEx);
			File myTempFile = File.createTempFile(fileNa, "." + fileEx);
			currentTempFilePath = myTempFile.getAbsolutePath();
			FileOutputStream fos = new FileOutputStream(myTempFile);
			byte buf[] = new byte[128];
			do {
				int numread = is.read(buf);
				if (numread <= 0) {
					break;
				}
				fos.write(buf, 0, numread);
			} while (true);
			Log.i(TAG, "getDataSource() Download  ok...");
			dialog.cancel();
			dialog.dismiss();
			openFile(myTempFile);
			try {
				is.close();
			} catch (Exception ex) {
				Log.e(TAG, "getDataSource() error: " + ex.getMessage(), ex);
			}
		}
	}

	private String getMIMEType(File f) {
		String type = "";
		String fName = f.getName();
		String end = fName.substring(fName.lastIndexOf(".") + 1, fName.length()).toLowerCase();
		if (end.equals("m4a") || end.equals("mp3") || end.equals("mid") || end.equals("xmf") || end.equals("ogg")
				|| end.equals("wav")) {
			type = "audio";
		} else if (end.equals("3gp") || end.equals("mp4")) {
			type = "video";
		} else if (end.equals("jpg") || end.equals("gif") || end.equals("png") || end.equals("jpeg")
				|| end.equals("bmp")) {
			type = "image";
		} else if (end.equals("apk")) {
			type = "application/vnd.android.package-archive";
		} else {
			type = "*";
		}
		if (end.equals("apk")) {
		} else {
			type += "/*";
		}
		return type;
	}

	public void delFile() {   
        Log.i(TAG, "The TempFile(" + currentTempFilePath + ") was deleted.");   
        File myFile = new File(currentTempFilePath);   
        if (myFile.exists()) {   
            myFile.delete();   
        }   
    }   
	
	private void openFile(File f) {
		Intent intent = new Intent();
		intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		intent.setAction(android.content.Intent.ACTION_VIEW);
		String type = getMIMEType(f);
		intent.setDataAndType(Uri.fromFile(f), type);
		startActivity(intent);
	}

	public void showWaitDialog() {
		dialog = new ProgressDialog(this);
		dialog.setMessage(this.getResources().getText(R.string.update_msg));
		dialog.setIndeterminate(true);
		dialog.setCancelable(true);
		dialog.show();
	}
}
