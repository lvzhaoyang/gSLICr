#include <time.h>
#include <stdio.h>

#include "../NVTimer.h"
#include "opencvUtils.h"

using namespace std;
using namespace gSLICr;

int main() {

  cv::Mat I, D_raw, D;   // rgb image and depth image
  I = cv::imread("../files/00000-color.png", CV_LOAD_IMAGE_ANYCOLOR);
  D_raw = cv::imread("../files/00000-depth.png", CV_LOAD_IMAGE_ANYDEPTH);
  //  CV_Assert(I.size() == D_raw.size());
  D_raw.convertTo(D, CV_32FC1);

  // bilateral filter over depth image
  cv::Mat bfD;
  cv::bilateralFilter(D, bfD, 7, 0.03, 5);    // 30mm, 5 pixels

  // for visualization
  cv::Mat boundry_draw_frame; boundry_draw_frame.create(I.size(), CV_8UC3);
  cv::Mat index_frame; index_frame.create(I.size(), CV_32SC1);

  // gSLICr settings
  objects::settings my_settings;
  my_settings.img_size.x = I.cols;
  my_settings.img_size.y = I.rows;
  my_settings.no_segs = 100;
  my_settings.spixel_size = 32;
  my_settings.coh_weight = 0.6f;
  my_settings.dh_weight = 0.5f;
  my_settings.no_iters = 5;
  my_settings.color_space = RGBD; // gSLICr::CIELAB for Lab, or gSLICr::RGB for RGB
  my_settings.seg_method = GIVEN_SIZE; // or gSLICr::GIVEN_NUM for given number
  my_settings.do_enforce_connectivity = true; // wheter or not run the enforce connectivity step

  engines::core_engine* gSLICr_engine = new engines::core_engine(my_settings);

  UChar4Image* in_img = new UChar4Image(my_settings.img_size, true, true);
  FloatImage* in_depth = new FloatImage(my_settings.img_size, true, true);
  UChar4Image* out_img = new UChar4Image(my_settings.img_size, true, true);

  // load image into color space
  load_image(I, in_img);
  load_depth(bfD, in_depth);

  StopWatchInterface *my_timer; sdkCreateTimer(&my_timer);
  sdkResetTimer(&my_timer); sdkStartTimer(&my_timer);
  if (my_settings.color_space == RGBD) {
    gSLICr_engine->Process_Frame(in_img, in_depth);
  } else {
    gSLICr_engine->Process_Frame(in_img);
  }
  sdkStopTimer(&my_timer);
  cout<<"\rsegmentation in:["<<sdkGetTimerValue(&my_timer)<<"]ms"<<flush;

  const IntImage* idx_img = gSLICr_engine->Get_Seg_Res(true);
  load_image(idx_img, index_frame);   // get superpixel segments
  cv::imwrite("idx.png", index_frame);

  gSLICr_engine->Draw_Segmentation_Result(out_img);

  load_image(out_img, boundry_draw_frame);  // get superpixel visualizations
  cv::imshow("segmentation", boundry_draw_frame);

  cv::waitKey(0);
}
