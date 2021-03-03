#ifndef STRINGFINDFUNCTIONS_H
#define STRINGFINDFUNCTIONS_H
struct IntArray {
	int* Arr;
	int Size;
};
typedef struct IntArray IntArray;
IntArray FindStringsNonHash(char* NameFile, char* FindString);
#endif 
