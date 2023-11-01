#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_db = QSqlDatabase::addDatabase("QODBC", "linguistics");
  m_db.setDatabaseName("linguistics");
  connect(ui->action_Quit, &QAction::triggered, this, &QApplication::quit);
  setTable();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setTable()
{
  int nItems = m_list.retrieve(&m_db);
  ui->tableWidget->setRowCount(0);
  if (nItems <= 0) {
      return;
  }
//  std::sort(keyList.begin(), keyList.end());

  QStringList header;
  header << "en"
         << "ja";

  ui->tableWidget->setColumnCount(header.count());
  ui->tableWidget->setHorizontalHeaderLabels(header);
  ui->tableWidget->verticalHeader()->setVisible(false);

  QList<Script> lst=m_list.list();
  for (int i = 0; i < lst.count(); i++) {
      Script item=lst.at(i);

      ui->tableWidget->insertRow(i);
      QTableWidgetItem *targetItem =
          new QTableWidgetItem(item.en());
      ui->tableWidget->setItem(i, 0, targetItem);
      QTableWidgetItem *descItem = new QTableWidgetItem(item.ja());
      ui->tableWidget->setItem(i, 1, descItem);
  }
}
