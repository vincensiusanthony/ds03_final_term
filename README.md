# SmartStudent

**SmartStudent** adalah aplikasi terminal mini berbasis C++ yang mensimulasikan sistem layanan mahasiswa digital untuk "Kampus Cakrawala".  
Aplikasi ini menampilkan implementasi berbagai struktur data klasik serta fitur interaktif berbasis menu terminal.

---

## Fitur Utama

1. **Login Mahasiswa**
   - Autentikasi menggunakan NIM dan password (Hash Table).
2. **Antrean Konsultasi Akademik**
   - Simulasi antrean konsultasi (Queue, FIFO).
3. **Peminjaman Buku**
   - Pencarian mahasiswa (Hash Table) dan pencatatan aktivitas peminjaman (Linked List dan Stack).
4. **Aktivitas Mahasiswa**
   - Tampilkan riwayat aktivitas mahasiswa (Stack untuk LIFO, Linked List untuk kronologis).
5. **Navigasi Kampus**
   - Menampilkan jalur terpendek antar lokasi kampus (Graph, Dijkstra).
6. **Daftar Buku Terurut**
   - Tampilkan daftar buku terurut berdasarkan judul (BST, in-order traversal).
7. **Pencarian Buku**
   - Cari buku berdasarkan ID (Hash Table).

---

## Struktur Data yang Diimplementasikan

- **Linked List** : Riwayat aktivitas mahasiswa (kronologis).
- **Queue** : Antrean konsultasi akademik (FIFO).
- **Stack** : Log aktivitas mahasiswa (LIFO).
- **Hash Table** : Akun mahasiswa & data buku.
- **Binary Search Tree (BST)** : Menyimpan dan menyortir buku berdasarkan judul.
- **Graph** : Navigasi lokasi kampus (jalur terpendek, Dijkstra).
- **Sorting & Searching** : Sorting dengan BST, searching buku via Hash Table.

---

## Struktur Proyek

```
SmartStudent/
├── main.cpp
├── models/
│   ├── Book.h
│   ├── Student.h
│   └── ActivityLog.h
├── structures/
│   ├── LinkedList.h
│   ├── Stack.h
│   ├── Queue.h
│   ├── HashTable.h
│   ├── BST.h
│   └── Graph.h
├── utils/
│   └── helper.h
└── data/
    ├── dummy_books.txt
    ├── dummy_students.txt
    └── dummy_graph.txt
```

---

## Instalasi & Menjalankan

1. **Clone/download repository dan masuk ke folder.**
2. **Pastikan data dummy tersedia di folder `data/`.**
3. **Compile program:**
    ```bash
    g++ -std=c++17 -o SmartStudent main.cpp
    ```
4. **Jalankan aplikasi:**
    ```bash
    ./SmartStudent
    ```

---

## Format Data Dummy

- **data/dummy_students.txt**
    ```
    NIM|Nama|Password
    12345|Budi|passbudi
    67890|Siti|passsiti
    ...
    ```
- **data/dummy_books.txt**
    ```
    ID|Judul|Penulis
    1|Algoritma Pemrograman|R. Soelistyo
    2|Struktur Data|A. Santosa
    ...
    ```
- **data/dummy_graph.txt**
    ```
    Lokasi1|Lokasi2|Jarak
    Gerbang|Gedung A|2
    Gedung A|Perpustakaan|2
    ...
    ```

---

## Catatan Penggunaan

- **Login** menggunakan NIM dan password yang ada di file dummy.
- Semua data disimpan di memori (tidak persistent ke file).
- Fitur menu dapat diakses interaktif via terminal.

---

## Pengembang

- Aplikasi ini dikembangkan untuk tujuan pembelajaran struktur data dan simulasi sistem layanan kampus.

---

## Lisensi

Proyek ini bebas digunakan untuk keperluan belajar dan pengajaran.