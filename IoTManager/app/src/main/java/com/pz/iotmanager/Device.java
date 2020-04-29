package com.pz.iotmanager;

import android.util.JsonReader;
import android.util.JsonToken;
import android.util.JsonWriter;

import org.json.*;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.io.*;

public class Device {
    public List<Integer> address;
    public String name;
    public String protocol;

    public static List<Device> readFromFile(File file)
    {
        ArrayList<Device> devices= new ArrayList<>();
        // if FileReader could not be opened or json file structure is compromised,
        // function will return empty array
        try {
            JsonReader reader = new JsonReader(new FileReader(file));
            // read all json objects
            reader.beginArray();
            while(reader.hasNext())
            {
                reader.beginObject();
                Device device = new Device();
                // read object attributes
                while(reader.hasNext())
                {
                    // get attribute name and parse values
                    String name = reader.nextName();
                    if (name.equals("address") && reader.peek() != JsonToken.NULL) {
                        reader.beginArray();
                        List<Integer> address_list = new ArrayList<>();
                        while (reader.hasNext()) {
                            address_list.add(reader.nextInt());
                        }
                        device.address = address_list;
                        reader.endArray();
                    } else if (name.equals("name"))
                    {
                        device.name = reader.nextString();
                    } else if (name.equals("protocol"))
                    {
                        device.protocol = reader.nextString();
                    } else reader.skipValue();
                }
                devices.add(device);
                reader.endObject();
            }
            reader.endArray();
            reader.close();
        } catch(Exception ex)
        {
            System.out.println(ex.getMessage());
        }
        return devices;
    }

    public static void writeToFile(File file, List<Device> devices) throws IOException
    {
        if (devices.isEmpty()) return;
        JsonWriter writer = new JsonWriter(new FileWriter(file));
        writer.setIndent("\t");
        writer.beginArray();
        Iterator<Device> deviceIterator = devices.iterator();
        while (deviceIterator.hasNext())
        {
            writer.beginObject();
            Device device = deviceIterator.next();
            if (device.address != null && !device.address.isEmpty()) {
                writer.name("address");
                writer.beginArray();
                Iterator<Integer> addressIterator = device.address.iterator();
                while (addressIterator.hasNext())
                    writer.value(addressIterator.next());
                writer.endArray();
            }
            if (device.name != null && !device.name.isEmpty())
                writer.name("name").value(device.name);
            if (device.protocol != null && !device.protocol.isEmpty())
                writer.name("protocol").value(device.protocol);
            writer.endObject();
        }
        writer.endArray();
        writer.close();
    }

}
