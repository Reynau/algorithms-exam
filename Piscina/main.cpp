#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned int uint;

using namespace std;

struct triplet {
    uint h;
    uint m;
    uint s;
};

uint getBase(triplet t) {
    return t.h*60*60 + t.m*60 + t.s;
}

bool smallerTriplet(triplet t1, triplet t2) {
    return (getBase(t1) < getBase(t2));
}

void printTriplet(triplet t) {
    cout << t.h << ":" << t.m << ":" << t.s << endl;
}

void printTriplets(vector<triplet> ts) {
    for (uint i = 0; i < ts.size(); ++i) {
        printTriplet(ts[i]);
    }
}

uint getMaxTime (vector<triplet> ts) {
    uint maxTime = 0;
    uint base = getBase(ts[0]);
    for (uint i = 1; i < ts.size(); ++i) {
        uint nextTime = getBase(ts[i])-60;
        uint diffBase = nextTime - base;
        if (diffBase > maxTime) maxTime = diffBase;
        base = nextTime;
    }
    return maxTime;
}

triplet createTriplet () {
    triplet t;
    cout << "Introduce hh:mm:ss" << endl;

    string str;
    cin >> str;
    t.h = (uint)((str[0]-48)*10 + (str[1]-48));
    t.m = (uint)((str[3]-48)*10 + (str[4]-48));
    t.s = (uint)((str[6]-48)*10 + (str[7]-48));

    return t;
}

bool between(uint x, uint a, uint b) {
    return (x >= a && a < b);
}

vector<triplet> distributeMinutes(uint m, uint n, vector<triplet> triplets) {
    uint fixTime = 0;

    uint size = triplets.size();
    if (size > 2*m) {
        uint base = getBase(triplets[m]);
        for (int i = m+1; i < size - m; ++i) {
            uint nextBase = getBase(triplets[i]);
            uint diff = nextBase - base;
            fixTime += diff;
            base = nextBase;
        }
    }

    uint maxVariableTime = 0; // Maximum free time
    for (uint i = 0; i < m+1; ++i) { // Diferent distributions
        vector<uint> aux(n, 0);
        for (int j = 0; j < m - i; ++j) aux[j] = 1;
        for (int j = size - i; j < size; ++j) aux[j] = 1;

        cout << "Distribution " << i << endl;
        for (int j = 0; j < n; ++j) cout << aux[j];
        cout << endl;

        uint base = getBase(triplets[0]) + aux[0]*60;
        uint acumDiff = 0;
        uint maxDiff = 999999999;
        for (uint j = 1; j < n; ++j) {
            if (aux[j]) {
                uint nextBase = getBase(triplets[j]);
                acumDiff += nextBase - base;
                if (acumDiff < maxDiff) maxDiff = acumDiff;
                base = nextBase + 60;
                acumDiff = 0;
            }
            else {
                uint nextBase = getBase(triplets[j]);
                acumDiff += nextBase - base;
                if (acumDiff < maxDiff) maxDiff = acumDiff;
                base = nextBase + 60;
            }
        }

        cout << "Max diff is " << maxDiff << endl;
        if (maxDiff > maxVariableTime) maxVariableTime = maxDiff;
    }
    cout << endl << "Total max diff is " << fixTime + maxVariableTime << endl;
}

int main (int argc, char* argv[]) {
    uint m, n;
    cout << "Introduce m and n" << endl;
    cin >> m >> n;
    while(m != 0 && n != 0) {
        vector<triplet> triplets(n);
        for (uint i = 0; i < n; ++i) {
            triplet t = createTriplet();
            triplets[i] = t;
        }
        sort(triplets.begin(), triplets.end(), smallerTriplet);
        distributeMinutes(m, n, triplets);
        cout << "Introduce m and n" << endl;
        cin >> m >> n;
    }
}