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

void menuLihatHewan(Hewan arr[], int jml) {
    if (jml == 0) { cout << "Data hewan kosong.\n"; return; }
    int pF, pS, pU;
    string filter = "";
    cout << "\n1. Tampilkan Semua\n2. Filter Spesies\nPilih: ";
    cin >> pF; cin.ignore();
    if (pF == 2) { 
        cout << "\n=== DAFTAR SPESIES TERSEDIA ===\n";
        cout << "+-----+----------------------+\n";
        cout << "| No  | Nama Spesies         |\n";
        cout << "+-----+----------------------+\n";
        
        int noSpesies = 1;
        for (int i = 0; i < jml; i++) {
            bool sudahAda = false;
            for (int j = 0; j < i; j++) {
                if (sama(arr[i].spesies, arr[j].spesies)) {
                    sudahAda = true;
                    break;
                }
            }
            if (!sudahAda) {
                cout << "| " << setw(3) << left << noSpesies++ << " | "
                     << setw(20) << left << arr[i].spesies << " |\n";
            }
        }
        cout << "+-----+----------------------+\n";
        cout << "Ketik spesies yang ingin ditampilkan: "; 
        getline(cin, filter); 
    }
    cout << "\n1. Sort Nama  2. Sort Umur\nPilih: ";
    cin >> pS; cin.ignore();
    cout << "1. Ascending  2. Descending\nPilih: ";
    cin >> pU; cin.ignore();

    sortHewan(arr, jml, pS, pU == 1);
    tampilHewan(arr, jml, filter);
}

void cariHewan(Hewan arr[], int jml) {
    tampilHewan(arr, jml, ""); 
    if (jml == 0) return;
    string nama, spesies, ras;
    cout << "\n--- PENCARIAN HEWAN (SPESIFIK) ---\n";
    cout << "Nama hewan yang dicari    : "; getline(cin, nama);
    cout << "Spesies hewan yang dicari : "; getline(cin, spesies);
    cout << "Ras hewan yang dicari     : "; getline(cin, ras);
    bool ditemukan = false;
    for (int i = 0; i < jml; i++) {
        if (sama(arr[i].nama, nama) && sama(arr[i].spesies, spesies) && sama(arr[i].ras, ras)) {
            cout << "\n=== Data Hewan Ditemukan ===\n"
                 << "Nama    : " << arr[i].nama    << "\n"
                 << "Spesies : " << arr[i].spesies << "\n"
                 << "Ras     : " << arr[i].ras     << "\n"
                 << "Umur    : " << arr[i].umur    << " bulan\n";
            ditemukan = true;
            break; 
        }
    }
    if (!ditemukan) cout << "Hewan tidak ditemukan atau data tidak cocok.\n";
}

void tambahHewan(Hewan arr[], int &jml) {
    tampilHewan(arr, jml, ""); 
    int n;
    cout << "\n--- TAMBAH DATA HEWAN ---\n";
    cout << "Jumlah hewan yang ditambahkan: ";
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        Hewan h;
        cout << "\nData hewan ke-" << jml + 1 << "\n";
        cout << "Nama    : "; getline(cin, h.nama);
        cout << "Spesies : "; getline(cin, h.spesies);
        cout << "Ras     : "; getline(cin, h.ras);
        
        bool isDuplicate = false;
        for (NodeHewan *c = headHewan; c; c = c->next) {
            if (sama(c->data.nama, h.nama) && 
                sama(c->data.spesies, h.spesies) && 
                sama(c->data.ras, h.ras)) {
                isDuplicate = true;
                break;
            }
        }
        if (isDuplicate) {
            cout << "-> ERROR: Hewan dengan Nama, Spesies, dan Ras tersebut sudah terdaftar di shelter!\n";
            cout << "-> Silakan masukkan data hewan yang berbeda.\n";
            i--; 
            continue; 
        }
        cout << "Umur    : "; cin >> h.umur; cin.ignore();
        
        arr[jml++] = h;
        dllTambah(h);
    }
    cout << "Hewan berhasil ditambahkan!\n";
}

void editHewan(Hewan arr[], int jml) {
    tampilHewan(arr, jml, ""); 
    if (jml == 0) return;

    string namaLama, spesiesLama, rasLama;
    cout << "\n--- EDIT DATA HEWAN ---\n";
    cout << "Ketik nama hewan yang ingin diedit    : "; getline(cin, namaLama);
    cout << "Ketik spesies hewan yang ingin diedit : "; getline(cin, spesiesLama);
    cout << "Ketik ras hewan yang ingin diedit     : "; getline(cin, rasLama);
    
    NodeHewan *n = nullptr;
    for (NodeHewan *c = headHewan; c; c = c->next) {
        if (sama(c->data.nama, namaLama) && sama(c->data.spesies, spesiesLama) && sama(c->data.ras, rasLama)) {
            n = c;
            break;
        }
    }

    if (!n) { cout << "Hewan dengan kombinasi data tersebut tidak ditemukan.\n"; return; }
    cout << "\nData saat ini -> Nama: " << n->data.nama
         << " | Spesies: " << n->data.spesies
         << " | Ras: " << n->data.ras
         << " | Umur: " << n->data.umur << " bulan\n";
    string namaBaru, spesiesBaru, rasBaru;
    int umurBaru;
    cout << "\nNama baru    : "; getline(cin, namaBaru);
    cout << "Spesies baru : "; getline(cin, spesiesBaru);
    cout << "Ras baru     : "; getline(cin, rasBaru);
    
    bool isDuplicate = false;
    for (NodeHewan *c = headHewan; c; c = c->next) {
        if (c != n && 
            sama(c->data.nama, namaBaru) && 
            sama(c->data.spesies, spesiesBaru) && 
            sama(c->data.ras, rasBaru)) {
            isDuplicate = true;
            break;
        }
    }
    if (isDuplicate) {
        cout << "-> ERROR: Gagal mengubah. Kombinasi Nama, Spesies, dan Ras tersebut sudah dimiliki hewan lain!\n";
        return; 
    }
    cout << "Umur baru    : "; cin >> umurBaru; cin.ignore();
    n->data.nama = namaBaru;
    n->data.spesies = spesiesBaru;
    n->data.ras = rasBaru;
    n->data.umur = umurBaru;
    
    cout << "Data hewan berhasil diupdate!\n";
}

void hapusHewan(Hewan arr[], int jml) {
    tampilHewan(arr, jml, ""); 
    if (jml == 0) return;
    string nama, spesies, ras;
    cout << "\n--- HAPUS DATA HEWAN ---\n";
    cout << "Ketik nama hewan yang ingin dihapus    : "; getline(cin, nama);
    cout << "Ketik spesies hewan yang ingin dihapus : "; getline(cin, spesies);
    cout << "Ketik ras hewan yang ingin dihapus     : "; getline(cin, ras);

    NodeHewan *target = nullptr;
    for (NodeHewan *c = headHewan; c; c = c->next) {
        if (sama(c->data.nama, nama) && sama(c->data.spesies, spesies) && sama(c->data.ras, ras)) {
            target = c;
            break;
        }
    }
    if (!target) { 
        cout << "Hewan dengan kombinasi data tersebut tidak ditemukan di shelter.\n"; 
        return; 
    }
    dllHapus(target);
    cout << "Hewan berhasil dihapus dari sistem!\n";
}

void ajukanAdopsi(Hewan arr[], int jml) {
    tampilHewan(arr, jml, ""); 
    if (jml == 0) return;

    cout << "\n--- FORM PENGAJUAN ADOPSI ---\n";
    string nama, spesies, ras;
    cout << "Ketik nama hewan yang ingin diadopsi    : "; getline(cin, nama);
    cout << "Ketik spesies hewan yang ingin diadopsi : "; getline(cin, spesies);
    cout << "Ketik ras hewan yang ingin diadopsi     : "; getline(cin, ras);
    int idx = -1;
    for (int i = 0; i < jml; i++) {
        if (sama(arr[i].nama, nama) && sama(arr[i].spesies, spesies) && sama(arr[i].ras, ras)) { 
            idx = i; 
            break; 
        }
    }
    if (idx == -1) { cout << "Hewan dengan kombinasi data tersebut tidak ditemukan di shelter.\n"; return; }

    Adopsi a;
    a.hewan   = arr[idx].nama;
    a.spesies = arr[idx].spesies;
    a.ras     = arr[idx].ras;
    cout << "Ketik Nama pengadopsi : "; getline(cin, a.adopter);
  
    bool sudahMengajukan = false;
    for (NodeAdopsi *c = headAdopsi; c != nullptr; c = c->next) {
        if (sama(c->data.adopter, a.adopter)) {
            sudahMengajukan = true;
            break;
        }
    }

    if (sudahMengajukan) {
        cout << "-> ERROR: Pengadopsi atas nama '" << a.adopter << "' sudah memiliki pengajuan aktif!\n";
        cout << "-> Satu orang hanya diperbolehkan mengajukan satu adopsi pada satu waktu.\n";
        return; 
    }
    cout << "Nomor Kontak          : "; getline(cin, a.kontak);
    cout << "Alamat Lengkap        : "; getline(cin, a.alamat);
    sllTambahAdopsi(a);
    cout << "Pengajuan adopsi atas nama '" << a.adopter << "' berhasil didaftarkan!\n";
}

void batalUser() {
    tampilPengajuan();
    if (!headAdopsi) return;

    cout << "\n--- BATALKAN PENGAJUAN ---\n";
    string adopter, hewan, spesies, ras;
    cout << "Ketik Nama pengadopsi : "; getline(cin, adopter);
    cout << "Ketik Nama hewan      : "; getline(cin, hewan);
    cout << "Ketik Spesies hewan   : "; getline(cin, spesies);
    cout << "Ketik Ras hewan       : "; getline(cin, ras);

    NodeAdopsi *c = headAdopsi, *p = nullptr;
    while (c) {
        if (sama(c->data.adopter, adopter) && 
            sama(c->data.hewan, hewan) && 
            sama(c->data.spesies, spesies) && 
            sama(c->data.ras, ras)) {
            
            sllHapusAdopsi(c, p);
            cout << "Pengajuan berhasil dibatalkan!\n";
            return;
        }
        p = c; c = c->next;
    }
    cout << "Data pengajuan tidak ditemukan.\n";
}

void batalAdmin() {
    tampilPengajuan();
    if (!headAdopsi) return;
    int no;
    cout << "\nNomor pengajuan yang ingin ditolak/dihapus: "; cin >> no; cin.ignore();
    
    if (no < 1) {
        cout << "Nomor pengajuan tidak valid. Harus dimulai dari 1.\n";
        return;
    }
    NodeAdopsi *c = headAdopsi, *p = nullptr;
    int pos = 1;
    while (c && pos < no) { p = c; c = c->next; pos++; }
    
    if (!c) { cout << "Nomor pengajuan tidak valid.\n"; return; }
    
    cout << "Pengajuan atas nama '" << c->data.adopter << "' telah dihapus.\n";
    sllHapusAdopsi(c, p);
}

void setujuiAdopsi(Hewan arr[], int &jml) {
    tampilPengajuan();
    if (!headAdopsi) return;
    int no;
    cout << "\nNomor pengajuan yang ingin disetujui: "; cin >> no; cin.ignore();

    if (no < 1) {
        cout << "Nomor pengajuan tidak valid. Harus dimulai dari 1.\n";
        return;
    }
    NodeAdopsi *target = headAdopsi;
    int pos = 1;
    while (target && pos < no) { 
        target = target->next; 
        pos++; 
    }
    
    if (!target) { cout << "Nomor pengajuan tidak valid.\n"; return; }
    string namaHewan = target->data.hewan;
    string spesiesHewan = target->data.spesies;
    string rasHewan = target->data.ras;
    string namaAdopter = target->data.adopter;
    cout << "Adopsi disetujui! Hewan '" << namaHewan << "' telah diadopsi oleh '" << namaAdopter << "'.\n";
    
    // Hapus dari data hewan
    NodeHewan *nh = headHewan;
    while (nh) {
        if (sama(nh->data.nama, namaHewan) && sama(nh->data.spesies, spesiesHewan) && sama(nh->data.ras, rasHewan)) {
            NodeHewan *tmp = nh; 
            nh = nh->next;
            dllHapus(tmp);
            cout << ">> Hewan otomatis dihapus dari daftar shelter.\n";
            break;
        } else {
            nh = nh->next;
        }
    }
    
    // Hapus dari antrean pengajuan
    int count = 0;
    NodeAdopsi *c = headAdopsi, *p = nullptr;
    while (c) {
        if (sama(c->data.hewan, namaHewan) && sama(c->data.spesies, spesiesHewan) && sama(c->data.ras, rasHewan)) {
            NodeAdopsi *tmp = c; 
            c = c->next;
            sllHapusAdopsi(tmp, p); 
            count++;
        } else { 
            p = c; 
            c = c->next; 
        }
    }
    cout << ">> " << count << " riwayat pengajuan (termasuk yang disetujui) telah dibersihkan dari daftar.\n";
}
