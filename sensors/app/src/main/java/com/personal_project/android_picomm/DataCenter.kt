package com.personal_project.android_picomm

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import java.util.*
import kotlin.collections.HashMap

object DataCenter : BroadcastReceiver(){
    val CONNECTION_BEGIN = "connection begin"
    val CONNECTION_END = "connection end"
    val SENSOR_VISIBILITY_CHANGE = "sensor visibility change"

    private val TAG = "DataCenter"
    private val mSensorMap = HashMap<String, Boolean>()

    fun getVisibleSensors(): HashSet<String> {
        return HashSet<String>()
    }

    override fun onReceive(context: Context?, intent: Intent?) {

    }

    fun setSensors(sensors: ArrayList<String>){
        for(i in sensors){
            if(!mSensorMap.containsKey(i))
                mSensorMap.put(i, true)
        }
    }
}