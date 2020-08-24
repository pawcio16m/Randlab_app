#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>

#include "Rectangle.h"

void Rectangle::drawMeInPict(cv::Mat& pict)
{
  cv::rectangle(pict, m_p1, m_p2, cv::Scalar(0));
}
