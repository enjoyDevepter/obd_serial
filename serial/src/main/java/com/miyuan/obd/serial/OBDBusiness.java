package com.miyuan.obd.serial;

import android.util.Log;

import java.io.FileDescriptor;
import java.util.List;

class OBDBusiness {

    private FileDescriptor mFd;

    static {
        System.loadLibrary("serial");
    }

    public OBDBusiness() {
        mFd = open("/dev/ttyMT1", 19200, 0);
        if (mFd == null) {
            Log.e("obd_core", "native open returns null");
            return;
        }
    }

    native void close();

    native String getVersion();

    native List<FaultCode> getFaultCode(String path);

    native boolean cleanFaultCode();

    native PanelBoardInfo getFixedData();

    native String getDynamicData(int dynamicDataType);

    native boolean setCarStatus(boolean status);

    native boolean initMileage(int mile);

    native FileDescriptor open(String path, int baudrate, int flags);

}
