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

void sllTambahAdopsi(Adopsi a) {
    NodeAdopsi *n = new NodeAdopsi;
    n->data = a;
    n->next = nullptr;
    
    if (!headAdopsi) {
        headAdopsi = n;
    } else {
        NodeAdopsi *temp = headAdopsi;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = n;
    }
}

void sllHapusAdopsi(NodeAdopsi *cur, NodeAdopsi *prev) {
    if (prev) prev->next = cur->next;
    else      headAdopsi = cur->next;
    delete cur;
}

void sinkron(Hewan *arr, int &jml) {
    jml = 0;
    for (NodeHewan *c = headHewan; c && jml < 50; c = c->next)
        arr[jml++] = c->data;
}

void simpanHewan(Hewan arr[], int jml) {
    FILE *f = fopen("hewan.txt", "w");
    if (!f) return;
    for (int i = 0; i < jml; i++)
        fprintf(f, "%s;%s;%s;%d\n",
            arr[i].nama.c_str(), arr[i].spesies.c_str(),
            arr[i].ras.c_str(),  arr[i].umur);
    fclose(f);
}

void loadHewan(Hewan arr[], int &jml) {
    FILE *f = fopen("hewan.txt", "r");
    if (!f) return;
    char a[100], b[100], c[100];
    int u;
    while (fscanf(f, "%99[^;];%99[^;];%99[^;];%d\n", a, b, c, &u) == 4 && jml < 50) {
        arr[jml].nama    = a;
        arr[jml].spesies = b;
        arr[jml].ras     = c;
        arr[jml].umur    = u;
        dllTambah(arr[jml++]);
    }
    fclose(f);
}
