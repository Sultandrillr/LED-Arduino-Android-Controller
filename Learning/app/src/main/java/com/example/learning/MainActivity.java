package com.example.learning;

import android.os.Bundle;
import android.util.Log;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.PrimaryKey;

import java.util.Calendar;

public class MainActivity extends AppCompatActivity {

    //private Button;
    //private TextView;

    //this is the fucking database. DO NOT REMOVE THIS THINKING ITS A 2ND CLASS
    @Entity
    public class Arduino_Info{
        @PrimaryKey
        public int Arduino_ID;
        @ColumnInfo(name = "IP Address")
        public String IP_Address;

        @ColumnInfo(name = "MAC Address")
        public String MAC_Address;

        @ColumnInfo(name = "Device Name")
        public String Device_Name;

        @ColumnInfo(name = "Port Number")
        public short Port;

        @ColumnInfo(name = "UUID")
        public String UUID;

        //When I implement HTTPS then I am going to uncomment this line below
        //@ColumnInfo(name = "Authentication Token")
        //public String Auth_Token;

    }



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

    public class Arduino_Controller{
        public String ID;
        public String Name;
        public String Name_On_Network;
        public String IP;
        public String MAC;
        public boolean is_Connected;

        public short red;
        public short green;
        public short blue;

        //This calls when a new controller object is created and sets all the values
        public Arduino_Controller(String ID, String Name, String Name_On_Network, String IP, String MAC, boolean is_Connected, short red, short green, short blue){
            this.ID = ID;
            this.Name = Name;
            this.Name_On_Network = Name_On_Network;
            this.IP = IP;
            this.MAC = MAC;
            this.is_Connected = is_Connected;
            this.red = red;
            this.green = green;
            this.blue = blue;
        }
        //apparently I need callbacks for error handling but im too tired so I will do that tomorrow. This is where you have stopped so far
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