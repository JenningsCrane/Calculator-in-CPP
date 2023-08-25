#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace jen {

MainWindow::MainWindow(CalcController *c, QWidget *parent)
    : QMainWindow(parent), controller(c), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->graphic->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  ui->lineEdit_x->setToolTip("Введите значение X в радианах");

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_clean, SIGNAL(clicked()), this, SLOT(ClearResult()));
  connect(ui->pushButton_clear_all, SIGNAL(clicked()), this,
          SLOT(ClearResult()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(SetDot()));
  connect(ui->pushButton_open_skoba, SIGNAL(clicked()), this, SLOT(SetSymb()));
  connect(ui->pushButton_closed_skoba, SIGNAL(clicked()), this,
          SLOT(SetSymb()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(ComputeResult()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(SetFunction()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(AddGraph()));
  connect(ui->pushButton_graph_clear, SIGNAL(clicked()), this,
          SLOT(ClearGraph()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ClearGraph() {
  ui->graphic->clearPlottables();
  ui->graphic->replot();
}

void MainWindow::AddGraph() {
  QList<double> mass_x(LEN_MASS);
  QList<double> mass_y(LEN_MASS);

  double step = (fabs(MIN_X) + MAX_X) / LEN_MASS;

  for (int i = 0; i < LEN_MASS; i++) {
    mass_x[i] = MIN_X + i * step;
  }

  int len_label = ui->result->text().size();
  char *str = new char(len_label);

  QByteArray arr = ui->result->text().toUtf8();

  strncpy(str, arr, len_label + 1);
  try {
    controller->CalculationGraph(str, mass_x.data(), mass_y.data(), LEN_MASS);
  } catch (...) {
    QMessageBox::critical(this, "ОШИБКА", "SegMANtation fault");
  }
  ui->graphic->addGraph();
  ui->graphic->graph(0)->setData(mass_x, mass_y);
  ui->graphic->xAxis->setLabel("x");
  ui->graphic->yAxis->setLabel("y");
  ui->graphic->xAxis->setRange(ui->lineEdit_x_min->text().toDouble(),
                               ui->lineEdit_x_max->text().toDouble());
  ui->graphic->yAxis->setRange(ui->lineEdit_y_min->text().toDouble(),
                               ui->lineEdit_y_max->text().toDouble());
  ui->graphic->replot();
}

void MainWindow::ClearResult() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->result->text();

  if (button->text() == "⌫") {
    new_label.chop(1);
    if (new_label.isEmpty() || new_label == " ") new_label = " 0";
    ui->result->setText(new_label);
  } else if (button->text() == "AC") {
    ui->result->setText(" 0");
    ui->lineEdit_x->setText("0");
  }
}

void MainWindow::SetDot() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;

  if (ui->result->text() == " 0")
    new_label = button->text();
  else
    new_label = ui->result->text() + '.';
  ui->result->setText(new_label);
}

void MainWindow::SetSymb() {
  QPushButton *button = (QPushButton *)sender();

  QString new_label;

  if (ui->result->text() == " 0")
    new_label = button->text();
  else
    new_label = ui->result->text() + button->text();
  ui->result->setText(new_label);
}

void MainWindow::SetFunction() {
  QPushButton *button = (QPushButton *)sender();

  QString new_label;

  if (ui->result->text() == " 0") ui->result->setText("");

  if (button->text() == "xʸ")
    new_label = (ui->result->text() + '^');
  else if (button->text() == "X =")
    new_label = (ui->result->text() + "x");
  else if (button->text() == "e")
    new_label = (ui->result->text() + "e");
  else if (button->text() == "asin")
    new_label = (ui->result->text() + "asin(");
  else if (button->text() == "acos")
    new_label = (ui->result->text() + "acos(");
  else if (button->text() == "atan")
    new_label = (ui->result->text() + "atan(");
  else if (button->text() == "sin")
    new_label = (ui->result->text() + "sin(");
  else if (button->text() == "cos")
    new_label = (ui->result->text() + "cos(");
  else if (button->text() == "tan")
    new_label = (ui->result->text() + "tan(");
  else if (button->text() == "√")
    new_label = (ui->result->text() + "sqrt(");
  else if (button->text() == "mod")
    new_label = (ui->result->text() + '%');
  else if (button->text() == "ln")
    new_label = (ui->result->text() + "ln(");
  else if (button->text() == "log")
    new_label = (ui->result->text() + "log(");

  ui->result->setText(new_label);
}

void MainWindow::ComputeResult() {
  int len_label = ui->result->text().size();
  if (len_label >= 255) {
    QMessageBox::critical(
        this, "ОШИБКА",
        "Слишком много символов. Максимум должно быть 254 символа");
    return;
  }
  double num = 0.0;
  char *str = new char(len_label);

  QByteArray arr = ui->result->text().toUtf8();

  strncpy(str, arr, len_label + 1);

  bool ok = false;
  double x = ui->lineEdit_x->text().toDouble(&ok);
  if (!ok) {
    QMessageBox::critical(this, "ОШИБКА", "SegMANtation fault");
  } else {
    try {
      num = controller->ComputeExpression(str, x);
    } catch (...) {
      QMessageBox::critical(this, "ОШИБКА", "SegMANtation fault");
    }

    ui->result->setText(QString::number(num, 'g', 8));
  }

  delete str;
}
}  // namespace jen
