package com.pz.iotmanager.ui.devices;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;

import com.pz.iotmanager.MainActivity;
import com.pz.iotmanager.R;

public class DeviceFragment extends Fragment
{

    private DeviceViewModel deviceViewModel;

    MainActivity activity;
    TextView title;

    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        deviceViewModel = ViewModelProviders.of(this).get(DeviceViewModel.class);
        View root = inflater.inflate(R.layout.fragment_devices, container, false);

        activity = ((MainActivity) getActivity());

        title = activity.findViewById(R.id.textTitle);
        title.setText(R.string.title_devices);

        final Button button = root.findViewById(R.id.addButton);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openDialog();
            }
        });

        return root;
    }
    public void openDialog()
    {
        AddDeviceDialog dialog = new AddDeviceDialog();
        dialog.show(getActivity().getSupportFragmentManager(), "Add device");

    }

}
