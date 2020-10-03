#ifndef NODO_H
#define NODO_H
#include "point.h"

class nodo{
public:
    nodo* hijo[8];
    Point base,alto;
    vector<Point>points;int color;
    long long Nump,Nump2;
    nodo(Point a,Point b){
        base=a;alto=b;color=1;//blanco
        Nump=(alto.x-base.x)*(alto.y-base.y)*(alto.y-base.y)*(0.5);
        if(Nump<1)Nump=1;
        for(int i=0;i<8;i++){
            hijo[i]=0;
        }
    }
};

#endif // NODO_H
