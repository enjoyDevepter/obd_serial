package com.miyuan.obd.serial;

/**
 * 固定数据类型
 */
public class FixedDataType {

    /**
     * 电瓶电压
     */
    public static final int FIXED_DATA_VOLTAGE = 1;
    /**
     * 瞬时油耗
     */
    public static final int FIXED_DATA_INSTANTANEOUS_FUEL_CONSUMPTION = 2;
    /**
     * 瞬时油耗
     */
    public static final int FIXED_DATA_AVERAGE_FUEL_CONSUMPTION = 3;
    /**
     * 本次行程总油耗
     */
    public static final int FIXED_DATA_TOTAL_FUEL_CONSUMPTION_DURING_THIS_TRIP = 4;
    /**
     * 本次行驶里程
     */
    public static final int FIXED_DATA_MILEAGE_OF_THIS_TRIP = 5;
    /**
     * 总里程
     */
    public static final int FIXED_DATA_TOTAL_MILEAGE = 6;
    /**
     * 本次行驶时长
     */
    public static final int FIXED_DATA_DRIVING_TIME_OF_THIS_TRIP = 7;
    /**
     * 行驶总时长
     */
    public static final int FIXED_DATA_TOTAL_DRIVING_TIME = 8;
}
