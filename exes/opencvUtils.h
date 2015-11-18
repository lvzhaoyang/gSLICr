
#pragma once

#include <gSLICr_Lib/gSLICr.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

void load_image(const cv::Mat& inimg, gSLICr::UChar4Image* outimg) {
    gSLICr::Vector4u* outimg_ptr = outimg->GetData(MEMORYDEVICE_CPU);

    for (int y = 0; y < outimg->noDims.y;y++)
        for (int x = 0; x < outimg->noDims.x; x++) {
            int idx = x + y * outimg->noDims.x;
            outimg_ptr[idx].b = inimg.at<cv::Vec3b>(y, x)[0];
            outimg_ptr[idx].g = inimg.at<cv::Vec3b>(y, x)[1];
            outimg_ptr[idx].r = inimg.at<cv::Vec3b>(y, x)[2];
        }
}

void load_image(const gSLICr::UChar4Image* inimg, cv::Mat& outimg)
{
    const gSLICr::Vector4u* inimg_ptr = inimg->GetData(MEMORYDEVICE_CPU);

    for (int y = 0; y < inimg->noDims.y; y++)
        for (int x = 0; x < inimg->noDims.x; x++)
        {
            int idx = x + y * inimg->noDims.x;
            outimg.at<cv::Vec3b>(y, x)[0] = inimg_ptr[idx].b;
            outimg.at<cv::Vec3b>(y, x)[1] = inimg_ptr[idx].g;
            outimg.at<cv::Vec3b>(y, x)[2] = inimg_ptr[idx].r;
        }
}

