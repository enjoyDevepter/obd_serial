package com.miyuan.obd.serial;

import android.util.Log;

import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.List;

class OBDBusiness {

    /*
     * Do not remove or rename the field mFd: it is used by native method close();
     */
    private FileDescriptor mFd;
    private FileInputStream mFileInputStream;
    private FileOutputStream mFileOutputStream;


    static {
        System.loadLibrary("serial");
    }

    public OBDBusiness() {
        mFd = open("/dev/ttyS0", 115200, 0);
//        mFd = open("/dev/ttyMT2", 19200, 0);
        if (mFd == null) {
            Log.e("obd_core", "native open returns null");
            return;
        }
        mFileInputStream = new FileInputStream(mFd);
        mFileOutputStream = new FileOutputStream(mFd);
    }

    native void close();

    native String getVersion();

    native List<FaultCode> getFaultCode();

    native boolean cleanFaultCode();

    native int getFixedData(int fixedDataType);

    native String getDynamicData(int dynamicDataType);

    native boolean setCarStatus(boolean status);

    native FileDescriptor open(String path, int baudrate, int flags);

    public InputStream getInputStream() {
        return mFileInputStream;
    }

    public OutputStream getOutputStream() {
        return mFileOutputStream;
    }
}
