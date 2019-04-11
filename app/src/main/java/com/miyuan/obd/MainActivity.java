package com.miyuan.obd;

import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

import com.miyuan.obd.serial.DynamicDataType;
import com.miyuan.obd.serial.FaultCode;
import com.miyuan.obd.serial.FixedDataType;
import com.miyuan.obd.serial.OBDCore;

import java.io.File;
import java.util.List;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    TextView sample_text;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        sample_text = findViewById(R.id.sample_text);
        findViewById(R.id.start).setOnClickListener(this);
        findViewById(R.id.stop).setOnClickListener(this);
        findViewById(R.id.getFaultCode).setOnClickListener(this);
        findViewById(R.id.cleanFaultCode).setOnClickListener(this);
        findViewById(R.id.getFixedData).setOnClickListener(this);
        findViewById(R.id.getDynamicData).setOnClickListener(this);
        sample_text.setText(OBDCore.getInstance(this).getVersion());
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.start:
                sample_text.setText(String.valueOf(OBDCore.getInstance(this).setCarStatus(true)));
                break;
            case R.id.stop:
                sample_text.setText(String.valueOf(OBDCore.getInstance(this).setCarStatus(false)));
                break;
            case R.id.getFaultCode:
                StringBuilder sb = new StringBuilder();
                File file = new File(Environment.getExternalStorageDirectory().getPath() + File.separator + "physical.db");
                if (!file.exists()) {
                    return;
                }
                if (!file.canRead()) {
                    return;
                }
                List<FaultCode> codes = OBDCore.getInstance(this).getFaultCode(file.getPath());
                for (FaultCode code : codes) {
                    sb.append(code.toString())
                            .append("\r\n");
                }
                sample_text.setText(sb.toString());
                break;
            case R.id.cleanFaultCode:
                sample_text.setText(String.valueOf(OBDCore.getInstance(this).cleanFaultCode()));
                break;
            case R.id.getFixedData:
                sample_text.setText(String.valueOf(OBDCore.getInstance(this).getFixedData(FixedDataType.FIXED_DATA_TOTAL_MILEAGE)));
                break;
            case R.id.getDynamicData:
                sample_text.setText(OBDCore.getInstance(this).getDynamicData(DynamicDataType.DYNAMIC_DATA_FUEL_TYPE));
                break;

        }
    }
}
