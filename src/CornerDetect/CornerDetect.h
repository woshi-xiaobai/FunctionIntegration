
#pragma once
#include <opencv2/opencv.hpp>

enum CornerDetectMethod { 
	Method_L1,// detectByHoughLines
	Method_L3,//detectByFitLines
	Method_L2,//detectByTriangle

};
class CornerDetect {
public:
  CornerDetect();
  ~CornerDetect();

   bool Detect(cv::Mat &_img, cv::Point2f &_point,
                     CornerDetectMethod _method = Method_L1);

private:

  /// @brief 通过轮廓计算法向量，提取法向量重合最大的两处拟合直线，计算交点
  /// @param _img 输入图像
  /// @param _point 输出结果点
  /// @return 
  bool detectByFitLines(cv::Mat &_img, cv::Point2f &_point);

  
  /// @brief 通过轮廓拟合三角形，查找顶点
  /// @param _img 输入图像
  /// @param _point 输出结果点
  /// @return 
  bool detectByTriangle(cv::Mat &_img, cv::Point2f &_point);

  
  /// @brief 轮廓配合HoughLines查找直线，计算交点
  /// @param _img 输入图像
  /// @param _point 输出结果点
  /// @return 
  bool detectByHoughLines(cv::Mat &_img, cv::Point2f &_point);

	//未成功函数
  bool detectBy(cv::Mat &_img, cv::Point2f &_point);
};


int detectCorner_test();
