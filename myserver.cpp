#include "myserver.h"
#include "mythread.h"

myserver::myserver(){}
myserver::~myserver(){}

void myserver::run(){
    server = new QTcpServer;
    connect(server,SIGNAL(newConnection()),this,SLOT(newconnect()));
    if(server->listen(QHostAddress::Any,2002)){
        emit sent_to_textbrowser("Listening...");
    }
    else {
        emit sent_to_textbrowser("NO Listening...");
    }
}

void myserver::newconnect(){
    mythread *mthread = new mythread(server->nextPendingConnection());
    connect(mthread,SIGNAL(sent_to_server(QString)),this,SLOT(by_thread(QString)));
    connect(mthread,SIGNAL(sent_login_pass(QString,QString)),this,SLOT(get_login_pass(QString,QString)));
    connect(this,SIGNAL(sent_to_client_query(QByteArray&)),mthread,SLOT(sent_to_client(QByteArray&)));
    connect(mthread,SIGNAL(simp_signal()),this,SLOT(simp_slot()));
    connect(mthread,SIGNAL(reg_login_pass(QString,QString)),this,SLOT(reg_check(QString,QString)));
    connect(mthread,SIGNAL(vector_del_list(QString)),this,SLOT(vector_del_list_slot(QString)));
    connect(mthread,SIGNAL(add_strings(QString,QString,QString)),this,SLOT(add_strings_slot(QString,QString,QString)));
    mthread->run();
}

void myserver::by_thread(QString str){
    emit sent_to_textbrowser(str);
}


void myserver::get_login_pass(QString login,QString pass){
    emit sent_login_pass(login,pass);
}


void myserver::sent_to_client(QByteArray &byte){
    emit sent_to_client_query(byte);
}

void myserver::simp_slot(){
    emit simp_signal();
}

void myserver::reg_check(QString login,QString pass){
    emit reg_login_password(login,pass);
}

void myserver::vector_del_list_slot(QString tmp){
    emit del_signal(tmp);
}

void myserver::add_strings_slot(QString number,QString name,QString count){
    emit add_strings_signal(number,name,count);
}
