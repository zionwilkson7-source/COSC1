// Your First C++ Program

#ifdef __cplusplus
#include <iostream>
#else
#include <stdio.h>
#endif

int main() {
#ifdef __cplusplus
    std::cout << "Hello World!\n";
#else
    printf("Hello World!\n");
#endif
    return 0;
}