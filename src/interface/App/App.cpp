#include "App.h"

std::pair<int, int> resolution = {1920, 1080};

App::App() {
    QLabel rb_screen = QLabel(this);
    rb_screen.resize(resolution.first, resolution.second);

    QLabel avl_screen = QLabel(this);
    avl_screen.resize(resolution.first, resolution.second);

    QLabel splay_screen = QLabel(this);
    splay_screen.resize(resolution.first, resolution.second);

    QLabel cartesian_screen = QLabel(this);
    cartesian_screen.resize(resolution.first, resolution.second);

    setFixedSize(resolution.first, resolution.second);

    Canvas rb_c(&rb_screen);
    Canvas avl_c(&avl_screen);
    Canvas splay_c(&splay_screen);
    Canvas cartesian_c(&cartesian_screen);

    rb_c.setFixedSize(resolution.first, resolution.second);
    avl_c.setFixedSize(resolution.first, resolution.second);
    splay_c.setFixedSize(resolution.first, resolution.second);
    cartesian_c.setFixedSize(resolution.first, resolution.second);
    rb_screen.show();
}
