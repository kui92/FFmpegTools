# FfmpegTool
将视频解码为一帧一帧的图片，并能执行FFmpeg命令。
  在Android手机上用FFmpeg可以很方便的处理视频，裁剪、压缩、转码等。
  
  
  之前遇到一个需求是将视频一秒一秒解码成一帧一帧的图片，用户滑动选择时间节点（微信朋友圈发10秒视频的编辑界面）。开始我是用的MediaMetadataRetriever类
来获取图片，但是对于分辨率比较大的视频（1920*1080）获取一个图片要0.7/0.8秒，太慢了。后来又用FFmpeg的命令来批量的解码视频成一帧一帧的图片，速度依然不快
每张图片得耗费0.5秒左右的时间。最后还是用FFmpeg，不过不是用命令行，而是用NDK，发现c解码视频再转换为图片保存起来效率大大挺高，一秒钟能解码4、5张图片，c就是快啊。


  工程很简单，主要的就FfmpegTool类，里面两个方法cmdRun执行FFmpeg命令，decodToImage一秒一秒的解码图片。两个方法都是阻塞的。
  
  
  
   cmdRun用法          
  
  
    String basePath = Environment.getExternalStorageDirectory().getPath();
  
    String cmd = String.format("ffmpeg -ss 00:00:10 -i "+ basePath+"/test/"+"c.mp4"
                       +" -f image2 -y  "+basePath+"/test"+"/"+"aaaa.jpg");
                       
               String dir=basePath+File.separator+"test"+File.separator;
               
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
   

decodToImage用法


    String path= Environment.getExternalStorageDirectory().getPath()+ File.separator+"test"+File.separator;
 
    String video=path+"c.mp4";
 
    FfmpegTool.decodToImage(video.replaceAll(File.separator,"/"),path.replaceAll(File.separator,"/"),0,60);

//新加方法
public native int decodToImageWithCall(String srcPath,String savePath,int startTime,int count);
该方法与decodToImage功能相同，不过该方法添加了jni回调，每当有一幅图片解码保存完成后都会调用public void decodToImageCall(String path,int index)（类FfmpegTool中的方法），用户可根据该方法监听进度。
用法：

        FfmpegTool  ffmpegTool=new FfmpegTool() ;
        
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
