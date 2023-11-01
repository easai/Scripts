#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scriptlist.h"
#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_db;
    ScriptList m_list;

    void setTable();
};
#endif // MAINWINDOW_H
