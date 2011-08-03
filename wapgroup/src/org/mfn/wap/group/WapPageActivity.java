package org.mfn.wap.group;

import android.app.Activity;
import android.os.Bundle;
import android.webkit.WebView;

public class WapPageActivity extends Activity {
	 public void onCreate(Bundle icicle) {
	        super.onCreate(icicle);
	        
	        setContentView(R.layout.wappage);
	        
	        WebView wv;
	        
	        wv = (WebView) findViewById(R.id.wv1);
	        
	        String url  = this.getIntent().getStringExtra(Constants.PARAM_WAP_URL);
	        
	        wv.loadUrl(url);
	 }
}
