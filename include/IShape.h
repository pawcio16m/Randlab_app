#pragma once

namespace cv
{
  class Mat;
}

struct IShape
{
  IShape() = default;
  virtual ~IShape() = default;
  virtual void drawMeInPict(cv::Mat&) = 0;
};
