#include<stdio.h>
#include<stdlib.h>
#include"StringFindFunctions.h"
#include"md5.h"
#include"sha256.h"
int main() {
	unsigned char* Un = get_md5("Boy");
	unsigned char* In = get_sha256("Boy");
	return 0;
}