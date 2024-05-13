#include "Canvas.h"

Canvas::Canvas(QWidget *parent) : QGraphicsView(parent) {

    scene = new QGraphicsScene(this);
    setScene(scene);
}

void Canvas::DrawNode(int x, int y, Node *Node) {

    scene->addEllipse(QRect(x, y, 20, 20));
}

void Canvas::ZoomIn() {

}

void Canvas::ZoomOut() {

}
