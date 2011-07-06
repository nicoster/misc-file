package com.ocp.dishes3;

import android.app.Application;

public class DishesApp extends Application {

	private static DishesApp app = null;

	public static DishesApp getInstance() {
		return app;
	}

	public void onCreate() {
		super.onCreate();
		app = this;
	}

	@Override
	public void onTerminate() {
		super.onTerminate();
	}
}
