package com.pz.iotmanager.ui.settings;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;

import com.pz.iotmanager.MainActivity;
import com.pz.iotmanager.R;

public class SettingsFragment extends Fragment {

    private SettingsViewModel settingsViewModel;

    MainActivity activity;
    TextView title;

    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        settingsViewModel = ViewModelProviders.of(this).get(SettingsViewModel.class);
        View root = inflater.inflate(R.layout.fragment_settings, container, false);

        activity = ((MainActivity) getActivity());

        title = activity.findViewById(R.id.textTitle);
        title.setText(R.string.title_settings);

        return root;
    }
}
