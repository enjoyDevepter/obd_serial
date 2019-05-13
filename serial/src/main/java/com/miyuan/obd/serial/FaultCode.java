package com.miyuan.obd.serial;

/**
 * 故障码实体类
 */
public class FaultCode {

    /**
     * 故障码ID
     */
    private String id;
    /**
     * 故障所对应车型
     */
    private String suit;
    /**
     * 故障码中文描述
     */
    private String desc_ch;
    /**
     * 故障码英文描述
     */
    private String desc_en;
    /**
     * 故障所归属系统类型
     */
    private String system;
    /**
     * 故障详情介绍
     */
    private String detail;

    /**
     * 获取故障码ID
     *
     * @return 故障码ID
     */
    public String getId() {
        return id;
    }

    void setId(String id) {
        this.id = id;
    }

    /**
     * 获取故障所适用车型
     *
     * @return
     */
    public String getSuit() {
        return suit;
    }

    void setSuit(String suit) {
        this.suit = suit;
    }

    /**
     * 获取故障码中文描述
     *
     * @return 故障码中文描述
     */
    public String getDesc_ch() {
        return desc_ch;
    }

    void setDesc_ch(String desc_ch) {
        this.desc_ch = desc_ch;
    }

    /**
     * 获取故障码英文描述
     *
     * @return 障码英文描述
     */
    public String getDesc_en() {
        return desc_en;
    }

    void setDesc_en(String desc_en) {
        this.desc_en = desc_en;
    }

    /**
     * 获取故障详情介绍
     *
     * @return 故障详情介绍
     */
    public String getDetail() {
        return detail;
    }

    void setDetail(String detail) {
        this.detail = detail;
    }

    /**
     * 获取故障所归属系统类型
     *
     * @return 故障所归属系统类型
     */
    public String getSystem() {
        return system;
    }

    void setSystem(String system) {
        this.system = system;
    }

    FaultCode(String id, String suit, String desc_ch, String desc_en, String system, String detail) {
        this.id = id;
        this.suit = suit;
        this.desc_ch = desc_ch;
        this.desc_en = desc_en;
        this.system = system;
        this.detail = detail;
    }

    @Override
    public String toString() {
        return "'" + id + '\'';
    }
}


