#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"

#define MAX(x,y) (x > y)? x:y

void LstCtor(List *List, size_t size, size_t len){
    *List = {
        .buffer = (Cell*) calloc (MAX(DefaultSize, len), sizeof(Cell)),
        .values = calloc (MAX(DefaultSize, len), size),
        .elsize = size,
        .free = 1,
        .head = 0,
        .tail = 0,
        .capasity = MAX(DefaultSize, len),
    };

    assert(List->buffer != NULL);

    for (size_t i = 0; i < List->capasity; i++){
        List->buffer[i].index = [i];
    }

    for (size_t i = 1; i < List->capasity; i++){

        if (i < List->capasity - 1)
            List->buffer[i].next = i + 1;
        printf("%d  %d ", List->buffer[i].next, List->capasity);
        List->buffer[i].prev = - 1;
        printf("%d\n", i);
    }

    List->buffer[0].next = List->head;
    List->buffer[0].next = List->tail;
    assert(List->buffer != NULL);
}

#undef MAX

void LstDtor(List *List){
    assert(List->buffer != NULL);
    free(List->buffer);
    List->capasity = 0;
    List->elsize = 0;
}

void AddAfterIndex(List *List, void *value, size_t index){

    size_t this_elem = List->free;

    List->free = List->buffer[List->free].next;

    if (List->buffer[List->free].next == 0){
        //resize!!
        ;
    }
    printf("%d\n", List->free);
    memcpy(List->values + List->elsize*this_elem, value, List->elsize);

    List->buffer[this_elem].next = List->buffer[index].next;
    List->buffer[this_elem].prev = index;
    List->buffer[List->buffer[index].next].prev = this_elem;
    List->buffer[index].next = this_elem;
}

size_t Search(List *List, void* value){
    size_t start = 0;
}

void Dump(List *List){
    for (size_t i = 0; i < List->capasity; i++){
        printf("Index: %d  ", List->buffer[i].index);
        if (List->buffer[i].prev == -1){
            printf("For free (Empty)[%lld]{%lld}\n", List->buffer[i].next, List->buffer[i].prev);
        }
        else{
            printf("For data (%d)[%lld]{%lld}\n", *((int*) ((char *)List->values + i*List->elsize)), List->buffer[i].next, List->buffer[i].prev);
        }
    }
}
