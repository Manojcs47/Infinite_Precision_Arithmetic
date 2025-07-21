#include "Integer.h"
#include<stdexcept>


InfinitePrecision::Integer::Integer() {
    digits.push_back(0);
}

InfinitePrecision::Integer::Integer(const string num) {
    size_t start=0;
    if (num[0] == '-') {
        sign=1;
        start=1;
    }
    for (int i=start; i<num.length(); ++i) {
        digits.push_back(num[i] - 48); //48 is the ascii code for 0, and remaining digits follow it, so doing ascii code of input - 48 will give exact digit.
    }
}

InfinitePrecision::Integer::Integer(const long long num) {
    long long n;
    if (num < 0) {n=-num;}
    else {n=num;}
    if (n == 0) {
        digits.push_back(0);
    }
    while (n > 0) {
        digits.push_back(n%10);
        n/=10;
    }
    reverse(digits.begin(), digits.end()); //since we appended in reverse order, we need to reverse the digits.
    sign=num<0;
}

InfinitePrecision::Integer::Integer(const Integer& i) {
    digits=i.digits;
    sign=i.sign;
}

InfinitePrecision::Integer InfinitePrecision::Integer::operator+=(const Integer n) {
    //make new copys of digits and reverse them to operate on them digit by digit.
    vector<digit> d1=digits;
    vector<digit> d2=n.digits;
    bool sign1=sign;
    bool sign2=n.sign;
    reverse(d1.begin(), d1.end());
    reverse(d2.begin(), d2.end());
    vector<digit> result={0};
    //if the number of digits of both the integers are not same, pad the other integer with zeros at the left. since the copies of the digits are reversed, we'll push back extra zeros to the smaller digits vector.
    for (; d1.size() != d2.size();) {
        d2.size() > d1.size() ? d1.push_back(0) : d2.push_back(0);
    }
    if (sign1 == sign2) {
        //iterate through all digits, make 2 variables res and carry. res adds to the current position in the result, while carry is pushed back as the next position in the result vector. so that in next iteration res will bee added to the carry, and so onn.
        for (int i=0; i<d1.size(); ++i) {
            digit res = d1[i] + d2[i];
            digit carry=res/10;
            res=res%10;
            result[i]+=res;
            result.push_back(carry);
        }
    }
    else {
        for (int i=0; i<d1.size(); ++i) {
            digit res=cmp(n) ? d1[i]-d2[i] : d2[i] - d1[i]; //subtract the digits with greater absolute value.
            result[i]+=res;
            digit carry=result[i] < 0 ? -1 : 0; //carry will be a -1 to the next digit if we got a negative value by subtracting 2 digits, and adding this to current position, no carry otherwise since subtracting 2 decimul digits will give a single decimul digit result.
            result[i]+=result[i] < 0 ? 10 : 0; //if the current position of the result is a negative value, then add a 10 since we also have a carry.
            result.push_back(carry);
        }
        // after doing this operation, assign the current object the sign of the integer with greater absolute value.
        sign=cmp(n) ? sign1 : sign2;
    }
    //next, remove all extra zeros if any. we will also make sure that the size of the result vector will be at least 1 since doing 0+0 should not remove all zeros in the result veector and make it empty.
    for (; *(--result.end()) == 0 && result.size() > 1;) {
        result.pop_back();
    }
    //finally, reverse back the result vector to get digits right and assign this to the current object.
    reverse(result.begin(), result.end());
    digits=result;
    if (digits.size() == 1 && digits[0] == 0) {
        //dont apply sine if the result is 0.
        sign=0;
    }
    return *this;
}

InfinitePrecision::Integer InfinitePrecision::Integer::operator-=(Integer n) {
    return *this += -n;
}

InfinitePrecision::Integer InfinitePrecision::Integer::operator*=(const Integer n) {
    Integer result; //final result, we'll keep adding the multiplied parts to it.
    vector<digit> d1=digits; //digits of current object.
    vector<digit> d2=n.digits; //digits of n.
    reverse(d1.begin(), d1.end());
    reverse(d2.begin(), d2.end());
    //we reversed the second operand's digits. now we also need to add zeros to avoid using wrong places.
    while (d2.size() < d1.size()) {
        d2.push_back(0);
    }
    for (int i=0; i<d1.size(); ++i) {
        vector<digit> res={0}; // a vector of digits for each multiplication.
        for (int j=0; j<d2.size(); ++j) {
            digit r=d1[i]*d2[j]; //multiply the digits.
            digit carry = r/10;
            r=r%10;
            res[j]+=r;
            res.push_back(carry);
        }
        reverse(res.begin(), res.end());
        //now, based on the position, append 0s to the res, just like we slide the multiplication with each digit while adding up all the multiplication result.
        for (int k=0; k<i; ++k) {
            res.push_back(0);
        }
        Integer r;
        r.digits=res;
        r.sign=sign^n.sign; //doing a xor to both the booliens will give the sign. that is, multiplying same signs (1 and 0 in booliens) should give a plus (0 in boolien). and multiplying different signs should give minus (1 in boolien).
        result+=r;
    }
    *this=result;
    return *this;
}

InfinitePrecision::Integer InfinitePrecision::Integer::operator/=(const Integer n) {
    Integer d; //an integer to divide digit by digit, by taking a digit, dividing and finding the reminder, then setting the reminder to the current integer, then appending the next digit of the current integer to the d, and so onn untill we run out of digits in current integer.
    Integer result; //0 by default, we will append digits to the result.
    for (int i=0; i<digits.size(); ++i) {
        d=d*10+digits[i];
        //now, loop through all possible quotients, and find the greatest one and append it to the result.
        int q;
        for (q=0; d.cmp(n*q); ++q) {
            }
            --q; //we will decrement q by 1 since the for loop increments q to check even false condition.
            d=d - n*q;
            result=result*10+q;
        }
        result.sign=sign^n.sign;
        *this=result;
        return *this;
    }


InfinitePrecision::Integer InfinitePrecision::Integer::operator+(const Integer n) const {
    Integer i=*this;
    return i+=n;
}

InfinitePrecision::Integer InfinitePrecision::Integer::operator-(const Integer n) const {
    Integer i=*this;
    return i-=n;
}

InfinitePrecision::Integer InfinitePrecision::Integer::operator*(const Integer n) const {
    Integer i=*this;
    return i *= n;
}

InfinitePrecision::Integer InfinitePrecision::Integer::operator/(const Integer n) const {
	if(n==0) {
	throw std::out_of_range ("Zero division error");
	}
    Integer i=*this;
    return i/=n;
}


bool InfinitePrecision::Integer::cmp(const Integer n) {
    if (digits.size() != n.digits.size()) {
        return digits.size() > n.digits.size();
    }
    for (int i=0; i<digits.size(); ++i) {
        if (n.digits[i] != digits[i]) {
            return digits[i] > n.digits[i];
        }
    }
    return true;
}

ostream& InfinitePrecision::operator<<(ostream& os, const Integer& n) {
    if (n.sign == true) {
        os << '-';
    }
    for (auto d=n.digits.begin(); d!=n.digits.end(); ++d) {
        os << static_cast<int>(*d);
    }
    return os;
}

InfinitePrecision::Integer InfinitePrecision::Integer::operator-() {
    Integer n=*this;
    n.sign=!sign;
    return n;
}

bool InfinitePrecision::Integer::operator<(const Integer num) const {
    vector<digit> d1=digits; //digits of current Integer.
    vector<digit> d2=num.digits; //digits of num.
    reverse(d1.begin(), d1.end()); //reverse digits.
    reverse(d2.begin(), d2.end());
    if (sign != num.sign) {
        return sign == 1; //return true if the current integer is negative and num is positive.
    }
    while (d1.size() != d2.size()) {
        d1.size() < d2.size() ? d1.push_back(0) : d2.push_back(0);
    }
    reverse(d1.begin(), d1.end()); //reverse digits back to normal after adding zeros.
    reverse(d2.begin(), d2.end());
    for (int i=0; i<d1.size(); ++i) {
        if (d1[i] < d2[i]) {
            return sign == 0; //return a true if sign is positive, and false if sign is negative.
        }
        else if (d1[i] > d2[i]) {
            return sign == 1; //return a true if sign is positive, and false if sign is negative.
        }
        else {
            continue;
        }
    }
    return false;
}

bool InfinitePrecision::Integer::operator>(const Integer num) const {
    vector<digit> d1=digits; //digits of current Integer.
    vector<digit> d2=num.digits; //digits of num.
    reverse(d1.begin(), d1.end()); //reverse digits.
    reverse(d2.begin(), d2.end());
    if (sign != num.sign) {
        return sign == 0; //return true if the current integer is positive and num is negative.
    }
    while (d1.size() != d2.size()) {
        d1.size() < d2.size() ? d1.push_back(0) : d2.push_back(0);
    }
    reverse(d1.begin(), d1.end()); //reverse digits back to normal after adding zeros.
    reverse(d2.begin(), d2.end());
    for (int i=0; i<d1.size(); ++i) {
        if (d1[i] > d2[i]) {
            return sign == 0; //if sign is positive, then this should be true.
        }
        else if (d1[i] < d2[i]) {
            return sign == 1; //if negative, then this should be true.
        }
        else {
            continue;
        }
    }
    return false;
}

bool InfinitePrecision::Integer::operator==(const Integer num) const {
    Integer n1=*this;
    Integer n2 = num;
    return (!(n1 < n2) && !(n1 > n2));
}

bool InfinitePrecision::Integer::operator!=(const Integer num) const {
    return !(*this == num);
}

bool InfinitePrecision::Integer::operator<=(const Integer num) const {
    return (*this < num || *this == num);
}

bool InfinitePrecision::Integer::operator>=(const Integer num) const {
    return (*this > num || *this == num);
}

InfinitePrecision::Integer InfinitePrecision::Integer::abs() {
    return *this < 0 ? -(*this) : *this;
}

InfinitePrecision::Integer InfinitePrecision::Integer::parse(const string num) {
    Integer n(num);
    return n;
}

vector<digit> InfinitePrecision::Integer::get_digits() {
    return digits;
}