//
//  mainten.c
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
    char * jim = malloc(162);
    
    char * json = malloc(30);
    char * mal = malloc(30);
    char * roy = malloc(15);
    
    free(roy);
    roy = malloc(15);
    free(roy);
    return 0;
}