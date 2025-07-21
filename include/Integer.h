#ifndef Integer_h
#define Integer_h

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef signed char digit;

// InfinitePrecision namespace
namespace InfinitePrecision {
// a re implementation of integer for infinite precision.
class Integer {
    //a list of digits and an bool for sign. 0 for + and 1 for minus.
    vector<digit> digits;
    bool sign=0;
    friend class Float;
    public :
    Integer(); //default constructor which initializes the class with 0.
    Integer(const string num); //parse the given string and initialize the Integer with the given digits.
    Integer(const long long num); //a constructor taking an integer as an input and constructing the object.
    Integer(const Integer& i); // copy constructor which takes another Integer as argument and initializes the class with it.
    Integer operator+=(const Integer n); //operator overloader for +=.
    Integer operator+(const Integer n) const; //operator overloader for +.
    Integer operator-=(const Integer n); //operator overloader for -=.
    Integer operator-(const Integer n) const; //operator overloader for -.
    Integer operator-(); //-(integer)
    Integer operator*=(const Integer n); //operator overloader for *=.
    Integer operator*(const Integer n) const; //operator overloader for *.
    Integer operator/=(const Integer n); //operator overloader for /=.
    Integer operator/(const Integer n) const; //operator overloader for /.
    Integer abs(); //returns the absolute value of current class.
    bool operator<(const Integer num) const; //operator overloader for <.
    bool operator>(const Integer num) const; //operator overloader for >.
    bool operator==(const Integer n) const; //operator overloader for ==.
    bool operator<=(const Integer num) const; //operator overloader for <=.
    bool operator>=(const Integer num) const; //operator overloader for >=.
    bool operator!=(const Integer n) const; //operator overloader for !=.
    Integer parse(const string num); //a parse function to return an instance of integer.
    vector<digit> get_digits(); //digits vector is needed later.
    private :
    bool cmp(const Integer n); //a function to compare the order after applying the modulus. returns true if current one is greater and false otherwise.
    friend ostream& operator<<(ostream& os, const Integer& n); //operator overloader for << operator.
};
ostream& operator<<(ostream& os, const Integer& n); //operator overloader for << for the Integer class.
}
#endif
