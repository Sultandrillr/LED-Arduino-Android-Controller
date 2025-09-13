package com.example.learning;

import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import android.util.Log;
import android.widget.Button;
import android.widget.TextView;
import java.util.Calendar;
import java.util.Date;

public class MainActivity extends AppCompatActivity {

    //private Button;
    //private TextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.buttstuff33), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
    }

    class LED{
        //this class is just for storing how the LED is supposed to be. It will update real LED integer but do not mistake this for real LED
        private int LightLevel = 0;
        public void SetLightLevel(int x){
            if (x>-1 && x<225){
                LightLevel = x;
                Log.d("LightLevel",(String.valueOf(LightLevel)));
            }else {
                Log.e(String.valueOf(Calendar.getInstance().getTime()), "Light Level Outside Of Possible Range 0-225");
            }
        }
        public int GetLightLevel(){
            return LightLevel;
        }
    }
    LED red = new LED();
    LED green = new LED();
    LED blue = new LED();
    public void addDevice(){
        //open the database connection
    }

    public void tryDevice1(){
        //attempt to handshake with device and establish connection
    }

    public void tryDevice2(){

    }

    public void tryDevice3(){

    }

    public void tryDevice4(){

    }

    //what to do..... maybe a database with the information that is needed to connect to teh device such as IP address, name if it is connected or not. copy the code form moe for connecting to database.
    //you can probably collapse all of the functions into one by having it be tryDevice(deviceNumber){code to try deviceNumber, ask the database what is going on, if statements for database results, error handling for when there is no device in database. more error handling for when device cannot be connected to. if can connect establish connection and move to next screen
    //add device will just be connect to arduino in ap mode and tell it what wifi it should connect to. later add functionality to clear out the arduino wifi credentials. arduino will connect and send over its IP address... lil nigga
    // long time later... I am going to first write the code for sending http packets to arduino, arduino unpacks and then based on the input does some stuff. I hate front end shit
}
//nigger