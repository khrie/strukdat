# Dokumentasi Sistem: Smart Campus Navigation System

Aplikasi ini dibangun menggunakan bahasa C++ dengan implementasi 7 struktur data murni (*from scratch*). Berikut adalah rincian teknis, letak kode (berdasarkan baris), dan cara kerjanya.

---

## 1. Hash Table (Modul Autentikasi & Login)
**📍 Lokasi Kode Inti: Baris 4 - 42**
**📍 Lokasi Eksekusi di Main: Baris 274, 310, 344, 354**

Hash Table digunakan untuk memetakan NIM mahasiswa ke data akun secara instan.
* **Struktur Data (Baris 4 - 14)**: 
  Sistem menyimpan data dalam bentuk `struct Mahasiswa`. Hash Table-nya sendiri dideklarasikan di **baris 14** sebagai `vector<Mahasiswa>* table[SIZE]`. Ini adalah array berukuran 101 yang berisi pointer ke `vector` (Teknik penanganan kolisi menggunakan *Chaining*).
* **Fungsi Hashing (Baris 16 - 20)**:
  Fungsi `hashFunc()` mengubah string `NIM` menjadi indeks angka (0-100) menggunakan algoritma *Polynomial Rolling Hash* (`h = h * 31 + c`).
* **Operasi Insert / Registrasi (Baris 25 - 29)**:
  Fungsi `registrasi()` mencari laci (*index*) menggunakan `hashFunc`. Jika laci kosong, sistem membuat vector baru (`new vector`), lalu memasukkan data mahasiswa (`push_back`). Diakses di menu utama pada **baris 344**.
* **Operasi Search / Login (Baris 31 - 41)**:
  Fungsi `cariAkun()` mencari data berdasarkan NIM. Fungsi `login()` akan memvalidasi apakah password yang diinput cocok dengan password di dalam Hash Table. Diakses di menu utama pada **baris 354**.

---

## 2. Linked List (Modul Riwayat Aktivitas)
**📍 Lokasi Kode Inti: Baris 44 - 66**
**📍 Lokasi Eksekusi di Main: Baris 275, 356, 366, 375, 394...**

Digunakan untuk mencatat jejak (*log*) aktivitas mahasiswa seperti "Login", "Tambah KRS", dll.
* **Struktur Node (Baris 44 - 48)**: Menggunakan `struct ActivityNode` yang berisi string `aktivitas`, string `waktu`, dan pointer `next` yang menunjuk ke memori aktivitas berikutnya.
* **Operasi Insert (Baris 55 - 59)**: Fungsi `tambah()` memasukkan riwayat baru selalu di posisi ekor (`tail`) tanpa menggeser data yang sudah ada (kompleksitas $O(1)$).
* **Operasi Traversal (Baris 61 - 65)**: Fungsi `tampilkan()` membaca data secara berurutan mulai dari kepala (`head`) hingga ekor (`tail`).

---

## 3. Queue (Modul Antrian Konsultasi Dosen)
**📍 Lokasi Kode Inti: Baris 68 - 103**
**📍 Lokasi Eksekusi di Main: Baris 276, 392, 396**

Digunakan untuk memastikan antrian layanan akademik adil dengan prinsip FIFO (*First In First Out*).
* **Struktur (Baris 68 - 79)**: Menggunakan pointer `front` (depan) dan `rear` (belakang).
* **Enqueue (Baris 85 - 89)**: Mahasiswa yang mengambil antrian akan diletakkan di posisi paling belakang (`rear`). Dipanggil pada **baris 392**.
* **Dequeue (Baris 91 - 98)**: Saat dosen memanggil giliran, antrian diambil dari posisi paling depan (`front`), dan memori node tersebut dihapus (`delete tmp`) untuk menghemat RAM. Dipanggil pada **baris 396**.

---

## 4. Tree (Struktur Organisasi Kampus)
**📍 Lokasi Kode Inti: Baris 105 - 128**
**📍 Lokasi Eksekusi di Main: Baris 291 - 297, 406**

Digunakan untuk menyimpan dan menampilkan hierarki jabatan di kampus.
* **Struktur Node (Baris 105 - 109)**: `struct OrgNode` menyimpan nama jabatan dan `vector<OrgNode*> anak` (N-ary Tree, di mana satu *parent* bisa memiliki banyak *child*).
* **Pembuatan Tree (Baris 291 - 297)**: Di dalam `main()`, node "Rektor" di-set sebagai `root`, lalu ditambahkan cabang-cabangnya secara manual (Wakil Rektor, Fakultas, dll).
* **Pencetakan (Baris 124 - 127)**: Mencetak hierarki ke layar menggunakan teknik rekursi bersarang (*Pre-Order Traversal*).

---

## 5. Graph (Modul Navigasi Kampus)
**📍 Lokasi Kode Inti: Baris 130 - 211**
**📍 Lokasi Eksekusi di Main: Baris 278 - 289, 415**

Digunakan untuk mencari rute jalan terpendek antar gedung.
* **Representasi Map (Baris 138 - 140)**: Menyimpan graf tak berarah (*Undirected Graph*) menggunakan *Adjacency List* (`adj`). Variabel `indexOf` digunakan untuk mengubah nama string (misal: "Kantin") menjadi angka *Vertex*.
* **Algoritma Dijkstra (Baris 171 - 210)**: 
  Sistem mengevaluasi bobot/jarak jalan antar gedung secara iteratif (pada perulangan `for` di **baris 177**). Node yang memiliki total bobot terpendek direkam di array `dist`, dan jejak rutenya direkam di array `prev` untuk dilacak ulang (di- *reverse*) saat rute dicetak ke layar.

---

## 6. Stack (Modul Undo Pengisian KRS)
**📍 Lokasi Kode Inti: Baris 213 - 243**
**📍 Lokasi Eksekusi di Main: Baris 277, 426, 429, 432**

Digunakan untuk simulasi pembatalan pilihan mata kuliah.
* **Prinsip (Baris 223)**: Hanya ada satu akses poin, yaitu `top` (tumpukan paling atas), sesuai prinsip LIFO (*Last In First Out*).
* **Push (Baris 225 - 229)**: Memasukkan mata kuliah baru yang otomatis menjadi `top` yang baru. Dipanggil di **baris 426**.
* **Undo / Pop (Baris 231 - 236)**: Membuang elemen `top` saat ini, dan menggantinya dengan node yang ada di bawahnya (`top->next`). Dipanggil di **baris 429**.

---

## 7. Priority Queue (Modul Layanan Prioritas)
**📍 Lokasi Kode Inti: Baris 245 - 287**
**📍 Lokasi Eksekusi di Main: Baris 278, 444, 448**

Digunakan untuk melayani mahasiswa berdasarkan tingkat prioritas (contoh: Beasiswa/Difabel dilayani duluan dibanding Reguler).
* **Struktur Min-Heap (Baris 251)**: Menggunakan manipulasi *array/vector* (`heap`) untuk meniru *Binary Tree*.
* **Mekanisme *Sift-Up* (Baris 253 - 258)**: Ketika data dimasukkan (`insert`), angka prioritas akan dibandingkan dengan *parent*-nya. Jika lebih kecil (lebih penting), posisinya akan "naik/ditukar" terus menerus hingga mencapai posisi puncaknya.
* **Mekanisme *Sift-Down* (Baris 260 - 269)**: Ketika prioritas tertinggi dipanggil (`extractMin`), posisinya digantikan oleh elemen paling bawah, yang kemudian di "turunkan/ditukar" ke bawah untuk menstabilkan struktur Heap.

---

## 8. Fungsi Helper & Sistem Interaktif (Main Loop)
**📍 Lokasi Kode Inti: Baris 289 - 485**

* **Clear Buffer (Baris 289 - 292)**: Mencegah *error input skip* jika *user* memasukkan tipe data yang salah di konsol.
* **Sesi Login Aktif (Baris 299)**: Variabel `loginActive` menahan NIM pengguna. 
* **Tampilan Status Otomatis (Baris 307 - 312)**: *Real-time check* menggunakan **Hash Table** `ht.cariAkun()` untuk menampilkan nama asli mahasiswa yang sedang *login* di bagian atas menu.
* **Switch-Case Loop (Baris 337 - 482)**: Sistem antarmuka *Command Line* yang menghubungkan ke-7 struktur data di atas sesuai dengan input angka dari pengguna.
