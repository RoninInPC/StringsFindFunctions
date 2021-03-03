#include<stdio.h>
#include"StringFindFunctions.h"
int main() {
	IntArray Ans1 = FindStringsNonHash("input.txt", "abcd");
	for (int i = 0; i < Ans1.Size; i++) {
		printf("%d\n", Ans1.Arr[i]);
	}
	return 0;
}