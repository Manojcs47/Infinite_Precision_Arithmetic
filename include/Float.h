#ifndef Float_h
#define Float_h

#include<iostream>
#include "Integer.h"

using namespace std;


// InfinitePrecision namespace
namespace InfinitePrecision {
    static int precise_digits=100; //made it static to make sure no other definitions of this exist.
// a re implementation of Float for infinite precision.
class Float {
    //represent float using 2 values. one is for the number itself and other is for exponent. for example, 1.05 is represented as 105e-2.
    Integer digits;
    Integer e;
    public :
    Float(); //default constructor which initializes the class with 0.
    Float(const string num); //parse the given string and initialize the Float with the given digits.
    Float(const double num); //a constructor taking an Float as an input and constructing the object.
    Float(const Float& i); // copy constructor which takes another Float as argument and initializes the class with it.
    Float operator+=(const Float n); //operator overloader for +=.
    Float operator+(const Float n) const; //operator overloader for +.
    Float operator-=(const Float n); //operator overloader for -=.
    Float operator-(const Float n) const; //operator overloader for -.
    Float operator-(); //-(Float)
    Float operator*=(const Float n); //operator overloader for *=.
    Float operator*(const Float n) const; //operator overloader for *.
    Float operator/=(const Float n); //operator overloader for /=.
    Float operator/(const Float n) const; //operator overloader for /.
    bool operator==(const Float n) const; //operator overloader for ==.
    bool operator<(const Float num) const; //operator overloader for <.
    bool operator<=(const Float num) const; //operator overloader for <=.
    bool operator>(const Float num) const; //operator overloader for >.
    bool operator>=(const Float num) const; //operator overloader for >=.
    Float parse(const string num); //a parse function to return an instance of Float.
    private :
    friend ostream& operator<<(ostream& os, const Float& n); //operator overloader for << operator.
};
ostream& operator<<(ostream& os, const Float& n); //operator overloader for << for the Float class.
    void set_precision(int pd);
}
#endif
