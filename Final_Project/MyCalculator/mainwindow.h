#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

#include "calculator.h"


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
    void connectSlots();
    void setShortcutKeys();

    Calculator m_calcu;
    Factory m_fact;

public slots:

    void digitClicked();
    void operatorClicked();
    void funClicked();

    void button_nega();
    void button_rec();
    void button_fac();
    void button_equal();

    void button_AC();
    void button_CE();
    void button_back();

};
#endif // MAINWINDOW_H
