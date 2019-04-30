#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

#include "drawer.h"
#include "imgwarp_mls_similarity.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;


int main(int argc, char ** argv)
{
  if(argc != 2)
  {
    cout << "usage: ./warper path_to_img" << endl;
    return -1;
  }

  cv::Mat img_ = cv::imread(string(argv[1]));
  cv::Mat img_dst, img_src;

  img_.copyTo(img_src);

  PolygonDrawer pd_src("src", img_src);
  std::vector<cv::Point> src_pts = pd_src.run();

  int i = 0;
  for (auto pt : src_pts)
  {
    i++;
    circle(img_src, pt, 5, Scalar(0,0,255), 2);
    putText(img_src, std::to_string(i), Point(pt.x - 10, pt.y - 10), 
            FONT_HERSHEY_PLAIN, 2,  Scalar(0,0,255), 2);
  }

  PolygonDrawer pd_dst("dst", img_src);
  std::vector<cv::Point> dst_pts = pd_dst.run();

  i = 0;
  for (auto pt : dst_pts)
  {
    i++;
    circle(img_src, pt, 5, Scalar(0,255,0), 2);
    putText(img_src, std::to_string(i), Point(pt.x - 10, pt.y - 10), 
            FONT_HERSHEY_PLAIN, 2,  Scalar(0,255,0), 2);
  }

  auto imgTrans = new ImgWarp_MLS_Similarity();

  img_dst = imgTrans->setAllAndGenerate(img_,
                                        src_pts,
			                                  dst_pts,
			                                  img_src.cols, 
                                        img_src.rows, 
                                        1);

  imshow("dst", img_dst);
  imshow("src", img_src);
  waitKey(0);

  
  return 0;
}
