#include <stdio.h>
#include <stdlib.h>

/* =============================== Data structures
 * ============================== */

#define TFOBJ_TYPE_INT 0
#define TFOBJ_TYPE_STR 1
#define TFOBJ_TYPE_BOOL 2
#define TFOBJ_TYPE_LIST 3
#define TFOBJ_TYPE_SYMBOL 4

typedef struct tfobj {
    int refcount;
    int type; // int, string, bool, etc..
              // TFOBJ_TYPE_*
    union {
        int i;
        struct {
            char *ptr;
            size_t len;
        } str;
        struct {
            struct tfobj **ele;
            size_t len;
        } list;
    };
} tfobj;

typedef struct tfparser {
    char *prg; // The program to compile into a list
    char *p;   // Next token to parse
} tfparser;

typedef struct tfctx {
    tfobj *stack;
} tfctx;

/* =============================== Allocation Wrappers
 * ============================ */
void *xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Out of memory allocation %zu bytes \n", size);
        exit(1);
    }
    return ptr;
}

/*
 * =============================== Object Related Functions
=====================
 * The following functions allocate Toy Forth Objects of different types.
Allocate and initialize a new Toy Forth Object*/
tfobj *createObject(int type) {
    tfobj *o = xmalloc(sizeof(tfobj));
    o->type = type;
    o->refcount = 1;
    return o;
}

tfobj *createStringObject(char *s, size_t len) {
    tfobj *o = createObject(TFOBJ_TYPE_STR);
    o->str.ptr = s;
    o->str.len = len;
    return o;
}

tfobj *createIntObject(int i) {
    tfobj *o = createObject(TFOBJ_TYPE_INT);
    o->i = i;
    return o;
}

tfobj *createBoolObject(int i) {
    tfobj *o = createObject(TFOBJ_TYPE_BOOL);
    o->i = i;
    return o;
}

tfobj *createListObject(void) {
    tfobj *o = createObject(TFOBJ_TYPE_LIST);
    o->list.ele = NULL;
    o->list.len = 0;
    return o;
}

/* ======================================= Main
 * ================================== */
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);

    printf("Source file size: %ld\n", file_size);

    fclose(fp);

    // tfobj *prg = compile(prgtext);
    // exec(prgtext);
    return 0;
}
