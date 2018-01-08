package com.esay.ffmtool;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import junit.framework.Test;

import java.io.File;

import static android.R.attr.path;
import static com.esay.ffmtool.FfmpegTool.cmdRun;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    FfmpegTool  ffmpegTool;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ffmpegTool=new FfmpegTool() ;
    }

    public void click1(View view){
       new Thread(){
           @Override
           public void run() {
               String basePath = Environment.getExternalStorageDirectory().getPath();
               String cmd = String.format("ffmpeg -ss 00:00:10 -i "+ basePath+"/test/"+"c.mp4"
                       +" -f image2 -y  "+basePath+"/test"+"/"+"aaaa.jpg");
               String dir=basePath+File.separator+"test"+File.separator;
               /**
                * ffmpeg -ss 0:1:30 -t 0:0:20 -i input.avi -vcodec copy -acodec copy output.avi    //剪切视频
                //-r 提取图像的频率，-ss 开始时间，-t 持续时间
                */
               String videoPath=dir+"c.mp4";
               String out=dir+"out.mp4";
               String cmd2=String.format("ffmpeg -ss 10"+" -t 15 -i "+videoPath
                       +" -vcodec copy -acodec copy "+out);

               String regulation="[ \\t]+";
               Log.i("MainActivity","cmd:"+cmd);
               Log.i("MainActivity","cmd2:"+cmd2);
               final String[] split = cmd.split(regulation);
               final String[] split2 = cmd2.split(regulation);
               int result=FfmpegTool.cmdRun(split2);
               Log.i("MainActivity","result:"+result);
           }
       }.start();
    }

    public void click2(View view){
        String path= Environment.getExternalStorageDirectory().getPath()+ File.separator+"test"+File.separator;
        String savepah=Environment.getExternalStorageDirectory().getPath()+ File.separator+"test2"+File.separator;
        File file=new File(savepah);
        if (!file.exists()){
            file.mkdirs();
        }
        String video=path+"c.mp4";
        FfmpegTool.decodToImage(video.replaceAll(File.separator,"/"),savepah,0,10);
    }

    public void click3(View view){
        new Thread(){
            @Override
            public void run() {
                String path= Environment.getExternalStorageDirectory().getPath()+ File.separator+"test"+File.separator;
                String video=path+"c.mp4";
                ffmpegTool.decodToImageWithCall(video.replaceAll(File.separator,"/")
                        ,Environment.getExternalStorageDirectory().getPath()
                        + File.separator+"test2"+File.separator,0,10);
            }
        }.start();
    }

}
