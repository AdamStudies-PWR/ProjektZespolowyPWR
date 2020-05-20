package com.pz.iotmanager.ui.devices;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatDialogFragment;

import com.pz.iotmanager.R;

public class AddDeviceDialog extends AppCompatDialogFragment {
    EditText name;
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
                }
                });
        name = view.findViewById(R.id.editText);
        return builder.create();

    }
}
