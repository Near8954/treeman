#include "Canvas.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QMouseEvent>

int64_t get_size(CartesianNode *t) {
    return t ? t->size : 0;
}

Canvas::Canvas(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
}

void Canvas::DrawCartesianNode(int64_t x, int64_t y, CartesianNode *Node) {
    auto node = new QGraphicsEllipseItem(x, y, 80, 80);
    node->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    QString text_s_val = QString::fromStdString(std::to_string(Node->val) + ";");
    QString text_s_prior = QString::fromStdString(std::to_string(Node->priority));
    auto text = new QGraphicsTextItem(text_s_val + '\n' + text_s_prior);
    text->setFont(QFont("Calibri", std::min(13, 89 / text_s_val.size())));
    text->setPos(x, y + 20);
    scene->addItem(node);
    scene->addItem(text);
}

void Canvas::DrawCartesianTree(CartesianTree *T) {
    scene->clear();
    if (T) {
        DrawCartesianTree(0, 0, T->get_root());
    }
}

void Canvas::DrawCartesianTree(int64_t x, int64_t y, CartesianNode *T) {
    if (!T) {
        return;
    }
    if (T->right) {
        T->right->x = x + get_size(T->right->left) * 100 + 80;
        T->right->y = y + 100 + 40;
        scene->addLine(x + 40, y + 40, x + get_size(T->right->left) * 100 + 80 + 40, y + 100 + 40);
        DrawCartesianTree(x + get_size(T->right->left) * 100 + 80, y + 100, T->right);
    }
    if (T->left) {
        T->left->x = x - (get_size(T->left->right) * 100 + 80);
        T->left->y = y + 100 + 40;
        scene->addLine(x + 40, y + 40, x - (get_size(T->left->right) * 100 + 80) + 40, y + 100 + 40);
        DrawCartesianTree(x - (get_size(T->left->right) * 100 + 80), y + 100, T->left);
    }
    DrawCartesianNode(x, y, T);
}



void Canvas::DrawSplayTree(int64_t x, int64_t y, Node *T) {
    if (!T) {
        return;
    }
    fix_size(T);
    if (T->right) {
        T->right->x = x + get_size(T->right->left) * 100 + 80;
        T->right->y = y + 100 + 40;
        scene->addLine(x + 40, y + 40, x + get_size(T->right->left) * 100 + 80 + 40, y + 100 + 40);
        DrawSplayTree(x + get_size(T->right->left) * 100 + 80, y + 100, T->right);
    }
    if (T->left) {
        T->left->x = x - (get_size(T->left->right) * 100 + 80);
        T->left->y = y + 100 + 40;
        scene->addLine(x + 40, y + 40, x - (get_size(T->left->right) * 100 + 80) + 40, y + 100 + 40);
        DrawSplayTree(x - (get_size(T->left->right) * 100 + 80), y + 100, T->left);
    }
    DrawSplayNode(x, y, T);
}

void Canvas::DrawSplayNode(int64_t x, int64_t y, Node *Node) {
    auto node = new QGraphicsEllipseItem(x, y, 80, 80);
    node->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    QString text_s_val = QString::fromStdString(std::to_string(Node->val));
    auto text = new QGraphicsTextItem(text_s_val);
    text->setFont(QFont("Calibri", std::min(13, 89 / text_s_val.size())));
    text->setPos(x, y + 20);
    scene->addItem(node);
    scene->addItem(text);
}

void Canvas::DrawSplayTree(Node *T) {
    scene->clear();
    if (T) {
        DrawSplayTree(0, 0, T);
    }
}

void Canvas::DrawAVLNode(int64_t x, int64_t y, Node *Node) {
    auto node = new QGraphicsEllipseItem(x, y, 80, 80);
    node->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    QString text_s_val = QString::fromStdString(std::to_string(Node->val));
    auto text = new QGraphicsTextItem(text_s_val);
    text->setFont(QFont("Calibri", std::min(13, 89 / text_s_val.size())));
    text->setPos(x, y + 20);
    scene->addItem(node);
    scene->addItem(text);
}

void Canvas::DrawAVLTree(AvlTree *T) {
    scene->clear();
    if (T) {
        DrawAVLTree(0, 0, T->get_root());
    }
}

void Canvas::DrawAVLTree(int64_t x, int64_t y, Node *T) {
    if (!T) {
        return;
    }
    fix_size(T);
    if (T->right) {
        T->right->x = x + get_size(T->right->left) * 100 + 80;
        T->right->y = y + 100 + 40;
        scene->addLine(x + 40, y + 40, x + get_size(T->right->left) * 100 + 80 + 40, y + 100 + 40);
        DrawAVLTree(x + get_size(T->right->left) * 100 + 80, y + 100, T->right);
    }
    if (T->left) {
        T->left->x = x - (get_size(T->left->right) * 100 + 80);
        T->left->y = y + 100 + 40;
        scene->addLine(x + 40, y + 40, x - (get_size(T->left->right) * 100 + 80) + 40, y + 100 + 40);
        DrawAVLTree(x - (get_size(T->left->right) * 100 + 80), y + 100, T->left);
    }
    DrawAVLNode(x, y, T);
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        auto coords = this->mapToScene(event->pos());
        emit mouseClicked((int) coords.x(), (int) coords.y());
    }
    QGraphicsView::mousePressEvent(event);
}

