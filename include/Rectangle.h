#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>

#include "IShape.h"

class Rectangle : public IShape
{
public:
    Rectangle(cv::Point p1, cv::Point p2)
    : m_p1(p1),
      m_p2(p2)
    {}
    virtual ~Rectangle() = default;
    void drawMeInPict(cv::Mat&) override;

private:
    cv::Point m_p1;
    cv::Point m_p2;
};
