# CHEATSHEET & PREDIKSI SOAL PRAKTIKUM MODUL 3
**Mata Kuliah: Jaringan Komputer | Departemen Teknik Informatika ITS**  
**Nama: Nabil Khairie | NRP: 5025251066 | Kelas: Jaringan Komputer C | IP Prefix: `10.181`**

---

## DAFTAR ISI
1. [Analisis Pola Soal: Pra-Praktikum vs Praktikum (Modul 1, 2, & 3)](#1-analisis-pola-soal-pra-praktikum-vs-praktikum)
2. [Naskah Prediksi Resmi: Soal Praktikum Modul 3](#2-naskah-prediksi-resmi-soal-praktikum-modul-3)
   - [Versi Bahasa Indonesia](#indo-version)
   - [English Version](#english-version)
3. [Panduan Instalasi Paket & Dependencies (Kea DHCP, iperf3, tc, dll.)](#3-panduan-instalasi-paket--dependencies-kea-dhcp4-iperf3-tc-dll)
4. [Skrip Otomasi Cepat Setup Topologi & Konfigurasi IP (Ready-to-Use 10.181)](#4-skrip-otomasi-cepat-setup-topologi--konfigurasi-ip-ready-to-use-10181)
5. [Ensiklopedi Perintah Traffic Control (`tc`) Lengkap](#5-ensiklopedi-perintah-traffic-control-tc-lengkap)
6. [Ensiklopedi Wireshark, Termshark & Tshark Filter](#6-ensiklopedi-wireshark-termshark--tshark-filter)
7. [Ensiklopedi TCP Congestion Control (CUBIC, Reno, BBR)](#7-ensiklopedi-tcp-congestion-control)
8. [Ensiklopedi Benchmark iperf3 (TCP vs UDP)](#8-ensiklopedi-benchmark-iperf3-tcp-vs-udp)
9. [Bank Jawaban Tanya Jawab Asisten Penguji (Oral Defense 100/100)](#9-bank-jawaban-tanya-jawab-asisten-penguji-oral-defense-100100)
10. [Troubleshooting Guide / Penyelamat Error Saat Praktikum](#10-troubleshooting-guide--penyelamat-error-praktikum)
11. [Prosedur Pemulihan Pasca Restart GNS3 (Disaster Recovery Protocol)](#11-prosedur-pemulihan-pasca-restart-gns3-disaster-recovery-protocol)

---

# 1. ANALISIS POLA SOAL: PRA-PRAKTIKUM VS PRAKTIKUM

Berdasarkan komparasi mendalam antara Modul 1 dan Modul 2:

| Aspek | Pra-Praktikum (Modul 1, 2, 3) | Praktikum (Modul 1, 2, 3) |
| :--- | :--- | :--- |
| **Bentuk Soal** | Tutorial modular terpisah (Part A, B, C, D, E) dengan panduan langkah demi langkah. | Satu skenario utuh (*integrated mission/prologue*) berorientasi *real-world problem*. |
| **Topologi** | Dibangun bertahap atau sudah disediakan sejak awal. | Menggunakan kembali topologi Pra-Praktikum (kadang ada penambahan 1 node atau pengujian terpusat). |
| **Fokus Pengujian** | Pengisian tabel data mentah dan bukti screenshot per sub-bab. | Demonstrasi langsung ke asisten (*live demo*) membuktikan fungsi bekerja sesuai kriteria (*Poin Keberhasilan*). |
| **Oral Defense** | Menjawab pertanyaan refleksi di `README.md`. | Wawancara langsung 2–3 pertanyaan analisis & diagnostik dengan asisten penguji. |
| **Durasi** | 1–2 minggu pengerjaan mandiri. | Tepat **2 Jam** tanpa AI/LLM, live di lab GNS3. |

### Transformasi Topologi Modul 3:
Pada Modul 3, topologi dasar telah mencakup:
- **3 Router**: `RhodesIsland` (Core/NAT Gateway), `Lungmen` (Router Subnet 3.0), `Ursus` (Router Subnet 4.0).
- **2 DHCP Server**: `Victoria` (Subnet 3.0), `Yan` (Subnet 4.0).
- **1 Web/Data Server**: `Laterano` (`10.181.4.15` di Subnet 4.0).
- **1 Desktop Client**: `Columbia` (DHCP di Subnet 3.0).

Pada sesi Praktikum, skenario akan menempatkan `RhodesIsland` sebagai **jalur WAN bottleneck** yang menghubungkan dua kantor cabang (`Columbia` dan `Laterano`), di mana praktikan diminta mengonfigurasi routing, mensimulasikan gangguan link secara live, membuktikan retransmisi TCP via packet capture, menguji algoritma congestion control, dan membandingkan TCP vs UDP.

---

# 2. NASKAH PREDIKSI RESMI: SOAL PRAKTIKUM MODUL 3

## Indo Version
**Praktikum Modul 3**  
**Reliable Data Transfer TCP, Congestion Control & Static Routing**  
**Pre-requisite:**
1. Praktikan sudah harus dan wajib mengerjakan seluruh soal yang ada pada pra-praktikum sebelum mengikuti praktikum.
2. Apabila ada bagian yang tidak dikerjakan, maka berisiko praktikan akan mengalami kendala.
3. Sudah terdapat GNS3 VM dan GNS3-GUI serta appliance `netics-pc` dan `netics-pc-desktop`.
4. Praktikan dapat melihat referensi online, namun **TIDAK boleh menggunakan AI/LLM** untuk menjawab soal.
5. Praktikum dilaksanakan selama **2 Jam**.

**Prolog:**  
Organisasi Rhodes Island sedang memperluas jaringan operasional antara dua fasilitas terpencil: Kantor Operasional Lapangan (Subnet Lungmen - Columbia) dan Pusat Arsip Farmasi / Server Data Medis (Subnet Ursus - Laterano). Seluruh komunikasi data antar cabang harus melintasi Router Pusat (RhodesIsland) yang terhubung ke jaringan WAN satelit.  
Namun, koneksi satelit tersebut memiliki kapasitas terbatas, latensi tinggi, dan rentan terhadap gangguan cuaca buruk (packet loss). Sebagai Network Engineer Rhodes Island, Anda ditugaskan oleh Dokter Kal'tsit untuk:
1. Memastikan interkonektivitas routing antar cabang dan akses internet NAT berjalan stabil.
2. Mengonfigurasi simulasi link WAN satelit pada Router RhodesIsland dengan pembatasan bandwidth, latensi, dan packet loss.
3. Membuktikan mekanisme keandalan transfer data TCP (3-Way Handshake, Duplicate ACK, dan Fast Retransmission) saat terjadi kehilangan paket melalui packet sniffing.
4. Menganalisis ketahanan transfer berkas rekam medis menggunakan perbandingan algoritma TCP Congestion Control (CUBIC vs Reno).
5. Membandingkan perilaku throughput dan keandalan transmisi antara TCP (aplikasi berkas) dan UDP (aplikasi streaming telemetri darurat).

**Topologi & Pemetaan Node:**
Gunakan topologi Pra-Praktikum Modul 3 dengan alokasi IP Prefix Anda (`10.181.x.x`).

| Node | Appliance | Peran | Alamat IP |
| :--- | :--- | :--- | :--- |
| **RhodesIsland** | netics-pc | Gateway Utama / NAT Router / Titik `tc` | eth0: DHCP (NAT Internet)<br>eth1: 10.181.1.1/24 (ke Lungmen)<br>eth2: 10.181.2.1/24 (ke Ursus) |
| **Lungmen** | netics-pc | Router Cabang Lungmen | eth0: 10.181.1.2/24 (gw 10.181.1.1)<br>eth1: 10.181.3.1/24 (LAN Columbia) |
| **Ursus** | netics-pc | Router Cabang Ursus | eth0: 10.181.2.2/24 (gw 10.181.2.1)<br>eth1: 10.181.4.1/24 (LAN Laterano) |
| **Victoria** | netics-pc | DHCP Server Subnet 3.0/24 | 10.181.3.2/24 (gw 10.181.3.1), pool 10.181.3.100–120 |
| **Columbia** | netics-pc-desktop | Client Uji (curl, iperf3, Wireshark/Browser) | Auto (DHCP dari Victoria) |
| **Yan** | netics-pc | DHCP Server Subnet 4.0/24 | 10.181.4.2/24 (gw 10.181.4.1), pool 10.181.4.50–60 |
| **Laterano** | netics-pc | Server HTTP Port 9999 & iperf3 Server | Auto (DHCP dari Yan, reservasi statis 10.181.4.15) |

---

### Soal Praktikum:
1. **Interkoneksi Jaringan, Routing & Internet Gateway:**  
   Konfigurasikan seluruh router (`RhodesIsland`, `Lungmen`, `Ursus`) dan DHCP Server (`Victoria`, `Yan`) agar client `Columbia` dan server `Laterano` mendapatkan IP otomatis serta seluruh node di topologi dapat saling terhubung (dibuktikan dengan ping) dan dapat mengakses internet melalui NAT RhodesIsland.
2. **Simulasi Karakteristik Link WAN Satelit (`tc`):**  
   Pada router `RhodesIsland`, simulasikan kondisi link WAN pada interface yang menghubungkan ke kedua cabang (`eth1` dan `eth2`):
   - Batasi bandwidth sebesar **2 Mbps** (menggunakan Token Bucket Filter / `tbf` dengan burst 32kbit).
   - Tambahkan *delay* transmisi sebesar **100 ms** (RTT bolak-balik $\approx 200$ ms) dan *random packet loss* sebesar **1%** (menggunakan `netem`).
   - Tunjukkan status qdisc aktif dengan perintah `tc -s qdisc show`.
3. **Observasi Mekanisme Reliable Data Transfer TCP (Wireshark / Termshark):**  
   Lakukan pengunduhan berkas uji (misal `tes5M.bin` atau berkas lain) dari `Laterano` ke `Columbia` menggunakan `curl`. Buka packet capture dan tunjukkan kepada asisten:
   - Proses **3-Way Handshake** (SYN, SYN-ACK, ACK) beserta nilai Sequence & Acknowledgment Number awal (ISN).
   - Bukti kemunculan **Duplicate ACK** pada sisi receiver (`Columbia`) saat segmen data hilang.
   - Bukti tindakan **Fast Retransmission** dan/atau **Retransmission** pada sisi sender (`Laterano`).
4. **Evaluasi TCP Congestion Control (CUBIC vs Reno):**  
   Lakukan uji coba unduh berkas yang sama dari `Laterano` ke `Columbia` dalam kondisi link WAN yang dibatasi pada Soal 2:
   - Uji algoritma default **CUBIC** pada `Laterano`, catat kecepatan transfer (*average speed*) dan durasi waktu.
   - Ubah algoritma congestion control pada `Laterano` menjadi **Reno**, jalankan pengunduhan yang sama, lalu catat hasilnya.
   - Tunjukkan kepada asisten perbandingan performa keduanya dan jelaskan kurva pertumbuhan window masing-masing saat terjadi packet loss.
5. **Uji Stres Transmisi Data: TCP vs UDP di Bawah Loss Tinggi:**  
   Tingkatkan *packet loss* pada `RhodesIsland` menjadi **5%** (atau **10%**).
   - Jalankan pengujian bandwidth menggunakan `iperf3` mode TCP selama 10 detik dari `Columbia` ke `Laterano`.
   - Jalankan pengujian bandwidth menggunakan `iperf3` mode UDP (`-u -b 5M`) selama 10 detik dari `Columbia` ke `Laterano`.
   - Bandingkan throughput riil, jumlah paket retransmisi pada TCP, serta persentase *lost datagrams* dan *jitter* pada UDP.
6. **Pertanyaan Analisis ke Asisten Penguji:**  
   Jelaskan kepada asisten:
   1. Mengapa TCP menginterpretasikan setiap kehilangan paket (*packet loss*) sebagai kemacetan jaringan (*congestion*), dan bagaimana dampak asumsi ini terhadap performa transfer pada media yang memiliki *random loss*?
   2. Mengapa receiver mengirimkan Duplicate ACK, dan mengapa sender harus menunggu tepat 3 Duplicate ACK sebelum melakukan Fast Retransmit?
   3. Mengapa UDP dapat mentransfer data dengan kecepatan stabil mendekati kapasitas target meskipun terjadi packet loss tinggi, sedangkan throughput TCP anjlok drastis?

---

### Poin Keberhasilan (Rubrik Penilaian):
1. Seluruh node di jaringan saling terhubung via ping (0% loss pada kondisi normal) dan dapat mengakses internet via NAT `RhodesIsland`.
2. Rule `tc` (tbf rate limit, netem delay, dan loss) terpasang dengan benar pada interface `eth1` dan `eth2` di `RhodesIsland`.
3. Mampu mendemonstrasikan proses Handshake, Duplicate ACK (minimal 3 dup ACK), dan Fast Retransmission pada Wireshark/Termshark secara langsung di hadapan asisten.
4. Berhasil membandingkan metrik performa CUBIC vs Reno menggunakan `curl` beserta penjelasan perbedaan algoritma.
5. Menampilkan hasil `iperf3` TCP vs UDP pada kondisi loss tinggi, membuktikan adanya retransmisi pada TCP dan packet loss konstan pada UDP.
6. Mampu menjawab pertanyaan lisan asisten mengenai mekanisme TCP, AIMD, dan perbandingan TCP vs UDP secara lugas dan ilmiah.

---

## English Version
**Module 3 Practicum**  
**Reliable Data Transfer TCP, Congestion Control & Static Routing**  
*(See Indonesian version above for technical specifications, topology mapping, and success criteria).*

---

# 3. PANDUAN INSTALASI PAKET & DEPENDENCIES (KEA-DHCP4, IPERF3, TC, DLL)

> [!IMPORTANT]
> **Prasyarat Wajib Sebelum Menjalankan `apk update`:**  
> Node internal (`Victoria`, `Yan`, `Laterano`, `Columbia`) hanya bisa mengunduh paket jika:
> 1. Router `RhodesIsland` sudah mengaktifkan NAT MASQUERADE (`iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE`) dan IP forwarding (`sysctl -w net.ipv4.ip_forward=1`).
> 2. Router perantara (`Lungmen` / `Ursus`) sudah memiliki default gateway ke `RhodesIsland` dan `sysctl -w net.ipv4.ip_forward=1`.
> 3. Node target sudah dikonfigurasi DNS resolver: `echo "nameserver 8.8.8.8" > /etc/resolv.conf`.
> 4. Tes koneksi: `ping -c 2 google.com` atau `ping -c 2 8.8.8.8` harus berhasil (0% packet loss).

---

### A. Tabel Kebutuhan Paket per Node
| Node | Paket yang Dibutuhkan | Fungsi Utama di Praktikum | Perintah Instalasi (Alpine Linux) |
| :--- | :--- | :--- | :--- |
| **RhodesIsland** | `iptables`, `iproute2` | NAT Masquerade, Traffic Control (`tc netem`, `tc tbf`) | `apk update && apk add iptables iproute2` |
| **Lungmen & Ursus** | `iproute2` | Routing & Gateway Forwarder | Sudah bawaan (atau `apk add iproute2`) |
| **Victoria** | `kea-dhcp4` (atau `kea`) | DHCP Server Subnet 3.0/24 | `apk update && apk add kea-dhcp4 kea` |
| **Yan** | `kea-dhcp4` (atau `kea`) | DHCP Server Subnet 4.0/24 (Reservasi IP Laterano) | `apk update && apk add kea-dhcp4 kea` |
| **Laterano** | `python3`, `iperf3` | Web HTTP Server port 9999 & Server Benchmark iperf3 | `apk update && apk add python3 iperf3` |
| **Columbia** | `curl`, `iperf3`, `tshark` | Client pengujian download berkas, iperf3, & sniffer | `apk update && apk add curl iperf3 tcpdump tshark` |

---

### B. Panduan Instalasi Khusus: Kea DHCP 4 Server (Victoria & Yan)
Kea DHCP adalah DHCP server modern standar industri yang digunakan di Modul 1 dan Modul 3 (menggantikan udhcpd / isc-dhcp-server lama).

#### 1. Perintah Instalasi di Alpine Linux:
```bash
# 1. Update indeks paket repository
apk update

# 2. Pasang paket kea-dhcp4
apk add kea-dhcp4 kea

# 3. WAJIB: Buat direktori penyimpanan lease database jika belum ada
mkdir -p /var/lib/kea
```

#### 2. Cek Apakah Kea DHCP Berhasil Terpasang:
```bash
# Periksa lokasi binary
which kea-dhcp4
# Output normal: /usr/sbin/kea-dhcp4

# Periksa versi
kea-dhcp4 -v
```

#### 3. Lokasi Berkas & Struktur Kunci Kea DHCP:
- **File Konfigurasi Utama**: `/etc/kea/kea-dhcp4.conf`
- **Database Leases (CSV)**: `/var/lib/kea/dhcp4.leases` atau `/var/lib/kea/kea-leases4.csv`
- **Menjalankan Service**:
  ```bash
  killall kea-dhcp4 2>/dev/null
  kea-dhcp4 -c /etc/kea/kea-dhcp4.conf &
  ```
- **Verifikasi Proses Berjalan**:
  ```bash
  ps aux | grep kea
  # Harus tampil proses /usr/sbin/kea-dhcp4
  ```

---

### C. Panduan Instalasi Paket Node Lainnya

#### 1. Node `RhodesIsland` (Iptables & Traffic Control `tc`):
```bash
apk update
apk add iptables iproute2
# Verifikasi:
which iptables tc
```

#### 2. Node `Laterano` (HTTP Server & iperf3):
```bash
apk update
apk add python3 iperf3
# Verifikasi:
python3 --version
iperf3 -v
```

#### 3. Node `Columbia` (Client Uji: Curl, iperf3, Sniffer):
```bash
apk update
apk add curl iperf3 tcpdump tshark
# Verifikasi:
which curl iperf3 tcpdump
```

> [!TIP]
> **Jika Node Berbasis Debian / Ubuntu (misal pada Desktop Client):**
> ```bash
> apt-get update
> apt-get install -y kea-dhcp4-server iperf3 curl iptables iproute2 python3 tcpdump
> ```

---

# 4. SKRIP OTOMASI CEPAT SETUP TOPOLOGI & KONFIGURASI IP (READY-TO-USE `10.181`)

> [!TIP]
> **Metode Dual-Layer**: Skrip di bawah ini melakukan dua hal sekaligus:
> 1. Menulis file `/etc/network/interfaces` agar konfigurasi IP tersimpan di disk.
> 2. Menjalankan perintah `ip addr replace` dan `ip link set up` sehingga alamat IP **langsung aktif detik itu juga** tanpa perlu restart networking.

---

### A. Node `RhodesIsland` (Core Router + NAT)
Buka terminal **`RhodesIsland`**, paste seluruh perintah berikut:
```bash
# 1. Simpan konfigurasi interfaces
cat << EOF > /etc/network/interfaces
auto eth0
iface eth0 inet dhcp

auto eth1
iface eth1 inet static
    address 10.181.1.1
    netmask 255.255.255.0

auto eth2
iface eth2 inet static
    address 10.181.2.1
    netmask 255.255.255.0
EOF

# 2. Terapkan IP secara instan di interface aktif
ip addr replace 10.181.1.1/24 dev eth1 && ip link set eth1 up
ip addr replace 10.181.2.1/24 dev eth2 && ip link set eth2 up
udhcpc -i eth0 -q 2>/dev/null  # Pastikan eth0 mendapat IP internet dari NAT

# 3. Buat dan jalankan skrip routing & NAT MASQUERADE
cat << EOF > /root/init.sh
#!/bin/sh
sysctl -w net.ipv4.ip_forward=1
iptables -F
iptables -t nat -F
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE

# Static Routes ke Subnet 3.0 (Lungmen) dan Subnet 4.0 (Ursus)
ip route replace 10.181.3.0/24 via 10.181.1.2 dev eth1
ip route replace 10.181.4.0/24 via 10.181.2.2 dev eth2

echo "RhodesIsland setup completed."
EOF
chmod +x /root/init.sh
/root/init.sh
```

---

### B. Node `Lungmen` (Router Subnet 3.0)
Buka terminal **`Lungmen`**, paste seluruh perintah berikut:
```bash
# 1. Simpan konfigurasi interfaces
cat << EOF > /etc/network/interfaces
auto eth0
iface eth0 inet static
    address 10.181.1.2
    netmask 255.255.255.0
    gateway 10.181.1.1

auto eth1
iface eth1 inet static
    address 10.181.3.1
    netmask 255.255.255.0
EOF

# 2. Terapkan IP secara instan
ip addr replace 10.181.1.2/24 dev eth0 && ip link set eth0 up
ip addr replace 10.181.3.1/24 dev eth1 && ip link set eth1 up

# 3. Buat dan jalankan skrip routing
cat << EOF > /root/init.sh
#!/bin/sh
sysctl -w net.ipv4.ip_forward=1
ip route replace default via 10.181.1.1 dev eth0
ip route replace 10.181.2.0/24 via 10.181.1.1 dev eth0
ip route replace 10.181.4.0/24 via 10.181.1.1 dev eth0
echo "nameserver 8.8.8.8" > /etc/resolv.conf
echo "Lungmen setup completed."
EOF
chmod +x /root/init.sh
/root/init.sh
```

---

### C. Node `Ursus` (Router Subnet 4.0)
Buka terminal **`Ursus`**, paste seluruh perintah berikut:
```bash
# 1. Simpan konfigurasi interfaces
cat << EOF > /etc/network/interfaces
auto eth0
iface eth0 inet static
    address 10.181.2.2
    netmask 255.255.255.0
    gateway 10.181.2.1

auto eth1
iface eth1 inet static
    address 10.181.4.1
    netmask 255.255.255.0
EOF

# 2. Terapkan IP secara instan
ip addr replace 10.181.2.2/24 dev eth0 && ip link set eth0 up
ip addr replace 10.181.4.1/24 dev eth1 && ip link set eth1 up

# 3. Buat dan jalankan skrip routing
cat << EOF > /root/init.sh
#!/bin/sh
sysctl -w net.ipv4.ip_forward=1
ip route replace default via 10.181.2.1 dev eth0
ip route replace 10.181.1.0/24 via 10.181.2.1 dev eth0
ip route replace 10.181.3.0/24 via 10.181.2.1 dev eth0
echo "nameserver 8.8.8.8" > /etc/resolv.conf
echo "Ursus setup completed."
EOF
chmod +x /root/init.sh
/root/init.sh
```

---

### D. Node `Victoria` (DHCP Server Subnet 3.0)
Buka terminal **`Victoria`**, paste seluruh perintah berikut:
```bash
# 1. Simpan konfigurasi interfaces
cat << EOF > /etc/network/interfaces
auto eth0
iface eth0 inet static
    address 10.181.3.2
    netmask 255.255.255.0
    gateway 10.181.3.1
EOF

# 2. Terapkan IP & Gateway secara instan
ip addr replace 10.181.3.2/24 dev eth0 && ip link set eth0 up
ip route replace default via 10.181.3.1 dev eth0
echo "nameserver 8.8.8.8" > /etc/resolv.conf

# 3. Pastikan kea-dhcp4 terpasang & direktori database siap
which kea-dhcp4 >/dev/null 2>&1 || (apk update && apk add kea-dhcp4 kea)
mkdir -p /var/lib/kea

# 4. Buat konfigurasi Kea DHCPv4 Subnet 3.0 (Pool .100 s.d .120)
cat << EOF > /etc/kea/kea-dhcp4.conf
{
  "Dhcp4": {
    "interfaces-config": { "interfaces": [ "eth0" ] },
    "lease-database": { "type": "memfile", "persist": true, "name": "/var/lib/kea/dhcp4.leases" },
    "valid-lifetime": 4000,
    "subnet4": [
      {
        "subnet": "10.181.3.0/24",
        "pools": [ { "pool": "10.181.3.100 - 10.181.3.120" } ],
        "option-data": [
          { "name": "routers", "data": "10.181.3.1" },
          { "name": "domain-name-servers", "data": "8.8.8.8" }
        ]
      }
    ]
  }
}
EOF

# 5. Jalankan daemon Kea DHCPv4 di background
killall kea-dhcp4 2>/dev/null
kea-dhcp4 -c /etc/kea/kea-dhcp4.conf &
echo "Victoria setup completed."
```

---

### E. Node `Yan` (DHCP Server Subnet 4.0 dengan Reservasi Laterano)
Buka terminal **`Yan`**, paste seluruh perintah berikut:
```bash
# 1. Simpan konfigurasi interfaces
cat << EOF > /etc/network/interfaces
auto eth0
iface eth0 inet static
    address 10.181.4.2
    netmask 255.255.255.0
    gateway 10.181.4.1
EOF

# 2. Terapkan IP & Gateway secara instan
ip addr replace 10.181.4.2/24 dev eth0 && ip link set eth0 up
ip route replace default via 10.181.4.1 dev eth0
echo "nameserver 8.8.8.8" > /etc/resolv.conf

# 3. Pastikan kea-dhcp4 terpasang & direktori database siap
which kea-dhcp4 >/dev/null 2>&1 || (apk update && apk add kea-dhcp4 kea)
mkdir -p /var/lib/kea

# 4. Buat konfigurasi Kea DHCPv4 Subnet 4.0 (Pool .50 s.d .60 + Reservasi Laterano .15)
cat << EOF > /etc/kea/kea-dhcp4.conf
{
  "Dhcp4": {
    "interfaces-config": { "interfaces": [ "eth0" ] },
    "lease-database": { "type": "memfile", "persist": true, "name": "/var/lib/kea/dhcp4.leases" },
    "valid-lifetime": 4000,
    "subnet4": [
      {
        "subnet": "10.181.4.0/24",
        "pools": [ { "pool": "10.181.4.50 - 10.181.4.60" } ],
        "reservations": [
          { "ip-address": "10.181.4.15" }
        ],
        "option-data": [
          { "name": "routers", "data": "10.181.4.1" },
          { "name": "domain-name-servers", "data": "8.8.8.8" }
        ]
      }
    ]
  }
}
EOF

# 5. Jalankan daemon Kea DHCPv4 di background
killall kea-dhcp4 2>/dev/null
kea-dhcp4 -c /etc/kea/kea-dhcp4.conf &
echo "Yan setup completed."
```

---

### F. Node `Laterano` (Web Server Port 9999 & iperf3 Server)
Buka terminal **`Laterano`**, paste seluruh perintah berikut:
```bash
# 1. Simpan konfigurasi interfaces
cat << EOF > /etc/network/interfaces
auto eth0
iface eth0 inet static
    address 10.181.4.15
    netmask 255.255.255.0
    gateway 10.181.4.1
EOF

# 2. Terapkan IP & Gateway secara instan
ip addr replace 10.181.4.15/24 dev eth0 && ip link set eth0 up
ip route replace default via 10.181.4.1 dev eth0
echo "nameserver 8.8.8.8" > /etc/resolv.conf

# 3. Pastikan dependencies terpasang
which python3 >/dev/null 2>&1 || apk add python3
which iperf3 >/dev/null 2>&1 || apk add iperf3

# 4. Buat berkas uji berbagai ukuran
mkdir -p /root/http
cd /root/http
[ ! -f tes1000.bin ] && dd if=/dev/urandom of=tes1000.bin bs=1000 count=1
[ ! -f tes10000.bin ] && dd if=/dev/urandom of=tes10000.bin bs=10000 count=1
[ ! -f tes50000.bin ] && dd if=/dev/urandom of=tes50000.bin bs=50000 count=1
[ ! -f tes5M.bin ] && dd if=/dev/urandom of=tes5M.bin bs=1M count=5

# 5. Jalankan HTTP Server Port 9999 & iperf3 Server di background
killall python3 2>/dev/null
killall iperf3 2>/dev/null
nohup python3 -m http.server 9999 > /tmp/http.log 2>&1 &
nohup iperf3 -s > /tmp/iperf.log 2>&1 &
echo "Laterano HTTP (port 9999) & iperf3 server ready!"
```

---

### G. Node `Columbia` (Client Uji)
Buka terminal **`Columbia`**, paste seluruh perintah berikut:
```bash
# 1. Konfigurasi interfaces
cat << EOF > /etc/network/interfaces
auto eth0
iface eth0 inet dhcp
EOF

# 2. Minta lease DHCP baru dari Victoria
killall udhcpc dhclient 2>/dev/null
udhcpc -i eth0 2>/dev/null || dhclient eth0 2>/dev/null
ip addr show eth0

# 3. Uji konektivitas ke Laterano dan Internet
ping -c 3 10.181.4.15
ping -c 3 google.com
```

---

# 5. ENSIKLOPEDI PERINTAH TRAFFIC CONTROL (`tc`) LENGKAP

Perintah `tc` dijalankan pada node **`RhodesIsland`** pada interface **`eth1`** (ke arah Columbia/Lungmen) dan/atau **`eth2`** (ke arah Laterano/Ursus).

### A. Reset / Bersihkan Rule `tc` (Kembali Normal)
```bash
tc qdisc del dev eth1 root 2>/dev/null
tc qdisc del dev eth2 root 2>/dev/null
tc -s qdisc show dev eth1
```

### B. Simulasi Packet Loss Saja (`netem`)
```bash
# 1% Loss
tc qdisc replace dev eth1 root netem loss 1%
tc qdisc replace dev eth2 root netem loss 1%

# 5% Loss
tc qdisc replace dev eth1 root netem loss 5%
tc qdisc replace dev eth2 root netem loss 5%

# 10% Loss
tc qdisc replace dev eth1 root netem loss 10%
tc qdisc replace dev eth2 root netem loss 10%
```

### C. Simulasi Delay & Jitter Saja (`netem`)
```bash
# Delay 100ms flat
tc qdisc replace dev eth1 root netem delay 100ms
tc qdisc replace dev eth2 root netem delay 100ms

# Delay 100ms dengan variasi (jitter) ±20ms
tc qdisc replace dev eth1 root netem delay 100ms 20ms
tc qdisc replace dev eth2 root netem delay 100ms 20ms
```

### D. Simulasi Bandwidth Throttling / Rate Limit (`tbf`)
```bash
# 2 Mbps Bandwidth Limit, Burst 32kbit, Latency 100ms
tc qdisc replace dev eth1 root handle 1: tbf rate 2mbit burst 32kbit latency 100ms
tc qdisc replace dev eth2 root handle 1: tbf rate 2mbit burst 32kbit latency 100ms

# 1 Mbps Bandwidth Limit
tc qdisc replace dev eth1 root handle 1: tbf rate 1mbit burst 16kbit latency 50ms
tc qdisc replace dev eth2 root handle 1: tbf rate 1mbit burst 16kbit latency 50ms
```

### E. Kombinasi Hierarki Paling Populer (Bandwidth 2 Mbps + Delay 100ms + Loss 1%)
*Skenario 3 Pra-Praktikum & Prediksi Soal Praktikum:*
```bash
# Bersihkan dulu
tc qdisc del dev eth1 root 2>/dev/null
tc qdisc del dev eth2 root 2>/dev/null

# Interface eth1
tc qdisc add dev eth1 root handle 1: tbf rate 2mbit burst 32kbit latency 100ms
tc qdisc add dev eth1 parent 1:1 handle 10: netem delay 100ms loss 1%

# Interface eth2
tc qdisc add dev eth2 root handle 1: tbf rate 2mbit burst 32kbit latency 100ms
tc qdisc add dev eth2 parent 1:1 handle 10: netem delay 100ms loss 1%
```

### F. Simulasi Reordering & Packet Corruption (Soal Kejutan/Variasi)
```bash
# Paket Out-of-Order (25% paket di-reorder dengan selisih delay 10ms)
tc qdisc replace dev eth1 root netem reorder 25% 50% delay 10ms

# Packet Corruption (1% paket bit-nya rusak / bad checksum)
tc qdisc replace dev eth1 root netem corrupt 1%
```

### G. Cek Status Rule Aktif dan Statistik Paket yang Didrop
```bash
tc -s qdisc show dev eth1
tc -s qdisc show dev eth2
```

---

# 6. ENSIKLOPEDI WIRESHARK, TERMSHARK & TSHARK FILTER

Gunakan display filter berikut saat membuka Wireshark pada node `Columbia` (receiver) atau `Laterano` (sender), atau saat filter capture:

| Kebutuhan Analisis | Display Filter Wireshark | Keterangan |
| :--- | :--- | :--- |
| **Filter Port HTTP** | `tcp.port == 9999` | Membatasi hanya traffic web server |
| **Three-Way Handshake** | `tcp.flags.syn == 1` | Menampilkan paket SYN dan SYN-ACK |
| **Paket FIN (Teardown)**| `tcp.flags.fin == 1` | Menampilkan penutupan koneksi |
| **Duplicate ACK** | `tcp.analysis.duplicate_ack` | Bukti receiver mendeteksi paket bolong/hilang |
| **Retransmission Umum** | `tcp.analysis.retransmission` | Paket yang dikirim ulang (Fast atau Timeout) |
| **Fast Retransmission** | `tcp.analysis.fast_retransmission` | Retransmisi akibat 3 Dup ACK (tanpa RTO) |
| **Spurious Retransmit**| `tcp.analysis.spurious_retransmission` | Retransmisi yang tidak perlu (karena delay) |
| **Out-of-Order Packet** | `tcp.analysis.out_of_order` | Paket tiba tidak berurutan |
| **Paket Hilang** | `tcp.analysis.lost_segment` | Wireshark mendeteksi nomor ACK melompat |
| **Window Full** | `tcp.analysis.window_full` | Sender telah menghabiskan receive window |
| **Zero Window Probe** | `tcp.analysis.zero_window` | Receiver buffer penuh, flow control pause |

### Menjalankan Sniffing Langsung dari CLI (Termshark / Tshark)
Jika GUI Wireshark terasa lambat, jalankan perintah ini di terminal node:
```bash
# Tampilkan paket SYN dan Retransmission secara real-time
tshark -i eth0 -Y "tcp.port == 9999 and (tcp.flags.syn == 1 or tcp.analysis.retransmission)"

# Hitung jumlah Duplicate ACK yang terjadi pada capture
tshark -r /tmp/capture.pcapng -Y "tcp.analysis.duplicate_ack" | wc -l

# Hitung jumlah Fast Retransmission
tshark -r /tmp/capture.pcapng -Y "tcp.analysis.fast_retransmission" | wc -l
```

### Rumus Validasi Sequence & Acknowledgment Number
1. **Paket SYN (Handshake 1):**  
   $Seq = ISN_{client}$, $Ack = 0$ (Relative: $Seq = 0$)
2. **Paket SYN-ACK (Handshake 2):**  
   $Seq = ISN_{server}$, $Ack = ISN_{client} + 1$ (Relative: $Seq = 0$, $Ack = 1$)
3. **Paket ACK (Handshake 3):**  
   $Seq = ISN_{client} + 1$, $Ack = ISN_{server} + 1$ (Relative: $Seq = 1$, $Ack = 1$)
4. **Data Segmen:**  
   $NextAck = CurrentSeq + PayloadLength$. Receiver selalu meng-ACK nomor urut byte **berikutnya yang diharapkan**.

---

# 7. ENSIKLOPEDI TCP CONGESTION CONTROL

Perintah dijalankan pada node pengirim data (**`Laterano`**):

### A. Cek Algoritma yang Tersedia & Sedang Aktif
```bash
# Cek yang sedang aktif
sysctl net.ipv4.tcp_congestion_control

# Cek daftar algoritma yang ter-install di kernel Linux
sysctl net.ipv4.tcp_available_congestion_control
```

### B. Mengubah Algoritma
```bash
# Ubah ke CUBIC
sysctl -w net.ipv4.tcp_congestion_control=cubic

# Ubah ke Reno
sysctl -w net.ipv4.tcp_congestion_control=reno

# Ubah ke BBR (jika didukung kernel)
sysctl -w net.ipv4.tcp_congestion_control=bbr 2>/dev/null
```

### C. Menjalankan Pengujian Download dari `Columbia` dengan Format Rapi
Jalankan di node **`Columbia`**:
```bash
curl -o /dev/null -s -w "size=%{size_download}B speed=%{speed_download}B/s total=%{time_total}s\n" http://10.181.4.15:9999/tes5M.bin
```

### D. Perbandingan Teori: CUBIC vs Reno vs BBR
| Karakteristik | TCP Reno | TCP CUBIC (Linux Default) | TCP BBR (Google) |
| :--- | :--- | :--- | :--- |
| **Metode Pertumbuhan Window** | Linier ($+1$ MSS per RTT pada Congestion Avoidance) | Fungsi Polinomial Kubik ($W(t) = C(t-K)^3 + W_{max}$) | Berdasarkan estimasi $BtlBw$ (bottleneck bandwidth) dan $RTprop$ (min RTT) |
| **Reaksi saat Packet Loss** | Multiplicative Decrease: Potong $cwnd$ sebesar $50\%$ | Potong $cwnd$ sebesar $30\%$ (faktor $\beta = 0.7$) | **Tidak** memotong window karena loss acak, hanya merespon antrean buffer |
| **Ketergantungan RTT** | Sangat sensitif terhadap RTT (aliran ber-RTT pendek merebut bandwidth) | RTT-independent (pertumbuhan window berbasis waktu riil $t$) | Mengukur RTT minimum murni |
| **Kinerja pada Link Delay Tinggi (BDP Besar)** | Lambat pulih (*slow recovery*), throughput rendah | Cepat pulih, kurva kubik agresif mendekati $W_{max}$ | Sangat tinggi, memaksimalkan pipa transmisi tanpa bufferbloat |

---

# 8. ENSIKLOPEDI BENCHMARK IPERF3 (TCP VS UDP)

### A. Persiapan Server di `Laterano`
```bash
# Jalankan iperf3 server mode daemon (background)
killall iperf3 2>/dev/null
iperf3 -s -D
```

### B. Pengujian Mode TCP dari `Columbia`
```bash
# Uji transfer data TCP selama 10 detik
iperf3 -c 10.181.4.15 -t 10
```
*Parameter penting yang diamati*:
- **Bitrate (Sender & Receiver)**: Akan anjlok saat ada packet loss karena AIMD memotong $cwnd$.
- **Retransmissions (Retr)**: Menunjukkan jumlah segmen yang dikirim ulang akibat paket hilang.

### C. Pengujian Mode UDP dari `Columbia`
```bash
# Uji transfer data UDP dengan target bandwidth 5 Mbps, paket size 1200 byte
iperf3 -c 10.181.4.15 -u -b 5M -t 10 -l 1200
```
> [!IMPORTANT]
> **Trik Penting**: Flag `-l 1200` mencegah terjadinya fragmentasi IP dan mengatasi error `iperf3: error - unable to read from stream socket: Resource temporarily unavailable` saat link mengalami *packet loss* tinggi!

*Parameter penting yang diamati*:
- **Bitrate**: Sender tetap memompa data sebesar 5.00 Mbps tanpa peduli link macet/hilang.
- **Jitter**: Variasi keterlambatan kedatangan paket (dalam milidetik).
- **Lost/Total Datagrams**: Menunjukkan persentase packet loss (misal $\approx 5.0\%$).

---

# 9. BANK JAWABAN TANYA JAWAB ASISTEN PENGUJI (ORAL DEFENSE 100/100)

> [!TIP]
> **Tips Praktis Menjawab Asisten:**
> Tidak perlu menghafal paragraf panjang. Cukup ucapkan bagian **Jawaban Singkat** dengan tenang dan santai. Sebutkan kata-kata kunci di bagian **Poin Kunci** karena itulah poin penilaian utama asisten penguji!

---

### Q1: Mengapa TCP menganggap packet loss sebagai tanda kemacetan (congestion), dan apa ruginya di jaringan nirkabel/lossy?

**Jawaban Singkat (Cukup ucapkan ini):**
> *"Karena TCP awalnya didesain untuk jaringan kabel, di mana paket hilang hampir pasti gara-gara antrean router penuh (macet). Makanya begitu ada paket hilang, TCP langsung panik dan memotong kecepatannya jadi separuh. Ruginya di jaringan nirkabel atau link yang sinyalnya jelek: paket hilang karena gangguan fisik, tapi TCP tetap memperlambat kecepatan, padahal jalurnya tidak sedang macet."*

**Poin Kunci yang Dicari Asisten:**
- **Asumsi TCP**: Paket hilang = antrean router penuh (*buffer overflow*).
- **Respon TCP**: Memotong *congestion window* ($cwnd$) hingga 50% (AIMD).
- **Dampak Negatif**: Kecepatan transfer anjlok padahal kapasitas bandwidth sebenarnya masih longgar.

---

### Q2: Mengapa receiver mengirim Duplicate ACK dan mengapa sender harus menunggu tepat 3 kali sebelum Fast Retransmit?

**Jawaban Singkat (Cukup ucapkan ini):**
> *"Receiver kirim Duplicate ACK untuk melapor ke sender kalau ada paket yang bolong atau urutannya melompat. Sender harus menunggu tepat 3 kali supaya yakin paketnya benar-benar hilang, bukan cuma sekadar datang terlambat atau salah urutan di jalan. Begitu genap 3 kali, sender langsung kirim ulang paket yang hilang (Fast Retransmit) tanpa perlu menunggu timeout yang lama."*

**Poin Kunci yang Dicari Asisten:**
- **Fungsi Dup ACK**: Meng-ACK paket terakhir yang berurutan dan memberitahu ada celah (*gap*) paket.
- **Alasan 3 Kali**: Menghindari *false alarm* akibat paket yang cuma sedikit terlambat (*reordering*).
- **Tindakan**: Memicu *Fast Retransmit* secara instan dibanding menunggu waktu *Timeout* (RTO).

---

### Q3: Apa perbedaan mendasar antara TCP Reno dan TCP CUBIC dalam memulihkan kecepatan (window) setelah loss?

**Jawaban Singkat (Cukup ucapkan ini):**
> *"Reno menaikkan kecepatannya pelan-pelan secara garis lurus (1 paket per putaran waktu RTT), jadi kalau jaringannya punya delay tinggi, pemulihannya sangat lama. Sedangkan CUBIC menaikkan kecepatannya menggunakan kurva melengkung (fungsi kubik) berbasis waktu riil, sehingga bisa kembali ke kecepatan maksimal jauh lebih cepat."*

**Poin Kunci yang Dicari Asisten:**
- **Reno**: Kenaikan linier ($+1$ MSS per RTT), lambat pulih pada jaringan berlatensi tinggi.
- **CUBIC**: Kenaikan kurva kubik independen dari RTT, agresif dan cepat kembali ke kapasitas puncak.

---

### Q4: Mengapa UDP tidak melakukan kirim ulang (retransmisi), dan kapan UDP lebih dipilih dibanding TCP?

**Jawaban Singkat (Cukup ucapkan ini):**
> *"Karena konsep UDP adalah 'kirim dan lupakan' tanpa perlu tanda terima (ACK), sehingga tidak ada rem kecepatan maupun kirim ulang. UDP dipilih untuk aplikasi real-time seperti panggilan suara (VoIP), video call, dan game online. Pada aplikasi ini, paket yang hilang lebih baik dilepas daripada ditunggu kirim ulangnya yang justru bikin suara atau gambar macet dan patah-patah."*

**Poin Kunci yang Dicari Asisten:**
- **Sifat UDP**: *Connectionless*, tanpa ACK, tanpa kirim ulang, tanpa *congestion control*.
- **Penggunaan**: Aplikasi *real-time* (VoIP, Zoom, live streaming, game).
- **Alasan**: Mengutamakan latensi rendah dan ketepatan waktu (*timeliness*) dibanding keandalan mutlak (*reliability*).

---

### Q5: Bagaimana protokol modern seperti QUIC (HTTP/3) menggabungkan keunggulan TCP dan UDP?

**Jawaban Singkat (Cukup ucapkan ini):**
> *"QUIC berjalan di atas UDP agar bebas dari rem lambat bawaan sistem operasi, tetapi aturan keandalan seperti kirim ulang dan enkripsi diatur sendiri oleh aplikasinya. Keunggulan terbesarnya: jika ada satu file yang hilang di tengah jalan, file lainnya tidak akan ikut macet tertahan (bebas dari Head-of-Line Blocking)."*

**Poin Kunci yang Dicari Asisten:**
- **Dasar**: Berjalan di atas UDP + fitur keandalan di layer aplikasi.
- **Solusi Utama**: Mengatasi antrean macet bersama (*Head-of-Line Blocking*) dan koneksi instan (*0-RTT*).

---

# 10. TROUBLESHOOTING GUIDE / PENYELAMAT ERROR PRAKTIKUM

### ⚠️ Masalah 1: `iperf3: error - unable to read from stream socket: Resource temporarily unavailable` pada UDP
- **Penyebab**: Ukuran datagram default (1470 byte) terfragmentasi atau buffer socket UDP penuh akibat paket control drop saat loss tinggi (5% - 10%).
- **Solusi**:
  1. Restart server iperf3 di `Laterano`:
     ```bash
     killall iperf3 && nohup iperf3 -s > /tmp/iperf.log 2>&1 &
     ```
  2. Jalankan client di `Columbia` dengan membatasi buffer size (`-l 1200`):
     ```bash
     iperf3 -c 10.181.4.15 -u -b 5M -t 10 -l 1200
     ```

---

### ⚠️ Masalah 2: `RTNETLINK answers: File exists` saat menjalankan `tc qdisc add`
- **Penyebab**: Rule root qdisc sudah ada pada interface tersebut sehingga `add` gagal.
- **Solusi**:
  Gunakan perintah `replace` atau hapus (`del`) terlebih dahulu:
  ```bash
  tc qdisc del dev eth1 root 2>/dev/null
  tc qdisc replace dev eth1 root ...
  ```

---

### ⚠️ Masalah 3: Node tidak bisa ping ke gateway atau ping RTO
- **Langkah Diagnostik Cepat**:
  1. Cek `ip_forward` di ketiga router (`RhodesIsland`, `Lungmen`, `Ursus`):
     ```bash
     sysctl net.ipv4.ip_forward
     # Jika bernilai 0, aktifkan:
     sysctl -w net.ipv4.ip_forward=1
     ```
  2. Cek tabel routing di router:
     ```bash
     ip route show
     ```
     Pastikan `RhodesIsland` memiliki rute ke `10.181.3.0/24` via `10.181.1.2` dan `10.181.4.0/24` via `10.181.2.2`.
  3. Cek default route di `Lungmen` dan `Ursus`:
     - Default route `Lungmen` harus via `10.181.1.1`.
     - Default route `Ursus` harus via `10.181.2.1`.

---

### ⚠️ Masalah 4: Client Columbia tidak mendapatkan IP dari Victoria
- **Solusi**:
  1. Periksa status proses Kea di `Victoria`:
     ```bash
     ps aux | grep kea
     ```
  2. Jika mati, jalankan ulang:
     ```bash
     kea-dhcp4 -c /etc/kea/kea-dhcp4.conf &
     ```
  3. Di `Columbia`, paksa minta lease baru:
     ```bash
     killall udhcpc dhclient 2>/dev/null
     udhcpc -i eth0 -q
     ```

---

### ⚠️ Masalah 5: Curl gagal atau port 9999 connection refused
- **Solusi**:
  Pastikan HTTP server Python berjalan di `Laterano`:
  ```bash
  cd /root/http
  nohup python3 -m http.server 9999 > /tmp/http.log 2>&1 &
  netstat -tuln | grep 9999
  ```

---
*Dokumen ini dibuat khusus sebagai panduan komprehensif praktikum untuk Nabil Khairie (5025251066).*

---

# 11. PROSEDUR PEMULIHAN PASCA RESTART GNS3 (DISASTER RECOVERY PROTOCOL)

> [!WARNING]
> **Kondisi Kritis Saat GNS3 / Node Direstart:**  
> Ketika project GNS3 ditutup, VM direstart, atau node di-stop lalu di-start kembali, **seluruh state yang ada di RAM akan HILANG**.
> 
> | Komponen | Status Pasca Restart | Dampak Langsung |
> | :--- | :--- | :--- |
> | **Berkas di Disk** (`/etc/network/interfaces`, `/root/init.sh`, dll.) | **AMAN (Tetap Ada)** | Skrip konfigurasi Anda tidak hilang. |
> | **Kernel `ip_forward`** | **RESET KE 0** | **Routing putus total!** Paket tidak bisa menyeberang antar subnet. |
> | **Aturan `iptables` NAT** | **HILANG (KOSONG)** | Seluruh node kehilangan koneksi internet. |
> | **Aturan `tc qdisc` (tbf, netem)** | **RESET KE DEFAULT** | Simulasi loss/delay/bandwidth hilang, kembali ke kondisi normal. |
> | **Daemon Background** (`kea-dhcp4`, `python3`, `iperf3`) | **MATI TOTAL** | Columbia tidak dapat IP, curl port 9999 ditolak (*connection refused*). |
> | **Lease DHCP Client** (`Columbia`) | **HILANG / EXPIRED** | Client tidak memiliki IP address. |

---

### Prosedur Pemulihan Kilat 1 Menit (Urutan Wajib):

Lakukan copy-paste perintah berikut pada masing-masing terminal node secara berurutan:

#### 1. Pada Router `RhodesIsland`:
```bash
# Menyalakan kembali ip_forward, NAT internet, dan static routes
/root/init.sh

# Pasang kembali rule tc yang sedang diuji (contoh Skenario 3: 2Mbit, 100ms, 1% loss):
tc qdisc add dev eth1 root handle 1: tbf rate 2mbit burst 32kbit latency 100ms 2>/dev/null
tc qdisc add dev eth1 parent 1:1 handle 10: netem delay 100ms loss 1% 2>/dev/null
tc qdisc add dev eth2 root handle 1: tbf rate 2mbit burst 32kbit latency 100ms 2>/dev/null
tc qdisc add dev eth2 parent 1:1 handle 10: netem delay 100ms loss 1% 2>/dev/null
```

#### 2. Pada Router `Lungmen`:
```bash
/root/init.sh
```

#### 3. Pada Router `Ursus`:
```bash
/root/init.sh
```

#### 4. Pada DHCP Server `Victoria`:
```bash
killall kea-dhcp4 2>/dev/null
kea-dhcp4 -c /etc/kea/kea-dhcp4.conf &
```

#### 5. Pada DHCP Server `Yan`:
```bash
killall kea-dhcp4 2>/dev/null
kea-dhcp4 -c /etc/kea/kea-dhcp4.conf &
```

#### 6. Pada Server `Laterano`:
```bash
cd /root/http
killall python3 iperf3 2>/dev/null
nohup python3 -m http.server 9999 > /tmp/http.log 2>&1 &
nohup iperf3 -s > /tmp/iperf.log 2>&1 &
```

#### 7. Pada Client `Columbia`:
```bash
# Minta kembali alamat IP dari DHCP server Victoria
killall udhcpc dhclient 2>/dev/null
udhcpc -i eth0 -q 2>/dev/null || dhclient eth0 2>/dev/null

# Verifikasi: ping ke web server Laterano harus langsung reply 0% loss!
ping -c 3 10.181.4.15
```

---

### Tips Permanen (Anti-Lupa Pasca Reboot)
Agar `ip_forward` tidak pernah mati lagi meskipun node di-restart berulang kali:
Jalankan perintah ini sekali saja di **`RhodesIsland`**, **`Lungmen`**, dan **`Ursus`**:
```bash
echo "net.ipv4.ip_forward = 1" >> /etc/sysctl.conf
sysctl -p
```
Dengan baris tersebut di `/etc/sysctl.conf`, kernel Linux otomatis mengaktifkan *IP forwarding* setiap kali node booting!
