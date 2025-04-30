#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Music {
    char title[30];
    char album[30];
    char duration[10];
    char artist[30];
    char genre[20];
    int releaseYear;
    float rating;
};

bool isEqual(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

void addMusic() {
    Music m;
    int jumlah;
    cout << "Ingin menambahkan berapa lagu? ";
    cin >> jumlah;
    cin.ignore();

    ofstream file("music.txt", ios::app);

    for (int i = 0; i < jumlah; i++) {
        cout << "\nLagu ke-" << i + 1 << endl;
        cout << "Judul: "; cin.getline(m.title, 30);
        cout << "Album: "; cin.getline(m.album, 30);
        cout << "Durasi: "; cin.getline(m.duration, 10);
        cout << "Artis: "; cin.getline(m.artist, 30);
        cout << "Genre: "; cin.getline(m.genre, 20);
        cout << "Tahun Rilis: "; cin >> m.releaseYear;
        cout << "Rating (0.0 - 5.0): "; cin >> m.rating;
        cin.ignore();

        file << m.title << ";" << m.album << ";" << m.duration << ";"
             << m.artist << ";" << m.genre << ";" << m.releaseYear << ";"
             << m.rating << "\n";
    }

    file.close();
    cout << jumlah << " lagu berhasil ditambahkan!\n";
}

void showAllMusic() {
    Music m;
    ifstream file("music.txt");
    cout << "\nDaftar Semua Lagu:\n";
    while (file.getline(m.title, 30, ';') &&
           file.getline(m.album, 30, ';') &&
           file.getline(m.duration, 10, ';') &&
           file.getline(m.artist, 30, ';') &&
           file.getline(m.genre, 20, ';') &&
           file >> m.releaseYear &&
           file.get() && file >> m.rating &&
           file.get())
    {
        cout << "Judul: " << m.title
             << "\nAlbum: " << m.album
             << "\nDurasi: " << m.duration
             << "\nArtis: " << m.artist
             << "\nGenre: " << m.genre
             << "\nTahun Rilis: " << m.releaseYear
             << "\nRating: " << m.rating << "\n\n";
    }
    file.close();
}

void insertionSort(Music arr[], int n) { // Insertion Sort
    for (int i = 1; i < n; i++) {
        Music key = arr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j].title, key.title) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSortByRating(Music arr[], int n) { // Selection Sort
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].rating > arr[maxIdx].rating)
                maxIdx = j;
        }
        swap(arr[i], arr[maxIdx]);
    }
}

void bubbleSortByYear(Music arr[], int n) { // Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].releaseYear > arr[j + 1].releaseYear) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(Music arr[], int l, int m, int r, bool byArtist = true) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Music L[100], R[100];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if ((byArtist && strcmp(L[i].artist, R[j].artist) <= 0) ||
            (!byArtist && strcmp(L[i].genre, R[j].genre) <= 0))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortByArtist(Music arr[], int l, int r) { // Merge Sort by Artist
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortByArtist(arr, l, m);
        mergeSortByArtist(arr, m + 1, r);
        merge(arr, l, m, r, true);
    }
}

void mergeSortByGenre(Music arr[], int l, int r) { // Merge Sort by Genre
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortByGenre(arr, l, m);
        mergeSortByGenre(arr, m + 1, r);
        merge(arr, l, m, r, false);
    }
}

int partition(Music arr[], int low, int high) {
    Music pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j].album, pivot.album) < 0) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortByAlbum(Music arr[], int low, int high) { // Quick Sort
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortByAlbum(arr, low, pi - 1);
        quickSortByAlbum(arr, pi + 1, high);
    }
}

void searchMusic() {
    Music list[100];
    int count = 0;

    ifstream file("music.txt");
    while (file.getline(list[count].title, 30, ';') &&
           file.getline(list[count].album, 30, ';') &&
           file.getline(list[count].duration, 10, ';') &&
           file.getline(list[count].artist, 30, ';') &&
           file.getline(list[count].genre, 20, ';') &&
           file >> list[count].releaseYear &&
           file.get() && file >> list[count].rating &&
           file.get()) {
        count++;
    }
    file.close();

    int option;
    cout << "\nCari berdasarkan:\n";
    cout << "1. Judul (Insertion Sort)\n";
    cout << "2. Album (Quick Sort)\n";
    cout << "3. Artis (Merge Sort)\n";
    cout << "4. Genre (Merge Sort)\n";
    cout << "5. Tahun Rilis (Bubble Sort)\n";
    cout << "6. Rating (Selection Sort)\n";
    cout << "Pilihan: ";
    cin >> option;
    cin.ignore();

    char keyword[30];
    int keywordInt;
    cout << "Masukkan keyword pencarian: ";

    if (option == 5) cin >> keywordInt;
    else cin.getline(keyword, 30);

    switch (option) {
        case 1: insertionSort(list, count); break;
        case 2: quickSortByAlbum(list, 0, count - 1); break;
        case 3: mergeSortByArtist(list, 0, count - 1); break;
        case 4: mergeSortByGenre(list, 0, count - 1); break;
        case 5: bubbleSortByYear(list, count); break;
        case 6: selectionSortByRating(list, count); break;
        default: break;
    }

    bool found = false;
    cout << "\nHasil pencarian:\n";
    for (int i = 0; i < count; i++) {
        bool match = false;
        switch (option) {
            case 1: match = isEqual(list[i].title, keyword); break;
            case 2: match = isEqual(list[i].album, keyword); break;
            case 3: match = isEqual(list[i].artist, keyword); break;
            case 4: match = isEqual(list[i].genre, keyword); break;
            case 5: match = (list[i].releaseYear == keywordInt); break;
            case 6: match = (list[i].rating == atof(keyword)); break;
        }
        if (match) {
            found = true;
            cout << "Judul: " << list[i].title
                 << "\nAlbum: " << list[i].album
                 << "\nDurasi: " << list[i].duration
                 << "\nArtis: " << list[i].artist
                 << "\nGenre: " << list[i].genre
                 << "\nTahun Rilis: " << list[i].releaseYear
                 << "\nRating: " << list[i].rating << "\n\n";
        }
    }

    if (!found) cout << "Tidak ditemukan.\n";
}

void deleteMusic() {
    int mode;
    cout << "\n1. Hapus berdasarkan judul\n2. Hapus semua lagu\nPilih mode: ";
    cin >> mode;
    cin.ignore();

    if (mode == 2) {
        ofstream clearFile("music.txt", ios::trunc);
        clearFile.close();
        cout << "Semua lagu telah dihapus.\n";
        return;
    }

    Music m;
    char deleteTitle[30];
    bool found = false;

    cout << "Masukkan judul lagu yang ingin dihapus: ";
    cin.getline(deleteTitle, 30);

    ifstream file("music.txt");
    ofstream temp("temp.txt");

    while (file.getline(m.title, 30, ';') &&
           file.getline(m.album, 30, ';') &&
           file.getline(m.duration, 10, ';') &&
           file.getline(m.artist, 30, ';') &&
           file.getline(m.genre, 20, ';') &&
           file >> m.releaseYear &&
           file.get() && file >> m.rating &&
           file.get())
    {
        if (!isEqual(m.title, deleteTitle)) {
            temp << m.title << ";" << m.album << ";" << m.duration << ";"
                 << m.artist << ";" << m.genre << ";" << m.releaseYear << ";"
                 << m.rating << "\n";
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("music.txt");
    rename("temp.txt", "music.txt");

    if (found)
        cout << "Lagu berhasil dihapus.\n";
    else
        cout << "Lagu tidak ditemukan.\n";
}

void updateRating() {
    Music m;
    char searchTitle[30];
    bool found = false;
    float newRating;

    cout << "Masukkan judul lagu yang ingin diperbarui ratingnya: ";
    cin.ignore();
    cin.getline(searchTitle, 30);

    ifstream file("music.txt");
    ofstream temp("temp.txt");

    while (file.getline(m.title, 30, ';') &&
           file.getline(m.album, 30, ';') &&
           file.getline(m.duration, 10, ';') &&
           file.getline(m.artist, 30, ';') &&
           file.getline(m.genre, 20, ';') &&
           file >> m.releaseYear &&
           file.get() && file >> m.rating &&
           file.get())
    {
        if (isEqual(m.title, searchTitle)) {
            cout << "Rating sekarang: " << m.rating << "\n";
            cout << "Masukkan rating baru (0.0 - 5.0): ";
            cin >> newRating;
            m.rating = newRating;
            found = true;
        }

        temp << m.title << ";" << m.album << ";" << m.duration << ";"
             << m.artist << ";" << m.genre << ";" << m.releaseYear << ";"
             << m.rating << "\n";
    }

    file.close();
    temp.close();

    remove("music.txt");
    rename("temp.txt", "music.txt");

    if (found)
        cout << "Rating berhasil diperbarui.\n";
    else
        cout << "Lagu tidak ditemukan.\n";
}

void displayMenu() {
    cout << "\n====================================\n";
    cout << "|              SPOTIFY             |\n";
    cout << "====================================\n";
    cout << "| 1.  Tambah Lagu                  |\n";
    cout << "| 2.  Tampilkan Semua Lagu         |\n";
    cout << "| 3.  Cari Lagu                    |\n";
    cout << "| 4.  Hapus Lagu                   |\n";
    cout << "| 5.  Update Rating Lagu           |\n";
    cout << "| 6.  Keluar                       |\n";
    cout << "====================================\n";
    cout << "Pilih menu [1-6]: ";
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: addMusic(); break;
            case 2: showAllMusic(); break;
            case 3: searchMusic(); break;
            case 4: deleteMusic(); break;
            case 5: updateRating(); break;
            case 6: cout << "Terima kasih telah menggunakan aplikasi!\n"; break;
            default: cout << "❗ Pilihan tidak valid, coba lagi!\n";
        }
    } while (choice != 6);

    return 0;
}
