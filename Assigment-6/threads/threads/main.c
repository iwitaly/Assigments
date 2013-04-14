//
//  main.c
//  threads
//
//  Created by Виталий Давыдов on 14.04.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

#define eps 0.000001
#define defaultNumberOfThreads 1

typedef struct set integrateSet;

float f(float x) {
    return x;
}

struct set{
    float(*f)(float);
    float a;
    float b;
    float result;
};

float integrate(float(*f)(float), float a, float b) {
    float integrateSumm = 0;
    float x;
    
    for (x = a + eps; x <= b; x += eps) {
        integrateSumm += eps * f(x);
    }
    
    return integrateSumm;
}

void *integrateHelperForThreads(void *seet) {
    integrateSet *newSet = (integrateSet *)seet;
        
    float(*function)(float) = newSet->f;
    float a = newSet->a;
    float b = newSet->b;
    
    newSet->result = integrate(function, a, b);
    
    return NULL;
}
int main(int argc, const char * argv[])
{
    float a = 0.0;
    float b = 2.0;
    float totalResult = 0;
    
    int numberOfThreads = defaultNumberOfThreads; //except main
    printf("please, input number of threads to start computation\n");
    scanf("%d", &numberOfThreads);
    
    if (numberOfThreads < 1) {
        numberOfThreads = defaultNumberOfThreads;
    }
    
    integrateSet sets[numberOfThreads];
    pthread_t threads[numberOfThreads];
    
    int i;
    float step = (b-a) / numberOfThreads;
    
    //init array of sets
    for (i = 0; i < numberOfThreads; ++i) {
        integrateSet s;
        s.a = a + i*step;
        s.b = s.a + step;
        s.f = f;
        s.result = 0;
        
        sets[i] = s;
    }
    
    //turn on all threads
    for (i = 0; i < numberOfThreads; ++i) {
        pthread_create(&threads[i], NULL, integrateHelperForThreads, &sets[i]);
    }
    
    for (i = 0; i < numberOfThreads; ++i) {
        pthread_join(threads[i], NULL);
        
        totalResult += sets[i].result;
    }
    
    printf("Comtutation have been complited with %d threads. Integral is: %f", numberOfThreads, totalResult);
    
    return 0;
}

