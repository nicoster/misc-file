package org.mfn.dishes;

import org.mfn.dishes.proto.main.MainClient;
import org.mfn.dishes.util.DishesDBHelpter;

import android.app.Application;

public class DishesApp extends Application {

	private static DishesApp app = null;

	public static DishesApp getInstance() {
		return app;
	}

	public void onCreate() {
		super.onCreate();
		app = this;
		
//		MainClient cli = MainClient.getInstance();
//		cli.init("xx23vxxxxxxsss", "android", "58.240.209.238", 7990, null);
//		cli.login("", "");
		
		DishesDBHelpter.init(this);
		DishesDBHelpter.getInstance().open();
	}

	@Override
	public void onTerminate() {
		
		DishesDBHelpter.getInstance().close();
		
		super.onTerminate();
	}
}
