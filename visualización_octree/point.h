#ifndef POINT_H
#define POINT_H
#include <iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include <sstream>
#include<string>
using namespace std;
class Point{
public:
    float x,y,z;
    Point(){};
    Point(const Point &o):x(o.x),y(o.y),z(o.z){}
    Point(float _x,float _y, float _z):x(_x),y(_y),z(_z){}
    Point operator+( const Point&r)const {return Point(x+r.x,y+r.y,z+r.z); }
    Point operator+(const int n)const{return Point(x+n,y+n,z+n);}
    Point operator-(const Point&r)const{return Point(x-r.x,y-r.y,z-r.z);}
    Point operator/( const Point&r)const{return Point(x/r.x,y/r.y,z/r.z);}
    Point operator/(float r){return Point(x/r,y/r,z/r);}

    friend ostream& operator<<(ostream& stream,Point &o){
        stream<<"x: "<<o.x<<"y: "<<o.y<<"z: "<<o.z;
        return stream;
    }
    Point(int n):x(n),y(n),z(n){}
    bool operator==(Point &r){ return x==r.x&&y==r.y&&z==r.z; }
    bool operator==(float n){return x==n&&y==n&&z==n;}
    Point operator=(const Point &r){ return Point(x=r.x,y=r.y,z=r.z); }
};

#endif // POINT_H
