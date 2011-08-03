package org.mfn.wap.group;

import android.app.Activity;
import android.content.Intent;
import android.net.http.SslError;
import android.os.Bundle;
import android.webkit.HttpAuthHandler;
import android.webkit.SslErrorHandler;
import android.webkit.WebView;
import android.webkit.WebViewClient;

public class WapPageActivity extends Activity {
	
	WebView wv;
	
	 public void onCreate(Bundle icicle) {
	        super.onCreate(icicle);
	        
	        setContentView(R.layout.wappage);
	        
	        wv = (WebView) findViewById(R.id.wv1);
	        
	        wv.getSettings().setJavaScriptEnabled(true);
	        
	        String url  = this.getIntent().getStringExtra(Constants.PARAM_WAP_URL);
	        
	        wv.loadUrl(url);
	        
	        WebViewClient wvc = new WebViewClient(){
	        	
	        	// before navigate
	        	public boolean shouldOverrideUrlLoading(WebView view, String url){
	        		view.loadUrl(url);
	        		return true;
	        	}	      
	        	
	        	public void onReceivedSslError(WebView view, SslErrorHandler handler,
	        	            SslError error) {
	        	        handler.proceed();
	        	    }
	        	
	        	
	        	public void onReceivedError(WebView view, int errorCode,
	        	            String description, String failingUrl) 
	        	{
	        		  super.onReceivedError(view, errorCode, description, failingUrl);
	        	}
	        	
	        };
	        
	        wv.setWebViewClient(wvc);
	 }
}
