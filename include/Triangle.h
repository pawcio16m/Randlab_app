#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>

#include "IShape.h"

class Triangle : public IShape
{
public:
    Triangle(cv::Point p1, cv::Point p2, cv::Point p3)
    : m_p1(p1),
      m_p2(p2),
      m_p3(p3)
    {}
    virtual ~Triangle() = default;
    void drawMeInPict(cv::Mat&) override;

private:
    cv::Point m_p1;
    cv::Point m_p2;
    cv::Point m_p3;
};
