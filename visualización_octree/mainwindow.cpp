#include "mainwindow.h"
#include <QtMath>
#include <cmath>
#include <vector>
#include "point.h"
#include "octree.h"
#include "nodo.h"

using namespace std;
MainWindow::MainWindow(QGLWidget *parent){
    setSurfaceType(QWindow::OpenGLSurface);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);
    setFormat(format);
    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);
    openGLFunctions = context->functions();
    Point min(-1.0,-1.0,-1.0);
    Point max(10.0,10.0,10.0);
    oc=new octree(min,max);
    circulo=0.0;graf=0.0;
    angulo=0.8;
    zoomScale=0.30;
    pres=false;
    radio=0.5;
}
MainWindow::~MainWindow() {
    delete oc;
}
void MainWindow::mouseMoveEvent(QMouseEvent *ev) {
        circulo.x = float(ev->x())/float(this->width())-0.5;
        circulo.y = float(ev->y())/float(this->height())-0.5;
        circulo.x *= 2;
        circulo.y *= -2;

        graf.x = circulo.x ;
        graf.y = circulo.y ;
        update();
}
void MainWindow::wheelEvent(QWheelEvent *ev) {
    QPoint numDegrees = ev->angleDelta();
    if (numDegrees.y() < 0)
        zoomScale = zoomScale/1.1;
    if (numDegrees.y() > 0)
        zoomScale = zoomScale*1.1;
    update();
}
void MainWindow::pushPoint(octree **p)
{
    if((*p)->root){cout<<"dibuja";
        node=(*p)->root;
        int t=node->points.size();
        for(int i=0;i<t;i++){
            W.push_back(node->points[i]);
        }
    }
}
void MainWindow::keyPressEvent(QKeyEvent *ev){
    if(ev->key() == 80){
        W.clear();
        update();
    }
}
void MainWindow::mousePressEvent(QMouseEvent *ev) {
    float x_p = float(ev->x())/float(this->width())-0.5;
    float y_p = float(ev->y())/float(this->height())-0.5;
    float z_p=0.0;Point p(x_p*2,y_p*-2,z_p*2);
    C.push_back(p);
    oc->insert(node,p,1);
    update();
}
void MainWindow::initializeGL() {
    resizeGL(this->width(),this->height());
}
void MainWindow::resizeGL(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,w,h);
   qreal aspectratio = qreal(w)/qreal(h);
   glOrtho(-1* aspectratio,1*aspectratio,-1,1,1,-1);
}
void MainWindow::paintGL() {
    glClearColor(255, 25, 255, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glScaled(zoomScale, zoomScale, zoomScale);
    glPointSize(9);
    gluPerspective(45.0,1.0,1.0,100.0);
    glTranslatef(0,0,-6);
    glRotatef(circulo.x*100,0,1,0);
    glRotatef(circulo.y*100,1,0,0);
    pres= false;
    glBegin(GL_POINTS);
    glColor3d(100,0,0);
    for(int i=0;i<int(W.size());i++){
        //qDebug() <<pointsW[i].first<< "paint " << pointsW[i].second<< "size" <<pointsW.size() ;
        glVertex3d(W[i].x,W[i].y,W[i].z);
    }
    glEnd();
    glFlush();
}
void MainWindow::resizeEvent(QResizeEvent *event) {
    resizeGL(this->width(),this->height());
    this->update();
}
void MainWindow::paintEvent(QPaintEvent *event) {
    paintGL();

}


