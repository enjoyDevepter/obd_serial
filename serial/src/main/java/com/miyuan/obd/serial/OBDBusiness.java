package com.miyuan.obd.serial;

import java.util.List;

class OBDBusiness {

    static {
        System.loadLibrary("t6_serial");
    }

    public OBDBusiness() {
    }

    native void initDBPath(String dbPath);

    native boolean open(String path);

    native void close();

    native String getVersion();

    native List<FaultCode> getFaultCode();

    native boolean cleanFaultCode();

    native PanelBoardInfo getFixedData();

    native boolean setCarStatus(boolean status);

    native boolean setAutoStart(boolean start);

    native boolean initMileage(int mile);

    native boolean isLaunched();

    native boolean isConnect();
}
