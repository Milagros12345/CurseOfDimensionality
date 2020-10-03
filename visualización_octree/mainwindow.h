#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/glu.h>
#include <QMouseEvent>
#include <vector>

#include "point.h"
#include "octree.h"
#include "nodo.h"
using namespace std;
class MainWindow : public QOpenGLWindow {
    Q_OBJECT

public:
    MainWindow(QGLWidget* parent=0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void keyPressEvent(QKeyEvent *);
    virtual void paintGL();
    bool pointIN(Point a);
    float zoomScale;
    octree *oc;
    vector<Point> W;
    vector<Point> C;
    nodo *node;
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void pushPoint(octree **p);
    Point circulo,graf;
    float angulo;
    bool pres;
    float radio;
private:
     QOpenGLContext *context;
     QOpenGLFunctions *openGLFunctions;
};

#endif // MAINWINDOW_H
