package com.pz.iotmanager.ui.sensors;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;

import com.pz.iotmanager.MainActivity;
import com.pz.iotmanager.R;

public class SensorsFragment extends Fragment {

    private SensorsViewModel sensorsViewModel;

    MainActivity activity;
    TextView title;

    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        sensorsViewModel = ViewModelProviders.of(this).get(SensorsViewModel.class);
        View root = inflater.inflate(R.layout.fragment_sensors, container, false);

        activity = ((MainActivity) getActivity());

        title = activity.findViewById(R.id.textTitle);
        title.setText(R.string.title_sensors);

        return root;
    }
}
