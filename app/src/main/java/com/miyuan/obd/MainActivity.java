package com.miyuan.obd;

import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.miyuan.obd.serial.FaultCode;
import com.miyuan.obd.serial.OBDCore;

import java.io.File;
import java.util.List;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    TextView sample_text;
    EditText indexET;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        sample_text = findViewById(R.id.sample_text);
        findViewById(R.id.start).setOnClickListener(this);
        findViewById(R.id.stop).setOnClickListener(this);
        findViewById(R.id.mile).setOnClickListener(this);
        findViewById(R.id.getFaultCode).setOnClickListener(this);
        findViewById(R.id.cleanFaultCode).setOnClickListener(this);
        findViewById(R.id.getFixedData).setOnClickListener(this);
        findViewById(R.id.getDynamicData).setOnClickListener(this);
        sample_text.setText(OBDCore.getInstance(this).getVersion());
        indexET = findViewById(R.id.index);
    }

    @Override
    public void onClick(View v) {
        int index = 0;
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
                try {
                    index = Integer.valueOf(indexET.getText().toString().trim());
                } catch (Exception e) {
                    Toast.makeText(this, "请输入数字后重试!", Toast.LENGTH_LONG).show();
                    break;
                }
//                sample_text.setText(String.valueOf(OBDCore.getInstance(this).getFixedData(index)));
                break;
            case R.id.getDynamicData:
                Intent intent = new Intent(this, PanelActivity.class);
                startActivity(intent);
                break;
            case R.id.mile:
                try {
                    index = Integer.valueOf(indexET.getText().toString().trim());
                } catch (Exception e) {
                    Toast.makeText(this, "请输入数字后重试!", Toast.LENGTH_LONG).show();
                    break;
                }
                sample_text.setText(String.valueOf(OBDCore.getInstance(this).initMiles(index)));
                break;
            default:
                break;
        }
    }
}
