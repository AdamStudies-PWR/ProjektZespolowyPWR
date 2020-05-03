package com.pz.iotmanager.ui.admin;

import android.app.ActionBar;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;

import com.pz.iotmanager.MainActivity;
import com.pz.iotmanager.R;
import com.pz.iotmanager.Device;

import org.jetbrains.annotations.NotNull;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Collection;
import java.util.Iterator;
import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;


public class AdminFragment extends Fragment
{

    private AdminViewModel adminViewModel;
    private final String PREFERENCE_FILE_KEY = "IoTSettings";
    private static final String admin_log = "log.txt";

    SharedPreferences preferences;
    SharedPreferences.Editor edit;

    MainActivity activity;
    TextView title;

    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        adminViewModel = ViewModelProviders.of(this).get(AdminViewModel.class);
        View root = inflater.inflate(R.layout.fragment_admin, container, false);

        activity = ((MainActivity) getActivity());

        title = activity.findViewById(R.id.textTitle);
        title.setText(R.string.title_admin);

        preferences = activity.getSharedPreferences(PREFERENCE_FILE_KEY, activity.MODE_PRIVATE);
        edit = preferences.edit();

        EditText terminal = root.findViewById(R.id.terminalText);

        if(preferences.getBoolean("logs", false))
        {
            Context context = activity.getApplicationContext();
            try
            {
                InputStream inputStream = context.openFileInput(admin_log);

                if ( inputStream != null )
                {
                    InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
                    BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
                    String receiveString = "";
                    StringBuilder stringBuilder = new StringBuilder();

                    while ( (receiveString = bufferedReader.readLine()) != null )
                    {
                        terminal.append(receiveString);
                        stringBuilder.append("\n").append(receiveString);
                    }

                    inputStream.close();
                    terminal.setText(stringBuilder.toString());
                }
            }
            catch (FileNotFoundException e) {}
            catch (IOException e) {}
        }


        return root;
    }
}
