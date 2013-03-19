//
//  main.c
//  myMalloc
//
//  Created by Виталий Давыдов on 17.03.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.

//память представлена в виде блоков свободной памяти
//использую список этих блоков ищем по списку, пока не найдем
//блок достаточно большого размера

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

typedef struct block IWBlock;

struct block {
    struct {
        struct block *ptr; //next block, if exists
        unsigned size; //size of that block
    } s;
    
    double x; //alligment для "выравнивания" размера
};

static IWBlock base;
static IWBlock *freep = NULL;

#define MinBlockAmount 1024

void myFree(void *ap) {//put ap in free block
    IWBlock *bp, *p;
    
    bp = (IWBlock *)ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            break;
        }
    }
    
    if (bp + bp->s.size == p->s.ptr) {//to the upper neighbor
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else {
        bp->s.ptr = p->s.ptr;
    }
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else {
        p->s.ptr = bp;
    }
    
    freep = p;
}

static IWBlock *takeMemoryFromOS(unsigned nu) {
    char *cp;
    char *sbrk(int);
    IWBlock *up;
    
    if (nu < MinBlockAmount) {
        nu = MinBlockAmount;
    }
    cp = sbrk(nu * sizeof(IWBlock));
    if (cp == (char *) - 1) {//no memory
        return NULL;
    }
    up = (IWBlock *)cp;
    up->s.size = nu;
    
    myFree((void *)(up + 1));
    
    return freep;
}

void *myMalloc(unsigned nbytes) {
    IWBlock *p;
    IWBlock *prevP;
    IWBlock *takeMemoryFromOS(unsigned);
    unsigned numberUnits;
    
    numberUnits = (nbytes + sizeof(IWBlock) - 1)/sizeof(IWBlock) + 1;
    if ((prevP = freep) == NULL) {//list not exists
        base.s.ptr = freep = prevP = &base;
        base.s.size = 0;
    }
    
    for (p = prevP->s.ptr; ; prevP = p, p = p->s.ptr) {
        if (p->s.size >= numberUnits) { //enought size
            if (p->s.size == numberUnits) { //fit size
                prevP->s.ptr = p->s.ptr;
            }
            else {//cut tail
                p->s.size -= numberUnits;
                p += p->s.size;
                p->s.size = numberUnits;
            }
            freep = prevP;
            return (void *)(p+1);
        }
        if (p == freep) {//link to the list
            if ((p = takeMemoryFromOS(numberUnits)) == NULL) {
                return NULL; //no memory
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    
    return 0;
}

