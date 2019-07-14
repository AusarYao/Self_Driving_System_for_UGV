package com.example.android_picomm

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.text.InputType.TYPE_NUMBER_FLAG_DECIMAL
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import android.text.InputType
import android.text.method.DigitsKeyListener


class MainActivity : AppCompatActivity() {
    lateinit var mConnectButton: Button
    lateinit var mDisconnectButton: Button
    lateinit var mSaveButton: Button
    lateinit var mIPTextView: TextView
    lateinit var mIPEditText: EditText
    lateinit var mPortTextView: TextView
    lateinit var mPortEditText: EditText
    lateinit var mSensorRecyclerView: RecyclerView

    enum class UI(val UIName: String){
        MAIN("main"),
    }

    data class SendAddress(var IP: String, var port: Int)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    fun setupUI(uiName: String){
        when(uiName){
            UI.MAIN.UIName -> {
                mConnectButton = findViewById(R.id.connect_button)
                mDisconnectButton = findViewById(R.id.disconnect_button)
                mIPTextView = findViewById(R.id.ip_textView)
                mSaveButton = findViewById(R.id.save_button)
                mIPEditText = findViewById(R.id.ip_editText)
                mIPEditText.onlyNumbers()
                mPortTextView = findViewById(R.id.port_textView)
                mPortEditText = findViewById(R.id.port_editText)
                mSensorRecyclerView = findViewById(R.id.sensor_list)

            }
        }
    }

    fun EditText.onlyNumbers() {
        inputType = InputType.TYPE_CLASS_NUMBER or InputType.TYPE_NUMBER_FLAG_DECIMAL or InputType.TYPE_NUMBER_FLAG_SIGNED
        keyListener = DigitsKeyListener.getInstance("0123456789.")
    }
}
