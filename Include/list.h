#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct Cell {
    size_t index;
    size_t next;
    size_t prev;
} listcell;

struct List {
    struct Cell *buffer;
    void* values;
    size_t elsize;
    size_t free;
    size_t head;
    size_t tail;
    size_t capasity;
};

const int DefaultSize = 8;

void LstCtor(List *List, size_t size, size_t len);
void LstDtor(List *List);
void Dump(List *List);
void AddAfterIndex(List *List, void *value, size_t index);

#endif //LIST_H_INCLUDED
