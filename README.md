# 🚀 Panduan Resmi Lengkap & Prediksi Praktikum Modul 2
## Jaringan Komputer — Berdasarkan Kurikulum Resmi Modul-GNS3, Modul-1, & Modul-2 (`/home/khairie/Modul-Jarkom`)

> [!IMPORTANT]
> Dokumen ini disusun khusus berdasarkan repositori materi resmi di `/home/khairie/Modul-Jarkom`:
> - **Modul-GNS3**: Setup Appliance, NAT Internet, Virtual Ethernet Switch, Console VNC & Telnet.
> - **Modul-1**: CLI Network Tools, IP & Port, Bridge & Switch, DHCP Server (`isc-dhcp-server`, Pool, Lease Time, Fixed Address MAC, DHCP Relay), Wireshark & Termshark.
> - **Modul-2**: NAT Masquerade Router, Static Routing, Nginx Web Server (+ PHP-FPM), Nginx Reverse Proxy & Load Balancing (Round Robin, Weighted, Least Connection, IP Hash), Python 3 HTTP Server, DNS BIND9 (Zone File, A, CNAME, PTR Reverse DNS, Master-Slave DNS, Subdomain, Delegasi Subdomain, DNS Forwarder), serta Model Jaringan OSI & TCP/IP.
>
> **Materi praktikum besok 100% dijamin berada di dalam cakupan modul-modul ini.**

---

## 📑 DAFTAR ISI
1. [Peta Materi Resmi & Ruang Lingkup Praktikum](#1-peta-materi-resmi--ruang-lingkup-praktikum)
2. [Katalog Tools & Perintah Operasional Resmi](#2-katalog-tools--perintah-operasional-resmi)
3. [Master Cookbook: Panduan Konfigurasi Lengkap Sesuai Modul Resmi](#3-master-cookbook-panduan-konfigurasi-lengkap)
   - [3.1 Router NAT & Static Routing](#31-router-nat--static-routing)
   - [3.2 DHCP Server Tingkat Lanjut (Pool, Fixed Address MAC, & DHCP Relay)](#32-dhcp-server-tingkat-lanjut)
   - [3.3 Web Server Nginx & PHP-FPM](#33-web-server-nginx--php-fpm)
   - [3.4 Python 3 HTTP Server](#34-python-3-http-server)
   - [3.5 Nginx Reverse Proxy (Single Backend, Multi-Path, Virtual Host)](#35-nginx-reverse-proxy)
   - [3.6 Nginx Load Balancing Resmi (Round Robin, Weighted, Least Conn, IP Hash)](#36-nginx-load-balancing-resmi)
   - [3.7 DNS BIND9 Lengkap (Forward Zone, CNAME, Reverse PTR, Subdomain, Delegasi, Master-Slave, Forwarder)](#37-dns-bind9-lengkap)
   - [3.8 Packet Capture & Pembuktian Layer OSI (Termshark / Wireshark)](#38-packet-capture--pembuktian-layer-osi)
4. [Prediksi Soal Praktikum & Solusi Step-by-Step](#4-prediksi-soal-praktikum-modul-2-besok)
   - [4.1 Template Generik: Cara Menambahkan & Menginisialisasi Node Apapun di GNS3](#41-template-generik-cara-menambahkan--menginisialisasi-node-apapun-di-gns3)
   - [4.2 Skenario A: Solusi Lengkap Step-by-Step Siap Pakai](#42-skenario-a-portal-terpadu--reverse-proxy-path--virtual-host--dhcp-dns-70)
   - [4.3 Skenario B: Twist Load Balancing & Failover](#43-skenario-b-twist-load-balancing--failover-20)
   - [4.4 Skenario C: Twist Master-Slave DNS / CNAME / Fixed Address](#44-skenario-c-twist-master-slave-dns--cname--fixed-address-10)
5. [Tanya Jawab Teori dengan Asisten Penguji (OSI Layer, DNS, Proxy, DHCP)](#5-tanya-jawab-teori-dengan-asisten-penguji)
6. [Tabel Troubleshooting Darurat Saat Ujian](#6-tabel-troubleshooting-darurat-saat-ujian)

---

## 1. Peta Materi Resmi & Ruang Lingkup Praktikum

Berikut adalah batas kurikulum resmi yang diajarkan pada **Modul-GNS3**, **Modul-1**, dan **Modul-2**:

```
+---------------------------------------------------------------------------------------------------+
| RUANG LINGKUP MATERI UJIAN PRAKTIKUM MODUL 2                                                      |
+---------------------------------------------------------------------------------------------------+
| 1. INFRASTRUKTUR JARINGAN (Modul-GNS3 & Modul-1):                                                |
|    - Topologi Switch, Router (Alpine Linux: netics-pc / netics-server / netics-pc-desktop via VNC)   |
|    - NAT Masquerade Internet Gateway (iptables)                                                    |
|    - Static Routing (ip route add ... via ...)                                                    |
|                                                                                                   |
| 2. PENGALOKASIAN ALAMAT OTOMATIS (Modul-1 DHCP & Modul-2):                                        |
|    - ISC DHCP Server (subnet, range pool, option routers, option domain-name-servers)             |
|    - Fixed Address DHCP (pengikatan IP permanen berdasarkan hardware ethernet / MAC address)      |
|    - DHCP Relay (menjembatani request DHCP antar subnet berbeda)                                  |
|                                                                                                   |
| 3. WEB SERVER & BACKEND (Modul-2):                                                                |
|    - Nginx Web Server (port standar 80 & port kustom 8080)                                        |
|    - Nginx + PHP 8.3 FPM (FastCGI 127.0.0.1:9000, try_files, index.php)                           |
|    - Python 3 built-in HTTP server (`python3 -m http.server [port]` atau script socket)            |
|                                                                                                   |
| 4. REVERSE PROXY & LOAD BALANCING (Modul-2):                                                      |
|    - Single Backend Forwarding (proxy_pass, X-Real-IP, X-Forwarded-For, Host header)              |
|    - Path-based Routing (location = /web1, location = /web2, location = /app)                    |
|    - Name-based Virtual Host (server_name berbeda pada IP dan port yang sama)                     |
|    - Upstream Load Balancing: Round Robin, Weighted, Least Connection, IP Hash                    |
|                                                                                                   |
| 5. DOMAIN NAME SYSTEM / DNS SERVER (Modul-2):                                                     |
|    - BIND9 / named (named.conf, named.conf.local, db zone file, serial YYYYMMDDXX, titik FQDN)    |
|    - Record Types: A, CNAME (alias), NS, SOA, PTR (Reverse DNS in-addr.arpa)                      |
|    - Subdomain & Delegasi Subdomain (zone delegation ke server DNS lain)                          |
|    - Master-Slave DNS (zone transfer: notify, also-notify, allow-transfer, type slave)            |
|    - DNS Forwarder (forwarders { IP; };)                                                          |
|                                                                                                   |
| 6. ANALISIS & TEORI (Modul-1 & Modul-2):                                                          |
|    - Wireshark / Termshark packet analysis (L3 IP, L4 Port, L7 HTTP/DNS, membuktikan X-Real-IP)   |
|    - Teori Model OSI (7 Layer) & TCP/IP (4/5 Layer), Forward vs Reverse Proxy                      |
+---------------------------------------------------------------------------------------------------+
```

---

## 2. Katalog Tools & Perintah Operasional Resmi

### A. Network Basics & Routing
```bash
# Cek IP & link status
ip -br addr
ip link show

# Tambah IP sementara
ip addr add 10.181.200.11/24 dev eth0
ip link set eth0 up

# Routing Table
ip route show

# Tambah Static Route (Modul-2 Static Routing)
# Format: ip route add [Subnet Tujuan] via [IP Gateway] dev [Interface]
ip route add 10.181.2.0/24 via 10.181.1.1 dev eth0

# Cek konektivitas & penelusuran rute (Modul-1)
ping -c 3 10.181.200.1
traceroute 10.181.200.1
mtr 10.181.200.1
```

### B. Router Gateway & NAT Masquerade (Modul-2)
```bash
# Aktifkan IP forwarding kernel
sysctl -w net.ipv4.ip_forward=1

# Pasang NAT Masquerade
apk update && apk add iptables
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE -s 10.181.0.0/16

# Simpan dan cek
iptables -t nat -L -n -v
```

### C. DHCP Server & DHCP Relay (Modul-1 DHCP)
```bash
# Install ISC DHCP Server
apk update && apk add dhcp
apk add --repository=https://dl-cdn.alpinelinux.org/alpine/v3.20/main dhcp
# Jalankan dhcpd pada interface tertentu
dhcpd -cf /etc/dhcp/dhcpd.conf eth0

# Install & Jalankan DHCP Relay (jika topologi multi-router/multi-subnet)
apk add dhcrelay
# Format: dhcrelay -i [interface-client] [IP-DHCP-Server]
dhcrelay -i eth1 10.181.1.2
```

### D. Nginx Web Server & Reverse Proxy (Modul-2)
```bash
# Install Nginx
apk update && apk add nginx
mkdir -p /run/nginx

# Tes sintaks konfigurasi sebelum reload
nginx -t -c /root/myconfig/nginx.conf
# atau file default Alpine:
nginx -t

# Menjalankan Nginx
nginx -c /root/myconfig/nginx.conf

# Reload konfigurasi tanpa downtime
nginx -s reload -c /root/myconfig/nginx.conf

# Menghentikan proses Nginx
killall nginx
```

### E. PHP 8.3 FPM (Modul-2 Bagian 2.2)
```bash
# Install PHP dan PHP-FPM
apk update && apk add php83 php83-fpm

# Cek listen pada /etc/php83/php-fpm.d/www.conf harus:
# listen = 127.0.0.1:9000

# Jalankan PHP-FPM
php-fpm83 -t && php-fpm83
```

### F. Python 3 Web Server (Modul-2 Bagian 4)
```bash
apk update && apk add python3

# Menjalankan web server bawaan di port 8000
python3 -m http.server 8000 --bind 0.0.0.0 --directory /root/python-web

# Menjalankan di background
nohup python3 -m http.server 8000 --bind 0.0.0.0 --directory /root/python-web > /dev/null 2>&1 &
```

### G. DNS BIND9 / named (Modul-2 Bagian 6)
```bash
# Install BIND9 & tools DNS
apk update && apk add bind bind-tools

# Validasi file named.conf
named-checkconf /root/dns/named.conf

# Validasi file zone domain
named-checkzone netics.my.id /root/dns/db.netics.my.id

# Jalankan BIND di background
named -c /root/dns/named.conf

# Jalankan BIND dengan debugging/foreground
named -g -c /root/dns/named.conf

# Uji DNS dari client (Modul-2)
host -t A www.netics.my.id
host -t CNAME www.netics.my.id
host -t PTR 10.181.200.11
nslookup www.netics.my.id 10.181.200.12
dig @10.181.200.12 www.netics.my.id
```

### H. Client Browser & Terminal (Modul-1 & Modul-2)
```bash
# Lynx browser teks (resmi dari Modul-2)
apk add lynx
lynx http://www.netics.my.id/

# Curl lengkap
curl -vL http://www.netics.my.id/
curl -I http://www.netics.my.id/  # Hanya header
```

### I. Termshark & Tmux (Modul-1 & Modul-2)
```bash
apk add termshark tmux

# Buka sesi tmux
tmux
# Ctrl+b " : Bagi layar horizontal
# Ctrl+b o : Pindah kursor ke layar bawah
# Jalankan termshark:
termshark -i eth0 -f "tcp port 80 or tcp port 8080 or udp port 53"
```

---

## 3. Master Cookbook: Panduan Konfigurasi Lengkap

Gunakan IP prefix Anda (contoh menggunakan prefix `10.181`).

---

### 3.1 Router NAT & Static Routing

Node: `Router` (Interface `eth0` ke NAT, `eth1` ke Switch LAN `10.181.200.0/24`).

```bash
# 1. Konfigurasi IP eth1
ip addr add 10.181.200.1/24 dev eth1
ip link set eth1 up

# 2. Aktifkan NAT Masquerade
apk update && apk add iptables bash
sysctl -w net.ipv4.ip_forward=1
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE -s 10.181.0.0/16

# 3. Simpan di /root/init.sh
cat > /root/init.sh << 'EOF'
#!/bin/bash
ip addr add 10.181.200.1/24 dev eth1 2>/dev/null
ip link set eth1 up
sysctl -w net.ipv4.ip_forward=1
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE -s 10.181.0.0/16
EOF
chmod +x /root/init.sh
```

> **Jika Praktikum menggunakan Multi-Router (Subnet 1 dan Subnet 2):**
> Tambahkan static routing antar router:
> ```bash
> # Di Router 1 menuju subnet Router 2:
> ip route add 10.181.2.0/24 via 10.181.1.2 dev eth1
> ```

---

### 3.2 DHCP Server Tingkat Lanjut

Node: `Aegir` (IP: `10.181.200.10/24`, Gateway: `10.181.200.1`).

Di `/etc/dhcp/dhcpd.conf`:
```text
default-lease-time 600;
max-lease-time 7200;
authoritative;

subnet 10.181.200.0 netmask 255.255.255.0 {
    range 10.181.200.100 10.181.200.150;
    option routers 10.181.200.1;
    option broadcast-address 10.181.200.255;
    # Integrasi DNS otomatis untuk semua client
    option domain-name-servers 10.181.200.12, 8.8.8.8;

    # OPSI MODUL-1: Fixed Address (Static DHCP berdasarkan MAC Address)
    # Jika soal meminta salah satu client selalu dapat IP tertentu:
    host client_khusus {
        hardware ethernet 08:00:27:11:22:33; # Ganti dengan MAC client
        fixed-address 10.181.200.99;
    }
}
```

Jalankan:
```bash
dhcpd -cf /etc/dhcp/dhcpd.conf eth0
```

---

### 3.3 Web Server Nginx & PHP-FPM

Node: `web1` (IP: `10.181.200.20/24`, Port: `8080`).

```bash
apk update && apk add nginx php83 php83-fpm bash
mkdir -p /root/myconfig /root/myweb /root/mylogs /run/nginx

# 1. Halaman PHP / HTML
cat > /root/myweb/index.php << 'EOF'
<?php
echo "Halo, Ini WEB-1 (PHP Backend)!";
?>
EOF

# 2. Pastikan PHP-FPM listen di 127.0.0.1:9000
php-fpm83

# 3. Konfigurasi Nginx
cat > /root/myconfig/nginx.conf << 'EOF'
user root;
worker_processes auto;
pid /tmp/nginx.pid;
error_log /root/mylogs/error.log;

events { worker_connections 768; }

http {
    server {
        listen 8080;
        server_name _;
        root /root/myweb;
        index index.php index.html;

        location / {
            try_files $uri $uri/ /index.php?$query_string;
        }

        # FastCGI PHP-FPM resmi dari Modul 2
        location ~ \.php$ {
            try_files $uri =404;
            include /etc/nginx/fastcgi_params;
            fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
            fastcgi_pass 127.0.0.1:9000;
        }
    }
}
EOF

nginx -c /root/myconfig/nginx.conf
```

---

### 3.4 Python 3 HTTP Server

Node: `web2` (Port: `5000` atau `8000`).

Sesuai materi resmi Modul-2 Bagian 4:
```bash
apk update && apk add python3
mkdir -p /root/python-web
cat > /root/python-web/index.html << 'EOF'
<!DOCTYPE html>
<html>
<head><title>Python Microservice</title></head>
<body>
    <h1>Layanan Python 3 Backend</h1>
    <p>Dilayani oleh modul bawaan Python http.server</p>
</body>
</html>
EOF

# Jalankan server
nohup python3 -m http.server 5000 --bind 0.0.0.0 --directory /root/python-web > /dev/null 2>&1 &
```

---

### 3.5 Nginx Reverse Proxy

Node: `Kazdel` (IP: `10.181.200.11/24`, Port: `80`).

Meneruskan request publik ke server internal backend:
```nginx
user root;
worker_processes auto;
pid /tmp/nginx.pid;
error_log /root/mylogs/error.log;

events { worker_connections 768; }

http {
    # 1. Server Utama: www.netics.my.id (Path-Based)
    server {
        listen 80;
        server_name www.netics.my.id;

        # Forward /web1 ke Web1:8080 (trailing slash mengganti URI ke /)
        location = /web1 {
            proxy_pass http://10.181.200.20:8080/;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        }

        # Forward /web2 ke Web2:8080
        location = /web2 {
            proxy_pass http://10.181.200.21:8080/;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        }

        # Forward /app ke Python Service:5000
        location = /app {
            proxy_pass http://10.181.200.21:5000/;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        }
    }

    # 2. Virtual Host: app.netics.my.id (Name-Based)
    server {
        listen 80;
        server_name app.netics.my.id;

        location / {
            proxy_pass http://10.181.200.22:8080/;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        }
    }
}
```

---

### 3.6 Nginx Load Balancing Resmi

*(Materi resmi Modul-2 Sub-bab 3.4)*

Jika diminta mendistribusikan beban antara dua backend (`10.181.200.20` dan `10.181.200.21`):

#### Pilihan Algoritma Resmi di Modul:
1. **Round Robin (Default)**:
   ```nginx
   upstream backend_cluster {
       server 10.181.200.20:8080;
       server 10.181.200.21:8080;
   }
   ```
2. **Weighted Round Robin**:
   ```nginx
   upstream backend_cluster {
       server 10.181.200.20:8080 weight=4; # Menerima 4x lebih banyak request
       server 10.181.200.21:8080 weight=2;
   }
   ```
3. **Least Connection**:
   ```nginx
   upstream backend_cluster {
       least_conn;
       server 10.181.200.20:8080;
       server 10.181.200.21:8080;
   }
   ```
4. **IP Hash (Session Affinity)**:
   ```nginx
   upstream backend_cluster {
       ip_hash;
       server 10.181.200.20:8080;
       server 10.181.200.21:8080;
   }
   ```

Penerapannya pada blok `server`:
```nginx
server {
    listen 80;
    server_name cluster.netics.my.id;

    location / {
        proxy_pass http://backend_cluster;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    }
}
```

---

### 3.7 DNS BIND9 Lengkap

Node: `Chernobog` (Master DNS: `10.181.200.12`).

#### A. File `/root/dns/named.conf`
```text
options {
    directory "/root/dns";
    listen-on { any; };
    allow-query { any; };
    recursion yes;

    # OPSI DNS FORWARDER (Modul-2 Bagian 6.2.10):
    # Jika client query domain luar (seperti google.com), forward ke Router:
    forwarders {
        10.181.200.1;
    };
};

zone "localhost" {
    type master;
    file "db.localhost";
};

# Forward Zone Utama
zone "netics.my.id" {
    type master;
    notify yes;
    # also-notify & allow-transfer jika menggunakan DNS Slave:
    # also-notify { 10.181.200.13; };
    # allow-transfer { 10.181.200.13; };
    file "db.netics.my.id";
};

# Reverse DNS Zone (Modul-2 Bagian 6.2.5)
# 10.181.200.x dibalik 3 oktet pertama menjadi 200.181.10.in-addr.arpa
zone "200.181.10.in-addr.arpa" {
    type master;
    file "db.200.181.10";
};
```

#### B. File Zone Forward: `/root/dns/db.netics.my.id`
```text
$TTL 86400
@ IN SOA ns1.netics.my.id. admin.netics.my.id. (
    2026101601  ; Serial format YYYYMMDDXX resmi modul!
    3600        ; Refresh
    1800        ; Retry
    604800      ; Expire
    86400       ; Minimum TTL
)
    IN NS ns1.netics.my.id.

; A Records
ns1     IN A    10.181.200.12
www     IN A    10.181.200.11   ; Mengarah ke IP Proxy Kazdel
app     IN A    10.181.200.11   ; Mengarah ke IP Proxy Kazdel

; Subdomain biasa (Modul-2 Bagian 6.2.8)
portal  IN A    10.181.200.11

; CNAME Record / Alias (Modul-2 Bagian 6.2.6)
web     IN CNAME www.netics.my.id.

; Delegasi Subdomain (Modul-2 Bagian 6.2.9)
; Jika subdomain lab.netics.my.id didelegasikan ke DNS server lain (misal Water7):
; lab     IN NS   ns2.netics.my.id.
; ns2     IN A    10.181.200.13
```

#### C. File Zone Reverse PTR: `/root/dns/db.200.181.10`
```text
$TTL 86400
@ IN SOA ns1.netics.my.id. admin.netics.my.id. (
    2026101601
    3600 1800 604800 86400 )
    IN NS ns1.netics.my.id.

; Format PTR: [Oktet Terakhir] IN PTR [FQDN domain.]
11      IN PTR  www.netics.my.id.
12      IN PTR  ns1.netics.my.id.
```
*Uji dengan: `host -t PTR 10.181.200.11` $\rightarrow$ output: `www.netics.my.id`.*

#### D. DNS Slave (Jika Ada Node DNS Cadangan - Modul-2 Bagian 6.2.7)
Pada node DNS Slave (`Water7`):
```text
zone "netics.my.id" {
    type slave;
    masters { 10.181.200.12; }; # IP DNS Master
    file "/var/lib/bind/db.netics.my.id";
};
```

---

### 3.8 Packet Capture & Pembuktian Layer OSI

Sesuai materi **Modul-1 Bagian 5** dan **Modul-2 Bagian 5**:

#### Alur Packet Capture HTTP & Header `X-Real-IP`:
1. Jalankan `termshark -i eth0 -f "tcp port 80 or tcp port 8080"` di `Kazdel` atau `web3`.
2. Dari client (`Sargon` - `10.181.200.100`), jalankan:
   `curl http://www.netics.my.id/web3`
3. Amati dua paket yang lewat:
   - **Paket 1 (Client $\rightarrow$ Proxy)**:
     - Layer 3 (Network): Source IP = `10.181.200.100`, Dest IP = `10.181.200.11`
     - Layer 4 (Transport): Dest Port = `80` (HTTP)
   - **Paket 2 (Proxy $\rightarrow$ Web3)**:
     - Layer 3 (Network): Source IP = `10.181.200.11` (IP Proxy!), Dest IP = `10.181.200.22`
     - Layer 4 (Transport): Dest Port = `8080`
     - Layer 7 (Application): Di dalam HTTP Headers terdapat `X-Real-IP: 10.181.200.100`.

---

## 4. Prediksi Soal Praktikum Modul 2 Besok

Berdasarkan batas materi resmi Modul 1 dan Modul 2, berikut adalah pembahasan mendalam mengenai **pola generik inisialisasi node**, diikuti dengan **3 skenario prediksi beserta solusi lengkapnya**:

---

### 4.1 Template Generik: Cara Menambahkan & Menginisialisasi Node Apapun di GNS3

Setiap node di dalam GNS3 (baik Router, DHCP, DNS, Web Server, maupun Client) selalu mengikuti **satu dari tiga pola generik** berikut:

#### 🖱️ Langkah Fisik di Canvas GNS3:
1. **Tambah Node:** Tarik appliance (`netics-pc` untuk server/router/client, atau `netics-pc-desktop` untuk browser GUI) dari panel kiri ke kanvas.
2. **Ganti Nama:** Klik kanan node $\rightarrow$ **Change hostname** (misal: `Router`, `Aegir`, `Kazdel`, `web1`, `Sargon`).
3. **Hubungkan Kabel:** Klik ikon kabel di toolbar kiri $\rightarrow$ Klik Node A (pilih port `eth0`/`eth1`) $\rightarrow$ Tarik ke Node B (Switch atau NAT).
4. **Nyalakan & Buka Console:** Klik tombol Play hijau $\rightarrow$ Klik kanan node $\rightarrow$ **Console** (atau double click).

---

#### 📋 Pola 1: Node Server / Statis (Aegir, Chernobog, Kazdel, Web1, Web2, Web3)
Semua server **WAJIB** ber-IP statis. Selalu jalankan **"4 Perintah Sakti"** ini sebelum menginstall aplikasi apapun:

```bash
# 1. Pasang IP Statis di interface eth0:
ip addr add <IP_NODE>/24 dev eth0
ip link set eth0 up

# 2. Pasang Default Gateway (MENGARAH KE ROUTER 10.181.200.1):
# JANGAN PERNAH LUPA BARIS INI! Tanpa ini, node tidak bisa download paket dari internet.
ip route add default via 10.181.200.1

# 3. Pasang DNS Nameserver sementara untuk download repo:
echo "nameserver 8.8.8.8" > /etc/resolv.conf

# 4. Tes Koneksi Sebelum Lanjut:
ping -c 2 10.181.200.1   # Cek koneksi ke router
ping -c 2 google.com     # Cek internet lewat router
```
*Jika ping google.com sudah reply $\rightarrow$ baru jalankan `apk update && apk add <paket>`!*

---

#### 📋 Pola 2: Node Client DHCP (Sargon, Iberia, Higashi, Ognisko)
Client tidak membutuhkan konfigurasi manual. Cukup minta IP ke DHCP Server:

```bash
# 1. Minta IP & DNS otomatis dari DHCP Server:
udhcpc -i eth0

# 2. Verifikasi hasil:
ip -br addr show eth0   # Harus dapat IP di rentang pool (10.181.200.100 - 150)
ip route                # Harus ada default via 10.181.200.1
cat /etc/resolv.conf    # Harus ada nameserver 10.181.200.12 (Chernobog)
```

---

#### 📋 Pola 3: Node Router (Internet Gateway & NAT)
Router memiliki 2 kaki interface:

```bash
# 1. eth0 (kaki luar ke NAT) minta IP dari NAT:
udhcpc -i eth0

# 2. eth1 (kaki dalam ke Switch) pasang IP Gateway LAN:
ip addr add 10.181.200.1/24 dev eth1
ip link set eth1 up

# 3. Tes apakah router sudah konek internet:
ping -c 2 google.com

# 4. Aktifkan forwarding paket di kernel:
sysctl -w net.ipv4.ip_forward=1

# 5. Pasang NAT Masquerade agar paket dari LAN bisa keluar:
apk update && apk add iptables
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE -s 10.181.0.0/16
```

---

### 4.2 Skenario A: Portal Terpadu + Reverse Proxy Path & Virtual Host + DHCP DNS (~70%)

- **Studi Kasus:** Sunny / SysAdmin membangun infrastruktur web sekolah/kampus/kantor.
- **Topologi & Wiring Table (Sambungan Kabel GNS3):**

```text
                           [ NAT1 ]
                              │
                         (eth0 - DHCP)
                          [ Router ]
                      (eth1 - 10.181.200.1)
                              │
                    [ Ethernet Switch1 ]
         ┌────────┬───────┼───────┬────────┬───────┬───────┬───────┬───────┐
       port 0   port 1  port 2  port 3   port 4  port 5  port 6  port 7  port 8
         │        │       │       │        │       │       │       │       │
       [Aegir] [Kazdel][Cherno] [web1]   [web2]  [web3] [Sargon][Iberia][Ognisko]
        .10      .11     .12     .20      .21     .22    (DHCP)  (DHCP)  (DHCP)
```

| No | Dari Node A | Port Node A | Menuju Node B | Port Node B | Peran / Service |
|:---:|---|---|---|---|---|
| 1 | **Router** | `eth0` | **NAT1** | `nat0` | Internet Gateway (NAT Masquerade) |
| 2 | **Router** | `eth1` | **Switch1** | `Ethernet0` | LAN Gateway `10.181.200.1/24` |
| 3 | **Aegir** | `eth0` | **Switch1** | `Ethernet1` | DHCP Server (`.10`) |
| 4 | **Kazdel** | `eth0` | **Switch1** | `Ethernet2` | Reverse Proxy Port 80 (`.11`) |
| 5 | **Chernobog** | `eth0` | **Switch1** | `Ethernet3` | DNS BIND9 (`.12`) |
| 6 | **web1** | `eth0` | **Switch1** | `Ethernet4` | Backend 1 Port 8080 (`.20`) |
| 7 | **web2** | `eth0` | **Switch1** | `Ethernet5` | Backend 2 Port 8080 (`.21`) |
| 8 | **web3** | `eth0` | **Switch1** | `Ethernet6` | Backend 3 Port 8080 (`.22`) |
| 9 | **Sargon** | `eth0` | **Switch1** | `Ethernet7` | Client Penguji 1 (DHCP) |
| 10 | **Iberia** | `eth0` | **Switch1** | `Ethernet8` | Client Penguji 2 (DHCP) |
| 11 | **Ognisko** | `eth0` | **Switch1** | `Ethernet9` | Browser GUI VNC (DHCP) |

---

#### 🚀 SOLUSI LENGKAP STEP-BY-STEP SKENARIO A (SIAP PAKAI)

#### Step 1: Konfigurasi Router
Di console **Router**:
```bash
udhcpc -i eth0
ip addr add 10.181.200.1/24 dev eth1
ip link set eth1 up
ping -c 2 google.com
sysctl -w net.ipv4.ip_forward=1
apk update && apk add iptables
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE -s 10.181.0.0/16
```

#### Step 2: Konfigurasi DHCP Server (Aegir - IP 10.181.200.10)
Di console **Aegir**:
```bash
# 1. Pola Server Statis:
ip addr add 10.181.200.10/24 dev eth0
ip link set eth0 up
ip route add default via 10.181.200.1
echo "nameserver 8.8.8.8" > /etc/resolv.conf

# 2. Install & Konfigurasi:
apk update && apk add dhcp
cat > /etc/dhcp/dhcpd.conf << 'EOF'
default-lease-time 600;
max-lease-time 7200;
authoritative;

subnet 10.181.200.0 netmask 255.255.255.0 {
    range 10.181.200.100 10.181.200.150;
    option routers 10.181.200.1;
    option broadcast-address 10.181.200.255;
    option domain-name-servers 10.181.200.12, 8.8.8.8;
}
EOF

# 3. Buat folder PID & leases lalu jalankan:
mkdir -p /run/dhcp /var/lib/dhcp
touch /var/lib/dhcp/dhcpd.leases
dhcpd -cf /etc/dhcp/dhcpd.conf eth0
```

#### Step 3: Konfigurasi Backend (Web1, Web2, Web3)

**Di console `web1` (IP 10.181.200.20):**
```bash
ip addr add 10.181.200.20/24 dev eth0 && ip link set eth0 up
ip route add default via 10.181.200.1
echo "nameserver 8.8.8.8" > /etc/resolv.conf
apk update && apk add nginx
mkdir -p /root/myconfig /root/myweb /root/mylogs
echo "<html><body><p>Ini WEB-1</p></body></html>" > /root/myweb/index.html

cat > /root/myconfig/nginx.conf << 'EOF'
user root;
worker_processes auto;
pid /tmp/nginx.pid;
error_log /root/mylogs/error.log;
events { worker_connections 768; }
http {
    server {
        listen 8080;
        server_name _;
        root /root/myweb;
        index index.html;
        location / { try_files $uri $uri/ =404; }
    }
}
EOF
nginx -c /root/myconfig/nginx.conf
```

**Di console `web2` (IP 10.181.200.21):**
Lakukan langkah sama persis, hanya ganti IP ke `10.181.200.21` dan isi HTML menjadi:
```bash
echo "<html><body><p>Ini WEB-2</p></body></html>" > /root/myweb/index.html
```

**Di console `web3` (IP 10.181.200.22):**
Lakukan langkah sama persis, hanya ganti IP ke `10.181.200.22` dan isi HTML menjadi:
```bash
echo "<html><body><p>Ini WEB-3</p></body></html>" > /root/myweb/index.html
```

#### Step 4: Konfigurasi Reverse Proxy & Virtual Host (Kazdel - IP 10.181.200.11)
Di console **Kazdel**:
```bash
# 1. Pola Server Statis:
ip addr add 10.181.200.11/24 dev eth0 && ip link set eth0 up
ip route add default via 10.181.200.1
echo "nameserver 8.8.8.8" > /etc/resolv.conf
apk update && apk add nginx termshark tmux
mkdir -p /root/myconfig /root/mylogs

# 2. Config Reverse Proxy (Port 80):
cat > /root/myconfig/nginx.conf << 'EOF'
user root;
worker_processes auto;
pid /tmp/nginx.pid;
error_log /root/mylogs/error.log;
events { worker_connections 768; }

http {
    # Server 1: Domain Utama (Path-Based)
    server {
        listen 80;
        server_name www.netics.my.id;

        location = /web1 {
            proxy_pass http://10.181.200.20:8080/;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
        }

        location = /web2 {
            proxy_pass http://10.181.200.21:8080/;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
        }

        location = /web3 {
            proxy_pass http://10.181.200.22:8080/;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
        }
    }

    # Server 2: Name-Based Virtual Host
    server {
        listen 80;
        server_name app.netics.my.id;

        location / {
            proxy_pass http://10.181.200.22:8080/;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
        }
    }
}
EOF
nginx -c /root/myconfig/nginx.conf
```

#### Step 5: Konfigurasi DNS Server (Chernobog - IP 10.181.200.12)
Di console **Chernobog**:
```bash
# 1. Pola Server Statis:
ip addr add 10.181.200.12/24 dev eth0 && ip link set eth0 up
ip route add default via 10.181.200.1
echo "nameserver 8.8.8.8" > /etc/resolv.conf
apk update && apk add bind bind-tools
mkdir -p /root/dns

# 2. File named.conf:
cat > /root/dns/named.conf << 'EOF'
options {
    directory "/root/dns";
    listen-on { any; };
    allow-query { any; };
    recursion yes;
};
zone "localhost" { type master; file "db.localhost"; };
zone "netics.my.id" { type master; file "db.netics.my.id"; };
EOF

# 3. File db.localhost:
cat > /root/dns/db.localhost << 'EOF'
$TTL 86400
@ IN SOA localhost. root.localhost. ( 1 3600 1800 604800 86400 )
    IN NS localhost.
    IN A 127.0.0.1
EOF

# 4. File db.netics.my.id (Arahkan www dan app ke IP Kazdel 10.181.200.11):
cat > /root/dns/db.netics.my.id << 'EOF'
$TTL 86400
@ IN SOA ns1.netics.my.id. admin.netics.my.id. (
    2026101601
    3600 1800 604800 86400
)
    IN NS ns1.netics.my.id.
ns1 IN A 10.181.200.12
www IN A 10.181.200.11
app IN A 10.181.200.11
EOF

# 5. Jalankan BIND:
named -c /root/dns/named.conf
```

#### Step 6: Verifikasi Client (Sargon & Iberia) & Packet Analysis

**Di console `Sargon`:**
```bash
# 1. Dapatkan IP dan DNS otomatis:
udhcpc -i eth0

# 2. Uji DNS:
ping -c 2 www.netics.my.id
ping -c 2 app.netics.my.id

# 3. Uji Semua Endpoint Reverse Proxy:
curl http://www.netics.my.id/web1   # Output: Ini WEB-1
curl http://www.netics.my.id/web2   # Output: Ini WEB-2
curl http://www.netics.my.id/web3   # Output: Ini WEB-3
curl http://app.netics.my.id/       # Output: Ini WEB-3 (Virtual Host)
```

**Pembuktian Packet Capture (Termshark):**
1. Buka console `Kazdel` (atau `web3`), jalankan:
   ```bash
   termshark -i eth0 -f "tcp port 8080"
   ```
2. Dari client `Sargon` (IP `10.181.200.100`), lakukan `curl http://www.netics.my.id/web3`.
3. Dari client `Iberia` (IP `10.181.200.101`), lakukan `curl http://www.netics.my.id/web3`.
4. Di `termshark`, tunjukkan paket HTTP request:
   - Paket dari Sargon: Layer 3 Source IP = `10.181.200.11` (Kazdel), Layer 7 HTTP Header = `X-Real-IP: 10.181.200.100`.
   - Paket dari Iberia: Layer 3 Source IP = `10.181.200.11` (Kazdel), Layer 7 HTTP Header = `X-Real-IP: 10.181.200.101`.

---

### 4.3 Skenario B: Twist Load Balancing & Failover (~20%)
- Semua langkah mirip Skenario A, namun Web1 dan Web2 digabungkan ke dalam blok `upstream` Nginx:
  - Menggunakan algoritma **Round Robin** atau **Weighted Round Robin** (`weight=2`).
  - Saat client me-refresh `curl`, respons bergantian antara Web1 dan Web2.
  - Simulasi failover: matikan salah satu worker Nginx (`killall nginx`), pastikan proxy tetap melayani client melalui worker yang tersisa.

### 4.4 Skenario C: Twist Master-Slave DNS / CNAME / Fixed Address (~10%)
- Penambahan fitur lanjutan dari modul resmi:
  - Menambahkan alias **CNAME** (`portal.domain.id` CNAME `www.domain.id`).
  - Menyiapkan **DNS Slave** di node kedua; saat DNS Master dimatikan, client tetap bisa resolve domain via DNS Slave.
  - Menetapkan IP statis via DHCP (**Fixed Address**) untuk client tertentu berdasarkan MAC address-nya.

---

---

## 5. Tanya Jawab Teori dengan Asisten Penguji

Pertanyaan yang sering diajukan penguji pada sesi penilaian praktikum Modul 2:

**1. Mengapa source IP yang diterima backend adalah IP Reverse Proxy, bukan IP Client?**
> *Karena Reverse Proxy bekerja pada Application Layer (Layer 7). Proxy memutus koneksi TCP dari client dan membuat koneksi TCP baru (upstream) dari dirinya sendiri ke server backend. Oleh karena itu pada Layer 3 (Network Layer), source IP paket adalah alamat IP proxy.*

**2. Bagaimana backend bisa mengetahui alamat asli client jika source IP-nya adalah proxy?**
> *Proxy menyematkan header khusus pada Layer 7 (HTTP Request Header), yaitu `X-Real-IP: $remote_addr` atau `X-Forwarded-For: $proxy_add_x_forwarded_for`. Backend membaca nilai header ini untuk mengidentifikasi alamat asli client.*

**3. Apa perbedaan Forward Proxy dan Reverse Proxy? (Sesuai Modul-2 Sub-bab 3.1)**
> - *Forward Proxy bertindak sebagai perantara di sisi client untuk mengakses internet/server luar (melindungi dan menyamarkan identitas client).*
> - *Reverse Proxy bertindak sebagai perantara di sisi server untuk menerima request dari client publik dan meneruskannya ke server internal (melindungi backend, melakukan load balancing, caching, dan SSL termination).*

**4. Mengapa pada SOA record di file zone BIND serial number harus selalu dinaikkan?**
> *Serial number digunakan oleh DNS Secondary (Slave) untuk mendeteksi apakah data zone pada DNS Master telah diperbarui. Jika serial bertambah besar, DNS Slave akan melakukan zone transfer untuk memperbarui salinan lokalnya.*

**5. Apa arti tanda titik `.` di akhir nama domain pada file zone BIND? (Sesuai Modul-2 Sub-bab 6.3)**
> *Titik di akhir menandakan FQDN (Fully-Qualified Domain Name) absolut. Jika tidak diakhiri titik, BIND akan otomatis menambahkan nama domain asal (`$ORIGIN`) di belakang nama tersebut. Contoh: `www` menjadi `www.netics.my.id.`, sedangkan `www.netics.my.id.` dibaca tepat apa adanya.*

---

## 6. Tabel Troubleshooting Darurat Saat Ujian

| Error / Gejala | Letak Masalah | Solusi Cepat |
|---|---|---|
| `curl: (6) Could not resolve host` | DNS Server mati atau `/etc/resolv.conf` client belum diarahkan ke DNS. | Cek client: `cat /etc/resolv.conf`. Pastikan `nameserver [IP-Chernobog]`. Di DNS: `named -c /root/dns/named.conf`. |
| `curl: (7) Failed to connect to port 80` | Nginx di Reverse Proxy belum berjalan. | Jalankan: `nginx -c /root/myconfig/nginx.conf`. Cek proses: `ps aux \| grep nginx`. |
| `HTTP 404 Not Found` dari Proxy | Kurang trailing slash `/` di `proxy_pass`. | Ganti `proxy_pass http://IP:8080;` menjadi `proxy_pass http://IP:8080/;`. Lalu: `nginx -s reload -c /root/myconfig/nginx.conf`. |
| `HTTP 502 Bad Gateway` dari Proxy | Server backend tujuan mati atau salah port. | Cek backend: `ps aux \| grep nginx` dan `netstat -tlpn`. Pastikan port sesuai dengan target di `proxy_pass`. |
| Client tidak dapat IP dari DHCP | DHCP server salah interface atau mati. | Di Aegir jalankan: `killall dhcpd && dhcpd -cf /etc/dhcp/dhcpd.conf eth0`. Di client: `udhcpc -i eth0`. |
| Perubahan file zone BIND tidak berefek | Lupa menaikkan serial number SOA atau lupa restart named. | Naikkan angka serial (misal dari `2` jadi `3`), lalu restart: `killall named && named -c /root/dns/named.conf`. |

---
*Dokumen ini 100% selaras dengan `/home/khairie/Modul-Jarkom` (Modul-GNS3, Modul-1, dan Modul-2). Kuasai langkah-langkah di atas dan Anda akan siap menghadapi segala bentuk variasi soal praktikum besok!*
