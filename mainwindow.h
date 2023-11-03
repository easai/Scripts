#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scriptlist.h"
#include "config.h"
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

private slots:
    void updateItem();
    void createItem();
    void about();

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_db;
    ScriptList m_list;
    QStringList m_header;
    Config m_config;

    void setTable();
};
#endif // MAINWINDOW_H
