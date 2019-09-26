package com.example.android_picomm

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout
import androidx.recyclerview.widget.RecyclerView
import com.personal_project.android_picomm.DataCenter
import com.personal_project.android_picomm.SensorController


class RecyclerViewAdapter: RecyclerView.Adapter<RecycleViewHolder>(){
    var listItems = arrayOf<String>()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecycleViewHolder {
        val linearLayout = LayoutInflater.from(parent.context).
                inflate(R.layout.recycler_list_base, parent, false) as LinearLayout
        listItems = DataCenter.getVisibleSensors().toTypedArray()
        return RecycleViewHolder(linearLayout)
    }

    override fun onBindViewHolder(holder: RecycleViewHolder, position: Int) {
        holder.setName(listItems[position])
    }

    override fun getItemCount() = DataCenter.getVisibleSensors().size
}