package com.personal_project.android_picomm

import android.app.Activity

open class SensorAdapter {
    protected val mActivity: Activity
    constructor(activity : Activity){
        mActivity = activity
    }
    open fun start(){}
    open fun pause(){}
}