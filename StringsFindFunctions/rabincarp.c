#include "rabincarp.h"
#define BASE 2004991
#define P 2
int my_mod(int num, int diver) {
    if ((num < 0) && (num % diver)) {
        return num % diver + diver;
    }
    else {
        return num % diver;
    }
}
int rk_hash(char* a, int len) {
    int res = a[0]; 
        int i;
    for (i = 1; i < len; i++) {
        res = my_mod(res * P + a[i], BASE);
    }
    return res;
}
int rk_search(char* src, char* ptr, unsigned int* col) {
    int ptr_hash = rk_hash(ptr, strlen(ptr)), tmp_hash = rk_hash(src,
        strlen(ptr));
    int res;
    int n = strlen(src), m = strlen(ptr), p_pow = 1;
    int i, j;
    int flag;
    char* colliz = malloc(m + 1);
    for (i = 0; i < m - 1; i++) {
        p_pow = my_mod(p_pow * P, BASE);
    }
    for (i = 0; i <= n - m; i++) {
        if (tmp_hash == ptr_hash) {
            strncpy(colliz, &src[i], m);
            colliz[m] = 0;
            //printf("%s\n\n", colliz);
            (*col)++;
            flag = 1;
            for (j = 0; j < m; j++) {
                if (src[i + j] != ptr[j]) {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) {
                return i;
            }
        }
        tmp_hash = my_mod((tmp_hash - src[i] * p_pow) * P + src[m +
            i], BASE);
    }
    return -1;
}
int rkmd5_search(char* src, char* ptr, unsigned int* col) {
    unsigned long long* ptr_hash = (unsigned long long*)get_md5_len(ptr, strlen(ptr));
    unsigned long long* tmp_hash = (unsigned long long*)get_md5_len(src, strlen(ptr));
    int res;
    int n = strlen(src), m = strlen(ptr), p_pow = 1;
    int i, j;
    int flag;
    for (i = 0; i < m - 1; i++) {
        p_pow = my_mod(p_pow * P, BASE);
    }
        for (i = 0; i <= n - m; i++) {
            if (tmp_hash[0] == ptr_hash[0] && tmp_hash[1] ==
                ptr_hash[1]) {
                (*col)++;
                flag = 1;
                for (j = 0; j < m; j++) {
                    if (src[i + j] != ptr[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    return i;
                }
            }
            free(tmp_hash);
            tmp_hash = get_md5_len(&src[i + 1], strlen(ptr));
        }
    free(ptr_hash);
    return -1;
}