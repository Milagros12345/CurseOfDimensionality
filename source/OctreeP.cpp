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
    Point operator-(const int n)const{return Point(x-n,y-n,z-n);}
    Point operator*(const Point&r)const{return Point(x*r.x,y*r.y,z*r.z);}
    Point operator/( const Point&r)const{return Point(x/r.x,y/r.y,z/r.z);}
    Point operator*(float r){return Point(x*r,y*r,z*r);}
    Point operator/(float r){return Point(x/r,y/r,z/r);}

    friend ostream& operator<<(ostream& stream,Point &o){
        stream<<"x: "<<o.x<<"y: "<<o.y<<"z: "<<o.z;
        return stream;
    }
    friend ostream& operator<<(ostream& stream, const Point&o){
        stream<<"x:"<<o.x<<" y:"<<o.y<<" z:"<<o.z;
        return stream;
    }
    Point operator+=( Point &r){
        x+=r.x;
        y+=r.y;
        z+=r.z;return Point(x,y,z);}

    Point(int n):x(n),y(n),z(n){}
    bool operator==(Point &r){ return x==r.x&&y==r.y&&z==r.z; }
    bool operator==(float n){return x==n&&y==n&&z==n;}
    Point operator=(const Point &r){ return Point(x=r.x,y=r.y,z=r.z); }
    bool operator!=(Point &r){return x!=r.x &&y!=r.y &&z!=r.z;}
    bool operator!=(float r){return x!=r &&y!=r &&z!=r;}


};

class Octree{
public:
    Point base;
    Point alto;
    Octree *padre;
    Octree *hijo[8];
    Point valor;

    Octree(Point a,Point b):base(a),alto(b),padre(0),valor(0){
        for(int i=0;i<8;i++){
            hijo[i]=0;
        }
    }
    Octree(float _x,float _y,float _z):valor(0),padre(0){
        Point m(_x*.5f,_y*.5f,_z*.5f);
        base=m;
        alto=m;
        for(int i=0;i<8;i++)
            hijo[i]=0;
    }
    Octree():padre(0),valor(0){
        for(int i=0;i<8;i++)
            hijo[i]=0;
    }
    ~Octree(){
        for(int i=0;i<8;i++)
            delete hijo[i];
    }
    bool limites( Point &p){
        return((p.x>alto.x ||p.x<base.x) ||(p.y>alto.y ||p.y<base.y) || (p.z>alto.z || p.z<base.z));
    }
    void insert(Point &p){
        cout<<base<<","<<alto<<","<<"Point: "<<p<<endl;
        if(this->hijo[0]==nullptr){
            //find(p);
            if(valor==0){
                valor=p;return;
            }
            else if(p.x==this->valor.x && p.y==this->valor.y && p.z==this->valor.z){
                cout<<"ya existe este Punto!!!!"<<endl;return;
            }
            else{
                for(int i=0;i<8;i++){
                    Point p_n=this->base;
                    p_n.x+=this->alto.x*(i&1 ? 0.5f : -0.5f);
                    p_n.y+=this->alto.y*(i&2 ? 0.5f : -0.5f);
                    p_n.z+=this->alto.z*(i&4 ? 0.5f : -0.5f);
                    hijo[i]=new Octree(p_n,this->alto*0.5f);
                    hijo[i]->padre=this;

                }
                Point aux=this->valor;
                valor=0;
                this->insert(aux);
                this->insert(p);
            }
        }
        else{
            this->hijo[get_posicion_hijo(p)]->insert(p);
        }

    }
    void radio(Point centro, float r,vector<Point*>&Ps){
        Point p_min=centro-r;
        Point p_max=centro+r;
        if(hijo[0]==nullptr){
            if(valor!=0){
                Point *p= &valor;
                if(p->x>p_max.x || p->y>p_max.y || p->z>p_max.z)return;
                if(p->x<p_min.x || p->y<p_min.y || p->z<p_min.z)return;
                Ps.push_back(p);//dua valor
            }
        }else{
            for(int i=0;i<8;i++){
                Point p_max1=hijo[i]->base+hijo[i]->alto;
                Point p_min1=hijo[i]->base-hijo[i]->alto;

                if(p_max1.x<p_min.x ||p_max1.y<p_min.y || p_max1.z<p_min.z)continue;
                if(p_min1.x>p_max.x ||p_min1.y>p_max.y || p_min1.z>p_max.z)continue;
                hijo[i]->radio(centro,r,Ps);
            }
        }

    }
    bool find(Point pn){//solo indica si encontro o no
        if(this->hijo[0]==nullptr){
            if(this->valor!=0){
                if(pn.x==this->valor.x&&pn.y==this->valor.y && pn.z==this->valor.z)
                    return true;
                return false;
            }
        }
        else{
            hijo[get_posicion_hijo(pn)]->find(pn);
        }
    }
    int get_posicion_hijo(const Point &p){
        int pos=0;
        if(p.x>=this->base.x)pos+=1;
        if(p.y>=this->base.y)pos+=2;
        if(p.z>=this->base.z)pos+=4;
        return pos;
    }
    void imprimir_p( vector<Point*>p){cout<<"imprimiendo"<<endl;
        for(int i=0;i<p.size();i++){
            cout<<(*p[i])<<endl;
        }
    }
};

int main()
{    vector<Point*>punto;
     Point base(1,0,0);
     Point fin(5,4,4);
     Octree t(base,fin);
     Point a(2,1,2);
     Point b(2,2,1);
     Point c(2,1,4);
     Point d(2,3,3);
     Point e(3,4,2);
     Point f(3,1,4);
     Point g(1,1,3);
     Point h(2,1,3);
     Point i(3,2,2);

     t.insert(h);
    t.insert(b);
    t.insert(c);
    t.insert(d);
    t.insert(e);
    t.insert(f);
    t.insert(g);
    t.insert(h);
    t.insert(i);
    t.radio(fin-base,3,punto);
    t.imprimir_p(punto);
    cout<<t.limites(i)<<endl;
    return 0;
}
