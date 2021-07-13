#include "md5.h"
#include <stdlib.h>
#include <stdio.h>
unsigned int F(unsigned int X, unsigned int Y, unsigned int Z) {
    return ((X & Y) | ((~X) & Z));
}
unsigned int G(unsigned int X, unsigned int Y, unsigned int Z) {
    return (X & Z) | (Y & (~Z));
}
unsigned int H(unsigned int X, unsigned int Y, unsigned int Z) {
    return X ^ Y ^ Z;
}
unsigned int I(unsigned int X, unsigned int Y, unsigned int Z) {
    return Y ^ (X | (~Z));
}
unsigned int rotate_left(unsigned int value, int shift) {
    return value << shift | value >> (32 - shift);
}
unsigned char* get_md5(char* in) {
    int length = strlen(in);
    int rest = length % 64; //остаток от деления
    int size = 0;
    unsigned long long bit_length;
    unsigned char* msg_for_decode;
    unsigned int* res;
    unsigned int A = 0x67452301, B = 0xefcdab89, C = 0x98badcfe, D =
        0x10325476;
    unsigned int T[64];
    unsigned int AA = 0, BB = 0, CC = 0, DD = 0;
    unsigned int* X;
    if (rest < 56) {
        size = length - rest + 56 + 8; //делаем до 448
    }
    else {
        size = length + 64 - rest + 56 + 8; //доп.блок из 512, если       больше 448
    }
    msg_for_decode = malloc(size);
    res = malloc(4 * sizeof(int));
    X = (unsigned int*)(msg_for_decode); //приведение 1 инт - 4 байта
    for (int i = 0; i < length; i++) {
        msg_for_decode[i] = in[i];
    }
    msg_for_decode[length] = 0x80; //дописывание единички и ноликов     10000000
        for (int i = length + 1; i < size; i++) {
            msg_for_decode[i] = 0;
        }
    bit_length = ((unsigned long long)length) * 8;
    for (int i = 0; i < 8; i++) {
        msg_for_decode[size - 8 + i] = (unsigned char)(bit_length >>
            i * 8);
    }
    for (int i = 0; i < 64; i++) {
        T[i] = (unsigned int)(pow(2, 32) * fabs(sin(i + 1)));
        //считаем Т
    }
    for (int i = 0; i < size / 4; i += 16) {
        AA = A; BB = B; CC = C; DD = D;
        //раунд 1
        A = B + rotate_left((A + F(B, C, D) + X[i + 0] + T[0]), 7);
        D = A + rotate_left((D + F(A, B, C) + X[i + 1] + T[1]), 12);
        C = D + rotate_left((C + F(D, A, B) + X[i + 2] + T[2]), 17);
        B = C + rotate_left((B + F(C, D, A) + X[i + 3] + T[3]), 22);
        A = B + rotate_left((A + F(B, C, D) + X[i + 4] + T[4]), 7);
        D = A + rotate_left((D + F(A, B, C) + X[i + 5] + T[5]), 12);
        C = D + rotate_left((C + F(D, A, B) + X[i + 6] + T[6]), 17);
        B = C + rotate_left((B + F(C, D, A) + X[i + 7] + T[7]), 22);
        A = B + rotate_left((A + F(B, C, D) + X[i + 8] + T[8]), 7);
        D = A + rotate_left((D + F(A, B, C) + X[i + 9] + T[9]), 12);
        C = D + rotate_left((C + F(D, A, B) + X[i + 10] + T[10]),
            17);
        B = C + rotate_left((B + F(C, D, A) + X[i + 11] + T[11]),
            22);
        A = B + rotate_left((A + F(B, C, D) + X[i + 12] + T[12]),
            7);
        D = A + rotate_left((D + F(A, B, C) + X[i + 13] + T[13]),
            12);
            C = D + rotate_left((C + F(D, A, B) + X[i + 14] + T[14]),
                17);
        B = C + rotate_left((B + F(C, D, A) + X[i + 15] + T[15]),
            22);
        //раунд 2
        A = B + rotate_left((A + G(B, C, D) + X[i + 1] + T[16]), 5);
        D = A + rotate_left((D + G(A, B, C) + X[i + 6] + T[17]), 9);
        C = D + rotate_left((C + G(D, A, B) + X[i + 11] + T[18]),
            14);
        B = C + rotate_left((B + G(C, D, A) + X[i + 0] + T[19]),
            20);
        A = B + rotate_left((A + G(B, C, D) + X[i + 5] + T[20]), 5);
        D = A + rotate_left((D + G(A, B, C) + X[i + 10] + T[21]),
            9);
        C = D + rotate_left((C + G(D, A, B) + X[i + 15] + T[22]),
            14);
        B = C + rotate_left((B + G(C, D, A) + X[i + 4] + T[23]),
            20);
        A = B + rotate_left((A + G(B, C, D) + X[i + 9] + T[24]), 5);
        D = A + rotate_left((D + G(A, B, C) + X[i + 14] + T[25]),
            9);
        C = D + rotate_left((C + G(D, A, B) + X[i + 3] + T[26]),
            14);
        B = C + rotate_left((B + G(C, D, A) + X[i + 8] + T[27]),
            20);
        A = B + rotate_left((A + G(B, C, D) + X[i + 13] + T[28]),
            5);
        D = A + rotate_left((D + G(A, B, C) + X[i + 2] + T[29]), 9);
        C = D + rotate_left((C + G(D, A, B) + X[i + 7] + T[30]),
            14);
        B = C + rotate_left((B + G(C, D, A) + X[i + 12] + T[31]),
            20);
        //раунд 3
        A = B + rotate_left((A + H(B, C, D) + X[i + 5] + T[32]), 4);
        D = A + rotate_left((D + H(A, B, C) + X[i + 8] + T[33]),
            11);
        C = D + rotate_left((C + H(D, A, B) + X[i + 11] + T[34]),
            16);
        B = C + rotate_left((B + H(C, D, A) + X[i + 14] + T[35]),
            23);
        A = B + rotate_left((A + H(B, C, D) + X[i + 1] + T[36]), 4);
        D = A + rotate_left((D + H(A, B, C) + X[i + 4] + T[37]),
            11);
        C = D + rotate_left((C + H(D, A, B) + X[i + 7] + T[38]),
            16);
        B = C + rotate_left((B + H(C, D, A) + X[i + 10] + T[39]),
            23);
            A = B + rotate_left((A + H(B, C, D) + X[i + 13] + T[40]),
                4);
        D = A + rotate_left((D + H(A, B, C) + X[i + 0] + T[41]),
            11);
        C = D + rotate_left((C + H(D, A, B) + X[i + 3] + T[42]),
            16);
        B = C + rotate_left((B + H(C, D, A) + X[i + 6] + T[43]),
            23);
        A = B + rotate_left((A + H(B, C, D) + X[i + 9] + T[44]), 4);
        D = A + rotate_left((D + H(A, B, C) + X[i + 12] + T[45]),
            11);
        C = D + rotate_left((C + H(D, A, B) + X[i + 15] + T[46]),
            16);
        B = C + rotate_left((B + H(C, D, A) + X[i + 2] + T[47]),
            23);
        //раунд 4
        A = B + rotate_left((A + I(B, C, D) + X[i + 0] + T[48]), 6);
        D = A + rotate_left((D + I(A, B, C) + X[i + 7] + T[49]),
            10);
        C = D + rotate_left((C + I(D, A, B) + X[i + 14] + T[50]),
            15);
        B = C + rotate_left((B + I(C, D, A) + X[i + 5] + T[51]),
            21);
        A = B + rotate_left((A + I(B, C, D) + X[i + 12] + T[52]),
            6);
        D = A + rotate_left((D + I(A, B, C) + X[i + 3] + T[53]),
            10);
        C = D + rotate_left((C + I(D, A, B) + X[i + 10] + T[54]),
            15);
        B = C + rotate_left((B + I(C, D, A) + X[i + 1] + T[55]),
            21);
        A = B + rotate_left((A + I(B, C, D) + X[i + 8] + T[56]), 6);
        D = A + rotate_left((D + I(A, B, C) + X[i + 15] + T[57]),
            10);
        C = D + rotate_left((C + I(D, A, B) + X[i + 6] + T[58]),
            15);
        B = C + rotate_left((B + I(C, D, A) + X[i + 13] + T[59]),
            21);
        A = B + rotate_left((A + I(B, C, D) + X[i + 4] + T[60]), 6);
        D = A + rotate_left((D + I(A, B, C) + X[i + 11] + T[61]),
            10);
        C = D + rotate_left((C + I(D, A, B) + X[i + 2] + T[62]),
            15);
        B = C + rotate_left((B + I(C, D, A) + X[i + 9] + T[63]),
            21);
        A += AA;
        B += BB;
        C += CC;
        D += DD;
    }
    res[0] = A;
    res[1] = B;
    res[2] = C;
    res[3] = D;
    res[4] = '\0';
    free(msg_for_decode);
    return (unsigned char*)res;
}
unsigned char* get_md5_len(char* in, int len) {
    char* tmp;
    tmp = malloc(len + 1);
    strncpy(tmp, in, len);
    tmp[len] = 0;
    char* result = get_md5(tmp);
    free(tmp);
    return result;
}