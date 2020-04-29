package com.pz.iotmanager;

import android.os.Bundle;
import android.widget.TextView;

import com.google.android.material.bottomnavigation.BottomNavigationView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.NavigationUI;

import java.io.File;
import java.io.IOException;
import java.util.List;

public class MainActivity extends AppCompatActivity
{

    TextView title;
    NavController navBar;
    private static final String devices_json_filename = "devices.json";
    public List<Device> devices;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        BottomNavigationView navView = findViewById(R.id.nav_view);
        navBar = Navigation.findNavController(this, R.id.nav_host_fragment);
        NavigationUI.setupWithNavController(navView, navBar);

        title = (TextView) findViewById(R.id.textTitle);
        title.setText(R.string.title_devices);

        // Read saved instances of device
        File file = new File(getFilesDir(), devices_json_filename);
        devices = Device.readFromFile(file);
    }
    @Override
    protected void onStop() {
        super.onStop();
        File file = new File(getFilesDir(), devices_json_filename);
        try {
            Device.writeToFile(file, devices);
        } catch (IOException ex)
        {
            //TODO handle
        }
    }

}
