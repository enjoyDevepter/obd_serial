package com.miyuan.obd;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import com.miyuan.obd.serial.OBDCore;
import com.miyuan.obd.serial.PanelBoardInfo;

import java.util.Timer;
import java.util.TimerTask;


public class PanelActivity extends AppCompatActivity {

    private TextView voltage;
    private TextView instantaneousFuelConsumption;
    private TextView averageFuelConsumption;
    private TextView totalFuelConsumptionDuringThisTrip;
    private TextView mileageOfTrip;
    private TextView totalMileage;
    private TextView drivingTimeOfTrip;
    private TextView totalDrivingTime;
    private TextView rotationRate;
    private TextView speed;
    private TextView temperature;
    private TextView engineLoad;
    private TextView residualFuel;
    Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            if (null != panelBoardInfo) {
                voltage.setText(String.valueOf(panelBoardInfo.getVoltage()) + "V");
                instantaneousFuelConsumption.setText(String.valueOf(panelBoardInfo.getInstantaneousFuelConsumption()) + "L/HOUR");
                averageFuelConsumption.setText(String.valueOf(panelBoardInfo.getAverageFuelConsumption()) + "L/100KM");
                totalFuelConsumptionDuringThisTrip.setText(String.valueOf(panelBoardInfo.getTotalFuelConsumptionDuringThisTrip()) + "L");
                mileageOfTrip.setText(String.valueOf(panelBoardInfo.getMileageOfTrip()) + "KM");
                totalMileage.setText(String.valueOf(panelBoardInfo.getTotalMileage()) + "KM");
                drivingTimeOfTrip.setText(String.valueOf(panelBoardInfo.getDrivingTimeOfTrip()) + "秒");
                totalDrivingTime.setText(String.valueOf(panelBoardInfo.getTotalDrivingTime()) + "秒");
                rotationRate.setText(String.valueOf(panelBoardInfo.getRotationRate()) + "RPM");
                speed.setText(String.valueOf(panelBoardInfo.getSpeed()) + "KM/H");
                temperature.setText(String.valueOf(panelBoardInfo.getTemperature()) + "℃");
                engineLoad.setText(String.valueOf(panelBoardInfo.getEngineLoad()) + "%");
                residualFuel.setText(String.valueOf(panelBoardInfo.getResidualFuel()) + "%");
            }
        }
    };
    private Timer timer;
    private TimerTask timerTask;

    private boolean start;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.panel_board);
        voltage = findViewById(R.id.voltage);
        instantaneousFuelConsumption = findViewById(R.id.instantaneousFuelConsumption);
        averageFuelConsumption = findViewById(R.id.averageFuelConsumption);
        totalFuelConsumptionDuringThisTrip = findViewById(R.id.totalFuelConsumptionDuringThisTrip);
        mileageOfTrip = findViewById(R.id.mileageOfTrip);
        totalMileage = findViewById(R.id.totalMileage);
        drivingTimeOfTrip = findViewById(R.id.drivingTimeOfTrip);
        totalDrivingTime = findViewById(R.id.totalDrivingTime);
        rotationRate = findViewById(R.id.rotationRate);
        speed = findViewById(R.id.speed);
        temperature = findViewById(R.id.temperature);
        engineLoad = findViewById(R.id.engineLoad);
        residualFuel = findViewById(R.id.residualFuel);
        OBDCore.getInstance(this).open("/dev/ttyMT0");

    }

    PanelBoardInfo panelBoardInfo;

    @Override
    protected void onResume() {
        super.onResume();
        timer = new Timer();
        timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                panelBoardInfo = OBDCore.getInstance(PanelActivity.this).getFixedData();
                handler.sendEmptyMessage(0);
            }
        }, 2000, 1000);
    }

    @Override
    protected void onPause() {
        super.onPause();
        timer.cancel();
    }
}
