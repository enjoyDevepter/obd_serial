#pragma

#include <jni.h>
#include <string>
#include <termios.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include "android/log.h"
// #include <sqlite3.h>
#include <openssl/crypto.h>
#include <openssl/des.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/ossl_typ.h>
#include <openssl/buffer.h>

static const char *TAG = "obd_core";
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)
#define HEAD 0x7e
#define TIMEOUT 3
#ifndef _Included_com_miyuan_obd_serial_OBDBusiness
#define _Included_com_miyuan_obd_serial_OBDBusiness
#ifdef __cplusplus
extern "C"
{
#endif

	std::string KEY = "MIYUAN_0BD";

	typedef struct
	{ // 故障码信息
		std::string id;
		std::string suit;
		std::string desc_ch;
		std::string desc_en;
		std::string system;
		std::string detail;
	} FaultCode;

	void formatStr(char *buf, char *data, int len)
	{
		if (buf == NULL || data == NULL)
		{
			return;
		}
		char temp[5] = {0};
		strcat(buf, "[");
		for (int i = 0; i < len; i++)
		{
			if (i != len - 1)
			{
				sprintf(temp, "%02X ", data[i]);
			}
			else
			{
				sprintf(temp, "%02X", data[i]);
			}
			strcat(buf, temp);
		}
		strcat(buf, "]\r\n");
	}

	void LOGE_HEX(char *msg, char *data, int len)
	{
		char *buffer = (char *)malloc((sizeof(char)) * 1024);
		char *temp = (char *)malloc((sizeof(char)) * 5);

		memset(buffer, 0, sizeof(buffer));

		sprintf(buffer, "%s[%d]", (char *)msg, len);

		if (len > 512)
		{ // 超出512个字符不打印
			return;
		}
		formatStr(buffer, data, len);
		LOGE("%s", buffer);
		free(buffer);
		free(temp);
		temp = NULL;
		buffer = NULL;
	}

	static speed_t getBaudrate(jint baudrate)
	{
		switch (baudrate)
		{
		case 0:
			return B0;
		case 50:
			return B50;
		case 75:
			return B75;
		case 110:
			return B110;
		case 134:
			return B134;
		case 150:
			return B150;
		case 200:
			return B200;
		case 300:
			return B300;
		case 600:
			return B600;
		case 1200:
			return B1200;
		case 1800:
			return B1800;
		case 2400:
			return B2400;
		case 4800:
			return B4800;
		case 9600:
			return B9600;
		case 19200:
			return B19200;
		case 38400:
			return B38400;
		case 57600:
			return B57600;
		case 115200:
			return B115200;
		case 230400:
			return B230400;
		case 460800:
			return B460800;
		case 500000:
			return B500000;
		case 576000:
			return B576000;
		case 921600:
			return B921600;
		case 1000000:
			return B1000000;
		case 1152000:
			return B1152000;
		case 1500000:
			return B1500000;
		case 2000000:
			return B2000000;
		case 2500000:
			return B2500000;
		case 3000000:
			return B3000000;
		case 3500000:
			return B3500000;
		case 4000000:
			return B4000000;
		default:
			return -1;
		}
	}
	int fd;
	/*
* Class:     com_miyuan_obd_serial_OBDBusiness
* Method:    open
* Signature: (Ljava/lang/String;II)Ljava/io/FileDescriptor;
*/
	JNIEXPORT jobject
		JNICALL
		Java_com_miyuan_obd_serial_OBDBusiness_open(JNIEnv *env, jclass thiz, jstring path, jint baudrate,
													jint flags)
	{
		speed_t speed;
		jobject mFileDescriptor;

		/* Check arguments */
		{
			speed = getBaudrate(baudrate);
			if (speed == -1)
			{
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
	int writeToBox(char *buffer, int len)
	{
		if (fd == -1)
		{
			LOGE("seriail open fail!");
			return -1;
		}
		LOGE_HEX("APP-OBD", buffer, len);
		int length = write(fd, buffer, len);
		sleep(1); //写完之后睡一秒
		if (length > 0)
		{
			LOGE("write device success");
			return length;
		}
		else
		{
			LOGE("write device error");
		}
		return -1;
	}

	int readFormBox(char *buffer, int timeOut)
	{
		if (fd == -1)
		{
			LOGE("seriail open fail!");
			return -1;
		}

		int ret;
		fd_set readfd;
		struct timeval timeout;
		while (fd != -1)
		{
			timeout.tv_sec = timeOut; //设定超时秒数
			timeout.tv_usec = 0;	  //设定超时毫秒数

			FD_ZERO(&readfd);									 //清空集合
			FD_SET(fd, &readfd);								 // 把要检测的句柄fd加入到集合里
			ret = select(fd + 1, &readfd, NULL, NULL, &timeout); // 检测我们上面设置到集合readfd里的句柄是否有可读信息
			LOGE("ret=%d", ret);
			switch (ret)
			{
			case -1: // 这说明select函数出错
				LOGE("fd read failure");
				return -1;
			case 0: // 说明在我们设定的时间值5秒加0毫秒的时间内，mTty的状态没有发生变化
				LOGE("fd read timeOut");
				return -1;
			default: //说明等待时间还未到0秒加500毫秒，mTty的状态发生了变化
				if (FD_ISSET(fd, &readfd))
				{ // 先判断一下mTty这外被监视的句柄是否真的变成可读的了
					char tempBuff[300];
					bzero(tempBuff, sizeof(tempBuff));
					int nread = read(fd, tempBuff, sizeof(tempBuff));
					if (nread > 0)
					{
						LOGE_HEX("OBD-APP", tempBuff, nread);
						memset(buffer, 0, sizeof(char) * 100);
						bool start = false;
						int k = 1;
						LOGE("nread[%d]", nread);
						for (int i = 0; i < nread; i++)
						{
							if (start)
							{
								buffer[k] = tempBuff[i];
								k++;
								if (tempBuff[i] == 0x7e)
								{
									LOGE_HEX("deal OBD-APP ", buffer, k);
									return k;
								}
							}
							if (!start && tempBuff[i] == 0x7e)
							{
								start = true;
								buffer[0] = 0x7e;
							}
						}
						return -1;
					}
				}
				break;
			}
		}
		return -1;
	}

	bool isValid(char *result, int len)
	{
		if (result[0] == 0x7e && result[len - 1] == 0x7e && len >= 7)
		{
			int cr = result[1];
			for (int i = 2; i < len - 2; i++)
			{
				cr = cr ^ result[i];
			}
			return cr == result[len - 2];
		}
		return false;
	}

	/*
* Class:     com_miyuan_obd_serial_OBDBusiness
* Method:    close
* Signature: ()V
*/
	JNIEXPORT void JNICALL
	Java_com_miyuan_obd_serial_OBDBusiness_close(JNIEnv *env, jobject jobj)
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

	char *base64_encode(const char *input, int length)
	{
		BIO *bmem = NULL;
		BIO *b64 = NULL;
		BUF_MEM *bptr = NULL;

		b64 = BIO_new(BIO_f_base64());
		BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
		bmem = BIO_new(BIO_s_mem());
		b64 = BIO_push(b64, bmem);
		BIO_write(b64, input, length);
		BIO_flush(b64);
		BIO_get_mem_ptr(b64, &bptr);

		char *buff = (char *)malloc(bptr->length + 1);
		memcpy(buff, bptr->data, bptr->length);
		buff[bptr->length] = 0;

		BIO_free_all(b64);

		return buff;
	}

	char *base64_decode(char *input, int length)
	{
		BIO *b64 = NULL;
		BIO *bmem = NULL;
		char *buffer = (char *)malloc(length);
		memset(buffer, 0, length);

		b64 = BIO_new(BIO_f_base64());
		BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
		bmem = BIO_new_mem_buf(input, length);
		bmem = BIO_push(b64, bmem);
		BIO_read(bmem, buffer, length);

		BIO_free_all(bmem);

		return buffer;
	}

	// 加密 ecb模式
	std::string des_encrypt(const std::string &clearText)
	{
		std::string cipherText; // 密文

		DES_cblock keyEncrypt;
		memset(keyEncrypt, 0, 8);

		// 构造补齐后的密钥
		if (KEY.length() <= 8)
			memcpy(keyEncrypt, KEY.c_str(), KEY.length());
		else
			memcpy(keyEncrypt, KEY.c_str(), 8);

		// 密钥置换
		DES_key_schedule keySchedule;
		DES_set_key_unchecked(&keyEncrypt, &keySchedule);

		// 循环加密，每8字节一次
		const_DES_cblock inputText;
		DES_cblock outputText;
		std::vector<unsigned char> vecCiphertext;
		unsigned char tmp[8];

		for (int i = 0; i < clearText.length() / 8; i++)
		{
			memcpy(inputText, clearText.c_str() + i * 8, 8);
			DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
			memcpy(tmp, outputText, 8);

			for (int j = 0; j < 8; j++)
				vecCiphertext.push_back(tmp[j]);
		}

		if (clearText.length() % 8 != 0)
		{
			int tmp1 = clearText.length() / 8 * 8;
			int tmp2 = clearText.length() - tmp1;
			memset(inputText, 0, 8);
			memcpy(inputText, clearText.c_str() + tmp1, tmp2);
			// 加密函数
			DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
			memcpy(tmp, outputText, 8);

			for (int j = 0; j < 8; j++)
				vecCiphertext.push_back(tmp[j]);
		}

		cipherText.clear();
		cipherText.assign(vecCiphertext.begin(), vecCiphertext.end());

		return cipherText;
	}

	// 解密 ecb模式
	std::string des_decrypt(const std::string &cipherText)
	{
		std::string clearText; // 明文

		DES_cblock keyEncrypt;
		memset(keyEncrypt, 0, 8);

		if (KEY.length() <= 8)
			memcpy(keyEncrypt, KEY.c_str(), KEY.length());
		else
			memcpy(keyEncrypt, KEY.c_str(), 8);

		DES_key_schedule keySchedule;
		DES_set_key_unchecked(&keyEncrypt, &keySchedule);

		const_DES_cblock inputText;
		DES_cblock outputText;
		std::vector<unsigned char> vecCleartext;
		unsigned char tmp[8];

		for (int i = 0; i < cipherText.length() / 8; i++)
		{
			memcpy(inputText, cipherText.c_str() + i * 8, 8);
			DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
			memcpy(tmp, outputText, 8);

			for (int j = 0; j < 8; j++)
				vecCleartext.push_back(tmp[j]);
		}

		if (cipherText.length() % 8 != 0)
		{
			int tmp1 = cipherText.length() / 8 * 8;
			int tmp2 = cipherText.length() - tmp1;
			memset(inputText, 0, 8);
			memcpy(inputText, cipherText.c_str() + tmp1, tmp2);
			// 解密函数
			DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
			memcpy(tmp, outputText, 8);

			for (int j = 0; j < 8; j++)
				vecCleartext.push_back(tmp[j]);
		}

		clearText.clear();
		clearText.assign(vecCleartext.begin(), vecCleartext.end());

		return clearText;
	}

	/*
* Class:     com_miyuan_obd_serial_OBDBusiness
* Method:    getVersion
* Signature: ()Ljava/lang/String;
*/
	JNIEXPORT jstring
		JNICALL
		Java_com_miyuan_obd_serial_OBDBusiness_getVersion(JNIEnv *env, jobject
																		   jobj)
	{
		std::string version = "V1.0";
		return env->NewStringUTF((des_decrypt(des_encrypt(version))).

								 c_str()

		);
	}

	// char *sql = NULL;
	// char *sql_temp;
	// int index = 1;

	// static int callback(void *NotUsed, int argc, char **argv, char **azColName)
	// {

	// 	int i;
	// 	if (sql_temp != NULL)
	// 	{
	// 		free(sql_temp);
	// 		sql_temp = NULL;
	// 	}

	// 	// sql_temp = (char *)malloc((sizeof(char)) * 1024 * 10);

	// 	char sql_temp[1024 * 5] = {0};

	// 	strcat(sql_temp, "UPDATE code set ");
	// 	for (i = 0; i < argc; i++)
	// 	{
	// 		char temp[1024 * 5] = {0};
	// 		// char *outstr1[1024] = {0};
	// 		// char *outstr2[1024] = {0};

	// 		char *encode;
	// 		// std::string deStr;
	// 		// if (argv[i] == NULL)
	// 		// {
	// 		// 	deStr = des_encrypt("NULL");
	// 		// }
	// 		// else
	// 		// {
	// 		// 	deStr = des_encrypt(argv[i]);
	// 		// }
	// 		encode = base64_encode(argv[i], strlen(argv[i]));

	// 		// LOGE("%s = '%s' %d \n", azColName[i], argv[i], strlen(argv[i]));
	// 		// LOGE("encode %s = '%s' %d \n", azColName[i], encode, strlen(encode));
	// 		std::string decrypt;
	// 		char *decrypt_char;
	// 		// decrypt_char = base64_decode((char*)encode.c_str(), encode.length());
	// 		// decrypt_char = base64_decode(encode, strlen(encode));
	// 		// decrypt = decrypt_char;
	// 		// decrypt = des_decrypt(decrypt);

	// 		// LOGE("decode %s = '%s' %d \n", azColName[i], decrypt_char, strlen(decrypt_char));

	// 		if (i == argc - 1)
	// 		{
	// 			sprintf(temp, " %s='%s' ", azColName[i], encode);
	// 		}
	// 		else
	// 		{
	// 			sprintf(temp, " %s='%s',", azColName[i], encode);
	// 		}
	// 		strcat(sql_temp, temp);
	// 	}

	// 	strcat(sql_temp, " where indez=");
	// 	char temp[30] = {0};
	// 	sprintf(temp, "'%d'", index);
	// 	strcat(sql_temp, temp);
	// 	LOGE("update sql %s;", sql_temp);
	// 	strncpy(sql, sql_temp, strlen(sql_temp));
	// 	return 0;
	// }

	// void updateCode()
	// {

	// 	if (sql == NULL)
	// 	{
	// 		return;
	// 	}

	// 	sqlite3 *db;
	// 	char *zErrMsg = 0;
	// 	const char *data = "Callback function called";
	// 	int rc;
	// 	/* Open database */
	// 	rc = sqlite3_open_v2("/storage/emulated/0/physical.db", &db, SQLITE_OPEN_READWRITE, NULL);
	// 	if (rc != SQLITE_OK)
	// 	{
	// 		// LOGE("Can't open database: %s", sqlite3_errmsg(db));
	// 		return;
	// 	}
	// 	else
	// 	{
	// 		// LOGE("Opened database successfully!");
	// 	}

	// 	rc = sqlite3_exec(db, sql, NULL, (void *)data, &zErrMsg);
	// 	if (rc != SQLITE_OK)
	// 	{
	// 		//			LOGE("update SQL error: %s", zErrMsg);
	// 		sqlite3_free(zErrMsg);
	// 		return;
	// 	}
	// 	else
	// 	{
	// 		//			LOGE("Operation done successfully");
	// 	}
	// 	sqlite3_close(db);
	// 	free(sql);
	// 	sql = NULL;
	// }

	char *jstring2str(JNIEnv *env, jstring
									   jstr)
	{
		if (jstr == NULL || env->GetStringLength(jstr) == 0)
		{
			return "";
		}
		char *rtn = NULL;
		jclass clsstring = env->FindClass("java/lang/String");
		jstring strencode = env->NewStringUTF("UTF-8");
		jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
		jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
		jsize alen = env->GetArrayLength(barr);
		jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
		if (alen > 0)
		{
			rtn = (char *)malloc(alen + 1);
			memcpy(rtn, ba, alen);
			rtn[alen] = 0;
		}

		env->ReleaseByteArrayElements(barr, ba,
									  0);
		return rtn;
	}

	// std::vector<std::string> ids;

	// static int callback1(void *NotUsed, int argc, char **argv, char **azColName)
	// {
	// 	int i;
	// 	for (i = 0; i < argc; i++)
	// 	{
	// 		ids.push_back(argv[i]);
	// 	}
	// 	return 0;
	// }

	// void getAllId()
	// {
	// 	sqlite3 *db;
	// 	char *zErrMsg = 0;
	// 	char *sql;
	// 	const char *data = "Callback function called";
	// 	int rc;
	// 	/* Open database */
	// 	rc = sqlite3_open_v2("/storage/emulated/0/physical.db", &db, SQLITE_OPEN_READWRITE, NULL);
	// 	if (rc != SQLITE_OK)
	// 	{
	// 		LOGE("Can't open database: %s", sqlite3_errmsg(db));
	// 		return;
	// 	}
	// 	else
	// 	{
	// 		LOGE("Opened database successfully!");
	// 	}
	// 	/* Create SQL statement */
	// 	sql = "SELECT id from code";

	// 	/* Execute SQL statement */
	// 	rc = sqlite3_exec(db, sql, callback1, (void *)data, &zErrMsg);
	// 	if (rc != SQLITE_OK)
	// 	{
	// 		LOGE("SQL error: %s", zErrMsg);
	// 		sqlite3_free(zErrMsg);
	// 	}
	// 	else
	// 	{
	// 		sqlite3_close(db);
	// 		LOGE("ids size %d", ids.size());
	// 		LOGE("Operation done successfully");
	// 	}
	// }

	// void selcet(int index)
	// {
	// 	if (sql != NULL)
	// 	{
	// 		free(sql);
	// 		sql = NULL;
	// 	}
	// 	sql = (char *)malloc((sizeof(char)) * 1024 * 10);
	// 	char sql[1024] = {0};
	// 	sqlite3 *db;
	// 	char *zErrMsg = 0;
	// 	// char *sql;
	// 	const char *data = "Callback function called";
	// 	int rc;
	// 	/* Open database */
	// 	rc = sqlite3_open_v2("/storage/emulated/0/physical.db", &db, SQLITE_OPEN_READONLY, NULL);
	// 	if (rc != SQLITE_OK)
	// 	{
	// 		// LOGE("Can't open database: %s", sqlite3_errmsg(db));
	// 		return;
	// 	}
	// 	else
	// 	{
	// 		// LOGE("Opened database successfully!");
	// 	}

	// 	strcat(sql, "SELECT detail from code where indez=");
	// 	char temp[10] = {0};

	// 	sprintf(temp, "'%d'", index);
	// 	strcat(sql, temp);

	// 	/* Create SQL statement */
	// 	//		LOGE("sql  %s", sql);

	// 	/* Execute SQL statement */
	// 	rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
	// 	if (rc != SQLITE_OK)
	// 	{
	// 		//			LOGE("SQL error: %s", zErrMsg);
	// 		sqlite3_free(zErrMsg);
	// 		return;
	// 	}
	// 	else
	// 	{
	// 		sqlite3_close(db);
	// 		//			updateCode();
	// 		//			LOGE("Operation done successfully");
	// 	}
	// }
	/*
* Class:     com_miyuan_obd_serial_OBDBusiness
* Method:    getFaultCode
* Signature: ()Ljava/util/List;
*/
	JNIEXPORT jobject
		JNICALL
		Java_com_miyuan_obd_serial_OBDBusiness_getFaultCode(JNIEnv *env, jobject jobj,
															jstring path)
	{
		char input[6] = {HEAD, 0x81, 0x01, 0x00, 0x00, HEAD};
		input[4] = input[1] ^ input[2] ^ input[3];

		writeToBox(input,
				   sizeof(input));

		char buf[1024] = {0};
		// int i;
		// 9757
		int len = readFormBox(buf, TIMEOUT);
		// for (i = 1; i < 9758; i++)
		// {
		// 	selcet(i);
		// 	index++;
		// }
		if (
			isValid(buf, len))
		{
			// 解析故障码总数
			int count, i;
			count = buf[5];
			jclass list_jcs = env->FindClass("java/util/ArrayList");
			//获取ArrayList构造函数id
			jmethodID list_init = env->GetMethodID(list_jcs, "<init>", "()V");
			//创建一个ArrayList对象
			jobject list_obj = env->NewObject(list_jcs, list_init, "");
			//获取ArrayList对象的add()的methodID
			jmethodID list_add = env->GetMethodID(list_jcs, "add",
												  "(Ljava/lang/Object;)Z");

			//获取FaultCode类
			jclass fault_code_cls = env->FindClass("com/miyuan/obd/serial/FaultCode");
			//获取FaultCode的构造函数
			jmethodID fault_code_init = env->GetMethodID(fault_code_cls, "<init>",
														 "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

			for (
				i = 0;
				i < count;
				i++)
			{
				FaultCode faultCode;
				char item[3] = {0};
				char code[8] = {0};
				memcpy(item, buf + 6 + i * 3, 3);
				LOGE_HEX(" item ", item, 3);
				switch ((item[1] & 0xFF) >> 6)
				{
				case 0:
					strcat(code,
						   "P");
					break;
				case 1:
					strcat(code,
						   "C");
					break;
				case 2:
					strcat(code,
						   "B");
					break;
				case 3:
					strcat(code,
						   "U");
					break;
				}
				char temp[4] = {0};
				sprintf(temp,
						"%02X", item[1] & 0x3F);
				strcat(code, temp);
				sprintf(temp,
						"%02X", item[2]);
				strcat(code, temp);
				faultCode.id = code;
				jobject fault_code_obj = env->NewObject(fault_code_cls, fault_code_init,
														env->NewStringUTF(faultCode.id.c_str()),
														env->NewStringUTF(faultCode.suit.c_str()),
														env->NewStringUTF(faultCode.desc_ch.c_str()),
														env->NewStringUTF(faultCode.desc_en.c_str()),
														env->NewStringUTF(faultCode.system.c_str()),
														env->NewStringUTF(faultCode.detail.c_str()));
				env->CallBooleanMethod(list_obj, list_add, fault_code_obj);
				LOGE("CODE %s", code);
			}
			return list_obj;
		}
		return NULL;
	}

	/*
* Class:     com_miyuan_obd_serial_OBDBusiness
* Method:    cleanFaultCode
* Signature: ()Z
*/
	JNIEXPORT jboolean
		JNICALL
		Java_com_miyuan_obd_serial_OBDBusiness_cleanFaultCode(JNIEnv *env, jobject
																			   jobj)
	{
		char input[6] = {HEAD, 0x81, 0x02, 0x00, 0x00, HEAD};
		input[4] = input[1] ^ input[2] ^ input[3];

		writeToBox(input,
				   sizeof(input));

		char result[1024];

		int len = readFormBox(result, TIMEOUT);

		if (
			isValid(result, len))
		{
			return result[5] == 0;
		}
		else
		{
			return false;
		}
	}

	/*
* Class:     com_miyuan_obd_serial_OBDBusiness
* Method:    getFixedData
* Signature: (I)Ljava/lang/String;
*/
	JNIEXPORT jstring
		JNICALL
		Java_com_miyuan_obd_serial_OBDBusiness_getFixedData(JNIEnv *env, jobject jobj,
															jint fixedType)
	{
		char input[7] = {HEAD, 0x83, 0x01, 0x00, 0x00, 0x00, HEAD};
		input[4] =
			fixedType;
		input[5] = input[1] ^ input[2] ^ input[3] ^ input[4];

		writeToBox(input,
				   sizeof(input));

		char buf[1024];
		memset(buf,
			   0, sizeof(char) * 1024);

		int len = readFormBox(buf, TIMEOUT);

		char result[1024] = {0};
		float tempF;
		unsigned short tempI;
		char temp[20] = {0};
		memset(result,
			   0, sizeof(char) * 1024);
		formatStr(result, buf, len);
		if (
			isValid(buf, len))
		{
			if (len == 14 && buf[1] == 0x03 && buf[2] == 0x01)
			{
				if (buf[7] == 0)
				{ //
					strcat(result,
						   "数据不支持");
				}
				else
				{
					short id = (buf[5] << 8) + buf[6];
					if (id == fixedType)
					{
						switch (fixedType)
						{
						case 0x02: // 瞬时油耗
						case 0x03: // 瞬时油耗
						case 0x04:
						case 0x05:
						case 0x06:
							tempF = ((buf[8] << 24) + (buf[9] << 16) + (buf[10] << 8) + buf[11]) * 0.1;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						default:
							tempI = (buf[8] << 24) + (buf[9] << 16) + (buf[10] << 8) + buf[11];
							sprintf(temp,
									"%d", tempI);
							strcat(result, temp);
							break;
						}
					}
					else
					{
						strcat(result,
							   "数据异常! CODE 1");
					}
				}
			}
			else
			{
				strcat(result,
					   "数据异常! CODE 2");
			}
		}
		else
		{
			strcat(result,
				   "数据异常! 校验失败");
		}
		return env->NewStringUTF(result);
	}

	/*
* Class:     com_miyuan_obd_serial_OBDBusiness
* Method:    getDynamicData
* Signature: (I)Ljava/lang/String;
*/
	JNIEXPORT jstring
		JNICALL
		Java_com_miyuan_obd_serial_OBDBusiness_getDynamicData(JNIEnv *env, jobject jobj,
															  jint dynamicType)
	{
		char input[7] = {HEAD, 0x83, 0x02, 0x01, 0x00, 0x00, HEAD};
		if (dynamicType == 300 || dynamicType == 301)
			input[4] = 3;
		else if (dynamicType == 200 || dynamicType == 201)
			input[4] = 20;
		else if (dynamicType == 210 || dynamicType == 211)
			input[4] = 21;
		else if (dynamicType == 220 || dynamicType == 221)
			input[4] = 22;
		else if (dynamicType == 230 || dynamicType == 231)
			input[4] = 23;
		else if (dynamicType == 240 || dynamicType == 241)
			input[4] = 24;
		else if (dynamicType == 250 || dynamicType == 251)
			input[4] = 25;
		else if (dynamicType == 260 || dynamicType == 261)
			input[4] = 26;
		else if (dynamicType == 270 || dynamicType == 271)
			input[4] = 27;
		else if (dynamicType == 360 || dynamicType == 361)
			input[4] = 36;
		else if (dynamicType == 370 || dynamicType == 371)
			input[4] = 37;
		else if (dynamicType == 380 || dynamicType == 381)
			input[4] = 38;
		else if (dynamicType == 390 || dynamicType == 391)
			input[4] = 39;
		else if (dynamicType == 400 || dynamicType == 401)
			input[4] = 40;
		else if (dynamicType == 410 || dynamicType == 411)
			input[4] = 41;
		else if (dynamicType == 420 || dynamicType == 421)
			input[4] = 42;
		else if (dynamicType == 430 || dynamicType == 431)
			input[4] = 43;
		else if (dynamicType == 520 || dynamicType == 521)
			input[4] = 52;
		else if (dynamicType == 530 || dynamicType == 531)
			input[4] = 53;
		else if (dynamicType == 540 || dynamicType == 541)
			input[4] = 54;
		else if (dynamicType == 550 || dynamicType == 551)
			input[4] = 55;
		else if (dynamicType == 560 || dynamicType == 561)
			input[4] = 56;
		else if (dynamicType == 570 || dynamicType == 571)
			input[4] = 57;
		else if (dynamicType == 580 || dynamicType == 581)
			input[4] = 58;
		else if (dynamicType == 590 || dynamicType == 591)
			input[4] = 59;
		else if (dynamicType == 850 || dynamicType == 851)
			input[4] = 85;
		else if (dynamicType == 860 || dynamicType == 861)
			input[4] = 86;
		else if (dynamicType == 870 || dynamicType == 871)
			input[4] = 87;
		else if (dynamicType == 880 || dynamicType == 881)
			input[4] = 88;
		else
			input[4] =
				dynamicType;
		input[5] = input[1] ^ input[2] ^ input[3] ^ input[4];

		writeToBox(input,
				   sizeof(input));

		char buf[1024];

		int len = readFormBox(buf, TIMEOUT);

		char result[1024] = {0};
		formatStr(result, buf, len);
		char temp[20] = {0};
		unsigned short tempS;
		float tempF;
		if (
			isValid(buf, len))
		{
			if (buf[1] == 0x03 && buf[2] == 0x02)
			{
				if (buf[7] == 0) // 数据不支持
				{
					strcat(result,
						   "数据不支持");
				}
				else
				{
					short id = buf[6];
					switch (id)
					{
					case 0x01: // 电脑(ECU)中存储的故障码数量
						tempS = buf[8] & 0x7f;
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x02: // 冻结故障码
						tempS = (buf[8] << 8) + buf[9];
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x03:
						switch (dynamicType)
						{
						case 300:
							switch (buf[9])
							{
							case 1:
								strcat(result,
									   "OBD II(California ARB)");
								break;
							case 2:
								strcat(result,
									   "OBD(Federal EPA)");
								break;
							case 3:
								strcat(result,
									   "OBD and OBD II");
								break;
							case 4:
								strcat(result,
									   "OBD I");
								break;
							case 5:
								strcat(result,
									   "Not intended to meet any OBD requirements");
								break;
							case 6:
								strcat(result,
									   "EOBD(Europe)");
								break;
							}
							break;
						case 301:
							strcat(result,
								   "数据不支持");
							break;
						}
						break;
					case 0x04:
						tempF = buf[8] * 100 / 255;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x05:
						tempS = buf[8] - 40;
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x06:
					case 0x07:
					case 0x08:
					case 0x09:
						tempF = buf[8] * 100 / 128 - 100;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x0A:
						tempS = buf[8] * 3;
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x0B:
						tempS = buf[8];
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x0C:
						tempF = ((buf[8] << 8) + buf[9]) / 4;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x0D:
						tempS = buf[8];
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x0E:
						tempF = buf[8] / 2 - 64;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x0F:
						tempS = buf[8] - 40;
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x10:
						tempF = ((buf[8] << 8) + buf[9]) / 100;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x11:
						tempF = buf[8] * 100 / 255;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x12:
						switch (buf[8])
						{
						case 1:
							strcat(result,
								   "Upstream");
							break;
						case 2:
							strcat(result,
								   "Downstream of catalytic converter");
							break;
						case 4:
							strcat(result,
								   "From the outside atmosphere or off ");
							break;
						case 8:
							strcat(result,
								   "Pump commanded on for diagnostics");
							break;
						}
						break;
					case 0x13:
						tempS = buf[8];
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x14:
						switch (dynamicType)
						{
						case 200:
							tempF = buf[9] * 0.005;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 201:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x15:
						switch (dynamicType)
						{
						case 210:
							tempF = buf[9] * 0.005;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 211:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x16:
						switch (dynamicType)
						{
						case 220:
							tempF = buf[9] * 0.005;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 221:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x17:
						switch (dynamicType)
						{
						case 230:
							tempF = buf[9] * 0.005;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 231:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x18:
						switch (dynamicType)
						{
						case 240:
							tempF = buf[9] * 0.005;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 241:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x19:
						switch (dynamicType)
						{
						case 250:
							tempF = buf[9] * 0.005;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 251:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x1A:
						switch (dynamicType)
						{
						case 260:
							tempF = buf[9] * 0.005;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 261:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x1B:
						switch (dynamicType)
						{
						case 270:
							tempF = buf[9] * 0.005;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 271:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x1C:
						switch (buf[8])
						{
						case 1:
							strcat(result,
								   "OBD II(California ARB)");
							break;
						case 2:
							strcat(result,
								   "OBD(Federal EPA)");
							break;
						case 3:
							strcat(result,
								   "OBD and OBD II");
							break;
						case 4:
							strcat(result,
								   "OBD I");
							break;
						case 5:
							strcat(result,
								   "Not intended to meet any OBD requirements");
							break;
						case 6:
							strcat(result,
								   "EOBD(Europe)");
							break;
						}
						break;
					case 0x1D:
						strcat(result,
							   "数据不支持!");
						break;
					case 0x1E:
						strcat(result, buf[8] & 1 == 0 ? "PTO not active" : "PTO active");
						break;
					case 0x1F:
						tempS = (buf[8] << 8) + buf[9];
						sprintf(result,
								"%hd", tempS);
						break;
					case 0x21:
						tempS = (buf[8] << 8) + buf[9];
						sprintf(result,
								"%hd", tempS);
						break;
					case 0x22:
						tempF = ((buf[8] << 8) + buf[9]) * 0.079;
						sprintf(result,
								"%0.2f", tempF);
						break;
					case 0x23:
						tempS = ((buf[8] << 8) + buf[9]) * 10;
						sprintf(result,
								"%hd", tempS);
						break;
					case 0x24:
						switch (dynamicType)
						{
						case 360:
							tempF = ((buf[10] << 8) + buf[11]) * 2 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 361:
							tempF = ((buf[8] << 8) + buf[9]) * 8 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x25:
						switch (dynamicType)
						{
						case 370:
							tempF = ((buf[10] << 8) + buf[11]) * 2 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 371:
							tempF = ((buf[8] << 8) + buf[9]) * 8 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x26:
						switch (dynamicType)
						{
						case 380:
							tempF = ((buf[10] << 8) + buf[11]) * 2 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 381:
							tempF = ((buf[8] << 8) + buf[9]) * 8 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x27:
						switch (dynamicType)
						{
						case 390:
							tempF = ((buf[10] << 8) + buf[11]) * 2 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 391:
							tempF = ((buf[8] << 8) + buf[9]) * 8 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x28:
						switch (dynamicType)
						{
						case 400:
							tempF = ((buf[10] << 8) + buf[11]) * 2 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 401:
							tempF = ((buf[8] << 8) + buf[9]) * 8 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x29:
						switch (dynamicType)
						{
						case 410:
							tempF = ((buf[10] << 8) + buf[11]) * 2 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 411:
							tempF = ((buf[8] << 8) + buf[9]) * 8 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x2A:
						switch (dynamicType)
						{
						case 420:
							tempF = ((buf[10] << 8) + buf[11]) * 2 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 421:
							tempF = ((buf[8] << 8) + buf[9]) * 8 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x2B:
						switch (dynamicType)
						{
						case 430:
							tempF = ((buf[10] << 8) + buf[11]) * 2 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 431:
							tempF = ((buf[8] << 8) + buf[9]) * 8 / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x2C:
						tempF = buf[8] * 100 / 255;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x2D:
						tempF = buf[8] * 100 / 128 - 100;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x2E:
					case 0x2F:
						tempF = buf[8] * 100 / 255;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x31:
						tempS = (buf[8] << 8) + buf[9];
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x32:
						tempF = ((buf[8] << 8) + buf[9]) / 4;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x33:
						tempS = buf[8];
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x34:
						switch (dynamicType)
						{
						case 520:
							tempF = ((buf[10] << 8) + buf[11]) / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 521:
							tempF = ((buf[8] << 8) + buf[9]) / 256 - 128;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x35:
						switch (dynamicType)
						{
						case 530:
							tempF = ((buf[10] << 8) + buf[11]) / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 531:
							tempF = ((buf[8] << 8) + buf[9]) / 256 - 128;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x36:
						switch (dynamicType)
						{
						case 540:
							tempF = ((buf[10] << 8) + buf[11]) / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 541:
							tempF = ((buf[8] << 8) + buf[9]) / 256 - 128;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x37:
						switch (dynamicType)
						{
						case 550:
							tempF = ((buf[10] << 8) + buf[11]) / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 551:
							tempF = ((buf[8] << 8) + buf[9]) / 256 - 128;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x38:
						switch (dynamicType)
						{
						case 560:
							tempF = ((buf[10] << 8) + buf[11]) / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 561:
							tempF = ((buf[8] << 8) + buf[9]) / 256 - 128;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x39:
						switch (dynamicType)
						{
						case 570:
							tempF = ((buf[10] << 8) + buf[11]) / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 571:
							tempF = ((buf[8] << 8) + buf[9]) / 256 - 128;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x3A:
						switch (dynamicType)
						{
						case 580:
							tempF = ((buf[10] << 8) + buf[11]) / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 581:
							tempF = ((buf[8] << 8) + buf[9]) / 256 - 128;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x3B:
						switch (dynamicType)
						{
						case 590:
							tempF = ((buf[10] << 8) + buf[11]) / 65536;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 591:
							tempF = ((buf[8] << 8) + buf[9]) / 256 - 128;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x3C:
					case 0x3D:
					case 0x3E:
					case 0x3F:
						tempF = ((buf[8] << 8) + buf[9]) / 10 - 40;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x42:
						tempF = ((buf[8] << 8) + buf[9]) / 1000;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x43:
						tempF = ((buf[8] << 8) + buf[9]) * 100 / 255;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x44:
						tempF = ((buf[8] << 8) + buf[9]) * 2 / 65535;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x45:
						tempF = buf[8] * 100 / 255;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x46:
						tempS = buf[8] - 40;
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x47:
					case 0x48:
					case 0x49:
					case 0x4A:
					case 0x4B:
					case 0x4C:
						tempF = buf[8] * 100 / 255;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x4D:
					case 0x4E:
						tempS = (buf[8] << 8) + buf[9];
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x51:
						switch (buf[8])
						{
						case 0x01:
							strcat(result,
								   "GAS");
							break;
						case 0x02:
							strcat(result,
								   "METH");
							break;
						case 0x03:
							strcat(result,
								   "ETH");
							break;
						case 0x04:
							strcat(result,
								   "DSL");
							break;
						case 0x05:
							strcat(result,
								   "LPG");
							break;
						case 0x06:
							strcat(result,
								   "CNG");
							break;
						case 0x07:
							strcat(result,
								   "PROP");
							break;
						case 0x08:
							strcat(result,
								   "ELEC");
							break;
						case 0x09:
							strcat(result,
								   "BI_GAS");
							break;
						case 0x0A:
							strcat(result,
								   "BI_METH");
							break;
						case 0x0B:
							strcat(result,
								   "BI_ETH");
							break;
						case 0x0C:
							strcat(result,
								   "BI_LPG");
							break;
						case 0x0D:
							strcat(result,
								   "BI_CNG");
							break;
						case 0x0E:
							strcat(result,
								   "BI_PROP");
							break;
						case 0x0F:
							strcat(result,
								   "BI_ELEC");
							break;
						}
						break;
					case 0x52:
						tempF = buf[8] * 100 / 255;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x53:
						tempF = ((buf[8] << 8) + buf[9]) / 200;
						sprintf(temp,
								"%0.2f", tempF);
						strcat(result, temp);
						break;
					case 0x54:
						tempS = (buf[8] << 8) + buf[9] - 32768;
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x55:
						switch (dynamicType)
						{
						case 850:
							tempF = buf[9] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 851:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x56:
						switch (dynamicType)
						{
						case 860:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 861:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x57:
						switch (dynamicType)
						{
						case 870:
							tempF = buf[9] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 871:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x58:
						switch (dynamicType)
						{
						case 880:
							tempF = buf[9] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						case 881:
							tempF = buf[8] * 100 / 128 - 100;
							sprintf(temp,
									"%0.2f", tempF);
							strcat(result, temp);
							break;
						}
						break;
					case 0x59:
						tempS = ((buf[9] << 8) + buf[8]) * 10;
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x5A:
					case 0x5B:
						tempF = buf[8] * 100 / 255;
						sprintf(temp,
								"%0.2F", tempF);
						strcat(result, temp);
						break;
					case 0x5C:
						tempS = buf[8] - 40;
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x5D:
						tempF = ((buf[8] << 8) + buf[9]) / 128 - 210;
						sprintf(temp,
								"%0.2F", tempF);
						strcat(result, temp);
						break;
					case 0x5E:
						tempF = ((buf[8] << 8) + buf[9]) / 20;
						sprintf(temp,
								"%0.2F", tempF);
						strcat(result, temp);
						break;
					case 0x61:
					case 0x62:
						tempS = buf[8] - 125;
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x63:
						tempS = ((buf[8] << 8) + buf[9]) * 10;
						sprintf(temp,
								"%hd", tempS);
						strcat(result, temp);
						break;
					case 0x64:
						strcat(result,
							   "数据不支持!");
						break;
					default:
						strcat(result,
							   "数据不支持!");
						break;
					}
				}
			}
		}
		else
		{
			strcat(result,
				   "数据异常! 校验失败");
		}
		return env->NewStringUTF(result);
	}

	/*
* Class:     com_miyuan_obd_serial_OBDBusiness
* Method:    setCarStatus
* Signature: (Z)V
*/
	JNIEXPORT jboolean
		JNICALL
		Java_com_miyuan_obd_serial_OBDBusiness_setCarStatus(JNIEnv *env, jobject jobj,
															jboolean status)
	{
		char input[6] = {HEAD, 0x89, 0x01, 0x01, 0x00, HEAD};
		if (!status)
		{
			input[3] = 0x00;
		}
		input[4] = input[1] ^ input[2] ^ input[3];

		writeToBox(input,
				   sizeof(input));

		char result[1024];

		int len = readFormBox(result, TIMEOUT);

		return isValid(result, len);
	}
#ifdef __cplusplus
}
#endif
#endif
