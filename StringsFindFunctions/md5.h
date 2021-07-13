#ifndef MD5_H
#define MD5_H
unsigned int F(unsigned int X, unsigned int Y, unsigned int Z);
unsigned int G(unsigned int X, unsigned int Y, unsigned int Z);
unsigned int H(unsigned int X, unsigned int Y, unsigned int Z);
unsigned int I(unsigned int X, unsigned int Y, unsigned int Z);
unsigned int rotate_left(unsigned int value, int shift);
unsigned char* get_md5(char* in);
unsigned char* get_md5_len(char* in, int len);
#endif 