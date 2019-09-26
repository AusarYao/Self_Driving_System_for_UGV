package com.personal_project.android_picomm

import android.app.Activity
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.util.Log
import java.util.*

class SensorController : BroadcastReceiver {
    private val TAG = "SENSOR_CONTROLLER"
    private val mActivity: Activity
    private val mSensorListers = LinkedList<SensorAdapter>()

    constructor(activity: Activity) {
        mActivity = activity
        mSensorListers.add(CameraAdapter(activity))
        mSensorListers.add(CommonSensorAdapter(activity))
        mSensorListers.add(GPSAdapter(activity))
    }

    override fun onReceive(context: Context?, intent: Intent?) {
        val action = intent!!.action
        when (action) {
            DataCenter.CONNECTION_BEGIN -> {
                mSensorListers.forEach { it.start() }
            }
            DataCenter.CONNECTION_END -> {
                mSensorListers.forEach { it.pause() }
            }
            else -> Log.e(TAG, "Error sensor start/end action")
        }
    }
}