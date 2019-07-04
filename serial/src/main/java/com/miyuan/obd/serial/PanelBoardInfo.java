package com.miyuan.obd.serial;

import java.io.Serializable;

/**
 * 仪表盘信息实体类
 */
public class PanelBoardInfo implements Serializable {
    private String voltage;
    private String instantaneousFuelConsumption;
    private String averageFuelConsumption;
    private String totalFuelConsumptionDuringThisTrip;
    private String mileageOfTrip;
    private String totalMileage;
    private String drivingTimeOfTrip;
    private String totalDrivingTime;
    private String rotationRate;
    private String speed;
    private String temperature;
    private String engineLoad;
    private String residualFuel;
    private String status;

    PanelBoardInfo(String voltage, String instantaneousFuelConsumption, String averageFuelConsumption, String totalFuelConsumptionDuringThisTrip, String mileageOfTrip, String totalMileage, String drivingTimeOfTrip, String totalDrivingTime, String rotationRate, String speed, String temperature, String engineLoad, String residualFuel, String status) {
        this.voltage = voltage;
        this.instantaneousFuelConsumption = instantaneousFuelConsumption;
        this.averageFuelConsumption = averageFuelConsumption;
        this.totalFuelConsumptionDuringThisTrip = totalFuelConsumptionDuringThisTrip;
        this.mileageOfTrip = mileageOfTrip;
        this.totalMileage = totalMileage;
        this.drivingTimeOfTrip = drivingTimeOfTrip;
        this.totalDrivingTime = totalDrivingTime;
        this.rotationRate = rotationRate;
        this.speed = speed;
        this.temperature = temperature;
        this.engineLoad = engineLoad;
        this.residualFuel = residualFuel;
        this.status = status;
    }

    /**
     * 获取电瓶电压
     *
     * @return
     */
    public String getVoltage() {
        return voltage;
    }

    /**
     * 获取瞬时油耗
     *
     * @return
     */
    public String getInstantaneousFuelConsumption() {
        return instantaneousFuelConsumption;
    }

    /**
     * 获取平均油耗
     *
     * @return
     */
    public String getAverageFuelConsumption() {
        return averageFuelConsumption;
    }

    /**
     * 获取本次行程总油耗
     *
     * @return
     */
    public String getTotalFuelConsumptionDuringThisTrip() {
        return totalFuelConsumptionDuringThisTrip;
    }

    /**
     * 获取本次行驶里程
     *
     * @return
     */
    public String getMileageOfTrip() {
        return mileageOfTrip;
    }

    /**
     * 获取总里程
     *
     * @return
     */
    public String getTotalMileage() {
        return totalMileage;
    }

    /**
     * 获取本次行驶时长
     *
     * @return
     */
    public String getDrivingTimeOfTrip() {
        return drivingTimeOfTrip;
    }

    /**
     * 获取当前行驶总时长
     *
     * @return
     */
    public String getTotalDrivingTime() {
        return totalDrivingTime;
    }

    /**
     * 获取转速
     *
     * @return
     */
    public String getRotationRate() {
        return rotationRate;
    }

    /**
     * 获取当前车速
     *
     * @return
     */
    public String getSpeed() {
        return speed;
    }

    /**
     * 获取当前水温
     *
     * @return
     */
    public String getTemperature() {
        return temperature;
    }

    /**
     * 获取发动机负荷
     *
     * @return
     */
    public String getEngineLoad() {
        return engineLoad;
    }

    /**
     * 获取剩余燃油
     *
     * @return
     */
    public String getResidualFuel() {
        return residualFuel;
    }

    /**
     * 获取车辆启动状态
     *
     * @return
     */
    public boolean getStatus() {
        return true;
    }


    @Override
    public String toString() {
        return "PanelBoardInfo{" +
                "voltage=" + voltage +
                ", instantaneousFuelConsumption=" + instantaneousFuelConsumption +
                ", averageFuelConsumption=" + averageFuelConsumption +
                ", totalFuelConsumptionDuringThisTrip=" + totalFuelConsumptionDuringThisTrip +
                ", mileageOfTrip=" + mileageOfTrip +
                ", totalMileage=" + totalMileage +
                ", drivingTimeOfTrip=" + drivingTimeOfTrip +
                ", totalDrivingTime=" + totalDrivingTime +
                ", rotationRate=" + rotationRate +
                ", speed=" + speed +
                ", temperature=" + temperature +
                ", engineLoad=" + engineLoad +
                ", residualFuel=" + residualFuel +
                ", status=" + status +
                '}';
    }
}
