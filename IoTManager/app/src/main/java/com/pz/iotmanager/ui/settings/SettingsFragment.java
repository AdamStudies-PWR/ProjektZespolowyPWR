package com.pz.iotmanager.ui.settings;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Switch;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;

import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.pz.iotmanager.MainActivity;
import com.pz.iotmanager.R;

public class SettingsFragment extends Fragment
{

    private SettingsViewModel settingsViewModel;
    private final String PREFERENCE_FILE_KEY = "IoTSettings";
    SharedPreferences preferences;
    SharedPreferences.Editor edit;

    MainActivity activity;
    TextView title;

    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        settingsViewModel = ViewModelProviders.of(this).get(SettingsViewModel.class);
        View root = inflater.inflate(R.layout.fragment_settings, container, false);

        activity = ((MainActivity) getActivity());

        title = activity.findViewById(R.id.textTitle);
        title.setText(R.string.title_settings);

        preferences = activity.getSharedPreferences(PREFERENCE_FILE_KEY, activity.MODE_PRIVATE);
        edit = preferences.edit();

        Switch adminSwitch = root.findViewById(R.id.admin_switch);
        adminSwitch.setChecked(preferences.getBoolean("admin", false));

        return root;
    }
}
