#include "sha256.h"
#include <stdlib.h>
#include <stdio.h>
#define MaxInt 65535 
unsigned int h0 = 0x6a09e667, h1 = 0xbb67ae85, h2 = 0x3c6ef372, h3 = 0xa54ff53a, h4 = 0x510e527f, h5 = 0x9b05688c,
h6 = 0x1f83d9ab, h7 = 0x5be0cd19;
int consts[64] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };
unsigned int rotate_right(unsigned int value, int shift) {
    return value >> shift | value << (32 - shift);
}
unsigned char* get_sha256(char* in) {
    //константы
    int length = strlen(in);
    int rest = length % 64; //остаток от деления
    int size = 0;
    unsigned long long bit_length;
    unsigned char* msg_for_decode;
    unsigned int* res = malloc(8 * sizeof(unsigned int));
    if (rest < 56) {
        size = length - rest + 56 + 8; //делаем до 448
    }
    else {
        size = length + 64 - rest + 56 + 8; //доп.блок из 512, если       больше 448
    }
    msg_for_decode = malloc(size);
    for (int i = 0; i < length; i++) {
        msg_for_decode[i] = in[i];
    }
    msg_for_decode[length] = 0x80; //дописывание единички и ноликов     10000000
    for (int i = length + 1; i < size; i++) {
        msg_for_decode[i] = 0;
    }
    bit_length = ((unsigned long long)length) * 8;
    for (int i = 0; i < 8; i++) {
        msg_for_decode[size - 8 + i] = (unsigned char)(bit_length >> i * 8);
    }
    unsigned int* X = (unsigned int*)(msg_for_decode); //приведение 1 инт - 4 байта
    int Xsize = size / 4;
    X = realloc(X, Xsize + 48 * sizeof(unsigned int));
    for (int i = 16; i < 63; i++) {
        unsigned int s0 = (rotate_right(X[i - 15], 7) | rotate_right(X[i - 15], 18) | (X[i - 15] >> 18));
        unsigned int s1 = (rotate_right(X[i - 2], 17) | rotate_right(X[i - 2], 19) | (X[i - 2] >> 10));
        X[i] = (X[i - 16] + X[i - 7] + s0 + s1);
    }
    unsigned int a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;
    for (int i = 0; i < 63; i++) {
        unsigned int E0 = rotate_right(a, 2) | rotate_right(a, 13) | rotate_right(a, 22);
        unsigned int Ma = (a & b) | (a & c) | (b & c);
        unsigned int t2 = E0 + Ma;
        unsigned int E1 = rotate_right(e, 6) | rotate_right(e, 11) | rotate_right(e, 25);
        unsigned int Ch = (e & f) | ((!e) & g);
        unsigned int t1 = h + E1 + Ch + consts[i] + X[i];
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }
    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
    h5 += f;
    h6 += g;
    h7 += h;
    res[0] = h0;
    res[1] = h1;
    res[2] = h2;
    res[3] = h3;
    res[4] = h4;
    res[5] = h5;
    res[6] = h6;
    res[7] = h7;
    free(msg_for_decode);
    return (unsigned char*)res;
}
unsigned char* get_sha256_len(char* in, int len) {
    char* tmp;
    tmp = malloc(len + 1);
    strncpy(tmp, in, len);
    tmp[len] = 0;
    char* result = get_sha256(tmp);
    free(tmp);
    return result;
}