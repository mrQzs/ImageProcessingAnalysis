#include "OpenCVTest.h"

#include <iostream>
#include <opencv2/opencv.hpp>

#include "ui_OpenCVTest.h"

using namespace std;
using namespace cv;

OpenCVTest::OpenCVTest(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::OpenCVTest) {
  ui->setupUi(this);
}

OpenCVTest::~OpenCVTest() { delete ui; }

void OpenCVTest::test() {
    namedWindow();
  Mat in_image, out_image;
  in_image = imread("E:\\test.png", IMREAD_UNCHANGED);
  imshow();
  cvtColor(in_image,out_image,);
}
