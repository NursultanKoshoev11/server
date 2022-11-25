#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QSqlQuery>

class mythread : public QThread
{
    Q_OBJECT
public:
    mythread(QTcpSocket*);
    ~mythread();
    void run();

private:
    QTcpSocket *socket;
    QByteArray data;
    qint16 sizeblock = 0;
    QString login,password;

public slots:
    void read_client();
    void sent_to_client(QByteArray&);

signals:
    void sent_to_server(QString);
    void sent_login_pass(QString login,QString pass);
    void simp_signal();
    void reg_login_pass(QString,QString);
    void vector_del_list(QString);
    void add_strings(QString,QString,QString);
};

#endif // MYTHREAD_H
