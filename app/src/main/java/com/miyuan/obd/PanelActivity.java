package com.miyuan.obd;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import com.miyuan.obd.serial.OBDCore;
import com.miyuan.obd.serial.PanelBoardInfo;
import com.tbruyelle.rxpermissions2.RxPermissions;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.List;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import me.jessyan.rxerrorhandler.core.RxErrorHandler;
import me.jessyan.rxerrorhandler.handler.listener.ResponseErrorListener;


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
    private TextView versionTV;
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
                if (panelBoardInfo.getStatus() != start) {
                    init(panelBoardInfo.getStatus());
                    start = panelBoardInfo.getStatus();
                }
            }
        }
    };

    private void init(boolean start) {
        String status = "";
        if (start) {
            // 开启
            status = "1 175";
        } else {
            // 关闭
            status = "0 175";
        }
        final File file = new File("/sys/devices/platform/rc_motor/stepmotor");
        if (file.exists()) {
            FileOutputStream fos = null;
            try {
                fos = new FileOutputStream(file);
                fos.write(status.getBytes());
                fos.flush();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    if (null != fos) {
                        fos.close();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

    }

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
        versionTV = findViewById(R.id.version);
        OBDCore.getInstance(this).open("/dev/ttyLP3");
//        Log.d("PanelActivity init ");
    }

    PanelBoardInfo panelBoardInfo;

    @Override
    protected void onResume() {
        super.onResume();
        ScheduledExecutorService scheduledExecutorService =
                Executors.newSingleThreadScheduledExecutor();
        scheduledExecutorService.scheduleAtFixedRate(new Runnable() {
                                                         @Override
                                                         public void run() {
                                                             panelBoardInfo = OBDCore.getInstance(PanelActivity.this).getFixedData();
                                                             handler.sendEmptyMessage(0);
                                                         }
                                                     },
                2, 1, TimeUnit.SECONDS);

        PermissionUtil.requestPermissionForInit(new PermissionUtil.RequestPermission() {
            @Override
            public void onRequestPermissionSuccess() {

            }

            @Override
            public void onRequestPermissionFailure(List<String> permissions) {
            }

            @Override
            public void onRequestPermissionFailureWithAskNeverAgain(List<String> permissions) {
            }
        }, new RxPermissions(this), RxErrorHandler.builder().with(this).responseErrorListener(new ResponseErrorListener() {
            @Override
            public void handleResponseError(Context context, Throwable t) {

            }
        }).build());
    }
}
