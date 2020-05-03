package com.pz.iotmanager;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.Switch;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import com.google.android.material.bottomnavigation.BottomNavigationView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.NavigationUI;

import org.jetbrains.annotations.NotNull;

import java.io.File;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class MainActivity extends AppCompatActivity
{

    TextView title;
    NavController navBar;
    private static final String devices_json_filename = "devices.json";
    private static final String admin_log = "log.txt";
    private final String PREFERENCE_FILE_KEY = "IoTSettings";
    SharedPreferences preferences;
    SharedPreferences.Editor edit;
    public List<Device> devices;
    boolean adminMode = false;
    public Device selected_device = null;

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

        navView.getMenu().findItem(R.id.navigation_admin).setVisible(false);

        preferences = getSharedPreferences(PREFERENCE_FILE_KEY, MODE_PRIVATE);
        edit = preferences.edit();
        edit.putBoolean("admin", false);
        edit.apply();
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

    public void adminMode(View view)
    {
        Switch admin_switch = findViewById(R.id.admin_switch);
        Switch log_switch = findViewById(R.id.log_switch);

        log_switch.setEnabled(admin_switch.isChecked());

        BottomNavigationView navView = findViewById(R.id.nav_view);
        navView.getMenu().findItem(R.id.navigation_admin).setVisible(admin_switch.isChecked());
        edit.putBoolean("admin", admin_switch.isChecked());
        edit.apply();
    }

    public void setSaveLogs(View view)
    {
        Switch log_switch = findViewById(R.id.log_switch);
        edit.putBoolean("logs", log_switch.isChecked());
        edit.apply();
    }

    public void onConnect(View view) {

        //Chwilowo do testów. Zmieni się jak będzie działało wyświetlanie urządzeń

        List<Integer> adres = new ArrayList<>();

        adres.addAll(Arrays.asList(172, 16, 0, 5));

        Device test = new Device();

        test.address = adres;
        test.name = "test";
        test.protocol = "http";

        selected_device = test;

        if (selected_device.protocol == "http")
        {

            String ip = "";

            for (int i = 0;i<test.address.size();i++)
            {
                ip+=test.address.get(i);

                if(i!=test.address.size()-1)
                {
                    ip+=".";
                }
            }

            String url = "http://"+ip+"/sensors";

            OkHttpClient okHttpClient = new OkHttpClient();

            Request request = new Request.Builder()
                    .url(url)
                    .build();

            okHttpClient.newCall(request).enqueue(new Callback() {
                @Override
                public void onFailure(@NotNull Call call, @NotNull IOException e) {
                    e.printStackTrace();
                }

                @Override
                public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                    if(response.isSuccessful())
                    {
                        String myResponse = response.body().string();

                        String[] separated = myResponse.split(" ");

                        List<String> sensors = new ArrayList<>();
                        List<String> sensor_signs = new ArrayList<>();

                        for(int i = 0;i<separated.length;i++)
                        {
                            String[] separated2 = separated[i].split(":");

                            sensors.add(separated2[0]);
                            sensor_signs.add(separated2[1]);

                        }

                        selected_device.sensors = sensors;
                        selected_device.sensor_signs = sensor_signs;

                    }
                }
            });

        }

    }


    public void onRead(View view) {

        if (selected_device != null)
        {
            final Device device = selected_device;

            if(device.protocol == "http")
            {

                String ip = "";

                for (int i = 0;i<device.address.size();i++)
                {
                    ip+=device.address.get(i);

                    if(i!=device.address.size()-1)
                    {
                        ip+=".";
                    }
                }

                if (device.sensor_signs != null && device.sensors != null){

                    for(int i = 0;i<device.sensors.size();i++)
                    {

                        String url = "http://"+ip+"/"+device.sensors.get(i);

                        final String sensor_sign = device.sensor_signs.get(i);

                        OkHttpClient okHttpClient = new OkHttpClient();

                        Request request = new Request.Builder()
                                .url(url)
                                .build();

                        okHttpClient.newCall(request).enqueue(new Callback() {
                            @Override
                            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                                e.printStackTrace();
                            }

                            @Override
                            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                                if(response.isSuccessful())
                                {
                                    String myResponse = response.body().string();

                                    final TableLayout tableLayout = (TableLayout) findViewById(R.id.main_table);

                                    final TableRow tableRow = new TableRow(MainActivity.this);

                                    tableRow.setLayoutParams(new TableRow.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));

                                    TextView id_urzadzenia = new TextView(MainActivity.this);

                                    id_urzadzenia.setText("1");
                                    id_urzadzenia.setGravity(Gravity.CENTER);

                                    TextView nazwa = new TextView(MainActivity.this);

                                    nazwa.setText(device.name);
                                    nazwa.setGravity(Gravity.CENTER);

                                    TextView odczyt = new TextView(MainActivity.this);

                                    myResponse = myResponse + sensor_sign;

                                    odczyt.setText(myResponse);
                                    odczyt.setGravity(Gravity.CENTER);

                                    tableRow.addView(id_urzadzenia);
                                    tableRow.addView(nazwa);
                                    tableRow.addView(odczyt);

                                    MainActivity.this.runOnUiThread(new Runnable() {
                                        @Override
                                        public void run() {
                                            tableLayout.addView(tableRow);
                                        }
                                    });

                                }
                            }
                        });

                    }
                }

            }
        }
    }


    public void sendCommand(View view)
    {
        final EditText outText = (EditText) findViewById(R.id.terminalText);
        ScrollView sview = (ScrollView) findViewById(R.id.adminScroll);
        EditText inputText = (EditText) findViewById(R.id.inText);

        String text = inputText.getText().toString();
        inputText.setText("");

        outText.append("\n>: " + text);
        if(!text.equals(""))
        {
            if(text.equals("help"))
            {
                outText.append("\nDostępne polecenia:");
                outText.append("\ntestwifi - Test łączności WiFi \ntestiot http://0.0.0.0/sensors - Test łączności z IoT\nclear - Wyczyść ekran");
            }
            if(text.equals("testwifi"))
            {

                String url = "https://postman-echo.com/get?foo1=bar1&foo2=bar2";

                OkHttpClient okHttpClient = new OkHttpClient();

                Request request = new Request.Builder()
                        .url(url)
                        .build();

                okHttpClient.newCall(request).enqueue(new Callback()
                {
                    @Override
                    public void onFailure(@NotNull Call call, @NotNull IOException e) {

                        final String myResponse = e.getMessage().toString();

                        MainActivity.this.runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                outText.append("\nProblem z połączeniem WiFi");
                            }
                        });



                    }

                    @Override
                    public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                        if(response.isSuccessful())
                        {
                            final String myResponse = response.body().string();

                            MainActivity.this.runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    outText.append("\nWifi aktywne");
                                }
                            });
                        }
                        else
                        {
                            MainActivity.this.runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    outText.append("\nProblem z połączeniem WiFi");
                                }
                            });
                        }
                    }
                });


            }
            if(text.equals("clear")) outText.setText("");

            String[] separated = text.split(" ");

            if(separated[0].equals("testiot"))
            {
                if(separated.length > 1)
                {
                    String url = separated[1];

                    OkHttpClient okHttpClient = new OkHttpClient();

                    Request request = new Request.Builder()
                            .url(url)
                            .build();

                    okHttpClient.newCall(request).enqueue(new Callback() {
                        @Override
                        public void onFailure(@NotNull Call call, @NotNull IOException e) {

                            final String myResponse = e.getMessage().toString();

                            MainActivity.this.runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    outText.append("\nOdpowiedź: ");
                                    outText.append(myResponse);
                                }
                            });



                        }

                        @Override
                        public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                            if(response.isSuccessful())
                            {
                                final String myResponse = response.body().string();

                                MainActivity.this.runOnUiThread(new Runnable() {
                                    @Override
                                    public void run() {
                                        outText.append("\nOdpowiedź: ");
                                        outText.append(myResponse);
                                    }
                                });
                            }
                            else
                            {
                                MainActivity.this.runOnUiThread(new Runnable() {
                                    @Override
                                    public void run() {
                                        outText.append("\nProblem z połączeniem z urządzeniem IoT");
                                    }
                                });
                            }
                        }
                    });
                }
            }
        }
        if(preferences.getBoolean("logs", false)) saveLog();
        sview.fullScroll(View.FOCUS_DOWN);
    }

    void saveLog()
    {
        Context context = getApplicationContext();
        EditText terminal = (EditText) findViewById(R.id.terminalText);
        try
        {
            OutputStreamWriter outputStreamWriter = new OutputStreamWriter(context.openFileOutput(admin_log, Context.MODE_PRIVATE));
            Log.println(Log.ERROR,"Zapisywanie!", terminal.getText().toString());
            outputStreamWriter.write(terminal.getText().toString());
            outputStreamWriter.close();
        }
        catch (IOException ex)
        {
            terminal.append("\nERRROR: Błąd zapisywania logów!");
            terminal.append("\n" + ex.getMessage());
        }
    }
}
