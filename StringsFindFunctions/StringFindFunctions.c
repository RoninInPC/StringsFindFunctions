#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"StringFindFunctions.h"
IntArray FindStringsNonHash(char* NameFile, char* FindString) {
	int sizeAns = 1;
	int* IntAns = (int*)malloc(sizeAns * sizeof(int));
	FILE* f;
	fopen_s(&f, NameFile, "r");
	char c;
	int i = 0;
	int num = 0;
	while (1) {
		fscanf_s(f, "%c", &c, 1);
		if (feof(f) != 0) {
			break;
		}
		if (c==FindString[i]) {
			if (i+1 == strlen(FindString)) {
				IntAns = realloc(IntAns, sizeAns * sizeof(int));
				IntAns[sizeAns - 1] = num - i;
				sizeAns++;
				i = 0;
			}
			i++;
		}
		num++;
	}
	fclose(f);
	IntArray Answer;
	Answer.Arr = IntAns;
	Answer.Size = sizeAns - 1;
	return Answer;
}