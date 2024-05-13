#include <QGraphicsView>
#include "../../trees/Node.h"
#ifndef TREEMAN_CANVAS_H
#define TREEMAN_CANVAS_H

class Canvas : public QGraphicsView {
Q_OBJECT;

public:
    Canvas(QWidget *parent = nullptr);
    void DrawNode(int x, int y, Node* Node);

public slots:
    void ZoomIn();
    void ZoomOut();
private:
    QGraphicsScene *scene;

};


#endif //TREEMAN_CANVAS_H
