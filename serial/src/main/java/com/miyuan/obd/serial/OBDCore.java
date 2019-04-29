package com.miyuan.obd.serial;

import android.content.Context;
import android.os.Environment;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

/**
 * OBD通信核心类
 */
public class OBDCore {

    private static OBDBusiness obdBusiness;

    /**
     * 禁止构造
     */
    private OBDCore() {
    }

    /**
     * 获得单例
     *
     * @return {@link OBDCore}
     */
    public static OBDCore getInstance(final Context context) {
        obdBusiness = new OBDBusiness();
        final File db = new File(Environment.getExternalStorageDirectory().getPath() + File.separator + "physical.db");
        if (!db.exists()) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        InputStream is = context.getAssets().open("physical.db");
                        final FileOutputStream fos = new FileOutputStream(db);
                        byte[] buffer = new byte[1024];
                        int byteCount = 0;
                        while ((byteCount = is.read(buffer)) != -1) {//循环从输入流读取 buffer字节
                            fos.write(buffer, 0, byteCount);//将读取的输入流写入到输出流
                        }
                        fos.flush();//刷新缓冲区
                        is.close();
                        fos.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }).start();
        }
        obdBusiness.initDBPath(db.getPath());
        return InstanceHolder.INSTANCE;
    }

    /**
     * 单例持有器
     */
    private static final class InstanceHolder {
        private static final OBDCore INSTANCE = new OBDCore();
    }

    /**
     * 开启串口设备
     *
     * @param path     串口名称
     * @param baudrate 波特率
     * @return 成功标识
     */
    public boolean open(String path, int baudrate) {
        return obdBusiness.open(path, baudrate);
    }

    /**
     * 关闭串口设备
     */
    public void close() {
        obdBusiness.close();
    }

    /**
     * 获取OBD版本号
     *
     * @return 版本号
     */
    public synchronized String getVersion() {
        return obdBusiness.getVersion();
    }


    /**
     * 获取故障码
     *
     * @return 故障码集合
     */
    public synchronized List<FaultCode> getFaultCode() {
        return obdBusiness.getFaultCode();
    }

    /**
     * 清除当前故障码
     *
     * @return 清除成功标示
     */
    public synchronized boolean cleanFaultCode() {
        return obdBusiness.cleanFaultCode();
    }


    /**
     * 获取仪表盘信息
     *
     * @return
     */
    public synchronized PanelBoardInfo getFixedData() {
        return obdBusiness.getFixedData();
    }


    /**
     * 根据实时数据类型获取相应数据
     *
     * @param dynamicDataType 实时数据类型 {@link com.miyuan.obd.serial.DynamicDataType}
     * @return 实时数据类型对应数据
     */
    public synchronized String getDynamicData(int dynamicDataType) {
        return obdBusiness.getDynamicData(dynamicDataType);
    }


    /**
     * 设置车辆起停状态
     *
     * @param status 起停状态
     *               true   车辆启动
     *               false  车辆停止
     */
    public synchronized boolean setCarStatus(boolean status) {
        return obdBusiness.setCarStatus(status);
    }

    /**
     * 设置车辆里程
     *
     * @param mile 仪表盘里程数
     */
    public synchronized boolean initMiles(int mile) {
        return obdBusiness.initMileage(mile);
    }

}
