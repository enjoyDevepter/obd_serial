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
     * 故障
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
        return "FaultCode{" +
                "id='" + id + '\'' +
                ", suit='" + suit + '\'' +
                ", desc_ch='" + desc_ch + '\'' +
                ", desc_en='" + desc_en + '\'' +
                ", system='" + system + '\'' +
                ", detail='" + detail + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        FaultCode code = (FaultCode) o;

        if (id != null ? !id.equals(code.id) : code.id != null) return false;
        if (suit != null ? !suit.equals(code.suit) : code.suit != null) return false;
        if (desc_ch != null ? !desc_ch.equals(code.desc_ch) : code.desc_ch != null) return false;
        if (desc_en != null ? !desc_en.equals(code.desc_en) : code.desc_en != null) return false;
        if (system != null ? !system.equals(code.system) : code.system != null) return false;
        return detail != null ? detail.equals(code.detail) : code.detail == null;
    }

    @Override
    public int hashCode() {
        int result = id != null ? id.hashCode() : 0;
        result = 31 * result + (suit != null ? suit.hashCode() : 0);
        result = 31 * result + (desc_ch != null ? desc_ch.hashCode() : 0);
        result = 31 * result + (desc_en != null ? desc_en.hashCode() : 0);
        result = 31 * result + (system != null ? system.hashCode() : 0);
        result = 31 * result + (detail != null ? detail.hashCode() : 0);
        return result;
    }
}


