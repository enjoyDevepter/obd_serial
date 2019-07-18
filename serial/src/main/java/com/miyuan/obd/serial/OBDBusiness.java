package com.miyuan.obd.serial;

class OBDBusiness {

    static {
        System.loadLibrary("t6_serial");
    }

    public OBDBusiness() {
    }

    native boolean open(String path);

    native void close();

    native String getVersion();

    native PanelBoardInfo getFixedData();

    native boolean setCarStatus(boolean status);

    native boolean initMileage(int mile);

    native boolean isLaunched();

    native boolean isConnect();
}
