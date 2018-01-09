package com.esay.ffmtool;

import android.app.Application;

import com.squareup.leakcanary.LeakCanary;

/**
 * Created by KUI on 2018/1/9/009.
 */

public class MyAplication extends Application {


    @Override
    public void onCreate() {
        super.onCreate();
        //初始化LeakCanary
        if (LeakCanary.isInAnalyzerProcess(this)) {
            return;
        }
        LeakCanary.install(this);
    }

}
