
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPointF>
#include <vector>

#include "OpenCVHelper.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  std::string testPath =
      QString(QApplication::applicationDirPath() + "/img/RawImage.tif")
          .toStdString();

  std::cout << testPath << std::endl;

  // 读取16位灰度图像
  cv::Mat src = cv::imread(testPath, cv::IMREAD_UNCHANGED);

  // 检查图像是否成功读取
  if (src.empty()) {
    std::cout << "Could not read the image" << std::endl;
    return 1;
  }

  // OpenCVHelper::getInstance().dealWithPic(src, 30000);
  // OpenCVHelper::getInstance().dealWithPic(src, 20000);
  // OpenCVHelper::getInstance().dealWithPic(src, 19000);
  // OpenCVHelper::getInstance().dealWithPic(src, 18000);
  // OpenCVHelper::getInstance().dealWithPic(src, 17000);
  // OpenCVHelper::getInstance().dealWithPic(src, 16000);
  // OpenCVHelper::getInstance().dealWithPic(src, 15000);
  // OpenCVHelper::getInstance().dealWithPic(src, 14000);
  // OpenCVHelper::getInstance().dealWithPic(src, 13000);
  // OpenCVHelper::getInstance().dealWithPic(src, 11000);
  // OpenCVHelper::getInstance().dealWithPic(src, 11000);
  // OpenCVHelper::getInstance().dealWithPic(src, 10000);

  // OpenCVHelper::getInstance().dealWithPic(src, 9500);
  // OpenCVHelper::getInstance().dealWithPic(src, 9000);
  // OpenCVHelper::getInstance().dealWithPic(src, 8500);
  // OpenCVHelper::getInstance().dealWithPic(src, 8000);
  // OpenCVHelper::getInstance().dealWithPic(src, 7500);
  // OpenCVHelper::getInstance().dealWithPic(src, 7000);
  // OpenCVHelper::getInstance().dealWithPic(src, 6500);
  // OpenCVHelper::getInstance().dealWithPic(src, 6000);
  // OpenCVHelper::getInstance().dealWithPic(src, 5500);
  // OpenCVHelper::getInstance().dealWithPic(src, 5000);
  // OpenCVHelper::getInstance().dealWithPic(src, 4500);
  // OpenCVHelper::getInstance().dealWithPic(src, 4000);
  // OpenCVHelper::getInstance().dealWithPic(src, 3500);
  // OpenCVHelper::getInstance().dealWithPic(src, 3000);

  // OpenCVHelper::getInstance().dealWithPic(src, 2900);
  // OpenCVHelper::getInstance().dealWithPic(src, 2500);
  // OpenCVHelper::getInstance().dealWithPic(src, 2100);
  // OpenCVHelper::getInstance().dealWithPic(src, 2000);
  // OpenCVHelper::getInstance().dealWithPic(src, 1600);
  // OpenCVHelper::getInstance().dealWithPic(src, 1000);
  // OpenCVHelper::getInstance().dealWithPic(src, 900);
  // OpenCVHelper::getInstance().dealWithPic(src, 800);
  // OpenCVHelper::getInstance().dealWithPic(src, 700);
  // OpenCVHelper::getInstance().dealWithPic(src, 600);
  // OpenCVHelper::getInstance().dealWithPic(src, 500);

  OpenCVHelper::getInstance().dealWithPic(src, 500);

  // auto PointT =
  //     OpenCVHelper::getInstance().groupPointsByY(allPoints, groupInterval_Y);
  // auto filteredGroups = OpenCVHelper::getInstance().filterPointsByYDeviation(
  //     PointT, maxDeviation_Y);

  // std::vector<MyCircle> filter;
  // for (auto x : filteredGroups) {
  //   std::vector<MyCircle> temp;
  //   for (auto y : x) temp.push_back(y);
  //   auto groupedXPoints =
  //       OpenCVHelper::getInstance().groupPointsByX(temp, groupInterval_X);
  //   auto points =
  //       OpenCVHelper::getInstance().filterPointsByXDeviation(groupedXPoints);
  //   for (auto z : points) filter.push_back(z);
  // }

  OpenCVHelper::getInstance().groupPointsByY(allPoints);
  allPoints.clear();

  for (auto p : points1) allPoints.push_back(p);
  for (auto p : points2) allPoints.push_back(p);
  for (auto p : points3) allPoints.push_back(p);
  for (auto p : points4) allPoints.push_back(p);
  for (auto p : points5) allPoints.push_back(p);
  for (auto p : points6) allPoints.push_back(p);

  OpenCVHelper::getInstance().paintImg(
      QApplication::applicationDirPath() + "/img/restlt_1.tif", allPoints);

  return 0;
}
