#pragma once

#include <string>
#include <vector>
#include <memory>

#include "opencv2/core/mat.hpp"

#include "IShape.h"
#include "Point.h"

class PicturePainter
{
public:
  PicturePainter() =default;
  virtual ~PicturePainter();

  void setWidth(unsigned int);
  void setHeight(unsigned int);
  void drawRectangle(Point, unsigned int, unsigned int);
  void drawTriangle(Point, Point, Point);
  void saveFile(std::string);

private:
  void drawShapesInPicture(cv::Mat&);

  unsigned int m_width{100};
  unsigned int m_height{200};
  std::vector<IShape*>  m_shapes;
};
