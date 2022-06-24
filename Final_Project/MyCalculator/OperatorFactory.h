#ifndef OPERATORFACTORY_H
#define OPERATORFACTORY_H

#include<map>
#include<string>
#include<functional>
#include<memory>
using namespace std;

#include"operator.h"

#define REGISTER(T,Key)  Factory::Register<T> reg_##T(Key);

class Factory{
public:
    static map<string, function<shared_ptr<Operator>()>> ms_operator;

    template <class T>
    class Register{
    public:
        Register(string opr) {
            Factory::ms_operator.emplace(opr, [] {return make_shared<T>(); });
        }
    };

    static shared_ptr<Operator> create(string opr) {
        auto it = ms_operator.find(opr);
        if (it != ms_operator.end())
            return it->second();
    }

};
























#endif // OPERATORFACTORY_H
