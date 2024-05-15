#include <QMainWindow>
#include <iostream>
#include <QLabel>
#include <QDialog>
#include <QKeyEvent>
#include <QPushButton>
#include <QLineEdit>
#include "../Canvas/Canvas.h"


#ifndef TREEMAN_APP_H
#define TREEMAN_APP_H


class App : public QMainWindow {
Q_OBJECT;
public:
    App();

public slots:

    void setAvlScreen();

    void setRbScreen();

    void setSplayScreen();

    void setCartesianScreen();

    void addNodes();

    void deleteNode(int x, int y);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QLabel *rb_screen_;

    bool rb_screen_active_;

    QLabel *avl_screen_;

    bool avl_screen_active_;

    QLabel *splay_screen_;

    bool splay_screen_active_;

    QLabel *cartesian_screen_;

    bool cartesian_screen_active_;

    Canvas *rb_canvas_;

    Canvas *avl_canvas_;

    Canvas *splay_canvas_;

    Canvas *cartesian_canvas_;

    QWidget *settings_;

    CartesianTree *Cartesian_tree_ = nullptr;

    Node *Splay_tree_ = nullptr;

    AvlTree *Avl_tree_ = nullptr;

    QLineEdit *line_edit_;

    qreal scale = 1;
};


#endif //TREEMAN_APP_H
