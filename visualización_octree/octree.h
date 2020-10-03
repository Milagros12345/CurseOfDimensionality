#ifndef OCTREE_H
#define OCTREE_H
#include "point.h"
#include "nodo.h"
#include <iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include <sstream>
#include<string>
using namespace std;

class octree{
public:

    nodo *root;
    octree(){}
    octree(Point lim1,Point lim2){
        root=new nodo(lim1,lim2);//creamos el nodo
    }
    bool limites( Point p,nodo *ptr){
        return((p.x>ptr->alto.x ||p.x<ptr->base.x) ||(p.y>ptr->alto.y ||p.y<ptr->base.y) || (p.z>ptr->alto.z || p.z<ptr->base.z));
    }

    int obtenerpos(Point p1,Point centro){
        if(p1.x<=centro.x && p1.y<=centro.y && p1.z<=centro.z)return 0;
        if(p1.x>centro.x && p1.y<=centro.y && p1.z<=centro.z)return 1;
        if(p1.x<=centro.x && p1.y<=centro.y && p1.z>centro.z)return 2;
        if(p1.x>centro.x && p1.y<=centro.y && p1.z>centro.z)return 3;
        if(p1.x<=centro.x && p1.y>centro.y && p1.z<=centro.z)return 4;
        if(p1.x>centro.x && p1.y>centro.y && p1.z<=centro.z)return 5;
        if(p1.x<=centro.x && p1.y>centro.y && p1.z>centro.z)return 6;
        if(p1.x>centro.x && p1.y>centro.y && p1.z>centro.z)return 7;
    }

    void radio(nodo *ptr,Point &p){
        p=(ptr->base+ptr->alto)/2;
    }
    void Cnodo(int pos,nodo *ptr,Point &medio,Point &i,Point &a){
        if(pos==0){i=ptr->base;a=medio;}
        else if(pos==1){i.x=medio.x;i.y=ptr->base.y;i.z=ptr->base.z;a.x=ptr->alto.x;a.y=medio.y;a.z=medio.z;}
        else if(pos==2){i.x=ptr->base.x;i.y=ptr->base.y;i.z=medio.z;a.x=medio.x;a.y=medio.y;a.z=ptr->alto.z;}
        else if(pos==3){i.x=medio.x;i.y=ptr->base.y;i.z=medio.z;a.x=ptr->alto.x;a.y=medio.y;a.z=ptr->alto.z;}
        else if(pos==4){i.x=ptr->base.x;i.y=medio.y;i.z=ptr->base.z;a.x=medio.x;a.y=ptr->alto.y;i.z=medio.z;}
        else if(pos==5){i.x=medio.x;i.y=medio.y;i.z=ptr->base.z;a.x=ptr->alto.x;a.y=ptr->alto.y;a.z=medio.z;}
        else if(pos==6){i.x=ptr->base.x;i.y=medio.y;i.z=medio.z;a.x=medio.x;a.y=ptr->alto.y;a.z=ptr->alto.z;}
        else if(pos==7){i=medio;a=ptr->alto;}
    }
    bool find(Point p,nodo *&ptr){
        if(limites(p,ptr))return false;
        if(ptr->Nump<=ptr->Nump2){int tam=ptr->points.size();
            for(int i=0;i<tam;i++){
                if(ptr->points[i]==p)return true;
            }
        return false;
        }
        else{
            Point medio;
            radio(ptr,medio);
            int pos=obtenerpos(p,medio);
            if(ptr->hijo[pos]==0 || ptr->hijo[pos]->color==0 )return false;
            find(p,ptr->hijo[pos]);
        }
    }

    void insert(nodo *&ptr,Point &p,int c){
        cout<<"limite inferior"<<ptr->base<<"   limite superior"<<ptr->alto<<"   Punto"<<p<<endl;
        if(limites(p,ptr) || find(p,ptr)){cout<<"fuera de limite "<<endl;return;}
        if(ptr->Nump2>=ptr->Nump){vector<Point>aux;
            for(int i=0;i<8;i++){
                if(ptr->hijo[i]==0)continue;
                int tam1=ptr->hijo[i]->points.size();
                for(int x=0;x<tam1;x++){
                    aux.push_back(ptr->hijo[i]->points[x]);
                }ptr->hijo[i]=nullptr;
            }int tam2=ptr->points.size();
            for(int i=0;i<tam2;i++){
                aux.push_back(ptr->points[i]);
            }aux.push_back(p);ptr->Nump2++;
            ptr->points=aux;
        }
        else{
            if(c!=0)ptr->Nump2++;Point medio;
            radio(ptr,medio);
            int pos=obtenerpos(p,medio);
            if(ptr->hijo[pos]->color==0 || ptr->hijo[pos]==0){cout<<"ente"<<endl;
                Point ini,fin;
                Cnodo(pos,ptr,medio,ini,fin);
                ptr->hijo[pos]=new nodo(ini,fin);
            }insert(ptr->hijo[pos],p,c);
        }

    }
    void insertP(octree oc,vector<vector<float>>points){
        int tam=points.size();
        for(int i=0;i<tam;i++){
            Point p(points[i][0],points[i][1],points[i][2]);
            nodo *ptr=oc.root;
            oc.insert(ptr,p,1);
        }
    }
};

#endif // OCTREE_H
