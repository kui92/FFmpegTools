package com.esay.ffmtool;

/**
 * Created by ZBK on 2017/9/28.
 * Describe:
 */

public class FfmpegTool {

    static {
        System.loadLibrary("avutil");
        System.loadLibrary("fdk-aac");
        System.loadLibrary("avcodec");
        System.loadLibrary("avformat");
        System.loadLibrary("swscale");
        System.loadLibrary("swresample");
        System.loadLibrary("avfilter");
        System.loadLibrary("jxffmpegrun");
    }

    /**
     * 执行FFmpeg命令
     * @param cmd
     *
     * @return
     */
    public static native int cmdRun(String[] cmd);

    /**
     *把视频按秒解码成图片
     * @param srcPath 视频源地址
     * @param savePath 要保存的图片目录
     * @param startTime 从视频的什么时间开始 单位秒
     * @param count 要解码多少个
     * @return 返回码 成功0
     */
    public static native int decodToImage(String srcPath,String savePath,int startTime,int count);

    //test

}
