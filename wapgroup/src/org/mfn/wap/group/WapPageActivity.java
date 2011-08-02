package org.mfn.wap.group;

import android.app.Activity;
import android.os.Bundle;
import android.webkit.WebView;

public class WapPageActivity extends Activity {
	 public void onCreate(Bundle icicle) {
	        super.onCreate(icicle);
	        
	        setContentView(R.layout.wappage);
	        
	        final String mimeType = "text/html";
	        final String encoding = "utf-8";
	        
	        WebView wv;
	        
	        wv = (WebView) findViewById(R.id.wv1);
	        wv.loadUrl("http://wap.taobao.com");
	 }
}
