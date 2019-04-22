#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void toolbar(int tb_value, void* userdata)
{
  cv::Mat img = *reinterpret_cast<cv::Mat*>(userdata);
  cv::Mat img_mod;
  img.copyTo(img_mod);

  for(auto el = img_mod.begin<int8_t>(); el != img_mod.end<int8_t>(); ++el)
  {
    int16_t t = *el;
    t *= ((double)tb_value / 100);
    if(t > 255)
    {
      t = 255;
    } else if(t < 0)
    {
      t = 0;
    }
    *el += t;
  }
  cv::imshow("new", img_mod);
  cv::moveWindow("new", 100, 100);
}

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

int main(int argc, char ** argv)
{
  if(argc != 2)
  {
    cout << "usage: ./hist path_to_img" << endl;
    return -1;
  }
  cout << "img_path: " << argv[1] << endl;
  Mat source_img = cv::imread(string(argv[1]));
  vector<cv::Mat> channels;
  cv::split(source_img, channels);
  cv::Mat img = channels.at(0);
  cv::Mat img_mod;
  img.copyTo(img_mod);
  namedWindow("orig");
  imshow("orig", img);
  int tb_val = 0;
  createTrackbar("", "orig", &tb_val, 100, toolbar, &img);
  imshow("new", img_mod);
  moveWindow("new", 100, 100);
  waitKey(0);
}