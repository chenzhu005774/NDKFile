//
// Created by Administrator on 2019/11/28 0028.
//

#ifndef NDKFILE_FILEUTIL_H
#define NDKFILE_FILEUTIL_H


#include <jni.h>

class fileutil {


public:
    fileutil();
    ~ fileutil();
    jint Delete_file(JNIEnv* env,jobject thiz,jstring filepath);
    jint Write_file(JNIEnv* env,jobject thiz,jstring content,jstring filepath);

};


#endif //NDKFILE_FILEUTIL_H
