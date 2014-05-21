//
//  mymalloc.h
//  PA6
//
//  Created by Abhishek Saha on 4/25/14.
//  Copyright (c) 2014 Abhishek Saha. All rights reserved.
//


#ifndef PA6_mymalloc_h
#define PA6_mymalloc_h


#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

static char BIGBLOCK[500];

struct MemEntry{
    char a; 
    int isFree :1;
    int  size;
    struct MemEntry * prev;
    struct MemEntry * succ;
    
    
};

typedef struct MemEntry MemEntry;
typedef struct MemEntry * MemEntryPtr;

void * mymalloc(int x, char * file, int line);
void myfree(void * p, char * file, int line);

void * findLoc(void* p, int flag);

#endif
