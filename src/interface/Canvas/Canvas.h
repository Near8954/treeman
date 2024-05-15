#include <QGraphicsView>
#include "../../trees/CartesianTree/CartesianTree.h"
#include "../../trees/SplayTree/SplayTree.h"
#include "../../trees/AvlTree/AvlTree.h"

#ifndef TREEMAN_CANVAS_H
#define TREEMAN_CANVAS_H


class Canvas : public QGraphicsView {

Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;

    void DrawCartesianNode(int64_t x, int64_t y, CartesianNode *Node);

    void DrawCartesianTree(CartesianTree *T);

    void DrawCartesianTree(int64_t x, int64_t y, CartesianNode *T);

    void DrawSplayNode(int64_t x, int64_t y, Node *Node);

    void DrawSplayTree(Node *T);

    void DrawSplayTree(int64_t x, int64_t y, Node *T);

    void DrawAVLNode(int64_t x, int64_t y, Node *Node);

    void DrawAVLTree(AvlTree *T);

    void DrawAVLTree(int64_t x, int64_t y, Node *T);

signals:

    void mouseClicked(int x, int y);

private:
    QGraphicsScene *scene;
};


#endif //TREEMAN_CANVAS_H
