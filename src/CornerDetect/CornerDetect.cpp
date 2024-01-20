#include "DetectCorner.h"
#include <unordered_map>
CornerDetect::CornerDetect (){}
CornerDetect::~CornerDetect() {}





/// @brief 根据角度值，给出标准角轮廓
/// @param _degree 输入角度 定义范围0-180
/// @param _corner_contours 输出角度对应的角轮廓 
/// @return 
bool createModel(int _degree,std::vector<cv::Point> &_corner_contours) {
  _corner_contours.clear();

  bool show = false; // true,false
  if (_degree < 0 || _degree>180) {
    return false;
  }
  for (size_t i = 99; i > 0; i--) {
    _corner_contours.push_back(cv::Point(100, 100+i));
  }

  // 画角线
  double angle = 90 - _degree;
  double angle_rad = angle * CV_PI / 180.0;
  for (size_t i = 0; i < 100; i++) {
    int y=tan(angle_rad) * i;
    _corner_contours.push_back(cv::Point(100+i, 100+y));
  }

  if (show) {
    // 创建一个黑色图像
    cv::Mat image = cv::Mat::zeros(200, 200, CV_8UC3);
    for (auto p : _corner_contours) {
      cv::circle(image, p, 1, cv::Scalar(255), -1, 8);
    }
    // 显示结果
     cv::imshow("30 Degree Line", image);
     cv::waitKey();
  }

  return true;
}

    // 计算两点之间的法向量
cv::Point2f computeNormalVector(const cv::Point2f &point1,
                                const cv::Point2f &point2) {
  // 计算方向向量
  cv::Point2f directionVector = point2 - point1;

  // 计算法向量（顺时针旋转90度）
  cv::Point2f normalVector(-directionVector.y, directionVector.x);

  // 归一化法向量
  float length = std::sqrt(normalVector.x * normalVector.x +
                           normalVector.y * normalVector.y);
  normalVector.x /= length;
  normalVector.y /= length;

  return normalVector;
}



// 计算两点之间的Freeman编码
int computeFreemanCode(const cv::Point &p1, const cv::Point &p2) {
  /*         8链码
  *             2
  *         3       1
  *     4               0
  *         5       7
  *             8
  * 
  * 
  */

  int dx = p2.x - p1.x;
  int dy = p2.y - p1.y;

  if (dx == 0 && dy == -1)
    return 0;
  if (dx == 1 && dy == -1)
    return 1;
  if (dx == 1 && dy == 0)
    return 2;
  if (dx == 1 && dy == 1)
    return 
