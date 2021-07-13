#include<stdio.h>
#include<stdlib.h>
#include"StringFindFunctions.h"
#include"md5.h"
#include"sha256.h"
int main() {
	unsigned char* In = get_sha256("Boy");
	unsigned char* Un = get_md5("Boy");

	free(In);
	free(Un);
	return 0;
}