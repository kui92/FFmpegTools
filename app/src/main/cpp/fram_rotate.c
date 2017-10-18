//
// Created by ESAY on 2017/10/18.
//


#include <libavutil/frame.h>
#include <libavformat/avformat.h>

/**
 * 逆时针90度
 * @param src
 * @param des
 */
void frame_rotate_90(AVFrame *src, AVFrame *des) {
    int n = 0;
    int hw = src->width >> 1;
    int hh = src->height >> 1;
    int size = src->width * src->height;
    int hsize = size >> 2;

    int pos = 0;
    //copy y
    for (int j = 0; j < src->width; j++) {
        pos = size;
        for (int i = src->height - 1; i >= 0; i--) {
            pos -= src->width;
            des->data[0][n++] = src->data[0][pos + j];
        }
    }
    //copy uv
    n = 0;
    for (int j = 0; j < hw; j++) {
        pos = hsize;
        for (int i = hh - 1; i >= 0; i--) {
            pos -= hw;
            des->data[1][n] = src->data[1][pos + j];
            des->data[2][n] = src->data[2][pos + j];
            n++;
        }
    }

    des->linesize[0] = src->height;
    des->linesize[1] = src->height >> 1;
    des->linesize[2] = src->height >> 1;
    des->height = src->width;
    des->width = src->height;
}

/**
 * 获取视频的旋转角度
 * @param st
 * @return

double get_rotation(AVStream *st) {
    AVDictionaryEntry *rotate_tag = av_dict_get(st->metadata, "rotate", NULL, 0);
    double theta = 0;

    if (rotate_tag && *rotate_tag->value && strcmp(rotate_tag->value, "0")) {
        //char *tail;
        //theta = av_strtod(rotate_tag->value, &tail);
        theta = atof(rotate_tag->value);
        // if (*tail)
        // theta = 0;
    }

    theta -= 360 * floor(theta / 360 + 0.9 / 360);

    if (fabs(theta - 90*round(theta/90)) > 2)
        LOGV("Odd rotation angle");

    LOGV("get_rotation %f",theta);

    return theta;
}*/

void frame_rotate_180(AVFrame *src, AVFrame *des) {
    int n = 0, i = 0, j = 0;
    int hw = src->width >> 1;
    int hh = src->height >> 1;
    int pos = src->width * src->height;

    for (i = 0; i < src->height; i++) {
        pos -= src->width;
        for (int j = 0; j < src->width; j++) {
            des->data[0][n++] = src->data[0][pos + j];
        }
    }

    n = 0;
    pos = src->width * src->height >> 2;

    for (i = 0; i < hh; i++) {
        pos -= hw;
        for (int j = 0; j < hw; j++) {

            des->data[1][n] = src->data[1][pos + j];
            des->data[2][n] = src->data[2][pos + j];
            n++;
        }
    }

    des->linesize[0] = src->width;
    des->linesize[1] = src->width >> 1;
    des->linesize[2] = src->width >> 1;

    des->width = src->width;
    des->height = src->height;
    des->format = src->format;

    des->pts = src->pts;
    des->pkt_pts = src->pkt_pts;
    des->pkt_dts = src->pkt_dts;

    des->key_frame = src->key_frame;
}


void frame_rotate_270(AVFrame *src, AVFrame *des) {
    int n = 0, i = 0, j = 0;
    int hw = src->width >> 1;
    int hh = src->height >> 1;
    int pos = 0;

    for (i = src->width - 1; i >= 0; i--) {
        pos = 0;
        for (j = 0; j < src->height; j++) {
            des->data[0][n++] = src->data[0][pos + i];
            pos += src->width;
        }
    }

    n = 0;
    for (i = hw - 1; i >= 0; i--) {
        pos = 0;
        for (j = 0; j < hh; j++) {
            des->data[1][n] = src->data[1][pos + i];
            des->data[2][n] = src->data[2][pos + i];
            pos += hw;
            n++;
        }
    }

    des->linesize[0] = src->height;
    des->linesize[1] = src->height >> 1;
    des->linesize[2] = src->height >> 1;

    des->width = src->height;
    des->height = src->width;
    des->format = src->format;

    des->pts = src->pts;
    des->pkt_pts = src->pkt_pts;
    des->pkt_dts = src->pkt_dts;

    des->key_frame = src->key_frame;
}