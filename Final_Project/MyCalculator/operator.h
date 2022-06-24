#ifndef OPERATOR_H
#define OPERATOR_H

#include<string>
#include<cmath>
using namespace std;

class Operator{
public:
    Operator(string sym, int numOpr, int priority):m_sym(sym),m_numOpr(numOpr),m_priority(priority){}

    string symbol() const {
        return m_sym;
    }
    int numOpr() const {
        return m_numOpr;
    }
    int priority() const {
        return m_priority;
    }

    virtual double get(double &a, double &b) const = 0;

    virtual ~Operator() {}
protected:
    const string m_sym;
    const int m_numOpr;
    const int m_priority;
};




class Add : public Operator {
public:
    Add() :Operator("+", 2, 2) {}
    double get(double &a, double &b) const {
        return a + b;
    }
};

class Sub :public Operator {
public:
    Sub() :Operator("-", 2, 2) {}
    double get(double &a, double &b) const {
        return a - b;
    }
};

class Multiply :public Operator {
public:
    Multiply() :Operator("*", 2, 3) {}
    double get(double &a, double &b) const {
        return a * b;
    }
};


class Divide :public Operator {
public:
    Divide() :Operator("/", 2, 3) {}
    double get(double &a, double &b) const {
        if(b==0){throw string("error2");}
        return a / b;
    }
};

class Hash :public Operator {
public:
    Hash() :Operator("#", 1, 1) {}
    double get(double &a, double& ) const {
        return a;
    }
};

class Left :public Operator {
public:
    Left() :Operator("(", 0, 0) {}
    double get(double &a, double& ) const {
        return a;
    }
};

class Right :public Operator {
public:
    Right() :Operator(")", 0, 0) {}
    double get(double &a, double &) const {
        return a;
    }
};

class Pow :public Operator {
public:
    Pow() :Operator("pow", 2, 4) {}
    double get(double &a, double &b) const {
        return pow(a,b);
    }
};

class Mod :public Operator {
public:
    Mod() :Operator("%", 2, 3) {}
    double get(double &a, double &b) const {
        return int(a) % int(b);
    }
};

class Sin :public Operator {
public:
    Sin() :Operator("sin", 1, 5) {}
    double get(double &, double &b) const {
        return sin(b);
    }
};

class Cos :public Operator {
public:
    Cos() :Operator("cos", 1, 5) {}
    double get(double &, double &b) const {
        return cos(b);
    }
};

class Tan :public Operator {
public:
    Tan() :Operator("tan", 1, 5) {}
    double get(double &, double &b) const {

        if(b==(atan(1.0) * 4)/2)
            throw string("error2");

        return tan(b);
    }
};

class Sqrt :public Operator {
public:
    Sqrt() :Operator("sqrt", 1, 5) {}
    double get(double &, double &b) const {
        return sqrt(b);
    }
};

class Log :public Operator {
public:
    Log() :Operator("log", 1, 5) {}
    double get(double &, double &b) const {
        return log10(b);
    }
};

class Ln :public Operator {
public:
    Ln() :Operator("ln", 1, 5) {}
    double get(double &, double &b) const {
        return log(b);
    }
};

class Reciprocal :public Operator {
public:
    Reciprocal() :Operator("rec", 1, 5) {}
    double get(double &, double &b) const {
        return 1/b;
    }
};

class Factorial :public Operator {
public:
    Factorial() :Operator("fact", 1, 5) {}
    double get(double &, double &b) const {
        long long sum=1;
        for(int i=1;i<=(int)b;i++){
            sum*=i;
        }
        return sum;
    }
};

class Negative :public Operator { // 运算符-
public:
    Negative() :Operator("~", 1, 5) {}
    double get(double &, double &b) const {
        return -b;
    }
};


class Equal :public Operator { //表达式结束符=
public:
    Equal() :Operator("=", 2, 0) {}
    double get(double &a, double &) const {
        return a;
    }
};

#endif // OPERATOR_H
