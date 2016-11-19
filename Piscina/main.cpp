#include <iostream>
#include <regex>

typedef unsigned int uint;

using namespace std;

void verify_triplet(string triplet) {
    regex rgx ("[0-9]{2}:[0-9]{2}:[0-9]{2}");
    if (regex_match(triplet, rgx)) {
        uint h, m, s;
        h = (uint)atoi(&triplet[0]);
        m = (uint)atoi(&triplet[3]);
        s = (uint)atoi(&triplet[6]);
        cout << h << " " << m << " " << s << endl;
    }
    else {
        cout << "Invalid triplet" << endl;
    }
}

// We want to return the free time
// We have an m, so we will put a minute in the first time zone, and then put the rest in inverse order, from the last to closer to init
int main(int argc, char* argv[]) {
    string triplet;
    uint m; // Minutes we want to bath
    uint n; // Number of time zones

    cin >> m >> n;

    for (uint i = 0; i < n; ++i) {
        cin >> triplet;

    }
}