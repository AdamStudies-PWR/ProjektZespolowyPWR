package com.pz.iotmanager.ui.devices;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatDialogFragment;

import com.pz.iotmanager.Device;
import com.pz.iotmanager.MainActivity;
import com.pz.iotmanager.R;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class AddDeviceDialog extends AppCompatDialogFragment {
    EditText name;
    EditText ip;
    EditText protocol;

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        LayoutInflater inflater = getActivity().getLayoutInflater();
        View view = inflater.inflate(R.layout.add_device_dialog, null);
        builder.setView(view)
                .setTitle("Add Device").setPositiveButton("Add",
                new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialogInterface, int i) {

                    MainActivity activity = ((MainActivity) getActivity());

                    String full_ip = ip.getText().toString();

                    full_ip = full_ip.trim();

                    String[] ip_separated = full_ip.split("[.]");

                    List<Integer> adres = new ArrayList<>();

                    for(int j = 0;j<ip_separated.length;j++){
                        adres.add(Integer.parseInt(ip_separated[j]));
                    }

                    Device device = new Device();
                    device.name = name.getText().toString();
                    device.protocol = protocol.getText().toString();
                    device.address = adres;
                    device.id = activity.devices.size();
                    activity.devices.add(device);

                    activity.display();
                }
                });

        name = view.findViewById(R.id.editText);
        ip = view.findViewById(R.id.editText3);
        protocol = view.findViewById(R.id.editText5);

        return builder.create();
    }

}
