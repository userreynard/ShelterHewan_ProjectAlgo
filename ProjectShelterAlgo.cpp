#include <iostream>
#include <iomanip>
using namespace std;

struct Hewan {
    string nama, spesies, ras;
    int umur; 
};

struct NodeHewan {
    Hewan data;
    NodeHewan *prev, *next;
};
NodeHewan *headHewan = nullptr, *tailHewan = nullptr;

struct Adopsi {
    string adopter, hewan, spesies, ras, kontak, alamat;
};

struct NodeAdopsi {
    Adopsi data;
    NodeAdopsi *next;
};
NodeAdopsi *headAdopsi = nullptr;

string toLower(string s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 32;
        }
    }
    return s;
}

bool sama(string a, string b) {
    return toLower(a) == toLower(b);
}
