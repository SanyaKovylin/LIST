#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int main(void){

    List lst = {};
    int elem = 10;
    LstCtor(&lst, sizeof(int), 16);
    Dump(&lst);
    printf("start");
    AddAfterIndex(&lst, &elem, 0);
    Dump(&lst);
    while (elem > 0){
    AddAfterIndex(&lst, &elem, 1);
    elem--;
    }
    Dump(&lst);
    return 0;
}
