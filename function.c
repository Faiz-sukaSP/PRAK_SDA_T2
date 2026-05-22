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

/* ================================================================== */
/*  SHUFFLE — Fisher-Yates                                              */
/* ================================================================== */

void shuffleInt(int arr[], int n) {
    int i, j, tmp;
    for (i = n - 1; i > 0; i--) 
    {
        j = rand() % (i + 1);
        if (i == j) continue;
        tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
    }
}

void shuffleStr(char arr[][MAX_WORD_LEN], int n) {
    int i, j;
    for (i = n - 1; i > 0; i--) 
    {
        j = rand() % (i + 1);
        if (i == j) continue;
        swapStr(arr[i], arr[j]);
    }
}

/* ================================================================== */
/*  STANDARD SORTING — integer ascending                               */
/* ================================================================== */

void bubbleSort(int arr[], int n) {
    int i, j, tertukar;
    if (n < 2) return;
    for (i = 0; i < n - 1; i++) 
    {
        tertukar = 0;
        for (j = 0; j < n - 1 - i; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                swapInt(&arr[j], &arr[j + 1]);
                tertukar = 1;
            }
        }
        if (!tertukar) break;
    }
}

void selectionSort(int arr[], int n) {
    int i, j, idxMin;
    if (n < 2) return;
    for (i = 0; i < n - 1; i++) 
    {
        idxMin = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[idxMin]) idxMin = j;
        if (idxMin != i) swapInt(&arr[i], &arr[idxMin]);
    }
}
void insertionSort(int arr[], int n)
{
    int i, j, kunci;
    if (n < 2)
        return;
    for (i = 1; i < n; i++)
    {
        kunci = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > kunci)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = kunci;
    }
}

/* ================================================================== */
/*  ADVANCE SORTING — string ascending leksikografis                   */
/* ================================================================== */

/* ---------- Quick Sort iteratif (stack di heap) ---------- */

static int partisiStr(char arr[][MAX_WORD_LEN], int lo, int hi)
{
    char pivot[MAX_WORD_LEN];
    int mid = lo + (hi - lo) / 2;
    int i, j;

    /* Pindahkan elemen tengah ke posisi hi sebagai pivot */
    swapStr(arr[mid], arr[hi]);
    memcpy(pivot, arr[hi], MAX_WORD_LEN);

    i = lo - 1;
    for (j = lo; j < hi; j++)
    {
        if (strcmp(arr[j], pivot) <= 0)
        {
            i++;
            swapStr(arr[i], arr[j]);
        }
    }
    swapStr(arr[i + 1], arr[hi]);
    return i + 1;
}

void quickSortStr(char arr[][MAX_WORD_LEN], int kiri, int kanan)
{
    int *stack;
    int top = -1, p, lo, hi;

    if (kiri >= kanan)
        return;

    stack = (int *)malloc(2 * (size_t)(kanan - kiri + 1) * sizeof(int));
    if (!stack)
    {
        fprintf(stderr, "[ERROR]: malloc gagal di quickSortStr\n");
        return;
    }

    stack[++top] = kiri;
    stack[++top] = kanan;

    while (top >= 0)
    {
        hi = stack[top--];
        lo = stack[top--];
        if (lo >= hi)
            continue;
        p = partisiStr(arr, lo, hi);
        if (p - 1 > lo)
        {
            stack[++top] = lo;
            stack[++top] = p - 1;
        }
        if (p + 1 < hi)
        {
            stack[++top] = p + 1;
            stack[++top] = hi;
        }
    }
    free(stack);
}

/* ---------- Merge Sort iteratif bottom-up ---------- */

static void mergeStr(char arr[][MAX_WORD_LEN],
                     int lo, int mid, int hi)
{
    int n1 = mid - lo + 1;
    int n2 = hi - mid;
    int i, j, k;

    char (*L)[MAX_WORD_LEN] = malloc((size_t)n1 * sizeof(*L));
    char (*R)[MAX_WORD_LEN] = malloc((size_t)n2 * sizeof(*R));
    if (!L || !R)
    {
        fprintf(stderr, "[ERROR]: malloc gagal di mergeStr\n");
        free(L);
        free(R);
        return;
    }

    for (i = 0; i < n1; i++)
        memcpy(L[i], arr[lo + i], MAX_WORD_LEN);
    for (j = 0; j < n2; j++)
        memcpy(R[j], arr[mid + 1 + j], MAX_WORD_LEN);

    i = 0;
    j = 0;
    k = lo;
    while (i < n1 && j < n2)
    {
        if (strcmp(L[i], R[j]) <= 0)
            memcpy(arr[k++], L[i++], MAX_WORD_LEN);
        else
            memcpy(arr[k++], R[j++], MAX_WORD_LEN);
    }
    while (i < n1)
        memcpy(arr[k++], L[i++], MAX_WORD_LEN);
    while (j < n2)
        memcpy(arr[k++], R[j++], MAX_WORD_LEN);

    free(L);
    free(R);
}

void mergeSortStr(char arr[][MAX_WORD_LEN], int kiri, int kanan)
{
    int lebar, lo, mid, hi;
    if (kiri >= kanan)
        return;
    for (lebar = 1; lebar <= kanan - kiri; lebar *= 2)
    {
        for (lo = kiri; lo < kanan; lo += 2 * lebar)
        {
            mid = lo + lebar - 1;
            hi = lo + 2 * lebar - 1;
            if (mid > kanan)
                mid = kanan;
            if (hi > kanan)
                hi = kanan;
            if (mid < hi)
                mergeStr(arr, lo, mid, hi);
        }
    }
}

/* ---------- Shell Sort — gap Knuth ---------- */

void shellSortStr(char arr[][MAX_WORD_LEN], int n)
{
    int gap, i, j;
    char tmp[MAX_WORD_LEN];
    if (n < 2)
        return;
    gap = 1;
    while (gap < n / 3)
        gap = gap * 3 + 1;
    while (gap >= 1)
    {
        for (i = gap; i < n; i++)
        {
            memcpy(tmp, arr[i], MAX_WORD_LEN);
            j = i;
            while (j >= gap && strcmp(arr[j - gap], tmp) > 0)
            {
                memcpy(arr[j], arr[j - gap], MAX_WORD_LEN);
                j -= gap;
            }
            memcpy(arr[j], tmp, MAX_WORD_LEN);
        }
        gap = (gap - 1) / 3;
    }
}

/* ================================================================== */
/*                 Tampilan & statistik sorting                       */
/* ================================================================== */

void tampilkanDataInt(int arr[], int n, int jumlahTampil,
                      const char *judul)
{
    int tampil, i;
    printf("\n--- %s ---\n", judul);
    if (n <= 0)
    {
        printf("(tidak ada data)\n");
        return;
    }
    tampil = (n < jumlahTampil) ? n : jumlahTampil;
    for (i = 0; i < tampil; i++)
    {
        printf("%5d", arr[i]);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
    if (tampil % 10 != 0)
        printf("\n");
    if (n > jumlahTampil)
        printf("... (%d data tidak ditampilkan)\n", n - jumlahTampil);
    printf("Total data: %d\n", n);
}

void tampilkanRingkasan(const char *namaAlgoritma, int n,
                        double waktuMs)
{
    printf("\n================================\n");
    printf("Algoritma  : %s\n", namaAlgoritma);
    printf("Jumlah data: %d\n", n);
    printf("Waktu      : %.2f ms\n", waktuMs);
    printf("================================\n");
}
