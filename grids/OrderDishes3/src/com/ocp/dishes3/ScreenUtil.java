package com.ocp.dishes3;

import android.util.DisplayMetrics;

public class ScreenUtil {

	public static int getRightPanelWidth() {
		DisplayMetrics dm = DishesApp.getInstance().getResources()
				.getDisplayMetrics();
		
		return dm.heightPixels/4;
	}

}
