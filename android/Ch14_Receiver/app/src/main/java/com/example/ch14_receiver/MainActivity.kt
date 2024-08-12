package com.example.ch14_receiver

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.content.pm.PackageManager
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.BatteryManager
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import androidx.activity.result.contract.ActivityResultContracts
import androidx.core.content.ContextCompat
import com.example.ch14_receiver.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var chargingReceiver: ChargingReceiver

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val binding = ActivityMainBinding.inflate(layoutInflater)

        //setContentView(R.layout.activity_main)
        setContentView(binding.root)

        chargingReceiver = ChargingReceiver(binding)

        val intentFilter = IntentFilter(Intent.ACTION_BATTERY_CHANGED)
        registerReceiver(chargingReceiver, intentFilter)


        //add......................
        val permissionLauncher = registerForActivityResult(
            ActivityResultContracts.RequestMultiplePermissions()
        ) {
            if (it.all { permission -> permission.value == true }) {
                val intent = Intent(this, MyReceiver::class.java)
                sendBroadcast(intent)
            } else {
                Toast.makeText(this, "permission denied...", Toast.LENGTH_SHORT).show()
            }
        }


        registerReceiver(null, IntentFilter(Intent.ACTION_BATTERY_CHANGED))!!.apply{
            when(getIntExtra(BatteryManager.EXTRA_STATUS, -1)){
                BatteryManager.BATTERY_STATUS_CHARGING -> {
                    when(getIntExtra(BatteryManager.EXTRA_PLUGGED, -1)){
                        BatteryManager.BATTERY_PLUGGED_USB -> {
                            binding.chargingResultView.text = "USB Plugged"
                            binding.chargingImageView.setImageBitmap(
                                BitmapFactory.decodeResource(
                                resources, R.drawable.usb
                            ))
                        }
                        BatteryManager.BATTERY_PLUGGED_AC -> {
                            binding.chargingResultView.text = "AC Plugged"
                            binding.chargingImageView.setImageBitmap(BitmapFactory.decodeResource(
                                resources, R.drawable.ac
                            ))
                        }
                    }
                }
                else -> {
                    binding.chargingResultView.text = "Not Plugged"
                }



            }

            val level = getIntExtra(BatteryManager.EXTRA_LEVEL, -1)
            val scale = getIntExtra(BatteryManager.EXTRA_SCALE, -1)
            val batteryPct = level / scale.toFloat() * 100
            binding.percentResultView.text = "$batteryPct %"

        }

        binding.button.setOnClickListener {
            if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
                if (ContextCompat.checkSelfPermission(
                        this,
                        "android.permission.POST_NOTIFICATIONS"
                    ) == PackageManager.PERMISSION_GRANTED
                ) {
                    val intent = Intent(this, MyReceiver::class.java)
                    sendBroadcast(intent)
                } else {
                    permissionLauncher.launch(
                        arrayOf(
                            "android.permission.POST_NOTIFICATIONS"
                        )
                    )

                    Log.d("neil","else...............")
                }
            }else {
                val intent = Intent(this, MyReceiver::class.java)
                sendBroadcast(intent)
            }

        }

    }

    override fun onDestroy() {
        super.onDestroy()
        unregisterReceiver(chargingReceiver)
    }

}

class ChargingReceiver(private val binding: ActivityMainBinding) : BroadcastReceiver() {
    override fun onReceive(context: Context, intent: Intent) {
        when(intent.getIntExtra(BatteryManager.EXTRA_STATUS, -1)){
            BatteryManager.BATTERY_STATUS_CHARGING -> {
                when(intent.getIntExtra(BatteryManager.EXTRA_PLUGGED, -1)){
                    BatteryManager.BATTERY_PLUGGED_USB -> {
                        binding.chargingResultView.text = "USB Plugged"
                        binding.chargingImageView.setImageBitmap(
                            BitmapFactory.decodeResource(
                                context.resources, R.drawable.usb
                            ))
                    }
                    BatteryManager.BATTERY_PLUGGED_AC -> {
                        binding.chargingResultView.text = "AC Plugged"
                        binding.chargingImageView.setImageBitmap(
                            BitmapFactory.decodeResource(
                                context.resources, R.drawable.ac
                            ))
                    }
                }
            }
            else -> {
                binding.chargingResultView.text = "Not Plugged"
                binding.chargingImageView.setImageBitmap(null) // 이미지 제거
            }
        }

        val level = intent.getIntExtra(BatteryManager.EXTRA_LEVEL, -1)
        val scale = intent.getIntExtra(BatteryManager.EXTRA_SCALE, -1)
        val batteryPct = level / scale.toFloat() * 100
        binding.percentResultView.text = "$batteryPct %"
    }
}
