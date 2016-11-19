#include <iostream>
#include <regex>
#include <vector>

#include "Triplet.h"

typedef unsigned int uint;

using namespace std;

void printTriplets (const vector<Triplet>& triplets) {
    for (uint i = 0; i < triplets.size(); ++i) {
        cout << triplets[i] << endl;
    }
}

void distributeMinutes (const uint m, vector<Triplet>& triplets) {
    sort(triplets.begin(), triplets.end());

    uint start = (uint) (triplets.size() - 1);
    uint end = (uint) (end - m);

    triplets[0].incrementMinutes(1);
    for (uint i = start; i > end; --i) {
        triplets[i].incrementMinutes(1);
    }
}

uint calculateMaxTime (vector<Triplet>& triplets) {
    uint maxTime = 0;

    uint base = triplets[0].getBase();
    for (uint i = 1; i < triplets.size(); ++i) {
        uint nextBase = triplets[i].getBase();
        uint diffBase = nextBase - base;
        if (diffBase > maxTime) maxTime = diffBase;
        base = nextBase;
    }

    return maxTime;
}

// We want to return the free time
// We have an m, so we will put a minute in the first time zone, and then put the rest in inverse order, from the last to closer to init
int main(int argc, char* argv[]) {
    uint m; // Minutes we want to bath
    uint n; // Number of time zones
    vector<Triplet> triplets(n); // Time zones

    cout << "Introduce m and n" << endl;
    cin >> m >> n;

    cout << "Introduce triplets" << endl;
    for (uint i = 0; i < n; ++i)
        cin >> triplets[i];

    sort(triplets.begin(), triplets.end());

    uint start = (uint) (triplets.size() - 1);
    uint end = (uint) (end - m);

    triplets[0].incrementMinutes(1);
    for (uint i = start; i > end; --i) {
        triplets[i].incrementMinutes(1);
    }

    uint maxTime = 0;

    uint base = triplets[0].getBase();
    for (uint i = 1; i < triplets.size(); ++i) {
        uint nextBase = triplets[i].getBase();
        uint diffBase = nextBase - base;
        if (diffBase > maxTime) maxTime = diffBase;
        base = nextBase;
    }

    cout << maxTime << endl;
}