#include <jni.h>
#include <string>
#include "fileutil.h"

// 静态注册的 函数
extern "C" JNIEXPORT
jstring
JNICALL
Java_com_example_administrator_ndkfile_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



jint File_write(JNIEnv* env,jobject thiz,jstring content,jstring filepath){
    fileutil* fileutil1 = new fileutil();
    jint  result = fileutil1->Write_file(env,thiz,content,filepath);
    delete(fileutil1);
    fileutil1=NULL;
    return result;

}


jint File_Delete(JNIEnv* env,jobject thiz, jstring filepath){
    fileutil* fileutil1 = new fileutil();
    jint  result = fileutil1->Delete_file(env,thiz,filepath);
    delete(fileutil1);
    fileutil1=NULL;
    return result;

}


// jni 函数列表
static JNINativeMethod getMethods[] = {
//        括号内代表传入参数的签名符号，为空可以不写，括号外代表返回参数的签名符号,为空填写 V，对应关系入下表
        {"FileWrite", "(Ljava/lang/String;Ljava/lang/String;)I",(void*)File_write},
        {"FileDelete", "(Ljava/lang/String;)I",(void*)File_Delete},

};

//此函数通过调用RegisterNatives方法来注册我们的函数
static int registerNativeMethods(JNIEnv* env, const char* className,JNINativeMethod* getMethods,int methodsNum){
    jclass clazz;
    //找到声明native方法的类
    clazz = env->FindClass(className);
    if(clazz == NULL){
        return JNI_FALSE;
    }
    //注册函数 参数：java类 所要注册的函数数组 注册函数的个数
    if(env->RegisterNatives(clazz,getMethods,methodsNum) < 0){
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static int registerNatives(JNIEnv* env){
    //指定类的路径，通过FindClass 方法来找到对应的类
    const char* className  = "com/example/administrator/ndkfile/FileUtils";
    return registerNativeMethods(env,className,getMethods, sizeof(getMethods)/ sizeof(getMethods[0]));
}

//回调函数 在加载JNI 的时候去注册函数
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved ){
    JNIEnv* env = NULL;
    //获取JNIEnv
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    __glibcxx_assert(env != NULL);
    //注册函数 registerNatives ->registerNativeMethods ->env->RegisterNatives
    if(!registerNatives(env)){
        return -1;
    }
    //返回jni 的版本
    return JNI_VERSION_1_6;

}
