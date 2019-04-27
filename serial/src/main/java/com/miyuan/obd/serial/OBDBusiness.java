package com.miyuan.obd.serial;

import java.util.List;

class OBDBusiness {

    static {
        System.loadLibrary("serial");
    }

    public OBDBusiness() {
    }

    native boolean open(String path, int baudrate);

    native void close();

    native String getVersion();

    native List<FaultCode> getFaultCode(String path);

    native boolean cleanFaultCode();

    native PanelBoardInfo getFixedData();

    native String getDynamicData(int dynamicDataType);

    native boolean setCarStatus(boolean status);

    native boolean initMileage(int mile);
}
