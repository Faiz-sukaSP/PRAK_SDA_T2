#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

/* 
   ===============================
 ||          KONSTANTA            ||                                               
   ===============================
*/

#define MAX_WORDS          4000   // Maks kata untuk advance sorting   
#define MAX_WORD_LEN       100    // Maks panjang setiap kata          
#define STANDARD_DATA_SIZE 1000   // Jumlah data integer (Angka Random)                 
#define TAMPIL_INT         30     // Jumlah int yang ditampilkan (Standard sorting)     
#define TAMPIL_STR         20     // Jumlah string yang ditampilkan (Advance sorting)   

/* 
   ===============================
 ||            FILE               ||                                               
   ===============================
*/

// Membaca kata pada File yang diberikan lalu menyimpannya ke array string
int  bacaFile(const char *namaFile, char words[][MAX_WORD_LEN]);

// Menampilkan data dari File, memberitahukan jumlah total data, dan jumlah data yang ditampilan
void tampilkanDataFile(char words[][MAX_WORD_LEN], int jumlah, int jumlahTampil, const char *judul);

/* 
   ===============================
 ||           SHUFFLE             ||                                               
   ===============================
*/

// Fisher-Yates-Shuffle untuk array integer (Standard sorting)
void shuffleInt(int arr[], int n);

// Fisher-Yates-Shuffle untuk array string (Advance sorting)
void shuffleStr(char arr[][MAX_WORD_LEN], int n);

/* 
   ===================================
 ||    STANDARD SORTING (Ascending)   ||                                               
   ===================================
*/

// Fungsi sorting dasar
void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);

/* 
   ===================================
 ||    ADVANCE SORTING (Ascending)   ||                                               
   ===================================
*/

// Quick Sort: iteratif menggunakan stack heap dan pivot tengah 
void quickSortStr(char arr[][MAX_WORD_LEN], int kiri, int kanan);

// Merge Sort: buffer sementara yang langsung dibebaskan setelah merge. 
void mergeSortStr(char arr[][MAX_WORD_LEN], int kiri, int kanan);

// Shell Sort: urutan gap Knuth (1, 4, 13, 40, ...). 
void shellSortStr(char arr[][MAX_WORD_LEN], int n);

/* 
   ===============================
 ||          TAMPILAN             ||                                               
   ===============================
*/

// Menampilkan jumlah data yang ditampilkan sebelum dan sesudah sebanyak yang ditentukan
void tampilkanDataInt(int arr[], int n, int jumlahTampil, const char *judul);

// Menampilkan statistik data (Nama algoritme, Jumlah data, dan Waktu)
void tampilkanRingkasan(const char *namaAlgoritma, int n, double waktuMs);

/* 
   ===============================
 ||            MENU               ||                                               
   ===============================
*/

// Membaca dan memvalidasi input integer dalam rentang [min, max]. Terus meminta ulang jika input tidak valid
int  bacaPilihanMenu(int min, int max);

// Loop submenu Sorting Dasar (Bubble, Selection, Insertion Sort)
void jalankanMenuStandard(void);

// Loop submenu Advance Sorting (Quick, Merge, Shell Sort)
void jalankanMenuAdvance(void);

// Entry point utama: tampil sambutan, loop menu utama hingga keluar untuk dipanggil di main
void jalankanProgram(void);

#endif
