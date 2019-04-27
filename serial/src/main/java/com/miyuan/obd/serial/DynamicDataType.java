package com.miyuan.obd.serial;

/**
 * 实时数据类型
 */
public class DynamicDataType {
    /**
     * 电脑(ECU)中存储的故障码数量
     */
    public static final int DYNAMIC_DATA_FAULT_CODE_COUNT = 1;
    /**
     * 冻结故障码
     */
    public static final int DYNAMIC_DATA_FREEZING_FAULT_CODE = 2;
    /**
     * 燃油系统1状态
     */
    public static final int DYNAMIC_DATA_FUEL_SYSTEM_1_STATUS = 300;
    /**
     * 燃油系统2状态
     */
    public static final int DYNAMIC_DATA_FUEL_SYSTEM_2_STATUS = 301;
    /**
     * 发动机负荷
     */
    public static final int DYNAMIC_DATA_ENGINE_LOAD = 4;
    /**
     * 发动机冷却液温度
     */
    public static final int DYNAMIC_DATA_ENGINE_COOLANT_TEMPERATURE = 5;
    /**
     * 短期燃油调整（缸组1）
     */
    public static final int DYNAMIC_DATA_SHORT_TERM_FUEL_ADJUSTMENT_CYLINDER_GROUP_1 = 6;
    /**
     * 长期燃油调整（缸组1）
     */
    public static final int DYNAMIC_DATA_LONG_TERM_FUEL_ADJUSTMENT_CYLINDER_GROUP_1 = 7;
    /**
     * 短期燃油调整（缸组2）
     */
    public static final int DYNAMIC_DATA_SHORT_TERM_FUEL_ADJUSTMENT_CYLINDER_GROUP_2 = 8;
    /**
     * 长期燃油调整（缸组2）
     */
    public static final int DYNAMIC_DATA_LONG_TERM_FUEL_ADJUSTMENT_CYLINDER_GROUP_2 = 9;
    /**
     * 油轨油压
     */
    public static final int DYNAMIC_DATA_OIL_PRESSURE_OF_RAIL = 10;

    /**
     * 进气管绝对压力
     */
    public static final int DYNAMIC_DATA_ABSOLUTE_PRESSURE_OF_INTAKE_PIPE = 11;

    /**
     * 引擎转速
     */
    public static final int DYNAMIC_DATA_ENGINE_SPEED = 12;
    /**
     * 车速
     */
    public static final int DYNAMIC_DATA_SPEED = 13;
    /**
     * 点火提前角
     */
    public static final int DYNAMIC_DATA_IGNITION_ADVANCE_ANGLE = 14;
    /**
     * 进气温度
     */
    public static final int DYNAMIC_DATA_INTAKE_TEMPERATURE = 15;
    /**
     * MAF 空气流量
     */
    public static final int DYNAMIC_DATA_MAF_AIR_FLOW = 16;
    /**
     * 节气门位置
     */
    public static final int DYNAMIC_DATA_THROTTLE_POSITION = 17;
    /**
     * 指令的二次空气喷射状态
     */
    public static final int DYNAMIC_DATA_SECONDARY_AIR_INJECTION_STATUS_OF_INSTRUCTIONS = 18;
    /**
     * 氧传感器当前状态
     */
    public static final int DYNAMIC_DATA_CURRENT_STATE_OF_OXYGEN_SENSOR_1 = 19;
    /**
     * 氧传感器输出电压（缸组1 传感器1）
     */
    public static final int DYNAMIC_DATA_OUTPUT_VOLTAGE_OF_OXYGEN_SENSOR_CYLINDER_GROUP_1_SENSOR_1 = 200;
    /**
     * 短期燃油修正（缸组1 传感器1）
     */
    public static final int DYNAMIC_DATA_SHORT_TERM_FUEL_CORRECTION_CYLINDER_GROUP_1_SENSOR_1 = 201;
    /**
     * 氧传感器输出电压（缸组1 传感器2）
     */
    public static final int DYNAMIC_DATA_OUTPUT_VOLTAGE_OF_OXYGEN_SENSOR_CYLINDER_GROUP_1_SENSOR_2 = 210;
    /**
     * 短期燃油修正（缸组1 传感器2）
     */
    public static final int DYNAMIC_DATA_SHORT_TERM_FUEL_CORRECTION_CYLINDER_GROUP_1_SENSOR_2 = 211;
    /**
     * 氧传感器输出电压（缸组1 传感器3）
     */
    public static final int DYNAMIC_DATA_OUTPUT_VOLTAGE_OF_OXYGEN_SENSOR_CYLINDER_GROUP_1_SENSOR_3 = 220;
    /**
     * 短期燃油修正（缸组1 传感器3）
     */
    public static final int DYNAMIC_DATA_SHORT_TERM_FUEL_CORRECTION_CYLINDER_GROUP_1_SENSOR_3 = 221;
    /**
     * 氧传感器输出电压（缸组1 传感器4）
     */
    public static final int DYNAMIC_DATA_OUTPUT_VOLTAGE_OF_OXYGEN_SENSOR_CYLINDER_GROUP_1_SENSOR_4 = 230;
    /**
     * 短期燃油修正（缸组1 传感器4）
     */
    public static final int DYNAMIC_DATA_SHORT_TERM_FUEL_CORRECTION_CYLINDER_GROUP_1_SENSOR_4 = 231;

    /**
     * 氧传感器输出电压（缸组2 传感器1）
     */
    public static final int DYNAMIC_DATA_OUTPUT_VOLTAGE_OF_OXYGEN_SENSOR_CYLINDER_GROUP_2_SENSOR_1 = 240;
    /**
     * 短期燃油修正（缸组2 传感器1）
     */
    public static final int DYNAMIC_DATA_SHORT_TERM_FUEL_CORRECTION_CYLINDER_GROUP_2_SENSOR_1 = 241;
    /**
     * 氧传感器输出电压（缸组2 传感器2）
     */
    public static final int DYNAMIC_DATA_OUTPUT_VOLTAGE_OF_OXYGEN_SENSOR_CYLINDER_GROUP_2_SENSOR_2 = 250;
    /**
     * 短期燃油修正（缸组2 传感器2）
     */
    public static final int DYNAMIC_DATA_SHORT_TERM_FUEL_CORRECTION_CYLINDER_GROUP_2_SENSOR_2 = 251;
    /**
     * 氧传感器输出电压（缸组2 传感器3）
     */
    public static final int DYNAMIC_DATA_OUTPUT_VOLTAGE_OF_OXYGEN_SENSOR_CYLINDER_GROUP_2_SENSOR_3 = 260;
    /**
     * 短期燃油修正（缸组2 传感器3）
     */
    public static final int DYNAMIC_DATA_SHORT_TERM_FUEL_CORRECTION_CYLINDER_GROUP_2_SENSOR_3 = 261;
    /**
     * 氧传感器输出电压（缸组2 传感器4）
     */
    public static final int DYNAMIC_DATA_OUTPUT_VOLTAGE_OF_OXYGEN_SENSOR_CYLINDER_GROUP_2_SENSOR_4 = 270;
    /**
     * 短期燃油修正（缸组2 传感器4）
     */
    public static final int DYNAMIC_DATA_SHORT_TERM_FUEL_CORRECTION_CYLINDER_GROUP_2_SENSOR_4 = 271;
    /**
     * 当前所使用的OBD标准
     */
    public static final int DYNAMIC_DATA_CURRENTLY_USED_OBD_STANDARDS = 28;
    /**
     * 氧传感器当前状态
     */
    public static final int DYNAMIC_DATA_CURRENT_STATE_OF_OXYGEN_SENSOR = 29;
    /**
     * 辅助输入状态
     */
    public static final int DYNAMIC_DATA_AUXILIARY_INPUT_STATUS = 30;
    /**
     * 引擎启动后的运行时间
     */
    public static final int DYNAMIC_DATA_RUNNING_TIME_AFTER_ENGINE_START_UP = 31;
    /**
     * 故障指示灯（MIL）亮的情况下行驶的距离
     */
    public static final int DYNAMIC_DATA_DISTANCE_OF_DRIVING_WHEN_THE_FAULT_INDICATOR_MIL_IS_ON = 33;
    /**
     * 油轨压力（相对于歧管的真空度）
     */
    public static final int DYNAMIC_DATA_RAIL_PRESSURE_RELATIVE_TO_MANIFOLD_VACUUM = 34;
    /**
     * 高压油轨压力（直喷柴油或汽油压力）
     */
    public static final int DYNAMIC_DATA_HIGH_PRESSURE_RAIL_PRESSURE_DIRECT_INJECTION_DIESEL_OR_GASOLINE_PRESSURE = 35;
    /**
     * 氧传感器1线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_1_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO_1 = 360;
    /**
     * 氧传感器1线性或宽带式氧传感器电压
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_1_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_VOLTAGE = 361;

    /**
     * 氧传感器2线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_2_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO_1 = 370;
    /**
     * 氧传感器2线性或宽带式氧传感器电压
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_2_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_VOLTAGE = 371;

    /**
     * 氧传感器3线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_3_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO_1 = 380;
    /**
     * 氧传感器3线性或宽带式氧传感器电压
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_3_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_VOLTAGE = 381;

    /**
     * 氧传感器4线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_4_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO_1 = 390;
    /**
     * 氧传感器4线性或宽带式氧传感器电压
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_4_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_VOLTAGE = 391;

    /**
     * 氧传感器5线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_5_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO_1 = 400;
    /**
     * 氧传感器5线性或宽带式氧传感器电压
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_5_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_VOLTAGE = 401;

    /**
     * 氧传感器6线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_6_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO_1 = 410;
    /**
     * 氧传感器6线性或宽带式氧传感器电压
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_6_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_VOLTAGE = 411;

    /**
     * 氧传感器7线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_7_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO_1 = 420;
    /**
     * 氧传感器7线性或宽带式氧传感器电压
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_7_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_VOLTAGE = 421;

    /**
     * 氧传感器8线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_8_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO_1 = 430;
    /**
     * 氧传感器8线性或宽带式氧传感器电压
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_8_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_VOLTAGE = 431;

    /**
     * 设置废气再循环
     */
    public static final int DYNAMIC_DATA_SETTING_UP_EXHAUST_GAS_RECIRCULATION = 44;
    /**
     * 废气再循环误差
     */
    public static final int DYNAMIC_DATA_EXHAUST_GAS_RECYCLING_ERROR = 45;
    /**
     * 可控蒸发净化
     */
    public static final int DYNAMIC_DATA_CONTROLLED_EVAPORATION_PURIFICATION = 46;
    /**
     * 燃油液位输入
     */
    public static final int DYNAMIC_DATA_FUEL_LEVEL_INPUT = 47;
    /**
     * 故障码清除后的行驶里程
     */
    public static final int DYNAMIC_DATA_DRIVING_MILEAGE_AFTER_REMOVAL_OF_FAULT_CODE = 49;

    /**
     * 燃油蒸汽排放系统蒸汽绝对压力（Kpa）
     */
    public static final int DYNAMIC_DATA_ABSOLUTE_STEAM_PRESSURE_KPA_IN_FUEL_STEAM_EMISSION_SYSTEM = 50;
    /**
     * 大气压
     */
    public static final int DYNAMIC_DATA_ATMOSPHERIC_PRESSURE = 51;
    /**
     * 氧传感器1线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_1_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO = 520;
    /**
     * 氧传感器1线性或宽带式氧传感器电流
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_1_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_CURRENT = 521;
    /**
     * 氧传感器2线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_2_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO = 530;
    /**
     * 氧传感器2线性或宽带式氧传感器电流
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_2_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_CURRENT = 531;
    /**
     * 氧传感器3线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_3_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO = 540;
    /**
     * 氧传感器3线性或宽带式氧传感器电流
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_3_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_CURRENT = 541;
    /**
     * 氧传感器4线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_4_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO = 550;
    /**
     * 氧传感器4线性或宽带式氧传感器电流
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_4_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_CURRENT = 551;
    /**
     * 氧传感器5线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_5_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO = 560;
    /**
     * 氧传感器5线性或宽带式氧传感器电流
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_5_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_CURRENT = 561;
    /**
     * 氧传感器6线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_6_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO = 570;
    /**
     * 氧传感器6线性或宽带式氧传感器电流
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_6_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_CURRENT = 571;
    /**
     * 氧传感器7线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_7_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO = 580;
    /**
     * 氧传感器7线性或宽带式氧传感器电流
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_7_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_CURRENT = 581;
    /**
     * 氧传感器8线性或宽带式氧传感器，当量比
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_8_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_EQUIVALENT_RATIO = 590;
    /**
     * 氧传感器8线性或宽带式氧传感器电流
     */
    public static final int DYNAMIC_DATA_OXYGEN_SENSOR_8_LINEAR_OR_BROADBAND_OXYGEN_SENSOR_CURRENT = 591;

    /**
     * 缸组1的1号传感器催化剂温度
     */
    public static final int DYNAMIC_DATA_CATALYST_TEMPERATURE_OF_NO_1_SENSOR_FOR_CYLINDER_GROUP_1 = 60;
    /**
     * 缸组1的2号传感器催化剂温度
     */
    public static final int DYNAMIC_DATA_CATALYST_TEMPERATURE_OF_NO_1_SENSOR_FOR_CYLINDER_GROUP_2 = 61;
    /**
     * 缸组2的1号传感器催化剂温度
     */
    public static final int DYNAMIC_DATA_CATALYST_TEMPERATURE_OF_NO_2_SENSOR_FOR_CYLINDER_GROUP_1 = 62;
    /**
     * 缸组2的2号传感器催化剂温度
     */
    public static final int DYNAMIC_DATA_CATALYST_TEMPERATURE_OF_NO_2_SENSOR_FOR_CYLINDER_GROUP_2 = 63;

    /**
     * 控制模块电压
     */
    public static final int DYNAMIC_DATA_CONTROL_MODULE_VOLTAGE = 66;
    /**
     * 绝对负载
     */
    public static final int DYNAMIC_DATA_ABSOLUTE_LOAD = 67;
    /**
     * 可控当量比
     */
    public static final int DYNAMIC_DATA_CONTROLLABLE_EQUIVALENT_RATIO = 68;
    /**
     * 节气门相对位置
     */
    public static final int DYNAMIC_DATA_RELATIVE_POSITION_OF_THROTTLE = 69;
    /**
     * 环境空气温度
     */
    public static final int DYNAMIC_DATA_AMBIENT_AIR_TEMPERATURE = 70;

    /**
     * 节气门绝对位置B
     */
    public static final int DYNAMIC_DATA_ABSOLUTE_THROTTLE_POSITION_B = 71;
    /**
     * 节气门绝对位置C
     */
    public static final int DYNAMIC_DATA_ABSOLUTE_THROTTLE_POSITION_C = 72;
    /**
     * 油门踏板位置 B
     */
    public static final int DYNAMIC_DATA_ACCELERATOR_PEDAL_POSITION_B = 73;
    /**
     * 油门踏板位置 E
     */
    public static final int DYNAMIC_DATA_ACCELERATOR_PEDAL_POSITION_E = 74;
    /**
     * 油门踏板位置 F
     */
    public static final int DYNAMIC_DATA_ACCELERATOR_PEDAL_POSITION_F = 75;
    /**
     * 操作节气门制动器
     */
    public static final int DYNAMIC_DATA_OPERATING_THROTTLE_BRAKE = 76;

    /**
     * 故障指示灯亮起后的运行时间
     */
    public static final int DYNAMIC_DATA_RUNNING_TIME_AFTER_FAILURE_INDICATOR_LIGHTS_UP = 77;
    /**
     * 故障码清理后的运行时间
     */
    public static final int DYNAMIC_DATA_RUNNING_TIME_AFTER_TROUBLESHOOTING = 78;
    /**
     * 燃油类型
     */
    public static final int DYNAMIC_DATA_FUEL_TYPE = 81;
    /**
     * 乙醇燃料百分比
     */
    public static final int DYNAMIC_DATA_PERCENTAGE_OF_ETHANOL_FUEL = 82;
    /**
     * 蒸发冷却系统绝对蒸汽压
     */
    public static final int DYNAMIC_DATA_ABSOLUTE_VAPOR_PRESSURE_OF_EVAPORATIVE_COOLING_SYSTEM = 83;
    /**
     * 蒸汽冷却系统蒸汽压
     */
    public static final int DYNAMIC_DATA_STEAM_PRESSURE_OF_STEAM_COOLING_SYSTEM = 84;
    /**
     * 短周期缸组1二次氧传感器燃油调整
     */
    public static final int DYNAMIC_DATA_FUEL_ADJUSTMENT_OF_SECONDARY_OXYGEN_SENSOR_FOR_SHORT_CYLINDER_GROUP_1 = 850;
    /**
     * 短周期缸组3二次氧传感器燃油调整
     */
    public static final int DYNAMIC_DATA_FUEL_ADJUSTMENT_OF_SECONDARY_OXYGEN_SENSOR_FOR_SHORT_CYLINDER_GROUP_3 = 851;


    /**
     * 长周期缸组1二次氧传感器燃油调整
     */
    public static final int DYNAMIC_DATA_FUEL_ADJUSTMENT_OF_SECONDARY_OXYGEN_SENSOR_FOR_LONG_CYLINDER_GROUP_1 = 860;
    /**
     * 长周期缸组3二次氧传感器燃油调整
     */
    public static final int DYNAMIC_DATA_FUEL_ADJUSTMENT_OF_SECONDARY_OXYGEN_SENSOR_FOR_LONG_CYLINDER_GROUP_3 = 861;


    /**
     * 短周期缸组2二次氧传感器燃油调整
     */
    public static final int DYNAMIC_DATA_FUEL_ADJUSTMENT_OF_SECONDARY_OXYGEN_SENSOR_FOR_SHORT_CYLINDER_GROUP_2 = 870;
    /**
     * 短周期缸组4二次氧传感器燃油调整
     */
    public static final int DYNAMIC_DATA_FUEL_ADJUSTMENT_OF_SECONDARY_OXYGEN_SENSOR_FOR_SHORT_CYLINDER_GROUP_4 = 871;

    /**
     * 长周期缸组2二次氧传感器燃油调整
     */
    public static final int DYNAMIC_DATA_FUEL_ADJUSTMENT_OF_SECONDARY_OXYGEN_SENSOR_FOR_LONG_CYLINDER_GROUP_2 = 880;
    /**
     * 长周期缸组4二次氧传感器燃油调整
     */
    public static final int DYNAMIC_DATA_FUEL_ADJUSTMENT_OF_SECONDARY_OXYGEN_SENSOR_FOR_LONG_CYLINDER_GROUP_4 = 881;

    /**
     * 油轨压力（绝对压力）
     */
    public static final int DYNAMIC_DATA_OIL_RAIL_PRESSURE_ABSOLUTE_PRESSURE = 89;
    /**
     * 油门踏板相对位置
     */
    public static final int DYNAMIC_DATA_RELATIVE_POSITION_OF_THROTTLE_PEDAL = 90;
    /**
     * 混合动力电池组的剩余寿命
     */
    public static final int DYNAMIC_DATA_RESIDUAL_LIFE_OF_HYBRID_BATTERY_PACK = 91;
    /**
     * 引擎润滑油温度
     */
    public static final int DYNAMIC_DATA_ENGINE_LUBRICANT_TEMPERATURE = 92;
    /**
     * 喷油提前角
     */
    public static final int DYNAMIC_DATA_FUEL_INJECTION_ADVANCE_ANGLE = 93;
    /**
     * 发动机燃油消耗率
     */
    public static final int DYNAMIC_DATA_FUEL_CONSUMPTION_RATE_OF_ENGINE = 94;
    /**
     * 驾驶者需求的引擎转矩百分比
     */
    public static final int DYNAMIC_DATA_PERCENTAGE_OF_ENGINE_TORQUE_REQUIRED_BY_DRIVERS = 97;
    /**
     * 引擎的实际转矩百分比
     */
    public static final int DYNAMIC_DATA_ACTUAL_TORQUE_PERCENTAGE_OF_ENGINE = 98;
    /**
     * 引擎参考转矩
     */
    public static final int DYNAMIC_DATA_ENGINE_REFERENCE_TORQUE = 99;
    /**
     * 引擎转矩百分比数据信息
     */
    public static final int DYNAMIC_DATA_ENGINE_TORQUE_PERCENTAGE_DATA_INFORMATION = 100;

}
