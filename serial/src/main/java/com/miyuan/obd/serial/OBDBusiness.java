package com.miyuan.obd.serial;

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

    native static FileDescriptor open(String path, int baudrate, int flags);

    native void close();

    native String getVersion();

    native List<FaultCode> getFaultCode();

    native boolean cleanFaultCode();

    native int getFixedData(int fixedDataType);

    native String getDynamicData(int dynamicDataType);

    native boolean setCarStatus(boolean status);

    public OBDBusiness() {
//        mFd = open("/", 112500, 0);
//        if (mFd == null) {
//            Log.e("", "native open returns null");
//        }
//        mFileInputStream = new FileInputStream(mFd);
//        mFileOutputStream = new FileOutputStream(mFd);
    }

    // Getters and setters
    public InputStream getInputStream() {
        return mFileInputStream;
    }

    public OutputStream getOutputStream() {
        return mFileOutputStream;
    }
}
