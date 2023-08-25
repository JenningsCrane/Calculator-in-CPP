#include <QApplication>
#include <memory>

#include "mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  jen::CalcModel calcModel;
  jen::CalcController calcController(&calcModel);
  jen::MainWindow w(&calcController);
  w.show();
  w.setFixedSize(722, 322);
  return a.exec();
}
