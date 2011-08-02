/* Copyright (C) 2009-2010 OpenPeak Inc.
 * All rights reserved.
 *
 * This file contains confidential information of
 * OpenPeak Inc. Unauthorized reproduction or
 * distribution of this file is subject to civil
 * and criminal penalties.
 *
 * http://www.openpeak.com
 * email: info@openpeak.com
 */

package org.mfn.dishes;

import android.util.DisplayMetrics;

public class Constants {

    public static String APP_TAG = "DISHES";

	public static final String ACCOUNT_TYPE = "org.mfn.dishes.sync";

    public static final String PARAM_SERVER_ADDRESS = "server_address";

    public static final String PARAM_SERVER_PORT = "server_port";

    public static final int SYNC_CONTACTS_POLL_FREQUENCY = 12 * 60 * 1000; // in seconds
    
    public static String DISHES_IMAGE_PATH = null;
    
    public static DisplayMetrics DISPLAY_METRICS = null;
    
    public static int DISHES_PER_PAGE = 8;
}
