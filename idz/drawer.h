#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

const Scalar WORKING_LINE_COLOR(125,125,125); 
const Scalar FINAL_LINE_COLOR(255,255,255); 

struct PolygonDrawer {

  std::string window_name_;
  bool done_;
  cv::Point current_;
  std::vector<cv::Point> points_;
  std::shared_ptr<cv::Mat> imgPtr;

  // PolygonDrawer(const std::string &window_name, std::string &imgName){
  //   window_name_ = window_name;
  //   done_ = false;
  //   current_ = cv::Point(0, 0); // Current position, so we can draw the line-in-progress
  //   imgPtr.reset(new cv::Mat(cv::imread(imgName)));
  // }

    PolygonDrawer(const std::string &window_name, cv::Mat &img){
    window_name_ = window_name;
    done_ = false;
    current_ = cv::Point(0, 0); // Current position, so we can draw the line-in-progress
    imgPtr.reset(new cv::Mat(img));
  }

  static void onMouse( int event, int x, int y, int f, void* data ) {
    PolygonDrawer *curobj = reinterpret_cast<PolygonDrawer*>(data);
    if (curobj->done_)
      return;

    if(event == cv::EVENT_MOUSEMOVE)
      curobj->current_ = cv::Point(x, y);
    else if(event == cv::EVENT_LBUTTONDOWN) {
      curobj->points_.push_back(cv::Point(x, y));
    } 
    else if(event == cv::EVENT_RBUTTONDOWN) {
      curobj->done_ = true;
    }
  }

  std::vector<cv::Point> run() {
    // Let's create our working window and set a mouse callback to handle events
    cv::namedWindow(window_name_, cv::WINDOW_KEEPRATIO);
    cv::imshow(window_name_, *imgPtr);
    cv::waitKey(1);
    cv::setMouseCallback(window_name_, onMouse, this);
    while(!done_) {
      cv::Mat img;
      imgPtr->copyTo(img);
      if (points_.size() > 0){
        // Draw all the current polygon segments
        const cv::Point *pts = (const cv::Point*) cv::Mat(points_).data;
        int npts = cv::Mat(points_).rows;

        cv::polylines(img, &pts, &npts, 1, false, FINAL_LINE_COLOR);
        // And  also show what the current segment would look like
        cv::line(img, points_[points_.size()-1], current_, WORKING_LINE_COLOR, 1.0);
        // Update the window
      }
      cv::imshow(window_name_, img);
      // And wait 50ms before next iteration (this will pump window messages meanwhile)
      if(cv::waitKey(50) == 27)
        done_ = true;
    }
    const cv::Point *pts = (const cv::Point*) cv::Mat(points_).data;
    int npts = cv::Mat(points_).rows;

    // user finished entering the polygon points
    if (points_.size() > 0) {
      cv::imshow(window_name_, *imgPtr);
      //Waiting for the user to press any key
      cv::waitKey();
      cv::destroyWindow(window_name_);
    }
    
    return points_;
  }
};