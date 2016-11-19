#ifndef PISCINA_TRIPLET_H
#define PISCINA_TRIPLET_H

#include <iostream>
#include <regex>

typedef unsigned int uint;

using namespace std;

class Triplet {

private:

public:
    uint h;
    uint m;
    uint s;

    uint getBase () {
        return (uint) (this->h*60*60 + this->m*60 + this->s);
    }

    void incrementHours(uint inc) {
        this->h += h;
    }
    void incrementMinutes(uint inc) {
        uint h_inc = (uint) inc/60;
        uint m_inc = (uint) inc%60;
        this->incrementHours(h_inc);

    }
    void incrementSeconds(uint inc) {
        uint m_inc = (uint) inc/60;
        uint s_inc = (uint) inc%60;
        this->incrementMinutes(m_inc);
        this->s += s_inc;
    }

    friend bool operator== (const Triplet &t1, const Triplet &t2) {
        return (t1.s == t2.s && t1.m == t2.m && t1.h == t2.h); // Fast comparison, seconds are easily different
    }
    friend bool operator!= (const Triplet &t1, const Triplet &t2) {
        return !(t1 == t2);
    }

    friend bool operator< (const Triplet &t1, const Triplet &t2) {
        if (t1.h < t2.h) return true;
        if (t1.h == t2.h && t1.m < t2.m) return true;
        if (t1.h == t2.h && t1.m == t2.m && t1.s < t2.s) return true;
        return false;
    }
    friend bool operator> (const Triplet &t1, const Triplet &t2) {
        if (t1.h > t2.h) return true;
        if (t1.h == t2.h && t1.m > t2.m) return true;
        if (t1.h == t2.h && t1.m == t2.m && t1.s > t2.s) return true;
        return false;
    }
    friend bool operator<= (const Triplet &t1, const Triplet &t2) {
        return (t1 < t2 || t1 == t2);
    }
    friend bool operator>= (const Triplet &t1, const Triplet &t2) {
        return (t1 > t2 || t1 == t2);
    }

    friend ostream &operator<<( ostream &output, const Triplet &T ) {
        output << T.h << ":" << T.m << ":" << T.s;
        return output;
    }
    friend istream &operator>>( istream  &input, Triplet &T ) {
        string triplet;
        input >> triplet;
        T.h = (uint)atoi(&triplet[0]);
        T.m = (uint)atoi(&triplet[3]);
        T.s = (uint)atoi(&triplet[6]);
        return input;
    }
};


#endif //PISCINA_TRIPLET_H
