#include <stdio.h>
#include <stdlib.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

int main( int argc, char ** argv )
{
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("a: " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(a) );
    printf("b: " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(b) );
    printf("a && b = %d\n", a && b );
    printf("a  & b = %d\n", a  & b );
    printf("a || b = %d\n", a || b );
    printf("a  | b = %d\n", a  | b );
//    printf("a ^^ b = %d\n", a ^^ b );
    printf("a  ^ b = %d\n", a  ^ b );
    return 0;
}
