#include"calculator.h"
#include"OperatorFactory.h"

int Calculator::isRight(const vector<string>& calcu){
    int is=1,left=0,right=0;

    for(UL i=0;i<calcu.size();i++){
        if((i!=0 && i!=calcu.size()-2)&&(calcu[i]=="+"||calcu[i]=="-"||calcu[i]=="*"||calcu[i]=="/"||calcu[i]=="^"||calcu[i]=="%")){
            if(calcu[i+1]=="+"||calcu[i+1]=="-"||calcu[i+1]=="*"||calcu[i+1]=="/"||calcu[i+1]=="^"||calcu[i+1]=="%"){
            is=0;
            return is;
            }
            if(!((calcu[i-1][0]>='0'&&calcu[i-1][0]<='9')||calcu[i-1][0] == '.'||calcu[i-1][0]=='e'||calcu[i-1]=="π"||calcu[i-1]==")")){
                is=0;
                return is;
            }
            if(calcu[i+1]==")"){
                is=0;
                return is;
            }

        }
        if((i==0||i==calcu.size()-2)&&(calcu[i]=="+"||calcu[i]=="-"||calcu[i]=="*"||calcu[i]=="/"||calcu[i]=="^"||calcu[i]=="%")){
            is=0;
            return is;
        }
        if(calcu[i]=="("){
            left+=1;
            if(i!=0){
                if((calcu[i-1][0]>='0'&&calcu[i-1][0]<='9')||calcu[i-1][0] == '.'||calcu[i-1][0]=='e'||calcu[i-1]=="π"){
                    is=0;
                    return is;
                }
            }
        }
        if(calcu[i]==")"){
            if(right<left)
                right+=1;
            else {
                is=0;
                return is;
            }
            if(i!=calcu.size()-2){
                if((calcu[i+1][0]>='0'&&calcu[i+1][0]<='9')||calcu[i+1][0] == '.'||calcu[i+1][0]=='e'||calcu[i+1]=="π"){
                    is=0;
                    return is;
                }
            }
        }
    }
    if(left!=right)
        is=0;
    return is;
}


double Calculator::readNum(const vector<string> &calcu,size_t &i){
     if (calcu[i]=="π"){
          return (std::atan(1.0) * 4);
     }
     else if(calcu[i]=="e"){
            double e=1.0,n=1.0;
            int i=1;
            while(1/n>1e-10){
                e+=1/n;
                i++;
                n=i*n;
             }
        return e;
         }
    int dot=0;
    for(UL j=0;j<calcu[i].size();j++){
        if(calcu[i][j]=='.')dot+=1;
        }
    if(dot>1)
        throw string("error1");
    return stod(calcu[i]);

}

void Calculator::calculate(){

    double num[2]={0};
    for(auto i=0;i<m_opr.top()->numOpr();i++){
        num[i]=m_num.top();
        m_num.pop();
    }
    m_num.push(m_opr.top()->get(num[1],num[0]));
    m_opr.pop();

}

double Calculator::Do(const vector<string>& calcu){
    if(isRight(calcu)==0){
        throw string("error");
    }
    else{
        for(UL i=0;i<calcu.size();i++){
            if (isNum(calcu,i)){
                m_num.push(readNum(calcu,i));
            }
            else{
                auto op=Factory::create(calcu[i]);
                if(op->symbol()=="("){
                    m_opr.push(Factory::create("#"));
                }
                else if(op->symbol()==")"){

                    while(m_opr.top()->symbol()!="#")calculate();
                    m_opr.pop();

                }
                else{
                    while(op->priority()<=m_opr.top()->priority()){
                       if(m_opr.top()->symbol()=="#")
                           break;
                       calculate();
                    }
                    if(op->symbol()!="=")
                        m_opr.push(op);
                }
             }
        }
        double result=m_num.top();
        m_num.pop();
        return result;
    }

}

