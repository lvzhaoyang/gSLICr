
#pragma once

#include <gSLICr_Lib/gSLICr.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

void load_image(const cv::Mat& inImg, gSLICr::UChar4Image* outimg) {
    gSLICr::Vector4u* outimg_ptr = outimg->GetData(MEMORYDEVICE_CPU);

    for (int y = 0; y < outimg->noDims.y;y++) {
        for (int x = 0; x < outimg->noDims.x; x++) {
            int idx = x + y * outimg->noDims.x;
            outimg_ptr[idx].b = inImg.at<cv::Vec3b>(y, x)[0];
            outimg_ptr[idx].g = inImg.at<cv::Vec3b>(y, x)[1];
            outimg_ptr[idx].r = inImg.at<cv::Vec3b>(y, x)[2];
        }
    }
}

void load_image(const gSLICr::UChar4Image* inImg, cv::Mat& outimg) {
    const gSLICr::Vector4u* inimg_ptr = inImg->GetData(MEMORYDEVICE_CPU);

    for (int y = 0; y < inImg->noDims.y; y++) {
        for (int x = 0; x < inImg->noDims.x; x++) {
            int idx = x + y * inImg->noDims.x;
            outimg.at<cv::Vec3b>(y, x)[0] = inimg_ptr[idx].b;
            outimg.at<cv::Vec3b>(y, x)[1] = inimg_ptr[idx].g;
            outimg.at<cv::Vec3b>(y, x)[2] = inimg_ptr[idx].r;
        }
    }
}

void load_image(const gSLICr::IntImage* inImg, cv::Mat& outimg) {
    const int* inimg_ptr = inImg->GetData(MEMORYDEVICE_CPU);

    for (int y = 0; y < inImg->noDims.y; y++) {
        for (int x = 0; x < inImg->noDims.x; x++) {
            int idx = x + y * inImg->noDims.x;
            outimg.at<int>(y, x) = inimg_ptr[idx];
        }
    }
}

void load_depth(const cv::Mat& inDep, gSLICr::FloatImage* outDep) {
    float* outdep_ptr = outDep->GetData(MEMORYDEVICE_CPU);

    switch(inDep.depth()) {
        case CV_16U: {
            for (int y = 0; y < outDep->noDims.y; y++) {
                for (int x =0; x < outDep->noDims.x; x++) {
                    int idx = x + y * outDep->noDims.x;
                    outdep_ptr[idx] = inDep.at<short>(y, x) / 1000.0f;
                }
            }
            break;
        }
        case CV_32F: {
            for (int y = 0; y < outDep->noDims.y; y++) {
                for (int x =0; x < outDep->noDims.x; x++) {
                    int idx = x + y * outDep->noDims.x;
                    outdep_ptr[idx] = inDep.at<float>(y, x) / 1000.0f;
                }
            }
            break;
        }
    }

}
