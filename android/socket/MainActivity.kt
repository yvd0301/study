package com.example.socket

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log

import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import java.io.InputStream
import java.io.OutputStream
import java.net.InetSocketAddress
import java.net.Socket


class MainActivity : AppCompatActivity() {

    private val serverIp = "1.2.3.4"
    private val serverPort = 8080

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // 코루틴을 사용하여 네트워크 작업 실행
        GlobalScope.launch(Dispatchers.IO) {
            connectToServer()
        }

    }


    private fun connectToServer() {
        val socket = Socket()
        Log.d("MainActivity", "connectToServer start")
        try {
            // 서버에 연결
            socket.connect(InetSocketAddress(serverIp, serverPort), 5000) // 5초 타임아웃 설정

            val outputStream: OutputStream = socket.getOutputStream()
            val inputStream: InputStream = socket.getInputStream()

            // 서버로 메시지 전송
            val message = "Hello from Android"
            outputStream.write(message.toByteArray())
            outputStream.flush()

            // 서버로부터 응답 받기
            val buffer = ByteArray(256)
            val bytesRead = inputStream.read(buffer)
            if (bytesRead > 0) {
                val response = String(buffer, 0, bytesRead)
                Log.d("Server Response", response)
            }

            // 소켓 닫기
            socket.close()
        } catch (e: Exception) {
            e.printStackTrace()
            Log.e("Socket Error", "Failed to connect to server: ${e.message}")
        }
    }

}