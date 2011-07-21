package org.mfn.dishes;

import org.mfn.dishes.util.DishesDBHelpter;

import android.app.Application;
import android.os.Environment;

public class DishesApp extends Application {

	private static DishesApp app = null;

	public static DishesApp getInstance() {
		return app;
	}

	public void onCreate() {
		super.onCreate();
		app = this;

		Constants.DISHES_IMAGE_PATH = Environment.getExternalStorageDirectory().getAbsolutePath() + "/Dishes/images/";
		
		DishesDBHelpter.init(this);
		DishesDBHelpter.getInstance().open();
	}

	@Override
	public void onTerminate() {
		
		DishesDBHelpter.getInstance().close();
		
		super.onTerminate();
	}
}
