package org.mfn.dishes;

import org.mfn.dishes.proto.main.MainClient;
import org.mfn.dishes.util.DishesDBHelpter;
import org.mfn.dishes.vo.DishTypeObj;
import org.mfn.dishes.vo.FlavorInfoObj;
import org.mfn.dishes.vo.ImageInfoObj;
import org.mfn.dishes.vo.UserInfoObj;

import android.app.Application;
import android.text.TextUtils;

public class DishesApp extends Application {

	private static DishesApp app = null;

	public static DishesApp getInstance() {
		return app;
	}
	
	@SuppressWarnings("unused")
	private void runClientTest()
	{
		MainClient cli = MainClient.getInstance();
		cli.init("admin", "pda", "58.240.209.238", 7990, null);
		cli.login("admin", "");
		UserInfoObj[] users = cli.getUserInfo();
//		DishObj[] dishes = cli.getDishInfo();
		DishTypeObj[] dishtypes = cli.getDishTypeInfo();
		FlavorInfoObj[] flv = cli.getFlavorInfo();
		ImageInfoObj imgs[] = cli.getImageInfo();
		
		for (int i = 0; i < imgs.length; i ++)
		{
			String name = imgs[i].name;
			if (TextUtils.isEmpty(name) || name.equalsIgnoreCase(".") || name.equalsIgnoreCase("..")) continue;
			cli.downloadImage(name, "/data/dishes");
		}
		int n = 0;
		n = 1;
	}

	public void onCreate() {
		super.onCreate();
		app = this;
				
//		runClientTest();
		
		DishesDBHelpter.init(this);
		DishesDBHelpter.getInstance().open();
	}

	@Override
	public void onTerminate() {
		
		DishesDBHelpter.getInstance().close();
		
		super.onTerminate();
	}
}
