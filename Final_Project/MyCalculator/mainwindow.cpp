#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QString>
#include <QToolTip>
#include <string>
#include <QKeyEvent>
#include <QShortcut>


using namespace std;

string text;
vector<string> calcu;
string history;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Factory::Register<Hash> reg_Hash("#");
    REGISTER(Add,"+")
    REGISTER(Sub,"-")
    REGISTER(Multiply,"*")
    REGISTER(Divide,"/")
    REGISTER(Equal,"=")
    REGISTER(Pow,"^")
    REGISTER(Mod,"%")
    REGISTER(Sin,"sin")
    REGISTER(Tan,"tan")
    REGISTER(Cos,"cos")
    REGISTER(Sqrt,"sqrt")
    REGISTER(Log,"log")
    REGISTER(Ln,"ln")
    REGISTER(Reciprocal,"rec")
    REGISTER(Factorial,"fact")
    REGISTER(Negative,"~")
    REGISTER(Left,"(")
    REGISTER(Right,")")


    setWindowTitle("My Calculator");
    setWindowIcon(QIcon(":/Resources/image.qrc/image/logo.ico"));

    connectSlots();
    setShortcutKeys();
    connect(ui->pushButton_nega,&QPushButton::clicked,this,&MainWindow::button_nega);
    connect(ui->pushButton_equal,&QPushButton::clicked,this,&MainWindow::button_equal);

    connect(ui->pushButton_rec,&QPushButton::clicked,this,&MainWindow::button_rec);
    connect(ui->pushButton_fac,&QPushButton::clicked,this,&MainWindow::button_fac);

    connect(ui->pushButton_AC,&QPushButton::clicked,this,&MainWindow::button_AC);
    connect(ui->pushButton_CE,&QPushButton::clicked,this,&MainWindow::button_CE);
    connect(ui->pushButton_back,&QPushButton::clicked,this,&MainWindow::button_back);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setShortcutKeys(){
            Qt::Key key[] = {
                Qt::Key_0,      Qt::Key_1,      Qt::Key_2,          Qt::Key_3,
                Qt::Key_4,      Qt::Key_5,      Qt::Key_6,          Qt::Key_7,
                Qt::Key_8,      Qt::Key_9,
                Qt::Key_Plus,   Qt::Key_Minus,  Qt::Key_Asterisk,   Qt::Key_Slash,
                Qt::Key_Enter,  Qt::Key_Period, Qt::Key_Backspace
            };

            QPushButton *btn[] = {
                ui->pushButton_0,ui->pushButton_1,ui->pushButton_2,ui->pushButton_3,
                ui->pushButton_4,ui->pushButton_5,ui->pushButton_6,ui->pushButton_7,
                ui->pushButton_8,ui->pushButton_9,
                ui->pushButton_add,ui->pushButton_sub,ui->pushButton_mul,ui->pushButton_div,
                ui->pushButton_equal,ui->pushButton_dot,ui->pushButton_back
            };

            for (int i = 0; i < 17; i++)
                btn[i]->setShortcut(QKeySequence(key[i]));

            QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Equal), this);
            connect(shortcut, &QShortcut::activated, ui->pushButton_equal, &QPushButton::click);
            ui->pushButton_AC->setShortcut(QKeySequence("Ctrl+Backspace"));
}

void MainWindow::connectSlots(){

    QPushButton *digiBtns[]={
        ui->pushButton_0,ui->pushButton_1,ui->pushButton_2,ui->pushButton_3,
        ui->pushButton_4,ui->pushButton_5,ui->pushButton_6,ui->pushButton_7,
        ui->pushButton_8,ui->pushButton_9,ui->pushButton_dot
    };

    for(auto btn:digiBtns){
        connect(btn,&QPushButton::clicked,this,&MainWindow::digitClicked);
    }

    QPushButton *operatorBtns[]={
        ui->pushButton_add,ui->pushButton_sub,ui->pushButton_mul,ui->pushButton_div,
        ui->pushButton_mod,ui->pushButton_pow,ui->pushButton_left,ui->pushButton_right,
        ui->pushButton_e,ui->pushButton_pi

    };

    for(auto btn:operatorBtns){
        connect(btn,&QPushButton::clicked,this,&MainWindow::operatorClicked);
    }



    QPushButton *funBtns[]={
        ui->pushButton_ln,ui->pushButton_log,ui->pushButton_sin,ui->pushButton_cos,
        ui->pushButton_tan
    };

    for(auto btn:funBtns){
        connect(btn,&QPushButton::clicked,this,&MainWindow::funClicked);
    }
}


void MainWindow::digitClicked(){
    QPushButton *digitBtn= static_cast<QPushButton*>(sender());
    QString t= digitBtn->text();
    text+=t.toStdString();
    ui->lineEdit_expr->setText(QString::fromStdString(text));
    if(calcu.size()>0){
        bool pr=0;
        for(size_t i=0;i<calcu[calcu.size()-1].size();i++){
            char a=calcu[calcu.size()-1][i];
            if(!((a>='0'&&a<='9')||a=='.'))pr=1;
        }
        if(pr==0)calcu[calcu.size()-1]+=t.toStdString();
        else calcu.push_back(t.toStdString());
    }
    else calcu.push_back(t.toStdString());
}



void MainWindow::operatorClicked(){
    QPushButton *oprBtn= qobject_cast<QPushButton*>(sender());
    QString t=oprBtn->text();
    text+=t.toStdString();
    ui->lineEdit_expr->setText(QString::fromStdString(text));
    calcu.push_back(t.toStdString());

}

void MainWindow::funClicked(){
    QPushButton *funBtn = qobject_cast<QPushButton*>(sender());
    QString t=funBtn->text();
    text+=t.toStdString();
    text+="(";
    ui->lineEdit_expr->setText(QString::fromStdString(text));
    calcu.push_back(t.toStdString());
    calcu.push_back("(");
}



void MainWindow::button_nega(){
    text+="-";
    calcu.push_back("~");
    ui->lineEdit_expr->setText(QString::fromStdString(text));
}

void MainWindow::button_rec(){
    text+="rec(";
    calcu.push_back("rec");
    calcu.push_back("(");
    ui->lineEdit_expr->setText(QString::fromStdString(text));
}

void MainWindow::button_fac(){
    text+="fact(";
    calcu.push_back("fact");
    calcu.push_back("(");
    ui->lineEdit_expr->setText(QString::fromStdString(text));
}

void MainWindow::button_equal(){
    //text+="=";

    QString c;
    calcu.push_back("=");
    double History;
    ui->lineEdit_expr->setText(QString::fromStdString(text));
    try {
       History=m_calcu.Do(calcu);
       ui->lineEdit_result->setText(QString::number(History));
       history=text;
       history+="=";
       history+=c.setNum(History).toStdString();
    }
    catch (string a) {
        ui->lineEdit_result->setText(QString::fromStdString(a));
        QToolTip::showText(ui->lineEdit_expr->mapToGlobal(QPoint(100, 0)), "输入格式错误");
        ui->lineEdit_expr->setStyleSheet("QLineEdit{border:1px solid red }");
    }
}

void MainWindow::button_AC(){
    ui->lineEdit_expr->setStyleSheet("QLineEdit{border:1px solid gray border-radius:1px}");
    string s,r;
    r+='0';
    text=s;
    ui->lineEdit_expr->setText(QString::fromStdString(text));
    ui->lineEdit_result->setText(QString::fromStdString(r));
    ui->lineEdit_histroy->setText(QString::fromStdString(history));
    calcu.clear();
}

void MainWindow::button_CE(){
    ui->lineEdit_expr->setStyleSheet("QLineEdit{border:1px solid gray border-radius:1px}");
    size_t t=0;
    if(calcu.size()>0&&((calcu[calcu.size()-1][0]>='0'&&calcu[calcu.size()-1][0]<='9')||calcu[calcu.size()-1][0] == '.'||calcu[calcu.size()-1][0]=='e'||calcu[calcu.size()-1]=="π")){
        t=calcu[calcu.size()-1].size();
        calcu.pop_back();
    }
    for(size_t i=0;i<t;i++){
        text.pop_back();
    }
          ui->lineEdit_expr->setText(QString::fromStdString(text));
}

void MainWindow::button_back(){
    ui->lineEdit_expr->setStyleSheet("QLineEdit{border:1px solid gray border-radius:1px}");
    string s;
    if(text.size()>0){
        if(calcu[calcu.size()-1]=="π"||calcu[calcu.size()-1]=="sin"||calcu[calcu.size()-1]=="cos"||calcu[calcu.size()-1]=="tan"||calcu[calcu.size()-1]=="sqrt"||calcu[calcu.size()-1]=="fact"||calcu[calcu.size()-1]=="rec"||calcu[calcu.size()-1]=="log"||calcu[calcu.size()-1]=="ln"){
            for(size_t i=0;i<text.size()-calcu[calcu.size()-1].size();i++){
                s+=text[i];
            }
        }
        else{
            for(size_t i=0;i<text.size()-1;i++){
                s+=text[i];
            }
        }
        text=s;
        ui->lineEdit_expr->setText(QString::fromStdString(text));
        if(calcu[calcu.size()-1].size()>1){
            if(calcu[calcu.size()-1]=="π"||calcu[calcu.size()-1]=="sin"||calcu[calcu.size()-1]=="cos"||calcu[calcu.size()-1]=="tan"||calcu[calcu.size()-1]=="sqrt"||calcu[calcu.size()-1]=="fact"||calcu[calcu.size()-1]=="rec"||calcu[calcu.size()-1]=="log"||calcu[calcu.size()-1]=="ln")
                calcu.pop_back();
            else
                calcu[calcu.size()-1].pop_back();
        }
        else {
            calcu.pop_back();
        }
    }
}


