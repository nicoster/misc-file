/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.ocp.media;

import org.ocp.app.App;
import org.ocp.app.Res;
import org.ocp.cache.CacheService;
import org.ocp.cache.ImageList;
import org.ocp.wallpaper.RandomDataSource;
import org.ocp.wallpaper.Slideshow;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.provider.MediaStore.Images;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.Toast;

public final class Gallery extends Activity {
    public static final String REVIEW_ACTION = "org.ocp.media.action.REVIEW";

    public static final String TAG = "ORDER_DISHES";

    private App mApp = null;

    private RenderView mRenderView = null;

    private GridLayer mGridLayer;

    private WakeLock mWakeLock;

    private boolean mDockSlideshow = false;

    private int mNumRetries;

    private boolean mImageManagerHasStorageAfterDelay = false;

    private HandlerThread mPicasaAccountThread = null;

    private static final int CHECK_STORAGE = 0;

    private static final int HANDLE_INTENT = 1;

    private static final int NUM_STORAGE_CHECKS = 25;

    private static Context mContext = null;

    private static boolean mIsShuttingDown = false;

    private Dialog mProgress = null;

    // Dimension of each image in the grid.
    // Originals HEIGHT = 72, WIDTH = 96
    private static final float GRID_ITEM_HEIGHT = 72;
    private static final float GRID_ITEM_WIDTH = 96;

    private final Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
            case CHECK_STORAGE:
                checkStorage();
                break;
            case HANDLE_INTENT:
                initializeDataSource();
                break;
            }
        }
    };

    private void checkStorage() {
        mNumRetries++;
        mImageManagerHasStorageAfterDelay = ImageManager.hasStorage();
        if (!mImageManagerHasStorageAfterDelay && mNumRetries < NUM_STORAGE_CHECKS) {
            if (mNumRetries == 1) {
                mApp.showToast(getResources().getString(Res.string.no_sd_card), Toast.LENGTH_LONG);
            }
            handler.sendEmptyMessageDelayed(CHECK_STORAGE, 200);
        } else {
            handler.sendEmptyMessage(HANDLE_INTENT);
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        startupGallery();
        Log.i(Gallery.TAG, TAG + ": " + "onCreate");
    }

    private void sendInitialMessage() {
        mNumRetries = 0;
        Message checkStorage = new Message();
        checkStorage.what = CHECK_STORAGE;
        handler.sendMessage(checkStorage);
    }

    @Override
    protected void onNewIntent(Intent intent) {
        setIntent(intent);
        handler.removeMessages(CHECK_STORAGE);
        handler.removeMessages(HANDLE_INTENT);

        sendInitialMessage();
    }

    @Override
    public void onRestart() {
        super.onRestart();
    }

    @Override
    public void onStart() {
        super.onStart();
    }

    @Override
    public void onResume() {
        super.onResume();
        if (mDockSlideshow) {
            if (mWakeLock != null) {
                if (mWakeLock.isHeld()) {
                    mWakeLock.release();
                }
            }
            PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
            mWakeLock = pm.newWakeLock(PowerManager.SCREEN_BRIGHT_WAKE_LOCK, "GridView.Slideshow.All");
            mWakeLock.acquire();
            return;
        }
        if (mRenderView != null) {
            mRenderView.onResume();
        }
    }

    @Override
    public void onPause() {
        super.onPause();
        if (mRenderView != null)
            mRenderView.onPause();
        if (mWakeLock != null) {
            if (mWakeLock.isHeld()) {
                mWakeLock.release();
            }
            mWakeLock = null;
        }

        LocalDataSource.sThumbnailCache.flush();
        LocalDataSource.sThumbnailCacheVideo.flush();

        mApp.onPause();
    }

    @Override
    public void onStop() {
        super.onStop();
        runtimeShutdown(true, false);
    }

    @Override
    public void onDestroy() {
        runtimeShutdown(false, true);
        super.onDestroy();
        mContext = null;
        Log.i(Gallery.TAG, TAG + ": " + "onDestroy");
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        if (mGridLayer != null) {
            mGridLayer.markDirty(30);
        }
        if (mRenderView != null)
            mRenderView.requestRender();
        Log.i(Gallery.TAG, TAG + ": " + "onConfigurationChanged");
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (mRenderView != null) {
            return mRenderView.onKeyDown(keyCode, event) || super.onKeyDown(keyCode, event);
        } else {
            return super.onKeyDown(keyCode, event);
        }
    }

    private boolean isPickIntent() {
        String action = getIntent().getAction();
        return (Intent.ACTION_PICK.equals(action) || Intent.ACTION_GET_CONTENT.equals(action));
    }

    private boolean isViewIntent() {
        String action = getIntent().getAction();
        return Intent.ACTION_VIEW.equals(action);
    }

    private boolean isReviewIntent() {
        String action = getIntent().getAction();
        return REVIEW_ACTION.equals(action);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
        case CropImage.CROP_MSG: {
            if (resultCode == RESULT_OK) {
                setResult(resultCode, data);
                finish();
            }
            break;
        }
        case CropImage.CROP_MSG_INTERNAL: {
            // We cropped an image, we must try to set the focus of the camera
            // to that image.
            if (resultCode == RESULT_OK) {
                String contentUri = data.getAction();
                if (mGridLayer != null && contentUri != null) {
                    mGridLayer.focusItem(contentUri);
                }
            }
            break;
        }
        }
    }

    @Override
    public void onLowMemory() {
        if (mRenderView != null) {
            mRenderView.handleLowMemory();
        }
    }

    private void initializeDataSource() {
        final boolean hasStorage = mImageManagerHasStorageAfterDelay;
        // Creating the DataSource objects.
        final LocalDataSource localDataSource = new LocalDataSource(Gallery.this, LocalDataSource.URI_ALL_MEDIA, false);

        // Depending upon the intent, we assign the right dataSource.
        if (!isPickIntent() && !isViewIntent() && !isReviewIntent()) {
            localDataSource.setMimeFilter(true, true);
            if (hasStorage) {
                mGridLayer.setDataSource(localDataSource);
            } 
        } 
    }

    public static void processScanComplete() {
        Log.i(TAG, "processScanComplete");
        if (mContext == null) {
            // We're not running so do nothing
            return;
        }

        if (mIsShuttingDown) {
            Gallery gal = (Gallery) mContext;

            gal.mProgress.dismiss();
            gal.runtimeShutdown(true, true);
            mIsShuttingDown = false;
        }
    }

    public static void processMediaChanged() {
        Log.i(TAG, "processMediaChanged");
        if (mContext == null) {
            // We're not running so do nothing
            return;
        }

        // Just shut down if we're not in the foreground
        // Let them relaunch us manually
        final Gallery gal = (Gallery) mContext;
        if (!gal.mApp.isPaused() && !mIsShuttingDown) {
            mIsShuttingDown = true;
            gal.mRenderView.onPause();
            gal.handler.post(new Runnable() {
                public void run() {
                    gal.mProgress = new Dialog(mContext, R.style.PopupActivity);
                    gal.mProgress.setContentView(R.layout.gallery_util);
                    gal.mProgress.setCancelable(false);
                    gal.mProgress.show();
                }
            });
        } else if (gal.mApp.isPaused()) {
            gal.finish();
        }
    }

    public static boolean isShuttingDown() {
        return mIsShuttingDown;
    }

    private void runtimeShutdown(boolean onStop, boolean onDestroy) {
        if (onStop) {
            if (mGridLayer != null)
                mGridLayer.stop();

            // Start the thumbnailer.
            CacheService.startCache(this, true);
        }
        if (onDestroy) {
            // Force GLThread to exit.
            setContentView(Res.layout.main);

            // Remove any post messages.
            handler.removeMessages(CHECK_STORAGE);
            handler.removeMessages(HANDLE_INTENT);

            if (mPicasaAccountThread != null) {
                mPicasaAccountThread.quit();
                mPicasaAccountThread = null;
            }
            if (mGridLayer != null) {
                DataSource dataSource = mGridLayer.getDataSource();
                if (dataSource != null) {
                    dataSource.shutdown();
                }
                mGridLayer.shutdown();
            }
            if (mRenderView != null) {
                mRenderView.shutdown();
                mRenderView = null;
            }
            mGridLayer = null;
            mApp.shutdown();

            handler.removeMessages(CHECK_STORAGE);
            handler.removeMessages(HANDLE_INTENT);
        }
        if (onStop && onDestroy) {
            startupGallery();
        }
    }

    private void startupGallery() {
        mApp = new App(Gallery.this);

        mContext = this;
        final boolean imageManagerHasStorage = ImageManager.hasStorage();
        boolean slideshowIntent = false;
        if (isViewIntent()) {
            Bundle extras = getIntent().getExtras();
            if (extras != null) {
                slideshowIntent = extras.getBoolean("slideshow", false);
            }
        }
        if (isViewIntent() && getIntent().getData().equals(Images.Media.EXTERNAL_CONTENT_URI) && slideshowIntent) {
            if (!imageManagerHasStorage) {
                Toast.makeText(this, getResources().getString(Res.string.no_sd_card), Toast.LENGTH_LONG).show();
                finish();
            } else {
                // notify user that there are no images to display
                if (((ImageList) CacheService.getImageList(mContext)).ids == null) {
                    Toast.makeText(this, getResources().getString(Res.string.no_items), Toast.LENGTH_LONG).show();
                    finish();
                }

                Slideshow slideshow = new Slideshow(this);
                slideshow.setDataSource(new RandomDataSource());
                setContentView(slideshow);
                mDockSlideshow = true;
            }
            return;
        }
        mRenderView = new RenderView(this);
        mGridLayer = new GridLayer(this, (int) (GRID_ITEM_WIDTH * App.PIXEL_DENSITY),
                (int) (GRID_ITEM_HEIGHT * App.PIXEL_DENSITY), new GridLayoutInterface(4), mRenderView);
        mRenderView.setRootLayer(mGridLayer);
        setContentView(mRenderView);

        sendInitialMessage();
    }
}
