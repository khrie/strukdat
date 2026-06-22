#include <bits/stdc++.h>
using namespace std;

struct Mahasiswa{
    string nim;
    string nama;
    string prodi;
    int semester;
    string password;
};

class HashTable{
    static const int SIZE = 101;
    vector<Mahasiswa>* table[SIZE];

    int hashFunc(const string& key){
        unsigned long h = 0;
        for(char c : key) h = h * 31 + c;
        return h % SIZE;
    }

public:
    HashTable(){ for(int i = 0; i < SIZE; i++) table[i] = nullptr; }

    void registrasi(const string& nim, const string& nama, const string& prodi, int semester, const string& password){
        int idx = hashFunc(nim);
        if(!table[idx]) table[idx] = new vector<Mahasiswa>();
        table[idx]->push_back({nim, nama, prodi, semester, password});
    }

    Mahasiswa* cariAkun(const string& nim){
        int idx = hashFunc(nim);
        if(!table[idx]) return nullptr;
        for(auto& m : *table[idx])
            if(m.nim == nim) return &m;
        return nullptr;
    }

    bool login(const string& nim, const string& password){
        Mahasiswa* m = cariAkun(nim);
        return m && m->password == password;
    }
};

struct ActivityNode{
    string aktivitas;
    string waktu;
    ActivityNode* next;
};

class RiwayatAktivitas{
    ActivityNode* head;
    ActivityNode* tail;
public:
    RiwayatAktivitas() : head(nullptr), tail(nullptr){}

    void tambah(const string& aktivitas, const string& waktu){
        ActivityNode* node = new ActivityNode{aktivitas, waktu, nullptr};
        if(!head) head = tail = node;
       else{ tail->next = node; tail = node; }
        cout << "  [Info] Riwayat dicatat: " << aktivitas << "\n";
    }

    void tampilkan(){
        if(!head){ cout << " (Riwayat kosong)\n"; return; }
        for(ActivityNode* cur = head; cur; cur = cur->next)
            cout << "  " << cur->waktu << " - " << cur->aktivitas << "\n";
    }
};

struct Konsultasi{
    string idAntrian;
    string nim;
    string nama;
    string dosen;
    string waktu;
};

struct QueueNode{
    Konsultasi data;
    QueueNode* next;
};

class AntrianKonsultasi{
    QueueNode* front;
    QueueNode* rear;
public:
    AntrianKonsultasi() : front(nullptr), rear(nullptr){}

    void enqueue(const Konsultasi& k){
        QueueNode* node = new QueueNode{k, nullptr};
        if(!rear) front = rear = node;
       else{ rear->next = node; rear = node; }
        cout << "  [Info] Masuk antrian konsultasi!\n";
    }

    Konsultasi dequeue(){
        Konsultasi k = front->data;
        QueueNode* tmp = front;
        front = front->next;
        if(!front) rear = nullptr;
        delete tmp;
        return k;
    }

    bool isEmpty(){ return front == nullptr; }
};

struct OrgNode{
    string jabatan;
    vector<OrgNode*> anak;
    OrgNode(string j) : jabatan(j){}
};

class StrukturOrganisasi{
    OrgNode* root;
public:
    StrukturOrganisasi(string namaRoot){ root = new OrgNode(namaRoot); }

    OrgNode* getRoot(){ return root; }

    OrgNode* tambahAnak(OrgNode* parent, string jabatan){
        OrgNode* node = new OrgNode(jabatan);
        parent->anak.push_back(node);
        return node;
    }

    void tampilkan(OrgNode* node, int depth = 0){
        cout << string(depth * 2, ' ') <<(depth ? "|- " : "") << node->jabatan << "\n";
        for(auto anak : node->anak) tampilkan(anak, depth + 1);
    }
};

struct Gedung{
    string id;
    string nama;
    string lokasi;
    double lat, lng;
};

class GraphKampus{
    map<string, int> indexOf;
    vector<string> namaLokasi;
    vector<vector<pair<int,int>>> adj; 
    map<string, Gedung> dataGedung;

    int getIndex(const string& lokasi){
        auto it = indexOf.find(lokasi);
        if(it != indexOf.end()) return it->second;
        int idx = namaLokasi.size();
        indexOf[lokasi] = idx;
        namaLokasi.push_back(lokasi);
        adj.push_back({});
        return idx;
    }

public:
    void tambahGedung(const string& id, const string& nama, const string& lokasi, double lat, double lng){
        dataGedung[nama] ={id, nama, lokasi, lat, lng};
        getIndex(nama);
    }

    Gedung* infoGedung(const string& nama){
        auto it = dataGedung.find(nama);
        return it != dataGedung.end() ? &it->second : nullptr;
    }
    
    void tambahJalan(const string& a, const string& b, int bobot){
        int ia = getIndex(a), ib = getIndex(b);
        adj[ia].push_back({ib, bobot});
        adj[ib].push_back({ia, bobot});
    }

    void ruteTercepat(const string& asal, const string& tujuan){
        int n = namaLokasi.size();
        vector<int> dist(n, INT_MAX);
        vector<int> prev(n, -1);
        vector<bool> visited(n, false);

        int src = getIndex(asal);
        dist[src] = 0;

        for(int iter = 0; iter < n; iter++){
            int u = -1, best = INT_MAX;
            for(int i = 0; i < n; i++)
                if(!visited[i] && dist[i] < best){ best = dist[i]; u = i; }
            if(u == -1) break;
            visited[u] = true;

            for(auto& edge : adj[u]){
                int v = edge.first, w = edge.second;
                if(!visited[v] && dist[u] + w < dist[v]){
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                }
            }
        }

        int dst = getIndex(tujuan);
        if(dist[dst] == INT_MAX){
            cout << "  [Error] Tidak ada rute dari " << asal << " ke " << tujuan << "\n";
            return;
        }

        vector<string> jalur;
        for(int v = dst; v != -1; v = prev[v]) jalur.push_back(namaLokasi[v]);
        reverse(jalur.begin(), jalur.end());

        cout << "  Rute Tercepat: ";
        for(size_t i = 0; i < jalur.size(); i++){
            cout << jalur[i];
            if(i + 1 < jalur.size()) cout << " -> ";
        }
        cout << "(Total Bobot/Waktu: " << dist[dst] << ")\n";
    }
};

struct StackNode{
    string kodeMK;
    StackNode* next;
};

class UndoKRS{
    StackNode* top;
public:
    UndoKRS() : top(nullptr){}

    void push(const string& kodeMK){
        StackNode* node = new StackNode{kodeMK, top};
        top = node;
        cout << "  [Info] Matkul " << kodeMK << " ditambahkan ke KRS\n";
    }

    void undo(){
        if(!top){ cout << "  [Error] Tidak ada pilihan untuk di-undo\n"; return; }
        cout << "  [Info] UNDO: " << top->kodeMK << " dihapus dari KRS\n";
        StackNode* tmp = top;
        top = top->next;
        delete tmp;
    }

    void tampilkan(){
        cout << "  Isi KRS saat ini: ";
        if(!top){ cout << "(kosong)\n"; return; }
        for(StackNode* cur = top; cur; cur = cur->next) cout << cur->kodeMK << " ";
        cout << "\n";
    }
};

struct Layanan{
    string nama;
    int prioritas; 
};

class PriorityQueueLayanan{
    vector<Layanan> heap;

    void naikkan(int i){
        while(i > 0 && heap[(i - 1) / 2].prioritas > heap[i].prioritas){
            swap(heap[i], heap[(i - 1) / 2]);
            i =(i - 1) / 2;
        }
    }

    void turunkan(int i){
        int n = heap.size();
        while(true){
            int kiri = 2 * i + 1, kanan = 2 * i + 2, kecil = i;
            if(kiri < n && heap[kiri].prioritas < heap[kecil].prioritas) kecil = kiri;
            if(kanan < n && heap[kanan].prioritas < heap[kecil].prioritas) kecil = kanan;
            if(kecil == i) break;
            swap(heap[i], heap[kecil]);
            i = kecil;
        }
    }

public:
    void insert(const string& nama, int prioritas){
        heap.push_back({nama, prioritas});
        naikkan(heap.size() - 1);
        cout << "  [Info] " << nama << " masuk antrian layanan(Prioritas " << prioritas << ")\n";
    }

    Layanan extractMin(){
        Layanan top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if(!heap.empty()) turunkan(0);
        return top;
    }

    bool isEmpty(){ return heap.empty(); }
};

void clearBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main(){
    HashTable ht;
    RiwayatAktivitas riwayat;
    AntrianKonsultasi antrian;
    UndoKRS krs;
    PriorityQueueLayanan pq;
    
    GraphKampus graph;
    graph.tambahGedung("G01", "Gerbang Utama", "Depan kampus", -7.2819, 112.7951);
    graph.tambahGedung("G02", "Perpustakaan", "Blok A", -7.2815, 112.7958);
    graph.tambahGedung("G03", "Fakultas Teknik", "Blok B", -7.2810, 112.7965);
    graph.tambahGedung("G04", "Gedung Rektorat", "Blok C", -7.2825, 112.7962);
    graph.tambahGedung("G05", "Lab Komputer", "Blok C", -7.2828, 112.7970);
    graph.tambahGedung("G06", "Kantin", "Blok D", -7.2820, 112.7975);
    graph.tambahJalan("Gerbang Utama", "Perpustakaan", 2);
    graph.tambahJalan("Gerbang Utama", "Gedung Rektorat", 3);
    graph.tambahJalan("Perpustakaan", "Fakultas Teknik", 2);
    graph.tambahJalan("Gedung Rektorat", "Lab Komputer", 3);
    graph.tambahJalan("Lab Komputer", "Kantin", 3);
    graph.tambahJalan("Fakultas Teknik", "Kantin", 3);

    StrukturOrganisasi org("Rektor");
    OrgNode* wrAkademik = org.tambahAnak(org.getRoot(), "Wakil Rektor Akademik");
    OrgNode* wrKemahasiswaan = org.tambahAnak(org.getRoot(), "Wakil Rektor Kemahasiswaan");
    org.tambahAnak(wrAkademik, "Fakultas Teknik");
    org.tambahAnak(wrAkademik, "Fakultas Ekonomi");
    org.tambahAnak(wrKemahasiswaan, "Biro Kemahasiswaan");

    string loginActive = "";

    int pilihan = -1;
    while(pilihan != 0){
        cout << "\n============================================\n";
        cout << "      SMART CAMPUS NAVIGATION SYSTEM        \n";
        cout << "============================================\n";
        if(loginActive.empty()){
            cout << "Status: Belum Login\n";
        }else{
            Mahasiswa* currentUser = ht.cariAkun(loginActive);
            cout << "Status: Logged in as " << currentUser->nama << "\n";
        }
        cout << "--------------------------------------------\n";
        cout << "1. Login / Registrasi(Hash Table)\n";
        cout << "2. Riwayat Aktivitas(Linked List)\n";
        cout << "3. Antrian Konsultasi(Queue)\n";
        cout << "4. Struktur Organisasi(Tree)\n";
        cout << "5. Navigasi Kampus(Graph)\n";
        cout << "6. Isi / Undo KRS(Stack)\n";
        cout << "7. Prioritas Layanan(Priority Queue)\n";
        cout << "0. Keluar Aplikasi\n";
        cout << "Pilih menu(0-7): ";
        cin >> pilihan;

        if(cin.fail()){
            clearBuffer();
            continue;
        }

        switch(pilihan){
            case 1:{ 
                cout << "\n-- MENU AUTENTIKASI --\n";
                cout << "1. Registrasi\n2. Login\n3. Logout\nPilih: ";
                int sub; cin >> sub; clearBuffer();
                
                if(sub == 1){
                    string nim, nama, prodi, pass; int smt;
                    cout << "NIM: "; getline(cin, nim);
                    cout << "Nama: "; getline(cin, nama);
                    cout << "Prodi: "; getline(cin, prodi);
                    cout << "Semester: "; cin >> smt; clearBuffer();
                    cout << "Password: "; getline(cin, pass);
                    ht.registrasi(nim, nama, prodi, smt, pass);
                    cout << "  [Info] Registrasi Sukses!\n";
                } 
               else if(sub == 2){
                    if(!loginActive.empty()){
                        cout << "  [Info] Anda sudah login sebagai " << loginActive << ". Silakan logout terlebih dahulu.\n";
                    }else{
                        string nim, pass;
                        cout << "NIM: "; getline(cin, nim);
                        cout << "Password: "; getline(cin, pass);
                        if(ht.login(nim, pass)){
                            loginActive = nim;
                            riwayat.tambah("Login", "Sekarang");
                        }else{
                            cout << "  [Error] Login Gagal!\n";
                        }
                    }
                }
               else if(sub == 3){
                    if(!loginActive.empty()){
                        riwayat.tambah("Logout", "Sekarang");
                        cout << "  [Info] Berhasil logout dari akun " << loginActive << ".\n";
                        loginActive = ""; 
                    }else{
                        cout << "  [Info] Anda belum login sama sekali.\n";
                    }
                }
               else{
                    cout << "  [Error] Pilihan tidak valid.\n";
                }
                break;
            }
            case 2:{ 
                cout << "\n-- RIWAYAT AKTIVITAS --\n";
                riwayat.tampilkan();
                break;
            }
            case 3:{ 
                cout << "\n-- ANTRIAN KONSULTASI --\n";
                cout << "1. Ambil Antrian\n2. Panggil Giliran\nPilih: ";
                int sub; cin >> sub; clearBuffer();
                if(sub == 1){
                    string nim, nama, dosen;
                    cout << "NIM: "; getline(cin, nim);
                    cout << "Nama: "; getline(cin, nama);
                    cout << "Dosen Tujuan: "; getline(cin, dosen);
                    antrian.enqueue({"A" + to_string(rand()%1000), nim, nama, dosen, "Sekarang"});
                    if(loginActive == nim) riwayat.tambah("Ambil Antrian Konsultasi", "Sekarang");
                }else if(sub == 2){
                    if(!antrian.isEmpty()){
                        Konsultasi k = antrian.dequeue();
                        cout << "  [Panggilan] " << k.nama << " harap menuju meja " << k.dosen << "\n";
                    }else{
                        cout << "  [Info] Antrian kosong.\n";
                    }
                }
                break;
            }
            case 4:{ 
                cout << "\n-- STRUKTUR ORGANISASI KAMPUS --\n";
                org.tampilkan(org.getRoot());
                break;
            }
            case 5:{ 
                cout << "\n-- NAVIGASI KAMPUS --\n";
                clearBuffer();
                string asal, tujuan;
                cout << "Lokasi Asal(ex: Gerbang Utama): "; getline(cin, asal);
                cout << "Lokasi Tujuan(ex: Fakultas Teknik): "; getline(cin, tujuan);
                graph.ruteTercepat(asal, tujuan);
                if(!loginActive.empty()) riwayat.tambah("Mencari rute ke " + tujuan, "Sekarang");
                break;
            }
            case 6:{
                cout << "\n-- PENGISIAN KRS --\n";
                cout << "1. Tambah Matkul\n2. Undo Pilihan Terakhir\n3. Lihat KRS\nPilih: ";
                int sub; cin >> sub; clearBuffer();
                if(sub == 1){
                    string mk;
                    cout << "Kode/Nama Matkul: "; getline(cin, mk);
                    krs.push(mk);
                    if(!loginActive.empty()) riwayat.tambah("Tambah KRS: " + mk, "Sekarang");
                }else if(sub == 2){
                    krs.undo();
                    if(!loginActive.empty()) riwayat.tambah("Undo KRS", "Sekarang");
                }else if(sub == 3){
                    krs.tampilkan();
                }
                break;
            }
            case 7:{ 
                cout << "\n-- PRIORITAS LAYANAN --\n";
                cout << "1. Daftar Layanan Khusus\n2. Panggil Layanan Teratas\nPilih: ";
                int sub; cin >> sub; clearBuffer();
                if(sub == 1){
                    string nama; int prio;
                    cout << "Nama Pemohon: "; getline(cin, nama);
                    cout << "Tingkat Prioritas(1=Beasiswa/Tinggi, 2=Difabel, 3=Reguler): "; 
                    cin >> prio;
                    pq.insert(nama, prio);
                }else if(sub == 2){
                    if(!pq.isEmpty()){
                        Layanan l = pq.extractMin();
                        cout << "  [Panggilan] Melayani: " << l.nama << "(Prioritas " << l.prioritas << ")\n";
                    }else{
                        cout << "  [Info] Tidak ada antrian khusus.\n";
                    }
                }
                break;
            }
            case 0:
                cout << "\nKeluar dari program. Terima kasih!\n";
                break;
            default:
                cout << "\nPilihan tidak valid.\n";
        }
    }
    return 0;
}
