package com.example.administrator.ndkfile;

public class FileUtils {

    //类初始化时，不初始化这个对象(延时加载，真正用的时候再创建)
    private static FileUtils instance;

    //构造器私有化
    private FileUtils(){}

    //方法同步，调用效率低
    public static synchronized FileUtils getInstance(){
        if(instance==null){
            instance=new FileUtils();
        }
        return instance;
    }

    public  native int FileWrite(String conten,String path);
    public  native int FileDelete(String path);
    public static void  callByJNI(int data){
        System.out.print("JNI 使用了回调："+data);
    }


}
