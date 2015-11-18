#include <time.h>
#include <stdio.h>

#include "../NVTimer.h"
#include "opencvUtils.h"

using namespace std;
using namespace cv;

int main() {

  cv::Mat I00, I01;
  I00 = cv::imread("../files/000000_10.png");
  I01 = cv::imread("../files/000000_11.png");

  // for visualization
  Mat boundry_draw_frame; boundry_draw_frame.create(I00.size(), CV_8UC3);

  // gSLICr settings
  gSLICr::objects::settings my_settings;
  my_settings.img_size.x = I00.cols;
  my_settings.img_size.y = I00.rows;
  my_settings.no_segs = 2000;
  my_settings.spixel_size = 16;
  my_settings.coh_weight = 0.6f;
  my_settings.no_iters = 5;
  my_settings.color_space = gSLICr::XYZ; // gSLICr::CIELAB for Lab, or gSLICr::RGB for RGB
  my_settings.seg_method = gSLICr::GIVEN_SIZE; // or gSLICr::GIVEN_NUM for given number
  my_settings.do_enforce_connectivity = true; // wheter or not run the enforce connectivity step

  gSLICr::engines::core_engine* gSLICr_engine = new gSLICr::engines::core_engine(my_settings);

  gSLICr::UChar4Image* in_img = new gSLICr::UChar4Image(my_settings.img_size, true, true);
  gSLICr::UChar4Image* out_img = new gSLICr::UChar4Image(my_settings.img_size, true, true);

  StopWatchInterface *my_timer; sdkCreateTimer(&my_timer);
  sdkResetTimer(&my_timer); sdkStartTimer(&my_timer);
  load_image(I00, in_img);
  gSLICr_engine->Process_Frame(in_img);
  sdkStopTimer(&my_timer);
  cout<<"\rsegmentation in:["<<sdkGetTimerValue(&my_timer)<<"]ms"<<flush;

  gSLICr_engine->Draw_Segmentation_Result(out_img);

  load_image(out_img, boundry_draw_frame);
  cv::imshow("segmentation", boundry_draw_frame);

  cv::waitKey(0);

}
