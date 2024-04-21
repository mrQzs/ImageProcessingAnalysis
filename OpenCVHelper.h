#ifndef OPENCVHELPER_H
#define OPENCVHELPER_H

#include <QString>
#include <opencv2/opencv.hpp>

struct MyCircle {
  double m_x;
  double m_y;
  double m_r;
  MyCircle(double x, double y, double r) : m_x{x}, m_y{y}, m_r{r} {}
};

extern std::vector<MyCircle> allPoints;
extern std::vector<MyCircle> localtions;

extern std::vector<MyCircle> points1;
extern std::vector<MyCircle> points2;
extern std::vector<MyCircle> points3;
extern std::vector<MyCircle> points4;
extern std::vector<MyCircle> points5;
extern std::vector<MyCircle> points6;

extern float groupInterval_Y;
extern float maxDeviation_Y;
extern float groupInterval_X;

class OpenCVHelper {
 public:
  static OpenCVHelper& getInstance();

 public:
  static void dealWithPic(cv::Mat& src, int value);

 public:
  static void paintImg(const QString& pic, std::vector<MyCircle>& points);

  static void groupPointsByY(const std::vector<MyCircle>& points);

  static std::map<int, std::vector<MyCircle>> groupPointsByY(
      const std::vector<MyCircle>& points, float groupInterval);

  static std::vector<std::vector<MyCircle>> filterPointsByYDeviation(
      std::map<int, std::vector<MyCircle>>& groupedPoints, float maxDeviation);

  static std::map<int, std::vector<MyCircle>> groupPointsByX(
      const std::vector<MyCircle>& points, float groupInterval);

  static std::vector<MyCircle> filterPointsByXDeviation(
      std::map<int, std::vector<MyCircle>>& groupedPoints);

 private:
  static void categorizedPoints(cv::Mat& binary, cv::Mat& colorImage);

 private:
 private:
  OpenCVHelper();
  ~OpenCVHelper();
  OpenCVHelper(const OpenCVHelper&) = delete;
  OpenCVHelper& operator=(const OpenCVHelper&) = delete;
};

#endif  // OPENCVHELPER_H
