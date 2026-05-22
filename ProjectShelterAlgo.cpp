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
void dllTambah(Hewan h) {
    NodeHewan *n = new NodeHewan;
    n->data = h;
    n->prev = nullptr;
    n->next = nullptr;
    if (!headHewan)
        headHewan = tailHewan = n;
    else {
        tailHewan->next = n;
        n->prev = tailHewan;
        tailHewan = n;
    }
}

void dllHapus(NodeHewan *n) {
    if (n->prev) n->prev->next = n->next;
    else         headHewan = n->next;
    if (n->next) n->next->prev = n->prev;
    else         tailHewan = n->prev;
    delete n;
}

NodeHewan *dllCari(string nama) {
    for (NodeHewan *c = headHewan; c; c = c->next)
        if (sama(c->data.nama, nama)) return c;
    return nullptr;
}
