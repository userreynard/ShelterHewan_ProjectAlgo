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

void simpanAdopsi() {
    FILE *f = fopen("adopsi.txt", "w");
    if (!f) return;
    for (NodeAdopsi *t = headAdopsi; t; t = t->next)
        fprintf(f, "%s;%s;%s;%s;%s;%s\n",
            t->data.adopter.c_str(), t->data.hewan.c_str(),
            t->data.spesies.c_str(), t->data.ras.c_str(),
            t->data.kontak.c_str(),  t->data.alamat.c_str());
    fclose(f);
}

void loadAdopsi() {
    FILE *f = fopen("adopsi.txt", "r");
    if (!f) return;
    char line[300];
    while (fgets(line, sizeof(line), f)) {
        char a[100], b[100], c[100], d[100], e[100], g[100];
        if (sscanf(line, "%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%99[^\n]",
                   a, b, c, d, e, g) == 6) {
            Adopsi ad;
            ad.adopter = a; ad.hewan   = b; ad.spesies = c;
            ad.ras     = d; ad.kontak  = e; ad.alamat  = g;
            sllTambahAdopsi(ad);
        }
    }
    fclose(f);
}

void sortHewan(Hewan *arr, int jml, int field, bool asc) {
    for (int i = 0; i < jml - 1; i++) {
        for (int j = i + 1; j < jml; j++) {
            bool tukar = (field == 1)
                ? (asc ? arr[i].nama > arr[j].nama : arr[i].nama < arr[j].nama)
                : (asc ? arr[i].umur > arr[j].umur : arr[i].umur < arr[j].umur);
            
            if (tukar) {
                Hewan temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void tampilHewan(Hewan arr[], int jml, string filter) {
    if (jml == 0) { cout << "\nData hewan di shelter masih kosong.\n"; return; }
    cout << "\n=== DAFTAR HEWAN PELIHARAAN ===\n";
    if (filter != "") cout << "Filter spesies: " << filter << "\n";
    cout << "+-----+----------------------+------------------+---------------+--------------+\n"
         << "| No  | Nama                 | Spesies          | Ras           | Umur (Bulan) |\n"
         << "+-----+----------------------+------------------+---------------+--------------+\n";

    int no = 1, tampil = 0;
    for (int i = 0; i < jml; i++) {
        if (filter == "" || sama(arr[i].spesies, filter)) {
            cout << "| " << setw(3) << left << no++ << " "
                 << "| " << setw(21) << left << arr[i].nama
                 << "| " << setw(17) << left << arr[i].spesies
                 << "| " << setw(14) << left << arr[i].ras
                 << "| " << setw(12) << right << arr[i].umur << " |\n";
            tampil++;
        }
    }
    cout << "+-----+----------------------+------------------+---------------+--------------+\n";
    if (tampil == 0)
        cout << "Tidak ada hewan dengan spesies '" << filter << "'.\n";
}

void tampilPengajuan() {
    if (!headAdopsi) { cout << "\nDaftar pengajuan adopsi kosong.\n"; return; }

    cout << "\n=== DAFTAR PENGAJUAN ADOPSI ===\n"
         << "+-----+-----------------+-----------------+-----------------+-----------------+-----------------+----------------------+\n"
         << "| No  | Adopter         | Hewan           | Spesies         | Ras             | Kontak          | Alamat               |\n"
         << "+-----+-----------------+-----------------+-----------------+-----------------+-----------------+----------------------+\n";
    int no = 1;
    for (NodeAdopsi *t = headAdopsi; t; t = t->next) {
        cout << "| " << setw(3) << left << no++ << " | "
             << setw(15) << left << t->data.adopter << " | "
             << setw(15) << left << t->data.hewan << " | "
             << setw(15) << left << t->data.spesies << " | "
             << setw(15) << left << t->data.ras << " | "
             << setw(15) << left << t->data.kontak << " | "
             << setw(20) << left << t->data.alamat << " |\n";
    }
    cout << "+-----+-----------------+-----------------+-----------------+-----------------+-----------------+----------------------+\n";
}
