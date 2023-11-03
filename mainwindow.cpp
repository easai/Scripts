#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"

#include <QDebug>
#include <QInputDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowIcon(QIcon("://images/favicon.ico"));
  m_db = QSqlDatabase::addDatabase("QODBC", "linguistics");
  m_db.setDatabaseName("linguistics");
  connect(ui->action_About, &QAction::triggered, this, &MainWindow::about);
  connect(ui->action_Quit, &QAction::triggered, this, &QApplication::quit);
  m_header << "id"
           << "en"
           << "ja"
           << "commentary";
  setTable();
  connect(ui->tableWidget, &QTableWidget::cellChanged, this,
          &MainWindow::updateItem);
  connect(ui->pushButton_add, &QPushButton::clicked, this,
          &MainWindow::createItem);
  m_config.load();
  restoreGeometry(m_config.geometry());
}

MainWindow::~MainWindow() {
  m_config.setGeometry(saveGeometry());
  m_config.save();
  delete ui;
}

void MainWindow::setTable() {
  int nItems = m_list.retrieve(&m_db);
  ui->tableWidget->setRowCount(0);
  if (nItems <= 0) {
    return;
  }
  m_list.sort();
  ui->tableWidget->setColumnCount(m_header.count());
  ui->tableWidget->setHorizontalHeaderLabels(m_header);
  ui->tableWidget->horizontalHeader()->hideSection(0);
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
      3, QHeaderView::Stretch);
  ui->tableWidget->verticalHeader()->setVisible(false);

  QList<Script> lst = m_list.list();
  for (int i = 0; i < lst.count(); i++) {
    Script item = lst.at(i);

    ui->tableWidget->insertRow(i);

    int cnt = 0;
    QTableWidgetItem *idItem =
        new QTableWidgetItem(QVariant(item.id()).toString());
    ui->tableWidget->setItem(i, cnt, idItem);
    idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);

    QTableWidgetItem *targetItem = new QTableWidgetItem(item.en());
    ui->tableWidget->setItem(i, ++cnt, targetItem);

    QTableWidgetItem *descItem = new QTableWidgetItem(item.ja());
    ui->tableWidget->setItem(i, ++cnt, descItem);

    QTableWidgetItem *commentaryItem = new QTableWidgetItem(item.commentary());
    ui->tableWidget->setItem(i, ++cnt, commentaryItem);
  }
}

void MainWindow::updateItem() {
  QList<QTableWidgetItem *> lst = ui->tableWidget->selectedItems();
  for (QTableWidgetItem *pItem : lst) {
    QString exp = pItem->text();
    int row = pItem->row();
    int col = pItem->column();
    QTableWidgetItem *pId = ui->tableWidget->item(row, 0);
    int id = pId->text().toInt();
    QString field = m_header.at(col);
    m_list.updateItem(&m_db, exp, field, id);
  }
}

void MainWindow::createItem() {
  bool ok;
  QString exp = QInputDialog::getText(this, tr("Add new script"), tr("en"),
                                      QLineEdit::Normal, "", &ok);
  if (ok) {
    m_list.createItem(&m_db, exp, "en");
    setTable();
  }
}

void MainWindow::about() {
  AboutDialog *dlg = new AboutDialog(this);
  dlg->exec();
}
