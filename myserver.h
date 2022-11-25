#ifndef MYSERVER
#define MYSERVER

#include <QTcpServer>
#include <QSqlQuery>


class myserver : public QTcpServer
{
    Q_OBJECT
public:
    myserver();
    ~myserver();

    void run();

    void sent_to_client(QByteArray &);

private:
    QTcpServer *server;

public slots:
    void newconnect();
    void by_thread(QString);
    void get_login_pass(QString login,QString pass);
    void simp_slot();
    void reg_check(QString,QString);
    void vector_del_list_slot(QString);
    void add_strings_slot(QString,QString,QString);

signals:
    void sent_to_textbrowser(QString str);
    void sent_login_pass(QString,QString);
    void sent_to_client_query(QByteArray &);
    void simp_signal();
    void reg_login_password(QString,QString);
    void del_signal(QString);
    void add_strings_signal(QString,QString,QString);

};

#endif // MYSERVER
