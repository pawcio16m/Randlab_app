#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>

#include "Triangle.h"

void Triangle::drawMeInPict(cv::Mat& pict)
{
  cv::line(pict, m_p1, m_p2, cv::Scalar(0));
  cv::line(pict, m_p2, m_p3, cv::Scalar(0));
  cv::line(pict, m_p3, m_p1, cv::Scalar(0));
}
