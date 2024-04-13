#ifndef OPENCVTEST_H
#define OPENCVTEST_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class OpenCVTest;
}
QT_END_NAMESPACE

class OpenCVTest : public QMainWindow {
  Q_OBJECT

 public:
  OpenCVTest(QWidget *parent = nullptr);
  ~OpenCVTest();

 public:
  void test();

 private:
  Ui::OpenCVTest *ui;
};
#endif  // OPENCVTEST_H
