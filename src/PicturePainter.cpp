#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#include "PicturePainter.h"
#include "Rectangle.h"
#include "Triangle.h"

const std::string JPEG_EXTENSION = ".jpeg";

PicturePainter::PicturePainter()
{

}

PicturePainter::~PicturePainter()
{
  for (auto shape : m_shapes)
  {
    delete shape;
  }
}

void PicturePainter::setWidth(unsigned int width)
{
	std::cout << "Setting width = " << width << std::endl;
	m_width = width;
}

void PicturePainter::setHeight(unsigned int height)
{
	std::cout << "Setting height = " << height << std::endl;
	m_height = height;
}

void PicturePainter::drawRectangle(Point rectPnt, unsigned int width, unsigned int height)
{
	std::cout << "Setting RectCoor(" << rectPnt.x << "," << rectPnt.y << ") with width = " << width << " and height = " << height << std::endl;

	if (rectPnt.x + width > m_width)
	{
	  std::cout << "ERROR Cannot draw rectangle because Rect.x(" << rectPnt.x << ") + width(" << width << ") is higher then picture width(" << m_width << ").\n";
	  return;
	}
  if (rectPnt.y + height > m_height)
  {
    std::cout << "ERROR Cannot draw rectangle because Rect.y(" << rectPnt.y << ") + height(" << height << ") is higher then picture height(" << m_height << ").\n";
    return;
  }
  m_shapes.push_back(new Rectangle(cv::Point(rectPnt.x, rectPnt.y), cv::Point(rectPnt.x + width, rectPnt.y + height)));
}

void PicturePainter::drawTriangle(Point corr1, Point corr2, Point corr3)
{
	std::cout << "Setting TringCoor1(" << corr1.x << "," << corr1.y << "),\nTringCoor2(" << corr2.x << "," << corr2.y << "),\nTringCoor3(" << corr3.x << "," << corr3.y << ")\n";
  if (corr1.x > m_width or corr2.y > m_height)
  {
    std::cout << "[PICTURE_PAINTER] ERROR Cannot draw triangle because Coor1(" << corr1.x << ", " << corr1.y << ") is within of picture size(" << m_width << ", " << m_height << ").\n";
    return;
  }
  if (corr2.x > m_width or corr2.y > m_height)
  {
    std::cout << "[PICTURE_PAINTER] ERROR Cannot draw triangle because Coor2(" << corr2.x << ", " << corr2.y << ") is within of picture size(" << m_width << ", " << m_height << ").\n";
    return;
  }
  if (corr3.x > m_width or corr3.y > m_height)
  {
    std::cout << "[PICTURE_PAINTER] ERROR Cannot draw triangle because Coor1(" << corr3.x << ", " << corr3.y << ") is within of picture size(" << m_width << ", " << m_height << ").\n";
    return;
  }

  m_shapes.push_back(new Triangle(cv::Point(corr1.x, corr1.y), cv::Point(corr2.x, corr2.y), cv::Point(corr3.x, corr3.y)));
}

void PicturePainter::saveFile(std::string filename)
{
	std::cout << "[PICTURE_PAINTER] Saving file " << filename << std::endl;
  std::vector<int> compressionPparams;
  compressionPparams.push_back(cv::IMWRITE_JPEG_QUALITY);
  cv::Mat picture(m_height, m_width, CV_8UC1, cv::Scalar(255));

  drawShapesInPicture(picture);

	cv::imwrite(filename + JPEG_EXTENSION, picture, compressionPparams);
  cv::imshow( "Created image", picture);

  cv::waitKey(0);
}

void PicturePainter::drawShapesInPicture(cv::Mat& pict)
{
  for (auto& shape : m_shapes)
  {
    shape->drawMeInPict(pict);
  }
}
