//
// Created by ESAY on 2017/10/18.
//

#include <libavutil/frame.h>

#ifndef FFMTOOL_FRAM_ROTATE_H
#define FFMTOOL_FRAM_ROTATE_H

#endif //FFMTOOL_FRAM_ROTATE_H
void frame_rotate_90(AVFrame *src, AVFrame *des);
void frame_rotate_270(AVFrame *src, AVFrame *des);
void frame_rotate_180(AVFrame *src, AVFrame *des);