package com.miyuan.obd.serial;

import java.util.ArrayList;
import java.util.List;

/**
 * OBD通信核心类
 */
public class OBDCore {

    private OBDBusiness obdBusiness;

    /**
     * 禁止构造
     */
    private OBDCore() {
        obdBusiness = new OBDBusiness();
    }

    /**
     * 获得单例
     *
     * @return {@link OBDCore}
     */
    public static OBDCore getInstance() {
        return InstanceHolder.INSTANCE;
    }

    /**
     * 单例持有器
     */
    private static final class InstanceHolder {
        private static final OBDCore INSTANCE = new OBDCore();
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
        return new ArrayList<>();
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
     * 根据固定数据类型获取相应数据
     *
     * @param fixedDataType 固定数据类型 {@link com.miyuan.obd.serial.FixedDataType}
     * @return 固定数据类型对应数据
     */
    public synchronized String getFixedData(int fixedDataType) {
        return obdBusiness.getFixedData(fixedDataType);
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

}
