//
//  maineight.c
//  PA6
//
//  Created by Abhishek Saha on 5/2/14.
//  Copyright (c) 2014 Abhishek Saha. All rights reserved.
//

#include <stdio.h>
#include "mymalloc.h"


int main(int argc, const char * argv[])
{
    char * bool = malloc(95);
    char * jim = malloc(95);
    char * ronny = malloc(95);
    char * tim = malloc(95);
    free(tim);
    free(ronny);
    char * roy = malloc(15);
    return 0;
}