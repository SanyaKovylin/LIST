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
        .capasity = MAX(DefaultSize, len),
    };

    assert(List->buffer != NULL);

    for (size_t i = 0; i < List->capasity; i++){
        List->buffer[i].index = i;
    }

    for (size_t i = 1; i < List->capasity; i++){

        if (i < List->capasity - 1)
            List->buffer[i].next = i + 1;

        List->buffer[i].prev = - 1;

    }
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

    memcpy((char*)List->values + List->elsize*this_elem, value, List->elsize);

    List->buffer[this_elem].next = List->buffer[index].next;
    List->buffer[this_elem].prev = index;
    List->buffer[List->buffer[index].next].prev = this_elem;
    List->buffer[index].next = this_elem;
}
#pragma GCC diagnostic ignored "-Wsign-compare"
int DeleteByIndex(List *List, size_t index){

    size_t this_elem = index;

    while (List->buffer[index].prev == -1 || List->buffer[0].next == 0){
        printf("DEBIL unable to delete - BAXTEPWA IS ANGRY");
        return 1;
    }

    memset((char*)List->values + List->elsize*this_elem, '\0', List->elsize);

    List->buffer[List->buffer[this_elem].next].prev = List->buffer[this_elem].prev;
    List->buffer[List->buffer[this_elem].prev].next = List->buffer[this_elem].next;

    List->buffer[this_elem].next = List->free;
    List->free = this_elem;
    List->buffer[this_elem].prev = -1;
    return 0;
}

size_t Search(List *List, void* value){
    size_t index_here = 0;
    bool c = false;
    while ((c = memcmp(((char*)List->values + index_here*List->elsize), value, List->elsize))){

        index_here = List->buffer[List->buffer[index_here].next].index;

        if (index_here == 0){
            break;
        }
    }
    if (c){
        return 0;
    }
    return index_here;
}

void AddAfterHead(List *List, void *value){
    AddAfterIndex(List, value, List->buffer[0].prev);
}

void AddAfterTail(List *List, void *value){
    AddAfterIndex(List, value, List->buffer[0].next);
}

void DeleteTail(List *List){
    DeleteByIndex(List, List->buffer[0].next);
}

void DeleteHead(List *List){
    DeleteByIndex(List, List->buffer[0].prev);
}

void Dump(List *List){
    for (size_t i = 0; i < List->capasity; i++){
        printf("Index: %lld  ", List->buffer[i].index);
        if (List->buffer[i].prev == -1){
            printf("For free (Empty)[%lld]{%lld}\n", List->buffer[i].next, List->buffer[i].prev);
        }
        else{
            printf("For data (%d)[%lld]{%lld}\n", *((int*) ((char *)List->values + i*List->elsize)), List->buffer[i].next, List->buffer[i].prev);
        }
    }

    FILE* out = fopen("e.txt", "w");

    fprintf(out, "digraph Dump \n{\nrankdir=LR;\nnode[shape=Mrecord];\n");
    for (size_t i = 0; i < List->capasity; i++){
       fprintf(out, "Node%lld[label = \"<i> Index: %lld| <v> Value: %d | <n> next: %lld | <p> prev: %lld\"];\n",
               i, List->buffer[i].index,*((int*) ((char *)List->values + i*List->elsize)),
               List->buffer[i].next, List->buffer[i].prev);
//        fprintf(out, "Node%lld[label =< <table>\n"
// "  <tr>\n"
// "    <td>Index</td>\n"
// "    <td>%lld</td>\n"
// "  </tr>\n"
// "  <tr>\n"
// "    <td>Data</td>\n"
// "    <td>%d</td>\n"
// "  </tr>\n"
// "  <tr>\n"
// "    <td>Next</td>\n"
// "    <td>%lld</td>\n"
// "  </tr>\n"
// "  <tr>\n"
// "    <td>Prev</td>\n"
// "    <td>%lld</td>\n"
// "  </tr>\n"
// "</table>>];\n",
//                i, List->buffer[i].index,*((int*) ((char *)List->values + i*List->elsize)),
//                List->buffer[i].next, List->buffer[i].prev);
    }

    for (size_t i = 0; i < List->capasity; i++){
       if (List->buffer[i].prev != -1){
           fprintf(out, "Node%lld:p -> Node%lld:v[color = red];\n"
                        "Node%lld:n -> Node%lld:v[color = green];\n",
            i, List->buffer[i].prev, i, List->buffer[i].next);
       }
       else{
           fprintf(out, "Node%lld:n -> Node%lld:v[color = blue];\n",
            i, List->buffer[i].next);
       }
    }

    fprintf(out, "}\n");
}
#pragma GCC diagnostic error "-Wsign-compare"
