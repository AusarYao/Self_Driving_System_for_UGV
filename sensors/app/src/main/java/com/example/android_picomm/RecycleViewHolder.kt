package com.example.android_picomm

import android.widget.*
import androidx.recyclerview.widget.RecyclerView
import com.personal_project.android_picomm.SensorController

class RecycleViewHolder : RecyclerView.ViewHolder {
    private lateinit var mSensorName: String
    private var mSensorSwitch: Switch
    private var mSensorDataView: TextView
    private var mSensorNameView: TextView

    constructor(linearView: LinearLayout) : super(linearView) {
        mSensorNameView = linearView.findViewById(R.id.sensor_name)
        mSensorDataView = linearView.findViewById(R.id.sensor_value)
        mSensorSwitch = linearView.findViewById(R.id.sensor_start_switch)

    }

    fun setName(name: String) {
        mSensorName = name
        mSensorNameView.text = name
//        mSensorSwitch.isChecked = SensorController.instance().getSensorStatus(name)
        mSensorSwitch.setOnCheckedChangeListener { buttonView, isChecked ->
            buttonView.isChecked = isChecked
//            SensorController.instance().setSensorStatus(name, isChecked)
        }
    }
}