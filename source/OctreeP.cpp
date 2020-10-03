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
    bool operator!=(Point &r){return x!=r.x &&y!=r.y &&z!=r.z;}
    bool operator==(Point &r){ return x==r.x&&y==r.y&&z==r.z; }
    bool operator==(float n){return x==n&&y==n&&z==n;}
    Point operator=(const Point &r){ return Point(x=r.x,y=r.y,z=r.z); }
};
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
class octree{
public:
    nodo*root;
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
        if(ptr->Nump<=ptr->Nump2){
            for(int i=0;i<ptr->points.size();i++){
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
        if(limites(p,ptr) || find(p,ptr)){cout<<"fuera de limite o ya existe "<<endl;return;}
        if(ptr->Nump2>=ptr->Nump){vector<Point>aux;
            for(int i=0;i<8;i++){
                if(ptr->hijo[i]==0)continue;
                for(int x=0;x<ptr->hijo[i]->points.size();x++){
                    aux.push_back(ptr->hijo[i]->points[x]);
                }ptr->hijo[i]=nullptr;
            }for(int i=0;i<ptr->points.size();i++){
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
        for(int i=0;i<points.size();i++){
            Point p(points[i][0],points[i][1],points[i][2]);
            nodo *ptr=oc.root;
            oc.insert(ptr,p,1);
        }
    }
    void remove(Point p,nodo* ptr){
        if(limites(p,ptr) || !find(p,ptr)){cout<<"fuera de limite o no existe "<<endl;return;}
        if(ptr->Nump2>=ptr->Nump){
            auto i=ptr->points.begin();
            while(*i!=p)++i;
            ptr->points.erase(i);
            if(ptr->points.size()==0)ptr->color=0;
        }else{
            Point *p1,medio;
            radio(ptr,medio);
            int pos=obtenerpos(p,medio);ptr->Nump2--;
            if(ptr->hijo[pos] == 0 || ptr->hijo[pos]->color == 0) return;
            remove(p,ptr->hijo[pos]);
        }
    }
    void imprimir(nodo*n){
        for(int i=0;i<n->points.size();i++){
            cout<<n->points[i]<<endl;
        }
    }
};
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
        cout<<"x:"<<x<<" y:"<<y<<" z:"<<z<<endl;
        peque.push_back(x);
        peque.push_back(y);
        peque.push_back(z);
//        for(int i=0;i<peque.size();i++)
//            cout<<peque[i]<<endl;
        point.push_back(peque);
        peque.clear();
    }
}
void print(vector<vector<float>>p){
    for(int i=0;i<p.size();i++){
        for(int j=0;j<p[i].size();j++)
            cout<<"point"<<p[i][j]<<" ";
            cout<<endl;
    }
}
int main()
{
    string dir="D:/sexto_semestre/EDA/code/prueba.obj"; vector<vector<float>>points;
    Point a(-1,-1,-1),b(10,10,10),c(2,3,2),d(5,5,2);
    octree oc(a,b);
    nodo *p1=oc.root;

    ObtenerPoints(dir,points);
    oc.insertP(oc,points);
    print(points);
    cout<<oc.find(d,p1)<<"encontro";
    oc.imprimir(p1);
    oc.remove(d,p1);
    //cout<<oc.find(d,p1)<<"encontro";

    return 0;
}
