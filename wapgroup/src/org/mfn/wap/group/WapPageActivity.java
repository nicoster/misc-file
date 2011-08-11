package org.mfn.wap.group;

import android.app.Activity;
import android.net.http.SslError;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.webkit.SslErrorHandler;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

public class WapPageActivity extends Activity {

	WebView wv;
	TextView titleTextView;
	
	String title;
	String url;

	public void onCreate(Bundle icicle) {
		super.onCreate(icicle);

		setContentView(R.layout.wappage);

		wv = (WebView) findViewById(R.id.wv1);

		wv.getSettings().setJavaScriptEnabled(true);
		wv.getSettings().setBuiltInZoomControls(true);

		url = this.getIntent().getStringExtra(Constants.PARAM_WAP_URL);
		title = this.getIntent().getStringExtra(Constants.PARAM_WAP_TITLE);

		titleTextView = (TextView) this.findViewById(R.id.wap_title_name);
		titleTextView.setText(this.getResources().getString(R.string.wap_load_msg)+"0 %");
		
		final ProgressBar pBar = (ProgressBar) this.findViewById(R.id.progressBar);
		
		WebViewClient wvc = new WebViewClient() {

			public void onReceivedSslError(WebView view, SslErrorHandler handler, SslError error) {
				handler.proceed();
			}

			public void onReceivedError(WebView view, int errorCode, String description, String failingUrl) {
				super.onReceivedError(view, errorCode, description, failingUrl);
			}

			public void onPageFinished(WebView view, String url) {
				Log.d("test", "test");
			}

		};

		wv.setWebViewClient(wvc);
		wv.loadUrl(url);
		wv.requestFocus();

		wv.setWebChromeClient(new WebChromeClient(){
			@Override  
		    public void onProgressChanged(WebView view, int newProgress) {  
				titleTextView.setText(getResources().getString(R.string.wap_load_msg) + newProgress + "%");
		        if(newProgress==100){  
		        	pBar.setVisibility(View.GONE);  
		        	titleTextView.setText(title);
		        }  
		    }  
		});
		
		View goBack = (ImageView) findViewById(R.id.goBackButton);
		View goForward = (ImageView) findViewById(R.id.goForwardButton);
		View goHome = (ImageView) findViewById(R.id.goHomeButton);

		goBack.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				if (wv.canGoBack()) {
					wv.goBack();
				}
			}
		});

		goForward.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				if (wv.canGoForward()) {
					wv.goForward();
				}
			}
		});
		
		goHome.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				finish();
			}
		});
	}

}
