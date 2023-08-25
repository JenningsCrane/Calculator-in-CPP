#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QWidget>

QT_BEGIN_NAMESPACE

#define LEN_MASS 10000
#define MIN_X -16
#define MAX_X 16
#define MIN_Y -1
#define MAX_Y 1

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

#include "calcController.h"

namespace jen {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(CalcController* c, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void SetFunction();
  void SetSymb();
  void SetDot();
  void ClearResult();
  void ComputeResult();
  void AddGraph();
  void ClearGraph();

 private:
  CalcController *controller;
  Ui::MainWindow *ui;
};
}  // namespace jen
#endif  // MAINWINDOW_H
