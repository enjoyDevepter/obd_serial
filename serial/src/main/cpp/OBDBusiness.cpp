#include <jni.h>
#include <string>
#include <termios.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include "android/log.h"
static const char *TAG="obd_core";
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)
#define HEAD 0x7e
#define TIMEOUT 5
#ifndef _Included_com_miyuan_obd_serial_OBDBusiness
#define _Included_com_miyuan_obd_serial_OBDBusiness
#ifdef __cplusplus
extern "C" {
#endif

void LOGE_HEX(char* msg,char* data,int len)
{
	char buffer[1024];
	char temp[5];

	memset(buffer, 0, sizeof(buffer));

	sprintf(buffer, "%s[%d][", (char*) msg, len);

 	for (int i = 0; i < len; i++) {
        sprintf((char*) temp, "%02X ", data[i]);
        strcat((char*) buffer, temp);
    }
    strcat((char*) buffer, "]\r\n");
    LOGE("%s", buffer);
}

static speed_t getBaudrate(jint baudrate)
{
	switch(baudrate) {
	case 0: return B0;
	case 50: return B50;
	case 75: return B75;
	case 110: return B110;
	case 134: return B134;
	case 150: return B150;
	case 200: return B200;
	case 300: return B300;
	case 600: return B600;
	case 1200: return B1200;
	case 1800: return B1800;
	case 2400: return B2400;
	case 4800: return B4800;
	case 9600: return B9600;
	case 19200: return B19200;
	case 38400: return B38400;
	case 57600: return B57600;
	case 115200: return B115200;
	case 230400: return B230400;
	case 460800: return B460800;
	case 500000: return B500000;
	case 576000: return B576000;
	case 921600: return B921600;
	case 1000000: return B1000000;
	case 1152000: return B1152000;
	case 1500000: return B1500000;
	case 2000000: return B2000000;
	case 2500000: return B2500000;
	case 3000000: return B3000000;
	case 3500000: return B3500000;
	case 4000000: return B4000000;
	default: return -1;
	}
}
int fd;
/*
 * Class:     com_miyuan_obd_serial_OBDBusiness
 * Method:    open
 * Signature: (Ljava/lang/String;II)Ljava/io/FileDescriptor;
 */
JNIEXPORT jobject JNICALL Java_com_miyuan_obd_serial_OBDBusiness_open(JNIEnv *env, jclass thiz, jstring path, jint baudrate, jint flags)
{
	speed_t speed;
	jobject mFileDescriptor;

	/* Check arguments */
	{
		speed = getBaudrate(baudrate);
		if (speed == -1) {
			/* TODO: throw an exception */
			LOGE("Invalid baudrate");
			return NULL;
		}
	}

	/* Opening device */
	{
		jboolean iscopy;
		const char *path_utf = env->GetStringUTFChars(path, &iscopy);
		LOGE("Opening serial port %s with flags 0x%x", path_utf, O_RDWR | flags);
		fd = open(path_utf, O_RDWR | flags);
		LOGE("open() fd = %d", fd);
		env->ReleaseStringUTFChars(path, path_utf);
		if (fd == -1)
		{
			/* Throw an exception */
			LOGE("Cannot open port");
			/* TODO: throw an exception */
			return NULL;
		}
	}

	/* Configure device */
	{
		struct termios cfg;
		LOGE("Configuring serial port");
		if (tcgetattr(fd, &cfg))
		{
			LOGE("tcgetattr() failed");
			close(fd);
			/* TODO: throw an exception */
			return NULL;
		}

		cfmakeraw(&cfg);
		cfsetispeed(&cfg, speed);
		cfsetospeed(&cfg, speed);

		if (tcsetattr(fd, TCSANOW, &cfg))
		{
			LOGE("tcsetattr() failed");
			close(fd);
			/* TODO: throw an exception */
			return NULL;
		}
	}

	/* Create a corresponding file descriptor */
	{
		jclass cFileDescriptor = env->FindClass("java/io/FileDescriptor");
		jmethodID iFileDescriptor = env->GetMethodID(cFileDescriptor, "<init>", "()V");
		jfieldID descriptorID = env->GetFieldID(cFileDescriptor, "descriptor", "I");
		mFileDescriptor = env->NewObject(cFileDescriptor, iFileDescriptor);
		env->SetIntField(mFileDescriptor, descriptorID, (jint)fd);
	}
	return mFileDescriptor;
}

/*
 * 向串口写入数据
 */
int writeToBox(char* buffer, int len)
{
	if(fd == -1){
		LOGE("seriail open fail!");
		return -1;
	}
	LOGE_HEX("APP-OBD",buffer,len);
	int length = write(fd, buffer, len);
	sleep(1); //写完之后睡一秒
    if (length > 0) {
        LOGE("write device success");
        return length;
    } else {
        LOGE("write device error");
    }
    return -1;
}

int readFormBox(char* buffer,int timeOut)
{
	if(fd == -1){
		LOGE("seriail open fail!");
		return -1;
	}

	int ret;
    fd_set readfd;
    struct timeval timeout;
    while (fd != -1) {
        timeout.tv_sec = timeOut; //设定超时秒数
        timeout.tv_usec = 0; //设定超时毫秒数

        FD_ZERO(&readfd); //清空集合
        FD_SET(fd, &readfd); // 把要检测的句柄fd加入到集合里
        ret = select(fd + 1, &readfd, NULL, NULL, &timeout); // 检测我们上面设置到集合readfd里的句柄是否有可读信息
        LOGE("ret=%d", ret);
        switch (ret) {
        case -1: // 这说明select函数出错
            LOGE("fd read failure");
            return -1;
            break;
        case 0: // 说明在我们设定的时间值5秒加0毫秒的时间内，mTty的状态没有发生变化
            LOGE("fd read timeOut");
            return -2;
        default: //说明等待时间还未到0秒加500毫秒，mTty的状态发生了变化
            if (FD_ISSET(fd, &readfd)) { // 先判断一下mTty这外被监视的句柄是否真的变成可读的了
                char tempBuff[1024];
                bzero(tempBuff, 1024);
                int nread = read(fd, tempBuff, 1024);
                if (nread > 0) {
					LOGE_HEX("OBD-APP", tempBuff, nread);
                    return nread;
                }
            }
            break;
        }
    }
    return -1;
}

bool isValid(char* result,int len)
{
	if(result[0]==0x7e && result[len-1]== 0x7e && len>=7)
	{	
		int cr;
		for(int i=1;i<len-2;i++){
			cr = cr ^ result[i];
		}
		return cr==result[len-2];
	}
	return false;
}

/*
 * Class:     com_miyuan_obd_serial_OBDBusiness
 * Method:    close
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_miyuan_obd_serial_OBDBusiness_close(JNIEnv * env, jobject jobj)
{
    jclass SerialPortClass = env->GetObjectClass(jobj);
    jclass FileDescriptorClass = env->FindClass("java/io/FileDescriptor");

    jfieldID mFdID = env->GetFieldID(SerialPortClass, "mFd", "Ljava/io/FileDescriptor;");
    jfieldID descriptorID = env->GetFieldID(FileDescriptorClass, "descriptor", "I");

    jobject mFd = env->GetObjectField(jobj, mFdID);
    jint descriptor = env->GetIntField(mFd, descriptorID);

    LOGE("close(fd = %d)", descriptor);
    close(descriptor);
}

/*
 * Class:     com_miyuan_obd_serial_OBDBusiness
 * Method:    getVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_miyuan_obd_serial_OBDBusiness_getVersion(JNIEnv * env, jobject jobj)
{
    std::string version = "V1.0";
    return env->NewStringUTF(version.c_str());
}

/*
 * Class:     com_miyuan_obd_serial_OBDBusiness
 * Method:    getFaultCode
 * Signature: ()Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_com_miyuan_obd_serial_OBDBusiness_getFaultCode(JNIEnv *env, jobject jobj)
{
    char input[6] = {HEAD,0x81,0x02,0x00,0x00,HEAD};
    input[4] = input[1]^input[2]^input[3];

    writeToBox(input,sizeof(input));

    char result[1024];

    int len = readFormBox(result,TIMEOUT);

    // sqlite3 *db;
    // char *zErrMsg = 0;
    // char *sql;
    // const char* data = "Callback function called";
    // int rc;
    // /* Open database */
    // rc = sqlite3_open("/mnt/sdcard/physical.db", &db);

    // if(rc){
    //   LOGE("Can't open database: %s",sqlite3_errmsg(db));
    //   return NULL;
    // } else {
    //   LOGE("Opened database successfully!");
    // }
    // /* Create SQL statement */
    // sql = "SELECT * from code where id = 'B0001'";

    // /* Execute SQL statement */
    // rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    // if( rc != SQLITE_OK ){
    //   LOGE("SQL error: %s",zErrMsg);
    //   sqlite3_free(zErrMsg);
    // }else{
    //   LOGE("Operation done successfully");
    // }
    // sqlite3_close(db);

    return NULL;
}

/*
 * Class:     com_miyuan_obd_serial_OBDBusiness
 * Method:    cleanFaultCode
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_miyuan_obd_serial_OBDBusiness_cleanFaultCode(JNIEnv *env, jobject jobj)
{
    char input[6] = {HEAD,0x81,0x02,0x00,0x00,HEAD};
    input[4] = input[1]^input[2]^input[3];

    writeToBox(input,sizeof(input));

    char result[1024];

    int len = readFormBox(result,TIMEOUT);

    return len>7 && result[5]==0;
}

/*
 * Class:     com_miyuan_obd_serial_OBDBusiness
 * Method:    getFixedData
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_miyuan_obd_serial_OBDBusiness_getFixedData(JNIEnv *env, jobject jobj, jint fixedType)
{
    char input[6] = {HEAD,0x83,0x01,0x01,0x00,HEAD};
    input[3] = fixedType;
    input[4] = input[1]^input[2]^input[3];

    writeToBox(input,sizeof(input));

    char buf[1024];

    int len = readFormBox(buf,TIMEOUT);

	char result[100];

	if(len==12 && buf[1]==0x03 && buf[2]==0x01 && buf[7]==0){ 
		short id = (buf[6]<<8) + buf[5];
		switch (fixedType)
		{
			case 0x02: // 瞬时油耗
			case 0x03: // 瞬时油耗
				float temp;
				temp =  ((buf[9]<<8) + buf[8])*0.1;
				sprintf(result,"%0.2f",temp);
				break;
			default:
				unsigned short tempS;
				tempS =  (buf[9]<<8) + buf[8];
				sprintf(result,"%hd",tempS);
				break;
		}
	}
	return env->NewStringUTF(result);;
}

/*
 * Class:     com_miyuan_obd_serial_OBDBusiness
 * Method:    getDynamicData
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_miyuan_obd_serial_OBDBusiness_getDynamicData(JNIEnv *env, jobject jobj, jint dynamicType)
{
    char input[6] = {HEAD,0x83,0x02,0x01,0x00,HEAD};
    input[3] = dynamicType;
    input[4] = input[1]^input[2]^input[3];

    writeToBox(input,sizeof(input));

    char buf[1024];

    int len = readFormBox(buf,TIMEOUT);

	char result[100];

	unsigned short tempS;
	float tempF;
	if(isValid(buf,len)){
		if(buf[1]==0x03 && buf[2]==0x02 && buf[7]==0){ 
			short id = (buf[6]<<8) + buf[5];
			switch (id)
			{
				case 0x01: // 电脑(ECU)中存储的故障码数量
					tempS = buf[8] & 0x7f;
					sprintf(result,"%hd",tempS);
					break;
				case 0x02: // 冻结故障码
					tempS = (buf[9]<<8) + buf[8];
					sprintf(result,"%hd",tempS);
					break;
				case 0x03:
					break;
				case 0x04:
					tempF = buf[8]*100/255;
					sprintf(result,"%0.2f",tempF);
					break;
				case 0x05:
					tempS = buf[8]-40;
					sprintf(result,"%hd",tempS);
					break;
				case 0x06:
				case 0x07:
				case 0x08:
				case 0x09:
					tempF = buf[8]*100/128-100;
					sprintf(result,"%0.2f",tempF);
					break;
				case 0x0A:
					tempS = buf[8]*3;
					sprintf(result,"%hd",tempS);
					break;
				case 0x0B:
					tempS = buf[8];
					sprintf(result,"%hd",tempS);
					break;
				case 0x0C:
					tempF = ((buf[9]<<8) + buf[8])/4;
					sprintf(result,"%0.2f",tempF);
					break;
				case 0x0D:
					tempS = buf[8];
					sprintf(result,"%hd",tempS);
					break;
				case 0x0E:
					tempF = buf[8]/2 - 64;
					sprintf(result,"%0.2f",tempF);
					break;
				case 0x0F:
					tempS = buf[8] - 40;
					sprintf(result,"%hd",tempS);
					break;
				case 0x10:
					tempF = ((buf[9]<<8) + buf[8])/100;
					sprintf(result,"%0.2f",tempF);
					break;
				case 0x11:
					tempF = buf[8]*100/255;
					sprintf(result,"%0.2f",tempF);
					break;
				case 0x12:
					break;
				case 0x13:
					tempS = buf[8];
					sprintf(result,"%hd",tempS);
					break;
				case 0x14:
					break;	
				case 0x15:
					break;
				case 0x16:
					break;
				case 0x17:
					break;	
				case 0x18:
					break;	
				case 0x19:
					break;
				case 0x1A:
					break;
				case 0x1B:
					break;
				case 0x1C:
					break;	
				case 0x1D:
					break;
				case 0x1E:
					break;
				case 0x1F:
					tempS = (buf[9]<<8) + buf[8];
					sprintf(result,"%hd",tempS);
					break;
				case 0x21:
					tempS = (buf[9]<<8) + buf[8];
					sprintf(result,"%hd",tempS);
					break;	
				case 0x22:
					tempF = ((buf[9]<<8) + buf[8])*0.079;
					sprintf(result,"%0.2f",tempF);
					break;
				case 0x23:
					tempS = ((buf[9]<<8) + buf[8])*10;
					sprintf(result,"%hd",tempS);
					break;
				case 0x24:
					tempF = ((buf[9]<<8) + buf[8])*2/65536;
					sprintf(result,"%0.2f",tempF);
					break;
				case 0x25:
					break;	
				case 0x26:
					break;
				case 0x27:
					break;
				case 0x28:
					break;
				case 0x29:
					break;	
				case 0x2A:
					break;
				case 0x2B:
					break;
				case 0x2C:
					tempF = buf[8]*100/255;
					sprintf(result,"%0.2f",tempF);
					break;
				case 0x2D:
					tempF = buf[8]*100/128-100;
					sprintf(result,"%0.2f",tempF);
					break;	
				case 0x2E:
				case 0x2F:
					tempF = buf[8]*100/255;
					sprintf(result,"%0.2f",tempF);
					break;
				case 0x31:
					break;
				case 0x32:
					break;	
				case 0x33:
					break;
				case 0x34:
					break;
				case 0x35:
					break;	
				case 0x36:
					break;	
				case 0x37:
					break;
				case 0x38:
					break;
				case 0x39:
					break;
				case 0x3A:
					break;
				case 0x3B:
					break;	
				case 0x3C:
					break;	
				case 0x3D:
					break;
				case 0x3E:
					break;
				case 0x3F:
					break;
				case 0x42:
					break;
				case 0x43:
					break;
				case 0x44:
					break;
				case 0x45:
					break;	
				case 0x46:
					break;	
				case 0x47:
					break;
				case 0x48:
					break;
				case 0x49:
					break;
				case 0x4A:
					break;	
				case 0x4B:
					break;	
				case 0x4C:
					break;
				case 0x4D:
					break;
				case 0x4E:
					break;
				case 0x51:
					break;	
				case 0x52:
					break;
				case 0x53:
					break;
				case 0x54:
					break;
				case 0x55:
					break;	
				case 0x56:
					break;	
				case 0x57:
					break;
				case 0x58:
					break;
				case 0x59:
					tempS = ((buf[9]<<8) + buf[8])*10;
					sprintf(result,"%hd",tempS);
					break;
				case 0x5A:	
				case 0x5B:
					tempF = buf[8]*100/255;
					sprintf(result,"%0.2F",tempF);
					break;	
				case 0x5C:
					tempS = buf[8]-40;
					sprintf(result,"%hd",tempS);
					break;
				case 0x5D:
					tempF = ((buf[9]<<8) + buf[8])/128-210;
					sprintf(result,"%0.2F",tempF);
					break;
				case 0x5E:
					tempF = ((buf[9]<<8) + buf[8])/20;
					sprintf(result,"%0.2F",tempF);
					break;	
				case 0x61:
				case 0x62:
					tempS = buf[8]-125;
					sprintf(result,"%hd",tempS);
					break;
				case 0x63:
					tempS = ((buf[9]<<8) + buf[8])*10;
					sprintf(result,"%hd",tempS);
					break;
				case 0x64:
					break;			
			}
		}
	}
    return env->NewStringUTF(result);
}



/*
 * Class:     com_miyuan_obd_serial_OBDBusiness
 * Method:    setCarStatus
 * Signature: (Z)V
 */
JNIEXPORT jboolean JNICALL Java_com_miyuan_obd_serial_OBDBusiness_setCarStatus(JNIEnv *env, jobject jobj, jboolean status)
{
	char input[6] = {HEAD,0x89,0x01,0x01,0x00,HEAD};
    if(!status){
		input[3] = 0x00;
	}
	input[4] = input[1]^input[2]^input[3];

	writeToBox(input,sizeof(input));

	char result[1024]; 

	int len = readFormBox(result,TIMEOUT);
	
	return len>7;
}
#ifdef __cplusplus
}
#endif
#endif
