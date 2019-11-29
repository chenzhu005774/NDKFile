//
// Created by Administrator on 2019/11/28 0028.
//

#include "fileutil.h"
#include <iostream>
#include <android/log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdlib>
#include <unistd.h>

// 定义info信息
#define  LOG_TAG    "[CHENZHU_JNILOG]"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
using namespace std;

fileutil::fileutil(){
    LOGI("构造函数");
};


/**
 * File_write--操作文件目录
 * 返回0--成功
 */

jint fileutil::Write_file(JNIEnv* env,jobject thiz,jstring content,jstring filepath){

    FILE * file;
    const char * file_path  = env->GetStringUTFChars( filepath, JNI_FALSE);
    const char * write_content  = env->GetStringUTFChars( content, JNI_FALSE);

    LOGI("go to file write:%s\n", file_path);

    file = fopen(file_path,"a+");//如果文件存在就添加内容，如果文件不存在就创建新文件
    if (file== NULL){
        LOGI("open file faile%s\n","");
    }else{
        LOGI("open file success%s\n","");
    }

    fputs(write_content,file);//写入操作
    fclose(file);//关闭文件流
    //free(filepath);//释放动态内存，防止内存泄露

    //在这里再回调一下 Java 告诉他写入完成
    jclass j_class = env->FindClass("com/example/administrator/ndkfile/FileUtils");
    jmethodID  method = env->GetStaticMethodID(j_class, "callByJNI","(I)V");
   // 回调静态方法
    env->CallStaticVoidMethod(j_class, method, 666);
    return 0;//正确 执行返回

}

jint fileutil::Delete_file(JNIEnv* env,jobject thiz,jstring filepath) {
    const  char* dirName = env->GetStringUTFChars(filepath,JNI_FALSE);

    if(0 == access(dirName,0)) {//目录存在
        LOGI("目录存在 需要删除\n");
        int issuccess= remove(dirName);
        if (issuccess==0){
            LOGI("目录存在 删除成功\n");
            return 0;
        } else{
            LOGI("目录存在 删除失败\n");
            return 1;
        }

    } else{
        LOGI("目录不存在 不用删除\n");
        return 0;
    }

}

fileutil::~fileutil() {
    LOGI("析构函数");
}