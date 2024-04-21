#include "OpenCVHelper.h"

#include <QApplication>
#include <QPainter>
#include <QPixmap>
#include <algorithm>

using namespace std;
using namespace cv;

float groupInterval_Y = 80.0f;  // 分组的y坐标间隔，需要根据具体数据调整
float maxDeviation_Y = 7.5f;  // 允许的最大y坐标偏差，需要根据具体数据调整
float groupInterval_X = 11.0f;  // 分组的x坐标间隔，需要根据具体数据调整

std::vector<MyCircle> allPoints;
std::vector<MyCircle> localtions;

std::vector<MyCircle> points1;
std::vector<MyCircle> points2;
std::vector<MyCircle> points3;
std::vector<MyCircle> points4;
std::vector<MyCircle> points5;
std::vector<MyCircle> points6;

bool compareByY(const MyCircle &a, const MyCircle &b) { return a.m_y < b.m_y; }

OpenCVHelper &OpenCVHelper::getInstance() {
  static OpenCVHelper instance;
  return instance;
}

void OpenCVHelper::dealWithPic(cv::Mat &src, int value) {
  // 应用中值滤波
  cv::Mat dst;
  int kernelSize = 5;  // 核大小应该是一个正奇数
  cv::medianBlur(src, dst, kernelSize);

  // 将灰度图转换为BGR彩色图
  cv::Mat colorImage;
  cv::cvtColor(dst, colorImage, cv::COLOR_GRAY2BGR);

  cv::Mat thres1;
  cv::threshold(dst, thres1, value, 65535, cv::THRESH_BINARY);
  std::string resultPath =
      QString(QApplication::applicationDirPath() + "/img/restlt_1.tif")
          .toStdString();
  cv::imwrite(resultPath, thres1);

  // 将16位图像转换为8位
  cv::Mat binary;
  double minVal, maxVal;
  // 查找图像的最小和最大像素值
  cv::minMaxIdx(src, &minVal, &maxVal);
  thres1.convertTo(binary, CV_8U, 255.0 / (maxVal - minVal),
                   -minVal * 255.0 / (maxVal - minVal));

  categorizedPoints(binary, colorImage);

  for (auto p : allPoints) {
    cout << "AY: " << p.m_y << std::endl;
  }

  for (auto p : localtions) {
    cout << "LY: " << p.m_y << std::endl;
  }

  // 显示图片
  // cv::imshow("Circles Detected", colorImage);
  // cv::waitKey(0);
}

void OpenCVHelper::paintImg(const QString &pic, std::vector<MyCircle> &points) {
  QPixmap pix(pic);
  QPainter painter(&pix);
  QPen pen;
  pen.setWidthF(1.6);
  pen.setColor(QColor(230, 0, 0));

  painter.setPen(pen);
  double x, y, r;

  for (size_t i = 0; i < points.size(); ++i) {
    r = 10 * 2;
    x = points[i].m_x - 10;
    y = points[i].m_y - 10;
    painter.drawLine(QPointF(x, y), QPointF(x + r, y));
    painter.drawLine(QPointF(x, y), QPointF(x, y + r));
    painter.drawLine(QPointF(x, y + r), QPointF(x + r, y + r));
    painter.drawLine(QPointF(x + r, y), QPointF(x + r, y + r));
  }

  painter.end();
  QString savePath = QApplication::applicationDirPath() + "/img/result_2.tif";
  pix.save(savePath);
}

void OpenCVHelper::groupPointsByY(const std::vector<MyCircle> &points) {
  std::sort(localtions.begin(), localtions.end(), compareByY);
  auto d1yL = localtions[0].m_y - 55;
  auto d1yH = localtions[0].m_y - 30;
  auto d2yL = localtions[1].m_y - 55;
  auto d2yH = localtions[1].m_y - 30;
  auto d3yL = localtions[1].m_y + 30;
  auto d3yH = localtions[1].m_y + 55;
  auto d4yL = localtions[2].m_y - 55;
  auto d4yH = localtions[2].m_y - 30;
  auto d5yL = localtions[3].m_y - 55;
  auto d5yH = localtions[3].m_y - 30;
  auto d6yL = localtions[3].m_y + 30;
  auto d6yH = localtions[3].m_y + 55;

  // cout << "L: " << d1yL << " H: " << d1yH << endl;
  // cout << "L: " << d2yL << " H: " << d2yH << endl;
  // cout << "L: " << d3yL << " H: " << d3yH << endl;
  // cout << "L: " << d4yL << " H: " << d4yH << endl;
  // cout << "L: " << d5yL << " H: " << d5yH << endl;
  // cout << "L: " << d6yL << " H: " << d6yH << endl;

  for (auto p : points) {
    auto y = p.m_y;
    if (y >= d1yL && y <= d1yH) points1.push_back(p);
    if (y >= d2yL && y <= d2yH) points2.push_back(p);
    if (y >= d3yL && y <= d3yH) points3.push_back(p);
    if (y >= d4yL && y <= d4yH) points4.push_back(p);
    if (y >= d5yL && y <= d5yH) points5.push_back(p);
    if (y >= d6yL && y <= d6yH) points6.push_back(p);
  }
}

std::map<int, std::vector<MyCircle>> OpenCVHelper::groupPointsByY(
    const std::vector<MyCircle> &points, float groupInterval) {
  std::map<int, std::vector<MyCircle>> groupedPoints;
  for (const auto &point : points) {
    int key = static_cast<int>(point.m_y / groupInterval);
    groupedPoints[key].push_back(point);
  }
  return groupedPoints;
}

std::vector<std::vector<MyCircle>> OpenCVHelper::filterPointsByYDeviation(
    std::map<int, std::vector<MyCircle>> &groupedPoints, float maxDeviation) {
  std::vector<std::vector<MyCircle>> filteredGroups;
  for (auto &group : groupedPoints) {
    float sumY = 0;
    for (const auto &point : group.second) {
      sumY += point.m_y;
    }
    float averageY = sumY / group.second.size();

    std::vector<MyCircle> filteredGroup;
    for (const auto &point : group.second) {
      if (std::abs(point.m_y - averageY) <= maxDeviation) {
        filteredGroup.push_back(point);
      }
    }
    if (!filteredGroup.empty()) {
      filteredGroups.push_back(filteredGroup);
    }
  }
  return filteredGroups;
}

std::map<int, std::vector<MyCircle>> OpenCVHelper::groupPointsByX(
    const std::vector<MyCircle> &points, float groupInterval) {
  std::map<int, std::vector<MyCircle>> groupedPoints;
  for (const auto &point : points) {
    int key = static_cast<int>(point.m_x / groupInterval);
    groupedPoints[key].push_back(point);
  }

  while (groupedPoints.size() > 24) {
    groupedPoints.clear();
    groupInterval += 0.25;
    for (const auto &point : points) {
      int key = static_cast<int>(point.m_x / groupInterval);
      groupedPoints[key].push_back(point);
    }
  }

  return groupedPoints;
}

std::vector<MyCircle> OpenCVHelper::filterPointsByXDeviation(
    std::map<int, std::vector<MyCircle>> &groupedPoints) {
  std::vector<MyCircle> points;
  auto iter = groupedPoints.begin();
  for (; iter != groupedPoints.end(); ++iter) {
    auto vs = iter->second;
    double aveX = 0;
    double aveY = 0;
    double aveR = 0;
    for (size_t i = 0; i < vs.size(); ++i) {
      aveX += vs[i].m_x;
      aveY += vs[i].m_y;
      aveR += vs[i].m_r;
    }
    MyCircle f(aveX / vs.size(), aveY / vs.size(), aveR / vs.size());
    points.push_back(f);
  }
  return points;
}

void OpenCVHelper::categorizedPoints(cv::Mat &binary, cv::Mat &colorImage) {
  // 检测圆
  std::vector<cv::Vec3f> circles;
  cv::HoughCircles(binary, circles, cv::HOUGH_GRADIENT, 1, 15, 300, 5.3, 4, 17);

  // 绘制检测到的圆
  for (size_t i = 0; i < circles.size(); i++) {
    cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    int radius = cvRound(circles[i][2]);
    // 圆心
    // cv::circle(colorImage, center, 3, cv::Scalar(0, 65535, 0), -1, 8, 0);
    // 圆轮廓
    auto dy = center.y;
    if (dy > 82 && dy < 95) {
      MyCircle f(cvRound(circles[i][0]), cvRound(circles[i][1]), radius);
      localtions.push_back(f);

    } else if (dy > 160 && dy < 175) {
      MyCircle f(cvRound(circles[i][0]), cvRound(circles[i][1]), radius);
      localtions.push_back(f);

    } else if (dy > 330 && dy < 345) {
      MyCircle f(cvRound(circles[i][0]), cvRound(circles[i][1]), radius);
      localtions.push_back(f);

    } else if (dy > 410 && dy < 435) {
      MyCircle f(cvRound(circles[i][0]), cvRound(circles[i][1]), radius);
      localtions.push_back(f);
    } else {
      cv::circle(colorImage, center, radius, cv::Scalar(0, 0, 65535), 2, 8, 0);
      MyCircle f(cvRound(circles[i][0]), cvRound(circles[i][1]), radius);
      allPoints.push_back(f);
    }
  }
}

OpenCVHelper::OpenCVHelper() {}

OpenCVHelper::~OpenCVHelper() {}
