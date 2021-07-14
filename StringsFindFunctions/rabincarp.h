#ifndef RABINCARP_H
#define RABINCARP_H

int rk_search(char* src, char* ptr, unsigned int* col);
int rkmd5_search(char* src, char* ptr, unsigned int* col);
int rksha256_search(char* src, char* ptr, unsigned int* col);

#endif 