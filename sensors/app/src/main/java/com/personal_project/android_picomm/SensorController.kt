package com.personal_project.android_picomm

import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.util.Log

class SensorController{
    private var mSensorManager: SensorManager
    val TAG = "SENSOR_CONTROLLER"
    private val mSensorReadInterval = 100000 //micro second
    private var mSensorsMap =  hashMapOf<Sensor, Boolean>()
    private val mSensorListenersMap = hashMapOf<Sensor, SensorListener>()

    private constructor(context: Context){
        mSensorManager = context.getSystemService(Context.SENSOR_SERVICE) as SensorManager
        listOf(mSensorManager.getSensorList(Sensor.TYPE_ALL)).forEach{
            it.forEach{
                val tmp = mSensorManager.getDefaultSensor(it.type)
                mSensorsMap.put(tmp, false)
                mSensorListenersMap.set(tmp, SensorListener(tmp))
            }
        }
    }

    companion object{
        private var mSensorController: SensorController? = null
        fun instance(context: Context): SensorController{
            if (mSensorController == null)
                mSensorController = SensorController(context)
            return mSensorController!!
        }
    }

    fun getAllSensors(): HashMap<Sensor, Boolean> {
        return mSensorsMap
    }

    fun setSensorAvailability(sensor: Sensor, availability: Boolean): Boolean {
        if (mSensorsMap.containsKey(sensor)){
            mSensorsMap[sensor] = availability
            return true
        }
        return false
    }

    fun startAllSensors(){
        mSensorListenersMap.forEach {
            if(mSensorsMap[it.key]!!)
                it.value.onResume()
        }
    }

    fun pauseSensor(sensor: Sensor){
        mSensorListenersMap[sensor]!!.onPause()
    }

    fun pauseAll(){
        mSensorListenersMap.forEach{
            it.value.onPause()
        }
    }

    inner class SensorListener: SensorEventListener{
        val mmSensor: Sensor
        constructor(sensor: Sensor){
            mmSensor = sensor
        }

        override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {
            Log.d(TAG, "Accuracy changed")
        }

        override fun onSensorChanged(event: SensorEvent){
            val tmp = "${event.timestamp} ${event.sensor.name} ${event.values.forEach { it.toString()}}"
            Log.v(TAG, tmp)
        }

        fun onResume() {
            mSensorManager.registerListener(this, mmSensor, mSensorReadInterval)
        }

        fun onPause() {
            mSensorManager.unregisterListener(this)
        }
    }
}