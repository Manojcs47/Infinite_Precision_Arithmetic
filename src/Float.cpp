#include "Float.h"


InfinitePrecision::Float::Float() {}

InfinitePrecision::Float::Float(const string num) {
    string d;
    bool counting_e=false;
    for (int i=0; i<num.size(); ++i) {
        if (num[i] == '.') {
            counting_e=true;
            continue;
        }
        if (counting_e) {
            e-=1;
        }
        d+=num[i];
    }
    reverse(d.begin(), d.end());
    while (*(d.end() - 1) == '0') {
        d.pop_back();
    }
    reverse(d.begin(), d.end());
    digits=d;
}

InfinitePrecision::Float::Float(double num) {
    while (num - (long long)num != 0) {
        num*=10;
        e-=1;
    }
    digits=num;
}

InfinitePrecision::Float::Float(const Float& f) {
    digits=f.digits;
    e=f.e;
}

InfinitePrecision::Float InfinitePrecision::Float::operator+=(const Float num) {
    Float f1=*this; //f1 is current number.
    Float f2=num; //f2 is num.
    //for making the additon easy, we will first make both the exponent terms equal. for example, adding 0.05 and 0.5. the numbers  will bee 5e-2 and 50e-2. so we can easyly add these 50 and 5 using Integer addition implementation, then use the new digits and exponent to assign it to the current float.
    while (f1.e != f2.e) {
        if (f1.e < f2.e) {
                    f2.e-=1;
                    f2.digits*=10;
        }
        else {
                    f1.e-=1;
                    f1.digits*=10;
        }
    }
    f1.digits+=f2.digits;
    *this=f1;
    return *this;
}

InfinitePrecision::Float InfinitePrecision::Float::operator-=(const Float num) {
    Float f = num;
    *this += -f;
    return *this;
}

InfinitePrecision::Float InfinitePrecision::Float::operator*=(const Float num) {
    digits*=num.digits;
    e+=num.e;
    return *this;
}

InfinitePrecision::Float InfinitePrecision::Float::operator/=(const Float num) {
    Float result; //we will manipulate this result while dividing.
    Integer numerator=digits;
    Integer denominator=num.digits;
    result.e=e-num.e;
    //we will take the absolute values of numerator and denominator since having sign may bring conflicts with remindders.
    numerator = numerator < 0 ? -numerator : numerator;
    denominator = denominator < 0 ? -denominator : denominator;
    //if the exponent of the result became positive, we will multiply the numerator by 10 and decrease the exponent.
    for (; result.e>0; result.e-=1) {
        numerator*=10;
    }
    //set the result and check if any reminder, if there is any reminder, then decrease the exponent of result and multiply the value of numerator with 10.
    result.digits=numerator/denominator;
    Integer reminder=numerator - denominator * result.digits;
    for (int i=0; i<precise_digits &&  reminder > 0; ++i) {
            numerator=reminder*10;
            result.e-=1;
            result.digits*=10;
            Integer q;
            q=numerator/denominator;
            result.digits+=q;
            reminder=numerator - denominator * q;
    }
    //set the current object to result.
    *this=*this < 0.0 ? -result : result;
    return *this;
}

InfinitePrecision::Float InfinitePrecision::Float::operator+(const Float num) const {
    Float f=*this;
    f+=num;
    return f;
}

InfinitePrecision::Float InfinitePrecision::Float::operator-(const Float num) const {
    Float f=*this;
    f-=num;
    return f;
}


InfinitePrecision::Float InfinitePrecision::Float::operator-() {
    Float newnum=*this;
    newnum.digits=-newnum.digits;
    return newnum;
}

InfinitePrecision::Float InfinitePrecision::Float::operator*(const Float num) const {
    Float f=*this;
    f*=num;
    return f;
}

InfinitePrecision::Float InfinitePrecision::Float::operator/(const Float num) const {
    Float f=*this;
    f/=num;
    return f;
}

bool InfinitePrecision::Float::operator<(const Float num) const {
    Float f1=*this;
    Float f2=num;
    if (f1.e != f2.e) {}
    while (f1.e != f2.e) {
        f2.e > f1.e ? f2.digits*=10 : f1.digits*=10;
        f2.e > f1.e ? f2.e -= 1 : f1.e -= 1;
    }
    return f1.digits < f2.digits;
}

bool InfinitePrecision::Float::operator>(const Float num) const {
    Float f1=*this;
    Float f2=num;
    if (f1.e != f2.e) {}
    while (f1.e != f2.e) {
        f2.e > f1.e ? f2.digits*=10 : f1.digits*=10;
        f2.e > f1.e ? f2.e -= 1 : f1.e -= 1;
    }
    return f1.digits > f2.digits;
}

bool InfinitePrecision::Float::operator==(const Float num) const {
    return (!(*this < num) && !(*this > num));
}

bool InfinitePrecision::Float::operator<=(const Float num) const {
    return (*this < num || *this == num);
}

bool InfinitePrecision::Float::operator>=(const Float num) const {
    return (*this > num || *this == num);
}



ostream& InfinitePrecision::operator<<(ostream& os, const Float& f) {
    Float num=f;
    if (num< 0) {
        os << "-";
    }
    vector<digit> d=num.digits.get_digits();
    reverse(d.begin(),d.end());
    Integer s=d.size();
    for (Integer i=0; i>num.e+s; i-=1) {
        d.push_back(0);
    }
    reverse(d.begin(), d.end());
    for (int i=0; i<d.size(); ++i) {
        if (num.e + d.size() == i) {
            if (i == 0) {
                os << 0;
            }
            os << ".";
        }
        os << static_cast<int>(d[i]);
    }
    return os;
}

void InfinitePrecision::set_precision(int pd) {
    precise_digits=pd;
}

InfinitePrecision::Float InfinitePrecision::Float::parse(const string num) {
    Float n(num);
    return n;
}