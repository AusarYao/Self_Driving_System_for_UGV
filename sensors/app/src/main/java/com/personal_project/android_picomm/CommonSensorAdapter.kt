package com.personal_project.android_picomm

import android.app.Activity
import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.util.Log

class CommonSensorAdapter : SensorAdapter {
    private val TAG = "CommonSensorAdapter"
    private val mSensorReadInterval = 10000
    private val mSensorManager: SensorManager
    private val mSensorsMap = HashMap<String, SensorListener>()

    constructor(activity: Activity): super(activity){
            mSensorManager = mActivity.getSystemService(Context.SENSOR_SERVICE) as SensorManager
            listOf(mSensorManager.getSensorList(Sensor.TYPE_ALL)).forEach {
                it.forEach {
                    val sensorType = mSensorManager.getDefaultSensor(it.type)
                    mSensorsMap.put(sensorType.name, SensorListener(sensorType))
                }
            }
    }
    override fun start() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    override fun pause() {
        TODO("not implemented") //To change body of created functions use File | Settings | File Templates.
    }

    inner class SensorListener : SensorEventListener {
        val mmSensor: Sensor

        constructor(sensor: Sensor) {
            mmSensor = sensor
        }

        override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {
            Log.d(TAG, "Accuracy changed")
        }

        override fun onSensorChanged(event: SensorEvent) {
            val tmp = "${event.timestamp} ${event.sensor.name} ${event.values.forEach { it.toString() }}"
            Log.d(TAG, tmp)
        }

        fun onResume() {
            mSensorManager.registerListener(this, mmSensor, mSensorReadInterval)
        }

        fun onPause() {
            mSensorManager.unregisterListener(this)
        }
    }
}