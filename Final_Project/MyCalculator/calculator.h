#ifndef CALCULATOR_H
#define CALCULATOR_H
#include"operator.h"
#include"stack.h"
#include"OperatorFactory.h"
#include<vector>
#include<memory>
#include<QObject>

typedef unsigned long UL;
class Calculator{
private:
    Stack<double> m_num;
    Stack<shared_ptr<Operator>> m_opr;

    int isRight(const vector<string>& calcu);
    bool isNum(const vector<string> &calcu,UL &i) {
        return( calcu[i][0] >= '0' && calcu[i][0] <= '9' )|| calcu[i][0] == '.'||calcu[i][0]=='e'||calcu[i]=="π";
    }
    double readNum(const vector<string>&calcu,UL &i);
    void calculate();

public:
    Calculator() {
        m_opr.push(make_shared<Hash>());
    }

    double Do(const vector<string>& calcu);
};


#endif // CALCULATOR_H
