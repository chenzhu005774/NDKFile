package com.example.administrator.ndkfile;

import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.VideoView;

import java.text.DecimalFormat;
import java.util.Formatter;
import java.util.Locale;

public class MainActivity extends AppCompatActivity implements MediaPlayer.OnErrorListener,MediaPlayer.OnPreparedListener {
        VideoView videoview;
        //将长度转换为时间
        StringBuilder mFormatBuilder = new StringBuilder();
        Formatter mFormatter = new Formatter(mFormatBuilder, Locale.getDefault());
    Handler handler = new Handler();
    int  i=0;
    String [] url =new String[] {
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/01_legaobaibaohe13473294591.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/02_legaokafeidianxilie13514676212.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/03_kaidimaoqiaokeliwanju13541281263.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/04_jingziguosanguan13563435504.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/05_binfenmianhuatang13584190385.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/06_miqibaomihuaji14043482406.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/22jiatingzhuangqiuyouxi153350732322.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/08_miqitaoyiji_xiaji14160242818.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/09_youqudezaozhishu14200413919.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/10_geibabizuoxinzaoxing142402185110.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/11_tianpincainiji142859615511.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/12_baibianbakeqiu143123185312.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/23tuomasidamaoxian153755432423.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/14_minibaolingqiu144632677414.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/15_wayizhibawanglong145017929015.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/16_meihuaboliping145237111516.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/17_baoxiaodiediele150002840417.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/21_fanfanlejiyiyouxi152224215321.ts",
            "http://183.223.222.117:36101/images_cdsb/videos/20190304/19_diyiciwanshituohua150527864019.ts",
    };



//    主要不要是 adb shell 下  adb pull /sdcard/data.txt data.txt
//    adb copy 到电脑的C:\Users\Administrator\Desktop  上

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        videoview = findViewById(R.id.videoview);
        videoview.setOnErrorListener(this);
        videoview.setOnPreparedListener(this);
        videoview.setVideoURI(Uri.parse(url[i]));
        System.out.println("------------------------>start");
        FileUtils.getInstance().FileDelete("/sdcard/data.txt");
        FileUtils.getInstance().FileWrite("<------------start------------>\n","/sdcard/data.txt");

    }

    @Override
    public boolean onError(MediaPlayer mediaPlayer, int i, int i1) {
        return false;
    }

    @Override
    public void onPrepared(MediaPlayer mediaPlayer) {

        int num = 1000*60;
        DecimalFormat df=new DecimalFormat("0.00");
        FileUtils.getInstance().FileWrite(df.format((float)mediaPlayer.getDuration()/num)+"\n ","/sdcard/data.txt");

        System.out.println("------------------------>"+df.format((float)mediaPlayer.getDuration()/num));
        videoview.start();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                if(i==(url.length-1)){
                    handler.removeCallbacks(this);
                    System.out.println();
                    FileUtils.getInstance().FileWrite("<------------end------------>\n ","/sdcard/data.txt");
                    return;

                }
                i+=1;
                videoview.setVideoURI(Uri.parse(url[i]));
            }
        },1000);
    }


    static {
        System.loadLibrary("native-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

}
