package com.example.android_picomm

//import com.personal_project.android_picomm.SensorController
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.personal_project.android_picomm.DataCenter


class MainActivity : AppCompatActivity() {

    private val TAG = "MAIN_ACTIVITY"
    private lateinit var mViewController: ViewController

    enum class UI(val UIName: String){
        MAIN("main"),
    }

    data class SendAddress(var IP: String, var port: Int)

    override fun onCreate(savedInstanceState: Bundle?){
        super.onCreate(savedInstanceState)
        mViewController = ViewController(this)
        mViewController.setupUI(ViewController.MAIN_ACTIVITY)
    }
}