package com.miyuan.obd.serial;

import android.content.Context;

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
     * @param path 串口名称
     * @return 成功标识
     */
    public boolean open(String path) {
        return obdBusiness.open(path);
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
     * 获取仪表盘信息
     *
     * @return
     */
    public synchronized PanelBoardInfo getFixedData() {
        return obdBusiness.getFixedData();
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

    /**
     * 车辆是否启动
     *
     * @return 启动状态
     * true     启动
     * false    停止
     */
    public synchronized boolean isLaunched() {
        return obdBusiness.isLaunched();
    }


    /**
     * 连接是否正常
     *
     * @return
     */
    public boolean isConnect() {
        return obdBusiness.isConnect();
    }

    /**
     * 设置车辆是否有启停功能
     *
     * @param has
     * @return
     */
    public boolean setAutoStart(boolean has) {
        return obdBusiness.setAutoStart(has);
    }
}
