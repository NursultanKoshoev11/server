#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connect_db.h"
#include <QSqlQuery>
#include <QSqlDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new myserver;


    connect(ui->start_button,SIGNAL(clicked(bool)),this,SLOT(start_bot_click()));
    connect(ui->stop_button,SIGNAL(clicked(bool)),this,SLOT(stop_bot_click()));
    connect(server,SIGNAL(sent_to_textbrowser(QString)),this,SLOT(by_server(QString)));
    connect(ui->db_button,SIGNAL(clicked(bool)),this,SLOT(db_bot_click()));
    connect(server,SIGNAL(sent_login_pass(QString,QString)),this,SLOT(get_login_pass(QString,QString)));
    connect(server,SIGNAL(simp_signal()),this,SLOT(simp_slot()));
    connect(server,SIGNAL(reg_login_password(QString,QString)),this,SLOT(reg_login_pass(QString,QString)));
    connect(server,SIGNAL(del_signal(QString)),this,SLOT(del_slot(QString)));
    connect(server,SIGNAL(add_strings_signal(QString,QString,QString)),this,SLOT(add_strings_slot(QString,QString,QString)));
}


void MainWindow::start_bot_click(){
    by_server("Starts!");
    server->run();

}

void MainWindow::stop_bot_click(){
    server->deleteLater();
    by_server("Server stop!");
}

QString MainWindow::get_time_and_text(QString str){

    time = QTime::currentTime();
    QString s;
    s.append("[ ");
    s.append(time.toString("hh:mm:ss"));
    s.append(" ] ");
    s.append(str);

    return s;
}


void MainWindow::db_bot_click(){
    m_connect_db = new connect_db();
    connect(m_connect_db,SIGNAL(is_open_signal(bool)),this,SLOT(is_open_db(bool)));
    m_connect_db->show();
}


void MainWindow::by_server(QString str){
    ui->textBrowser->append(get_time_and_text(str));
}


void MainWindow::is_open_db(bool open){
    if(open){
        by_server("База данных подключен!");
    }
    else {
        by_server("База данных не подключен!");
    }
}

void MainWindow::get_login_pass(QString login,QString pass){
    db = m_connect_db->get_db();
    if(db.open()){
        QSqlQuery *query = new QSqlQuery(db);
        query->exec("select * from Пользователи where Пользователи = '"+login+"' and Пароль = '"+pass+"'");

        while (query->next()) {
            if(query->value(0).toString()==login && query->value(1).toString()==pass){
                ui->textBrowser->append(get_time_and_text("Client login = "+login+" success enter!"));
                data.clear();
                QString access = query->value(2).toString();
                QString h = "ok";
                QDataStream out(&data,QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_6_3);
                out<<qint16(0)<<h<<access;
                out.device()->seek(0);
                out<<qint16(data.size()-sizeof(qint16));
                server->sent_to_client(data);
            }
            else {
                ui->textBrowser->append(get_time_and_text("Client login = "+login+" no success enter!"));
                data.clear();
                QString h = "no";
                QDataStream out(&data,QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_6_3);
                out<<qint16(0)<<h;
                out.device()->seek(0);
                out<<qint16(data.size()-sizeof(qint16));
                server->sent_to_client(data);
            }
        }

        db.close();
    }
    else {

    }
}


void MainWindow::simp_slot(){
    if(db.open()){
        QSqlQuery *query = new QSqlQuery(db);
        QDataStream out(&data,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_3);
        data.clear();
        out<<qint16(0);
        query->exec("select * from Товар");
        while(query->next()){
            QString s1,s2,s3;
            s1 = query->value(0).toString();
            s2 = query->value(1).toString();
            s3 = query->value(2).toString();
            out<<s1<<s2<<s3;
        }
        out.device()->seek(0);
        out<<qint16(data.size()-sizeof(qint16));
        server->sent_to_client(data);
        db.close();
    }
    else {
        qDebug()<<"db not open!";
    }
}

void MainWindow::reg_login_pass(QString login,QString pass){
    if(db.open()){
      QSqlQuery *q = new QSqlQuery(db);
      q->exec("select count(*) from Пользователи where Пользователи = '"+login+"'");
      QString s;
      while(q->next()){
          qDebug()<<q->value(0).toInt();
          if(q->value(0).toInt() >0 && login!=""){
                s = "reg_no_success";
          }
          else {
                s = "reg_success";
                q->exec("insert into Пользователи (Пользователи,Пароль,[Уровень доступа]) values ('"+login+"','"+pass+"','READ')");
          }
      }
      if(s == "reg_success"){
          by_server("Клиент login = "+login+" успешно зарегистрирован!");
      }

      data.clear();
      QDataStream out(&data,QIODevice::WriteOnly);
      out.setVersion(QDataStream::Qt_6_3);
      out<<qint16(0)<<s;
      out.device()->seek(0);
      out<<qint16(data.size()-sizeof(qint16));
      server->sent_to_client(data);
      db.close();
    }

}


void MainWindow::del_slot(QString tmp){
    if(db.open()){
        QSqlQuery *q = new QSqlQuery(db);
        q->exec("delete from Товар where [Номер товара] = "+tmp);
        simp_slot();
        db.close();
    }
    else{
        qDebug()<<"бд не открыт!";
    }
}

void MainWindow::add_strings_slot(QString number,QString name,QString count){
    if(db.open()){
        QSqlQuery *q = new QSqlQuery(db);
        q->exec("insert into Товар ([Номер товара],[Название товара],[Количество товара]) values ("+number+",'"+name+"',"+count+")");
        simp_slot();
        db.close();
    }
    else{
        qDebug()<<"db not open!";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

