#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include "myserver.h"
#include <QTime>
#include <QTextStream>
#include <QSqlDatabase>
#include "connect_db.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString get_time_and_text(QString str);


private:
    Ui::MainWindow *ui;
   myserver *server;
   connect_db *m_connect_db;
   QSqlDatabase db;
   QTime time;
   QByteArray data;


public slots:
   void start_bot_click();
   void stop_bot_click();
   void by_server(QString str);
   void db_bot_click();
   void is_open_db(bool);
   void get_login_pass(QString,QString);
   void simp_slot();
   void reg_login_pass(QString,QString);
   void del_slot(QString);
   void add_strings_slot(QString,QString,QString);

};


#endif // MAINWINDOW_H
