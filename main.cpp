
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPointF>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

struct MyCircle {
  double m_x;
  double m_y;
  double m_r;
  MyCircle(double x, double y, double r) : m_x{x}, m_y{y}, m_r{r} {}
};

double expectedDiameter = 15;
double diameterTolerance = expectedDiameter * 0.4;  // 允许20%的误差

double expectedRadius = 15 / 2.0;
double radiusTolerance = expectedRadius * 0.3;  // 允许20%的误差

float groupInterval_Y = 80.0f;  // 分组的y坐标间隔，需要根据具体数据调整
float maxDeviation_Y = 7.5f;  // 允许的最大y坐标偏差，需要根据具体数据调整

float groupInterval_X = 11.0f;  // 分组的x坐标间隔，需要根据具体数据调整

std::vector<MyCircle> allPoints;
std::vector<MyCircle> localtions;

void funcWay3(cv::Mat& binary, cv::Mat& colorImage);

std::vector<std::vector<MyCircle>> filterPointsByYDeviation(
    std::map<int, std::vector<MyCircle>>& groupedPoints, float maxDeviation) {
  std::vector<std::vector<MyCircle>> filteredGroups;
  for (auto& group : groupedPoints) {
    float sumY = 0;
    for (const auto& point : group.second) {
      sumY += point.m_y;
    }
    float averageY = sumY / group.second.size();

    std::vector<MyCircle> filteredGroup;
    for (const auto& point : group.second) {
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

std::map<int, std::vector<MyCircle>> groupPointsByY(
    const std::vector<MyCircle>& points, float groupInterval) {
  std::map<int, std::vector<MyCircle>> groupedPoints;
  for (const auto& point : points) {
    int key = static_cast<int>(point.m_y / groupInterval);
    groupedPoints[key].push_back(point);
  }
  return groupedPoints;
}

std::map<int, std::vector<MyCircle>> groupPointsByX(
    const std::vector<MyCircle>& points, float groupInterval);
std::vector<MyCircle> filterPointsByXDeviation(
    std::map<int, std::vector<MyCircle>>& groupedPoints);

void func(cv::Mat& src, int value) {  // 应用中值滤波
  cv::Mat dst;
  int kernelSize = 5;  // 核大小应该是一个正奇数
  cv::medianBlur(src, dst, kernelSize);

  // 将灰度图转换为BGR彩色图
  cv::Mat colorImage;
  cv::cvtColor(dst, colorImage, cv::COLOR_GRAY2BGR);

  cv::Mat thres1;
  cv::threshold(dst, thres1, value, 65535, cv::THRESH_BINARY);
  // cv::imshow("threshold", thres1);
  cv::imwrite("D://test.png", thres1);

  // 将16位图像转换为8位
  cv::Mat binary;
  double minVal, maxVal;
  // 查找图像的最小和最大像素值
  cv::minMaxIdx(src, &minVal, &maxVal);
  thres1.convertTo(binary, CV_8U, 255.0 / (maxVal - minVal),
                   -minVal * 255.0 / (maxVal - minVal));

  // cv::imshow("binary", binary);
  funcWay3(binary, colorImage);

  // 显示图片
  // cv::imshow("Circles Detected", colorImage);
  // cv::waitKey(0);
}

void paintImg(const QString& pic, vector<MyCircle>& points) {
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
  pix.save("E:\\program\\OpenCVTest\\debug\\img\\r4_2.tif");
}

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  // 读取16位灰度图像
  cv::Mat src = cv::imread("E:\\program\\OpenCVTest\\debug\\img\\RawImage.tif",
                           cv::IMREAD_UNCHANGED);

  // 检查图像是否成功读取
  if (src.empty()) {
    std::cout << "Could not read the image" << std::endl;
    return 1;
  }

  std::vector<MyCircle> allPoints_H;

  std::vector<MyCircle> allPoints_M;

  std::vector<MyCircle> allPoints_L;

  func(src, 30000);
  func(src, 20000);
  func(src, 19000);
  func(src, 18000);
  func(src, 17000);
  func(src, 16000);
  func(src, 15000);
  func(src, 14000);
  func(src, 13000);
  func(src, 11000);
  func(src, 11000);
  func(src, 10000);

  for (auto x : allPoints) allPoints_H.push_back(x);
  allPoints.clear();

  func(src, 9500);
  func(src, 9000);
  func(src, 8500);
  func(src, 8000);
  func(src, 7500);
  func(src, 7000);
  func(src, 6500);
  func(src, 6000);
  func(src, 5500);
  func(src, 5000);
  func(src, 4500);
  func(src, 4000);
  func(src, 3500);
  func(src, 3000);
  for (auto x : allPoints) allPoints_M.push_back(x);
  allPoints.clear();

  func(src, 2900);
  func(src, 2500);
  func(src, 2100);
  func(src, 2000);
  func(src, 1600);
  func(src, 1000);
  func(src, 900);
  func(src, 800);
  func(src, 700);
  func(src, 600);
  func(src, 500);
  // func(src, 400);
  // func(src, 300);
  for (auto x : allPoints) allPoints_L.push_back(x);
  allPoints.clear();

  auto HP = groupPointsByY(allPoints_H, groupInterval_Y);
  auto FHG = filterPointsByYDeviation(HP, maxDeviation_Y);
  auto MP = groupPointsByY(allPoints_M, groupInterval_Y);
  auto FM = filterPointsByYDeviation(MP, maxDeviation_Y);
  auto LP = groupPointsByY(allPoints_L, groupInterval_Y);
  auto FL = filterPointsByYDeviation(LP, maxDeviation_Y);

  for (auto x : FHG)
    for (auto y : x) allPoints.push_back(y);
  for (auto x : FM)
    for (auto y : x) allPoints.push_back(y);
  for (auto x : FL)
    for (auto y : x) allPoints.push_back(y);

  // func(src, 7500);
  // func(src, 7200);
  // func(src, 6900);
  // func(src, 6600);
  // func(src, 6300);
  // func(src, 2500);

  // func(src, 700);
  // func(src, 500);

  auto PointT = groupPointsByY(allPoints, groupInterval_Y);
  auto filteredGroups = filterPointsByYDeviation(PointT, maxDeviation_Y);

  std::vector<MyCircle> filter;
  for (auto x : filteredGroups) {
    std::vector<MyCircle> temp;
    for (auto y : x) temp.push_back(y);
    auto groupedXPoints = groupPointsByX(temp, groupInterval_X);
    auto points = filterPointsByXDeviation(groupedXPoints);
    for (auto z : points) filter.push_back(z);
  }

  paintImg("D://test.png", filter);

  // for (auto x : allPoints) {
  //   cout << "X: " << x.m_x << " Y: " << x.m_y << endl;
  // }

  return 0;
}

void funcWay3(cv::Mat& binary, cv::Mat& colorImage) {
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
    if (dy > 80 && dy < 100) {
      MyCircle f(cvRound(circles[i][0]), cvRound(circles[i][1]), radius);
      localtions.push_back(f);

    } else if (dy > 160 && dy < 180) {
      MyCircle f(cvRound(circles[i][0]), cvRound(circles[i][1]), radius);
      localtions.push_back(f);

    } else if (dy > 330 && dy < 350) {
      MyCircle f(cvRound(circles[i][0]), cvRound(circles[i][1]), radius);
      localtions.push_back(f);

    } else if (dy > 410 && dy < 440) {
      MyCircle f(cvRound(circles[i][0]), cvRound(circles[i][1]), radius);
      localtions.push_back(f);
    } else {
      cv::circle(colorImage, center, radius, cv::Scalar(0, 0, 65535), 2, 8, 0);
      MyCircle f(cvRound(circles[i][0]), cvRound(circles[i][1]), radius);
      allPoints.push_back(f);
    }
  }
}

std::map<int, std::vector<MyCircle>> groupPointsByX(
    const std::vector<MyCircle>& points, float groupInterval) {
  std::map<int, std::vector<MyCircle>> groupedPoints;
  for (const auto& point : points) {
    int key = static_cast<int>(point.m_x / groupInterval);
    groupedPoints[key].push_back(point);
  }

  while (groupedPoints.size() > 24) {
    groupedPoints.clear();
    groupInterval += 0.25;
    for (const auto& point : points) {
      int key = static_cast<int>(point.m_x / groupInterval);
      groupedPoints[key].push_back(point);
    }
  }

  return groupedPoints;
}

std::vector<MyCircle> filterPointsByXDeviation(
    std::map<int, std::vector<MyCircle>>& groupedPoints) {
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
