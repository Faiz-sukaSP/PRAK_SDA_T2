#include "function.h"

/* 
    ============================== 
           HELPER INTERNAL                                                     
    ==============================
*/

// Fungsi untuk menukarkan nilai dari dua buah integer (Akan dipanggil di setiap algoritma sorting)
static void swapInt(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fungsi untuk menukarkan nilai dari dua buah string — aman terhadap self-swap (a == b)
static void swapStr(char a[], char b[]) {
    
    char temp[MAX_WORD_LEN]; // menyiapkan wadah string kosong
    if (a == b) return; // self-swap protection
    
    // menggunakan fungsi memcpy (memory copy) 
    memcpy(temp, a,   MAX_WORD_LEN);
    memcpy(a,   b,   MAX_WORD_LEN);
    memcpy(b,   temp, MAX_WORD_LEN);
}

// Fungsi untuk menduplikasi seluruh isi array ke array yang baru (Standard sorting)
static void salinInt(int dst[], const int src[], int n) {
    for (int i = 0; i < n; i++) 
        dst[i] = src[i];
}


// Fungsi untuk menduplikasi seluruh isi array ke array yang baru (Advance sorting)
static void salinStr(char dst[][MAX_WORD_LEN], char src[][MAX_WORD_LEN], int n) {
    for (int i = 0; i < n; i++) 
        memcpy(dst[i], src[i], MAX_WORD_LEN);
}