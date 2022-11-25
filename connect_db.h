#ifndef CONNECT_DB_H
#define CONNECT_DB_H

#include <QWidget>
#include <QSqlDatabase>
#include <QThread>


class con_class : public QObject {
    Q_OBJECT
public:
    con_class();
    ~con_class();
    void connect_db_start(QSqlDatabase &db,QString server_name,QString db_name,QString user_name,QString password);

private:


public slots:

signals:
    void is_open(bool);


};


namespace Ui {
class connect_db;
}

class connect_db : public QWidget
{
    Q_OBJECT

public:
    explicit connect_db(QWidget *parent = nullptr);
    ~connect_db();
    QString server_name_str,db_name_str,user_name_str,password_str;
    QSqlDatabase &get_db(){
        return db;
    }

private:
    Ui::connect_db *ui;
    QSqlDatabase db;
    QThread *thread;
    QSqlQuery *query;


    con_class *connect_class;

public slots:
    void start_connect_click();
    void exit_bot_click();
    void is_open_db(bool);

signals:
    void is_open_signal(bool);
};




#endif // CONNECT_DB_H
