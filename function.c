#include "function.h"

/*
    ==============================
           HELPER INTERNAL
    ==============================
*/

// Fungsi untuk menukarkan nilai dari dua buah integer (Akan dipanggil di setiap algoritma sorting)
static void swapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fungsi untuk menukarkan nilai dari dua buah string — aman terhadap self-swap (a == b)
static void swapStr(char a[], char b[])
{

    char temp[MAX_WORD_LEN]; // menyiapkan wadah string kosong
    if (a == b)
        return; // self-swap protection

    // menggunakan fungsi memcpy (memory copy)
    memcpy(temp, a, MAX_WORD_LEN);
    memcpy(a, b, MAX_WORD_LEN);
    memcpy(b, temp, MAX_WORD_LEN);
}

// Fungsi untuk menduplikasi seluruh isi array ke array yang baru (Standard sorting)
static void salinInt(int dst[], const int src[], int n)
{
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

// Fungsi untuk menduplikasi seluruh isi array ke array yang baru (Advance sorting)
static void salinStr(char dst[][MAX_WORD_LEN], char src[][MAX_WORD_LEN], int n)
{
    for (int i = 0; i < n; i++)
        memcpy(dst[i], src[i], MAX_WORD_LEN);
}

/*
    =======================
             FILE
    =======================
*/

// Fungsi untuk membuka dan membaca File yang diberikan
int bacaFile(const char *namaFile, char words[][MAX_WORD_LEN])
{
    FILE *fp;
    int jumlah = 0, melebihiBatas = 0;
    char buffer[MAX_WORD_LEN + 2];
    size_t len;

    // membuka dan membaca file
    fp = fopen(namaFile, "r");
    // validasi pembacaan file
    if (fp == NULL)
    {
        // pengecekam jika kesalahan disebabkan karena izin pembacaan tidak ada/ditolak (EACCES)
        if (errno == EACCES)
        {
            fprintf(stderr, "ERROR: Izin tidak ada untuk membuka File '%s'\n", namaFile);
            printf("================================================\n");
        }
        // pengecekan jika kesalan karena file tidak ada
        else
        {
            fprintf(stderr, "ERROR: File '%s' tidak ditemukan! \n Pastikan File berada di folder yang sama\n", namaFile);
            printf("================================================\n");
        }
        return -1;
    }

    // menbaca file baris demi baris, membersihkannya, dan menyimpannya kedalam array 2D (words)
    while (fgets(buffer, (int)sizeof(buffer), fp) != NULL)
    {
        len = strlen(buffer);
        // mengubah '\n' pada akhir string menjadi '\0'
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[--len] = '\0';

        // jika len kosong maka lompat ke proses selanjutnya
        if (len == 0)
            continue;

        // pengecekan apakah panjang kata melebihi/samadengan batas maksimal string
        if (jumlah >= MAX_WORDS)
        {
            melebihiBatas = 1;
            break; // berhenti membaca File
        }
        // menyalin buffer kedalam string jumlah
        strncpy(words[jumlah], buffer, MAX_WORD_LEN - 1);
        words[jumlah][MAX_WORD_LEN - 1] = '\0'; // set nilai terkahir menjadi null terminator
        jumlah++;
    }
    // menutup File
    fclose(fp);

    // validasi sederhana
    if (jumlah == 0)
    {
        fprintf(stderr, "ERROR: File '%s' Kosong\n", namaFile);
        printf("--------------------------------------------------\n");
    }
    if (melebihiBatas)
    {
        printf("Peringatan: hanya '%d' kata pertama yang dimuat! \n", MAX_WORDS);
        printf("--------------------------------------------------\n");
    }
    if (jumlah < 2)
    {
        printf("Peringatan: Tidak ada kata yang bisa di urutkan (kata hanya 1)\n");
        printf("--------------------------------------------------------------\n");
    }
    return jumlah;
}

void tampilkanDataFile(char words[][MAX_WORD_LEN], int jumlah,int jumlahTampil, const char *judul) 
{
    int tampil, i;
    printf("\n--- %s ---\n", judul);
    if (jumlah <= 0) 
    { 
        printf("(tidak ada data)\n"); return;
    }
    tampil = (jumlah < jumlahTampil) ? jumlah : jumlahTampil;
    
    for (i = 0; i < tampil; i++)
        printf("%4d. %s\n", i + 1, words[i]);
    
    if (jumlah > jumlahTampil)
        printf("     ... (%d kata tidak ditampilkan)\n",
               jumlah - jumlahTampil);
               
    printf("Total kata dimuat: %d\n", jumlah);
}