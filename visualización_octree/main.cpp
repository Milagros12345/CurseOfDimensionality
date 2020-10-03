#include "mainwindow.h"
#include "octree.h"
#include "point.h"
#include <QApplication>
#include <iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include <sstream>
#include<string>
using namespace std;
void ObtenerPoints(string dir,vector<vector<float>>&point){
    ifstream archivo(dir);
    string s;vector<float>peque;
    float x,y,z;
    if(archivo.fail()){
        cout<<"fallo..."<<endl;
    }
    while(!archivo.eof()){
        archivo>>s;
        if(s!="v")break;
        archivo>>x>>y>>z;
        //cout<<"x:"<<x<<" y:"<<y<<" z:"<<z<<endl;//x*=100;y*=100;z*=100;
        peque.push_back(x);
        peque.push_back(y);
        peque.push_back(z);
//        for(int i=0;i<peque.size();i++)
//            cout<<peque[i]<<endl;
        point.push_back(peque);
        peque.clear();
    }
}
void print(vector<vector<float>>&p){
    int t=p.size(),t2;cout<<t<<endl;
    for(int i=0;i<t;i++){
        t2=p[i].size();
        for(int j=0;j<t2;j++)
            cout<<"point"<<p[i][j]<<" ";
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    string dir="D:/sexto_semestre/EDA/tarea3/carro.obj"; vector<vector<float>>points;
    Point p11(-1.0,-1.0,-1.0),p12(10.0,10.0,10.0);
    //nodo *p1=oc.root;
    octree oc(p11,p12);
    ObtenerPoints(dir,points);
    w.oc->insertP(oc,points);
    int t=points.size();
    for(int i=0;i<t;i++){
        w.W.push_back(Point(points[i][0],points[i][1],points[i][2]));
    }
    w.paintGL();
    w.resize(1500,1500);
    w.show();
    return a.exec();
}
