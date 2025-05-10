#include <iostream>
using namespace std;

struct Musik {
    string judul;
    string album;
    string durasi;
    string artis;
    string genre;
    int tahunRilis;
    float rating;
    Musik* berikutnya;
};

Musik* kepala = nullptr;
int jumlahMusik = 0;

bool samaPersis(const string &a, const string &b) {
    return a == b;
}

void tambahMusik() {
    int jumlah;
    cout << "Ingin menambahkan berapa lagu? ";
    cin >> jumlah;
    cin.ignore();

    for (int i = 0; i < jumlah; i++) {
        Musik* musikBaru = new Musik();
        cout << "\nLagu ke-" << i + 1 << endl;
        cout << "Judul: "; getline(cin, musikBaru->judul);
        cout << "Album: "; getline(cin, musikBaru->album);
        cout << "Durasi: "; getline(cin, musikBaru->durasi);
        cout << "Artis: "; getline(cin, musikBaru->artis);
        cout << "Genre: "; getline(cin, musikBaru->genre);
        cout << "Tahun Rilis: "; cin >> musikBaru->tahunRilis;
        cout << "Rating (0.0 - 5.0): "; cin >> musikBaru->rating;
        cin.ignore();
        
        musikBaru->berikutnya = kepala;
        kepala = musikBaru;
        jumlahMusik++;
    }

    cout << jumlah << " lagu berhasil ditambahkan!\n";
}

void tampilkanMusik(Musik* musik) {
    cout << "Judul: " << musik->judul
         << "\nAlbum: " << musik->album
         << "\nDurasi: " << musik->durasi
         << "\nArtis: " << musik->artis
         << "\nGenre: " << musik->genre
         << "\nTahun Rilis: " << musik->tahunRilis
         << "\nRating: " << musik->rating << "\n\n";
}

void lihatMusik() {
    if (kepala == nullptr) {
        cout << "\nTidak ada lagu dalam daftar.\n";
    } else {
        cout << "\nDaftar Semua Lagu (" << jumlahMusik << " lagu):\n";
        Musik* sekarang = kepala;
        while (sekarang != nullptr) {
            tampilkanMusik(sekarang);
            sekarang = sekarang->berikutnya;
        }
    }
    
    // Fitur kembali
    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.ignore(10000, '\n');
}

// Algoritma Pengurutan
void urutJudul() { // Insertion Sort
    if (kepala == nullptr || kepala->berikutnya == nullptr) return;
    
    Musik* terurut = nullptr;
    Musik* sekarang = kepala;
    
    while (sekarang != nullptr) {
        Musik* berikut = sekarang->berikutnya;
        
        if (terurut == nullptr || terurut->judul >= sekarang->judul) {
            sekarang->berikutnya = terurut;
            terurut = sekarang;
        } else {
            Musik* sementara = terurut;
            while (sementara->berikutnya != nullptr && sementara->berikutnya->judul < sekarang->judul) {
                sementara = sementara->berikutnya;
            }
            sekarang->berikutnya = sementara->berikutnya;
            sementara->berikutnya = sekarang;
        }
        
        sekarang = berikut;
    }
    
    kepala = terurut;
}

void urutRating() { // Selection Sort
    if (kepala == nullptr || kepala->berikutnya == nullptr) return;
    
    Musik* sekarang = kepala;
    while (sekarang != nullptr) {
        Musik* maks = sekarang;
        Musik* sementara = sekarang->berikutnya;
        
        while (sementara != nullptr) {
            if (sementara->rating > maks->rating) {
                maks = sementara;
            }
            sementara = sementara->berikutnya;
        }
        
        // Tukar data
        swap(sekarang->judul, maks->judul);
        swap(sekarang->album, maks->album);2
        swap(sekarang->durasi, maks->durasi);
        swap(sekarang->artis, maks->artis);
        swap(sekarang->genre, maks->genre);
        swap(sekarang->tahunRilis, maks->tahunRilis);
        swap(sekarang->rating, maks->rating);
        
        sekarang = sekarang->berikutnya;
    }
}

void urutTahun() { // Bubble Sort
    if (kepala == nullptr || kepala->berikutnya == nullptr) return;
    
    bool ditukar;
    Musik* ptr1;
    Musik* lptr = nullptr;
    
    do {
        ditukar = false;
        ptr1 = kepala;
        
        while (ptr1->berikutnya != lptr) {
            if (ptr1->tahunRilis > ptr1->berikutnya->tahunRilis) {
                // Tukar data
                swap(ptr1->judul, ptr1->berikutnya->judul);
                swap(ptr1->album, ptr1->berikutnya->album);
                swap(ptr1->durasi, ptr1->berikutnya->durasi);
                swap(ptr1->artis, ptr1->berikutnya->artis);
                swap(ptr1->genre, ptr1->berikutnya->genre);
                swap(ptr1->tahunRilis, ptr1->berikutnya->tahunRilis);
                swap(ptr1->rating, ptr1->berikutnya->rating);
                ditukar = true;
            }
            ptr1 = ptr1->berikutnya;
        }
        lptr = ptr1;
    } while (ditukar);
}

Musik* gabungkanByArtis(Musik* a, Musik* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    
    if (a->artis <= b->artis) {
        a->berikutnya = gabungkanByArtis(a->berikutnya, b);
        return a;
    } else {
        b->berikutnya = gabungkanByArtis(a, b->berikutnya);
        return b;
    }
}

void pisahkan(Musik* sumber, Musik** depan, Musik** belakang) {
    Musik* cepat;
    Musik* lambat;
    lambat = sumber;
    cepat = sumber->berikutnya;
    
    while (cepat != nullptr) {
        cepat = cepat->berikutnya;
        if (cepat != nullptr) {
            lambat = lambat->berikutnya;
            cepat = cepat->berikutnya;
        }
    }
    
    *depan = sumber;
    *belakang = lambat->berikutnya;
    lambat->berikutnya = nullptr;
}

void urutArtis() { // Merge Sort
    if (kepala == nullptr || kepala->berikutnya == nullptr) return;
    
    Musik* a;
    Musik* b;
    
    pisahkan(kepala, &a, &b);
    
    kepala = gabungkanByArtis(a, b);
}

Musik* gabungkanByGenre(Musik* a, Musik* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    
    if (a->genre <= b->genre) {
        a->berikutnya = gabungkanByGenre(a->berikutnya, b);
        return a;
    } else {
        b->berikutnya = gabungkanByGenre(a, b->berikutnya);
        return b;
    }
}

void urutGenre() { // Merge Sort
    if (kepala == nullptr || kepala->berikutnya == nullptr) return;
    
    Musik* a;
    Musik* b;
    
    pisahkan(kepala, &a, &b);
    
    kepala = gabungkanByGenre(a, b);
}

Musik* partisiByAlbum(Musik* kepala, Musik* akhir, Musik** kepalaBaru, Musik** akhirBaru) {
    Musik* pivot = akhir;
    Musik* sebelumnya = nullptr;
    Musik* sekarang = kepala;
    Musik* ekor = pivot;
    
    while (sekarang != pivot) {
        if (sekarang->album < pivot->album) {
            if (*kepalaBaru == nullptr) *kepalaBaru = sekarang;
            sebelumnya = sekarang;
            sekarang = sekarang->berikutnya;
        } else {
            if (sebelumnya) sebelumnya->berikutnya = sekarang->berikutnya;
            Musik* sementara = sekarang->berikutnya;
            sekarang->berikutnya = nullptr;
            ekor->berikutnya = sekarang;
            ekor = sekarang;
            sekarang = sementara;
        }
    }
    
    if (*kepalaBaru == nullptr) *kepalaBaru = pivot;
    *akhirBaru = ekor;
    
    return pivot;
}

Musik* urutAlbumRec(Musik* kepala, Musik* akhir) {
    if (!kepala || kepala == akhir) return kepala;
    
    Musik* kepalaBaru = nullptr;
    Musik* akhirBaru = nullptr;
    
    Musik* pivot = partisiByAlbum(kepala, akhir, &kepalaBaru, &akhirBaru);
    
    if (kepalaBaru != pivot) {
        Musik* sementara = kepalaBaru;
        while (sementara->berikutnya != pivot) sementara = sementara->berikutnya;
        sementara->berikutnya = nullptr;
        
        kepalaBaru = urutAlbumRec(kepalaBaru, sementara);
        
        sementara = kepalaBaru;
        while (sementara && sementara->berikutnya) sementara = sementara->berikutnya;
        sementara->berikutnya = pivot;
    }
    
    pivot->berikutnya = urutAlbumRec(pivot->berikutnya, akhirBaru);
    
    return kepalaBaru;
}

void urutAlbum() { // Quick Sort
    Musik* sementara = kepala;
    while (sementara && sementara->berikutnya) sementara = sementara->berikutnya;
    
    kepala = urutAlbumRec(kepala, sementara);
}

// Algoritma Pencarian
Musik* cariSeq(const string& judul) {
    Musik* sekarang = kepala;
    while (sekarang != nullptr) {
        if (samaPersis(sekarang->judul, judul)) {
            return sekarang;
        }
        sekarang = sekarang->berikutnya;
    }
    return nullptr;
}

Musik* cariBin(const string& judul) {
    // Urutkan terlebih dahulu berdasarkan judul
    urutJudul();
    
    Musik* kiri = kepala;
    Musik* kanan = nullptr;
    
    while (kiri != kanan) {
        Musik* tengah = kiri;
        int hitung = 0;
        
        // Hitung node dari kiri ke kanan
        Musik* sementara = kiri;
        while (sementara != kanan) {
            sementara = sementara->berikutnya;
            hitung++;
        }
        
        // Pindahkan tengah ke posisi tengah
        for (int i = 0; i < hitung/2; i++) {
            tengah = tengah->berikutnya;
        }
        
        if (tengah->judul == judul) {
            return tengah;
        } else if (tengah->judul < judul) {
            kiri = tengah->berikutnya;
        } else {
            kanan = tengah;
            // Untuk menangani kasus ketika kanan menjadi nullptr
            if (kanan == kepala) {
                if (kepala->judul == judul) return kepala;
                else break;
            }
        }
    }
    
    return nullptr;
}

void cariMusik() {
    if (kepala == nullptr) {
        cout << "Tidak ada lagu dalam daftar.\n";
    } else {
        int pilihan;
        cout << "\nCari berdasarkan:\n";
        cout << "1. Judul\n";
        cout << "2. Album\n";
        cout << "3. Artis\n";
        cout << "4. Genre\n";
        cout << "5. Tahun Rilis\n";
        cout << "6. Rating\n";
        cout << "7. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        
        if (pilihan == 7) {
            cin.ignore();
            return;
        }
        
        cin.ignore();

        cout << "\nMetode pencarian:\n";
        cout << "1. Pencarian Sequential\n";
        cout << "2. Pencarian Binary (hanya untuk judul yang sudah diurutkan)\n";
        cout << "3. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        int metodePencarian;
        cin >> metodePencarian;
        
        if (metodePencarian == 3) {
            cin.ignore();
            return;
        }
        
        cin.ignore();

        string kataKunci;
        int kataKunciInt;
        float kataKunciFloat;
        cout << "Masukkan kata kunci pencarian (masukkan 'kembali' untuk kembali ke menu): ";

        if (pilihan == 5) {
            cin >> kataKunciInt;
            cin.ignore();
        } else if (pilihan == 6) {
            cin >> kataKunciFloat;
            cin.ignore();
        } else {
            getline(cin, kataKunci);
            if (kataKunci == "kembali") return;
        }

        bool ditemukan = false;
        Musik* sekarang = kepala;
        
        if (metodePencarian == 2 && pilihan == 1) {
            Musik* hasil = cariBin(kataKunci);
            if (hasil != nullptr) {
                cout << "\nHasil pencarian:\n";
                tampilkanMusik(hasil);
                ditemukan = true;
            }
        } else {
            cout << "\nHasil pencarian:\n";
            while (sekarang != nullptr) {
                bool cocok = false;
                switch (pilihan) {
                    case 1: cocok = samaPersis(sekarang->judul, kataKunci); break;
                    case 2: cocok = samaPersis(sekarang->album, kataKunci); break;
                    case 3: cocok = samaPersis(sekarang->artis, kataKunci); break;
                    case 4: cocok = samaPersis(sekarang->genre, kataKunci); break;
                    case 5: cocok = (sekarang->tahunRilis == kataKunciInt); break;
                    case 6: cocok = (sekarang->rating == kataKunciFloat); break;
                }
                if (cocok) {
                    tampilkanMusik(sekarang);
                    ditemukan = true;
                }
                sekarang = sekarang->berikutnya;
            }
        }

        if (!ditemukan) cout << "Tidak ditemukan.\n";
    }
    
    // Fitur kembali
    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.ignore(10000, '\n');
}

void hapusMusik() {
    if (kepala == nullptr) {
        cout << "Tidak ada lagu dalam daftar.\n";
    } else {
        int mode;
        cout << "\n1. Hapus berdasarkan judul\n2. Hapus semua lagu\n3. Kembali ke menu utama\nPilih mode: ";
        cin >> mode;
        
        if (mode == 3) {
            cin.ignore();
            return;
        }
        
        cin.ignore();

        if (mode == 2) {
            while (kepala != nullptr) {
                Musik* sementara = kepala;
                kepala = kepala->berikutnya;
                delete sementara;
            }
            jumlahMusik = 0;
            cout << "Semua lagu telah dihapus.\n";
        } else if (mode == 1) {
            string judulHapus;
            cout << "Masukkan judul lagu yang ingin dihapus (masukkan 'kembali' untuk kembali ke menu): ";
            getline(cin, judulHapus);
            
            if (judulHapus == "kembali") return;

            Musik* sekarang = kepala;
            Musik* sebelumnya = nullptr;
            bool ditemukan = false;

            while (sekarang != nullptr) {
                if (samaPersis(sekarang->judul, judulHapus)) {
                    ditemukan = true;
                    if (sebelumnya == nullptr) {
                        kepala = sekarang->berikutnya;
                    } else {
                        sebelumnya->berikutnya = sekarang->berikutnya;
                    }
                    delete sekarang;
                    jumlahMusik--;
                    break;
                }
                sebelumnya = sekarang;
                sekarang = sekarang->berikutnya;
            }

            if (ditemukan)
                cout << "Lagu berhasil dihapus.\n";
            else
                cout << "Lagu tidak ditemukan.\n";
        }
    }
    
    // Fitur kembali
    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.ignore(10000, '\n');
}

void updateRating() {
    if (kepala == nullptr) {
        cout << "Tidak ada lagu dalam daftar.\n";
    } else {
        string judulCari;
        bool ditemukan = false;
        float ratingBaru;

        cout << "Masukkan judul lagu yang ingin diperbarui ratingnya (masukkan 'kembali' untuk kembali ke menu): ";
        getline(cin, judulCari);
        
        if (judulCari == "kembali") return;

        Musik* sekarang = kepala;
        while (sekarang != nullptr) {
            if (samaPersis(sekarang->judul, judulCari)) {
                cout << "Rating sekarang: " << sekarang->rating << "\n";
                cout << "Masukkan rating baru (0.0 - 5.0) atau -1 untuk kembali: ";
                cin >> ratingBaru;
                
                if (ratingBaru == -1) {
                    cin.ignore();
                    return;
                }
                
                cin.ignore();
                sekarang->rating = ratingBaru;
                ditemukan = true;
                break;
            }
            sekarang = sekarang->berikutnya;
        }

        if (ditemukan)
            cout << "Rating berhasil diperbarui.\n";
        else
            cout << "Lagu tidak ditemukan.\n";
    }
    
    // Fitur kembali
    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.ignore(10000, '\n');
}

void urutMusik() {
    if (kepala == nullptr) {
        cout << "Tidak ada lagu dalam daftar.\n";
    } else {
        int pilihan;
        cout << "\nUrutkan berdasarkan:\n";
        cout << "1. Judul (Insertion Sort)\n";
        cout << "2. Album (Quick Sort)\n";
        cout << "3. Artis (Merge Sort)\n";
        cout << "4. Genre (Merge Sort)\n";
        cout << "5. Tahun Rilis (Bubble Sort)\n";
        cout << "6. Rating (Selection Sort)\n";
        cout << "7. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        
        if (pilihan == 7) {
            cin.ignore();
            return;
        }
        
        cin.ignore();

        switch (pilihan) {
            case 1: urutJudul(); break;
            case 2: urutAlbum(); break;
            case 3: urutArtis(); break;
            case 4: urutGenre(); break;
            case 5: urutTahun(); break;
            case 6: urutRating(); break;
            default: cout << "Pilihan tidak valid.\n"; return;
        }

        cout << "\nDaftar Lagu setelah diurutkan:\n";
        Musik* sekarang = kepala;
        while (sekarang != nullptr) {
            tampilkanMusik(sekarang);
            sekarang = sekarang->berikutnya;
        }
    }
    
    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.ignore(10000, '\n');
}

void menu() {
    cout << "\n====================================\n";
    cout << "|              SPOTIFY             |\n";
    cout << "====================================\n";
    cout << "| 1.  Tambah Lagu                  |\n";
    cout << "| 2.  Tampilkan Semua Lagu         |\n";
    cout << "| 3.  Urutkan Lagu                 |\n";
    cout << "| 4.  Cari Lagu                    |\n";
    cout << "| 5.  Hapus Lagu                   |\n";
    cout << "| 6.  Perbarui Rating Lagu         |\n";
    cout << "| 7.  Keluar                       |\n";
    cout << "====================================\n";
    cout << "Pilih menu [1-7]: ";
}

int main() {
    int pilihan;
    do {
        menu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: tambahMusik(); break;
            case 2: lihatMusik(); break;
            case 3: urutMusik(); break;
            case 4: cariMusik(); break;
            case 5: hapusMusik(); break;
            case 6: updateRating(); break;
            case 7: cout << "Terima kasih telah menggunakan program!\n"; break;
            default: cout << "❗ Pilihan tidak valid, coba lagi!\n";
        }
    } while (pilihan != 7);

    // Membersihkan memori
    while (kepala != nullptr) {
        Musik* sementara = kepala;
        kepala = kepala->berikutnya;
        delete sementara;
    }

    return 0;
}
