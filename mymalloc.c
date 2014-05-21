//
//  mymalloc.c
//  PA6
//
//  Created by Abhishek Saha on 4/25/14.
//  Copyright (c) 2014 Abhishek Saha. All rights reserved.
//
#define BLOCKSIZE  500
#include <stdio.h>
#include "mymalloc.h"

static int mid;

static MemEntryPtr lroot, rroot, sizeptr, lsiz, rsiz;

void * mymalloc(int size, char * file, int line ){
    
    static int initialized = 0;
    static int l_in = 0;
    static int total = 500;
    
    MemEntryPtr p, succ, pre;
    
    if(size<40){
        
        
        if (initialized==0 && l_in==0) {
            int i =0;
            for (i=0; i<500; i++) {
                BIGBLOCK[i] = '\0';
            }
            printf("BigBlock: %p\n", BIGBLOCK);
            lroot = (MemEntryPtr) BIGBLOCK;
            lroot->prev = lroot->succ = 0;
            lroot->size = BLOCKSIZE - (int)sizeof(MemEntry);
            mid = 500-sizeof(MemEntry);
            lroot->isFree = 1;
            initialized = 1;
            total = 500-sizeof(MemEntry);
            sizeptr = lroot;
            lsiz = lroot;
        }
        if (initialized==0 && l_in!=0) {
            lroot = (MemEntryPtr) BIGBLOCK;
            lroot->prev = lroot->succ = 0;
            int x = rsiz->size;
            lroot->size = x-sizeof(MemEntry);
            lroot->isFree = 1;
            initialized = 1;
            sizeptr->size -= sizeof(MemEntry);
            rsiz = sizeptr;
            sizeptr = lroot;
            lsiz = lroot;
        }
        
        p = lroot;
        
        
        p = (MemEntryPtr)findLoc(p, 0);
        
        while(1){
            if (p==0) {
                printf("Not enough memory to fill that request <100\n");
                printf("%p\n", sizeptr);
                return NULL;
            }
            if (p->size<size) {
                
                p = p->succ;
            }
            
            else if(p->size < (size + sizeof(MemEntry))){
                p->isFree = 0;
                if (p->succ == 0) {
                    sizeptr = p;
                    if (l_in!=0) {
                        rsiz->size = 0;
                    }
                }
                printf("%p SIZE LEFT: %d\n", p, sizeptr->size);
                p->a=126;
                return (char*) p + sizeof(MemEntry);
            }
            else{
                
                succ = (MemEntry*) ((char *) p + sizeof(MemEntry) + size);
                succ-> prev = p;
                succ-> succ = p->succ;
                
                if(p->succ!=0){
                    p->succ->prev = succ;
                }
                succ->size = p->size - (int)sizeof(MemEntry) - size;
                if (p->succ == 0) {
                    sizeptr = succ;
                    if(l_in!=0){
                        rsiz->size = sizeptr->size;
                    }
                    lsiz = sizeptr;
                }
                p-> succ = succ;
                
                succ->isFree = 1;
                p-> size = size;
                p->isFree = 0;
                
                
                printf("%p SIZE LEFT: %d\n", p, sizeptr->size);
                p->a=126;
                return (char *)p + sizeof(struct MemEntry);
            }
            p = (MemEntryPtr)findLoc(p, 0);
        }
    }
    else{
        if (initialized==0 && l_in==0) {
            int i =0;
            for (i=0; i<500; i++) {
                BIGBLOCK[i] = '\0';
            }
            rroot = (MemEntryPtr)&(BIGBLOCK[476]) ;
            rroot->prev = rroot->succ = 0;
            rroot->size = BLOCKSIZE - sizeof(MemEntry);
            rroot->isFree = 1;
            l_in = 1;
            sizeptr = rroot;
            rsiz = sizeptr;
            printf("%p\n", rroot);}
        if (l_in==0 && initialized!=0) {
            rroot = (MemEntryPtr)&(BIGBLOCK[476]) ;
            rroot->prev = rroot->succ = 0;
            int q = sizeptr->size;
            rroot->size = q-(int)sizeof(MemEntry);
            rroot->isFree = 1;
            l_in = 1;
            sizeptr->size -= (int)sizeof(MemEntry);
            lsiz = sizeptr;
            sizeptr = rroot;
            rsiz = sizeptr;
        }
        
        p = rroot;
        if (size>=(500-sizeof(MemEntry))) {
            printf("Entry is too big to be malloc'd ERROR\n");
            printf("%p SIZE LEFT: %d\n", p, sizeptr->size);
            return NULL;
        }
        
        
        
        
        p = (MemEntryPtr)findLoc(p, 1);
        
        while(1){
            if (p==0) {
                printf("Not enough memory to fill that request\n");
                printf("%p SIZE LEFT: %d\n", sizeptr, sizeptr->size);
                return NULL;
            }
            if (p->size<size) {
                
                p = p->prev;
            }
            
            else if(p->size < (size + sizeof(MemEntry))){
                p->isFree = 0;
                if (p->prev==0) {
                    sizeptr = 0;
                    if (initialized!=0) {
                        lsiz->size = 0;
                    }
                    rsiz = p;
                    printf("%p SIZE LEFT: %d\n", p, sizeptr->size);
                    p->a=127;
                    return (char*) p - (int)size;
                }
                printf("%p SIZE LEFT: %d\n", p, sizeptr->size);
                p->a=127;
                return (char*) p - (int)size;
            }
            else{
                pre = (MemEntry*) ((char *) p - sizeof(MemEntry) - size);
                pre-> succ = p;
                pre-> prev = p->prev;
                
                if(p->prev!=0){
                    p->prev->succ = pre;
                }
                pre->size = p->size - (int)sizeof(MemEntry) - size;
                if (p->prev==0) {
                    sizeptr = pre;
                    if (initialized!=0) {
                        lsiz->size = sizeptr->size;
                    }
                    
                    rsiz = sizeptr;
                }
                p-> prev = pre;
                
                pre->isFree = 1;
                p-> size = size;
                p->isFree = 0;
                
                
                printf("%p SIZE LEFT: %d\n", p, sizeptr->size);
                p->a=127;
                return (char *)p - (int)size;
            }
            p = (MemEntryPtr)findLoc(p, 0);
        }
        
        
    }
}


void * findLoc(void * p, int flag){
    
    if (flag==0) {
        
        
        MemEntryPtr pee  = (MemEntryPtr) p;
        for (; ; ) {
            if (pee==0) {
                break;
            }
            if (pee->isFree==0) {
                pee = pee->succ;
            }
            else{
                break;
            }
            
        }
        return pee;
    }
    else{
        MemEntryPtr pee  = (MemEntryPtr) p;
        for (; ; ) {
            if (pee==0) {
                break;
            }
            if (pee->isFree==0) {
                pee = pee->prev;
            }
            else{
                break;
            }
            
        }
        return pee;
    }
    
}



void myfree(void*p, char * file, int line){
    
    MemEntryPtr ptr;
    MemEntryPtr prev, succ;
    if (p==0) {
        printf("Unable to be free, try different value, File: %s Line: %d\n", file, line);
        return;
    }
    char * v = (char*)p;
    char * ay = BIGBLOCK;
    ptr = (MemEntryPtr) (v - sizeof(MemEntry));
    int flip = 0;
    if ((char*)ptr==ay) {
        ptr = rsiz->succ;
    }
    else{
    if (ptr->a==127) {
        ptr = ptr->succ;
        flip = 1;}
    else if(ptr->a==126){
        
    }
    else{
        printf("Unable to be free, try different value, File: %s Line: %d\n", file, line);
        return;}
    }
    
    if (ptr->isFree!=0) {
        
        printf("Unable to be free, already free, File: %s Line: %d\n", file, line);
        return;
    }
    char cc = *v;
    
    ptr->isFree = 1;
    if (flip==0) {
        
        MemEntryPtr temp = ptr->succ;
        MemEntryPtr tomp = ptr->prev;
        if((prev = ptr->prev) !=0 && prev->isFree){
            prev->size += sizeof(MemEntry) + ptr->size;
            prev->succ = ptr->succ;
            ptr->isFree = 1;
            if (ptr->succ!=0) {
                ptr->succ->prev = prev;
            }
        }
        else{
            ptr->isFree = 1;
            prev = ptr;
        }
        if ((succ = ptr->succ)!=0 && succ->isFree) {
            prev->size += sizeof(struct MemEntry) + succ-> size;
            prev->succ = succ->succ;
            if(succ->succ !=0)
                succ->succ->prev = prev;
            
        }
        
        if (succ==0) {
            sizeptr = prev;
            lsiz = sizeptr;
        }
        
    }
    
    else{
        if((succ = ptr->succ) !=0 && succ->isFree){
            succ->size += sizeof(MemEntry) + ptr->size;
            ptr->isFree = 1;
            succ->prev = ptr->prev;
            if (ptr->prev!=0) {
                ptr->prev->succ = succ;
            }
        }
        else{
            ptr->isFree = 1;
            succ = ptr;
        }
        if ((prev = ptr->prev)!=0 && prev->isFree) {
            succ->size += sizeof(struct MemEntry) + prev-> size;
            succ->prev = prev->prev;
            if(prev->prev !=0)
                prev->prev->succ = succ;
        }
        
        if (prev==0) {
            sizeptr = succ;
            rsiz = sizeptr;
        }
        
        
    }
}

