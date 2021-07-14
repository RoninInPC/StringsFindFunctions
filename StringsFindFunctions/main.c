#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include"StringFindFunctions.h"
#include"md5.h"
#include"rabincarp.h"
#include"sha256.h"
time_t timer;
void start_time() {
	timer = clock();
}
double get_time() {
	return (double)(clock() - timer) / CLOCKS_PER_SEC;
}
char* load_mem_file(char* filename) {
    // открываем файл (получаем файловый дескриптор)
    HANDLE fd = CreateFileA(
        filename, // имя файла
        GENERIC_READ | GENERIC_WRITE, // права доступа
        0,
        NULL,
        OPEN_EXISTING, // открываемый файл должен существовать
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    // создаем проекцию файла в память
    HANDLE mapd = CreateFileMappingA(fd, NULL, PAGE_READWRITE, 0,GetFileSize(fd, NULL), NULL);
    // отображаем проекцию в память
    char* mem = (char*)MapViewOfFile(mapd, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    return mem;
}

int main() {
    //War_and_Peace.txt
    char* file_name[4] = { "MyText1.txt", "MyText2.txt", "War_and_Peace.txt","Anna_Karenina.txt" };
    char* word[4] = { "abc","abc","door","door" };
    for (int i = 0; i < 4; i++){
        printf("%s\n", file_name[i]);
        start_time();
            IntArray Ans = FindStringsNonHash(file_name[i], word[i]);
        get_time();
        printf("time in int = %d, time in sec = %.3f, num = %d\n", timer, timer, Ans.Size);
        start_time();
            char* mem = load_mem_file(file_name[i]);
            IntArray Ans2 = FindStringsNonHashNonFile(mem, word[i]);
        get_time();
        printf("time in int = %d, time in sec = %.3f, num = %d\n", timer, timer, Ans.Size);
        start_time();
        int l = 0;
            int k = rk_search(mem, word[i], &l);
        get_time();
        printf("time in int = %d, time in sec = %.3f, num = %d, collizy = %d\n", timer, timer, k, l);
        start_time();
        l = 0;
            k = rkmd5_search(mem, word[i], &l);
        get_time();
        printf("time in int = %d, time in sec = %.3f, num = %d, collizy = %d\n", timer, timer, k, l);
        start_time();
        l = 0;
            k = rksha256_search(mem, word[i], &l);
        get_time();
        printf("time in int = %d, time in sec = %.3f, num = %d, collizy = %d\n", timer, timer, k, l);
}
	return 0;
}