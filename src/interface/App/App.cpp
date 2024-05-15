#include "App.h"

int buttonWidth = 250;
int buttonHeight = 50;
int spacing = 20;


std::pair<int, int> resolution = {1920, 1080};

App::App() {
    auto rb_screen = new QLabel(this);
    rb_screen->resize(resolution.first, resolution.second);

    auto avl_screen = new QLabel(this);
    avl_screen->resize(resolution.first, resolution.second);

    auto splay_screen = new QLabel(this);
    splay_screen->resize(resolution.first, resolution.second);

    auto cartesian_screen = new QLabel(this);
    cartesian_screen->resize(resolution.first, resolution.second);

    setFixedSize(resolution.first, resolution.second);

    auto rb_c = new Canvas(rb_screen);
    auto avl_c = new Canvas(avl_screen);
    auto splay_c = new Canvas(splay_screen);
    auto cartesian_c = new Canvas(cartesian_screen);

    rb_c->setFixedSize(resolution.first - 50, resolution.second - 50);
    avl_c->setFixedSize(resolution.first - 50, resolution.second - 50);
    splay_c->setFixedSize(resolution.first - 50, resolution.second - 50);
    cartesian_c->setFixedSize(resolution.first - 50, resolution.second - 50);

    rb_screen_ = rb_screen;
    avl_screen_ = avl_screen;
    splay_screen_ = splay_screen;
    cartesian_screen_ = cartesian_screen;
    rb_screen_active_ = false;
    avl_screen_active_ = false;
    splay_screen_active_ = false;
    cartesian_screen_active_ = false;

    rb_canvas_ = rb_c;
    connect(rb_canvas_, &Canvas::mouseClicked, this, &App::deleteNode);
    avl_canvas_ = avl_c;
    connect(avl_canvas_, &Canvas::mouseClicked, this, &App::deleteNode);
    splay_canvas_ = splay_c;
    connect(splay_canvas_, &Canvas::mouseClicked, this, &App::deleteNode);
    cartesian_canvas_ = cartesian_c;
    connect(cartesian_canvas_, &Canvas::mouseClicked, this, &App::deleteNode);

    settings_ = new QWidget();
    auto avl_btn = new QPushButton("AVL", settings_);
    auto rb_btn = new QPushButton("RB", settings_);
    auto splay_btn = new QPushButton("Splay", settings_);
    auto cartesian_btn = new QPushButton("Cartesian", settings_);
    auto line_edit = new QLineEdit(settings_);
    line_edit->move(0, 4 * buttonHeight + 4 * spacing);
    line_edit_ = line_edit;
    line_edit->setFixedSize(350, 30);
    auto label = new QLabel("Input node count:", settings_);
    label->move(0, 4 * buttonHeight + 3 * spacing);
    auto confirm_btn = new QPushButton("Confirm", settings_);
    confirm_btn->move(360, 4 * buttonHeight + 4 * spacing);
    confirm_btn->resize(140, 30);

    connect(avl_btn, SIGNAL(clicked()), this, SLOT(setAvlScreen()));
    connect(rb_btn, SIGNAL(clicked()), this, SLOT(setRbScreen()));
    connect(splay_btn, SIGNAL(clicked()), this, SLOT(setSplayScreen()));
    connect(cartesian_btn, SIGNAL(clicked()), this, SLOT(setCartesianScreen()));
    connect(confirm_btn, SIGNAL(clicked()), this, SLOT(addNodes()));

    avl_btn->setFixedSize(buttonWidth, buttonHeight);
    rb_btn->setFixedSize(buttonWidth, buttonHeight);
    splay_btn->setFixedSize(buttonWidth, buttonHeight);
    cartesian_btn->setFixedSize(buttonWidth, buttonHeight);

    int x = (resolution.first - settings_->width()) / 2;
    int y = (resolution.second - settings_->height()) / 2;

    settings_->setFixedSize(500, 500);
    settings_->setWindowTitle("Settings");
    settings_->move(x, y);

    avl_btn->move(0, 0);
    rb_btn->move(buttonWidth + spacing, 0);
    splay_btn->move(0, buttonHeight + spacing);
    cartesian_btn->move(buttonWidth + spacing, buttonHeight + spacing);

}

void App::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        close();
        settings_->close();
    } else if (event->key() == Qt::Key_Tab) {
        settings_->show();
        settings_->activateWindow();
    } else if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) {
        if (cartesian_screen_active_ && scale < 3) {
            scale += 0.1;
            cartesian_canvas_->scale(scale, scale);
        }
    } else if (event->key() == Qt::Key_Minus) {
        std::cout << scale << std::endl;
        if (cartesian_screen_active_ && scale > 0.4) {
            scale -= 0.1;
            cartesian_canvas_->scale(scale, scale);
        }
    }
}

void App::setAvlScreen() {
    if (!Avl_tree_) {
        Avl_tree_ = new AvlTree();
    }
    rb_screen_->hide();
    splay_screen_->hide();
    cartesian_screen_->hide();
    avl_screen_->show();
    rb_screen_active_ = false;
    avl_screen_active_ = true;
    splay_screen_active_ = false;
    cartesian_screen_active_ = false;
}

void App::setRbScreen() {
    splay_screen_->hide();
    avl_screen_->hide();
    cartesian_screen_->hide();
    rb_screen_->show();
    rb_screen_active_ = true;
    avl_screen_active_ = false;
    splay_screen_active_ = false;
    cartesian_screen_active_ = false;
}

void App::setSplayScreen() {
    avl_screen_->hide();
    rb_screen_->hide();
    cartesian_screen_->hide();
    splay_screen_->show();
    rb_screen_active_ = false;
    avl_screen_active_ = false;
    splay_screen_active_ = true;
    cartesian_screen_active_ = false;
}

void App::setCartesianScreen() {
    if (!Cartesian_tree_) {
        Cartesian_tree_ = new CartesianTree();
    }
    avl_screen_->hide();
    rb_screen_->hide();
    splay_screen_->hide();
    cartesian_screen_->show();
    rb_screen_active_ = false;
    avl_screen_active_ = false;
    splay_screen_active_ = false;
    cartesian_screen_active_ = true;
}

void App::addNodes() {
    std::mt19937 rnd(48);
    if (cartesian_screen_active_) {
        int cnt = line_edit_->text().toInt();
        for (int i = 0; i < cnt;) {
            int64_t key = rnd();
            if (Cartesian_tree_->exists(key)) {
                continue;
            }
            Cartesian_tree_->insert(key);
            ++i;
        }
        cartesian_canvas_->DrawCartesianTree(Cartesian_tree_);
    } else if (splay_screen_active_) {
        int cnt = line_edit_->text().toInt();
        for (int i = 0; i < cnt;) {
            int64_t key = rnd();
            if (splay_find(Splay_tree_, key)) {
                continue;
            }
            add_splay(Splay_tree_, key);
            ++i;
        }
        splay_canvas_->DrawSplayTree(Splay_tree_);
    } else if (avl_screen_active_) {
        int cnt = line_edit_->text().toInt();
        for (int i = 0; i < cnt;) {
            int64_t key = rnd();
            if (Avl_tree_->search(key)) {
                continue;
            }
            Avl_tree_->insert(key);
            ++i;
        }
        avl_canvas_->DrawAVLTree(Avl_tree_);
    }
}

void App::deleteNode(int x, int y) {
    if (avl_screen_active_) {
        Node *node = Avl_tree_->find(x, y);
        if (!node) {
            return;
        }
        int64_t key = node->val;
        Avl_tree_->remove(key);
        avl_canvas_->DrawAVLTree(Avl_tree_);
    } else if (cartesian_screen_active_) {
        CartesianNode* node = Cartesian_tree_->find(x, y);
        if (!node) {
            return;
        }
        int64_t key = node->val;
        Cartesian_tree_->remove(key);
        cartesian_canvas_->DrawCartesianTree(Cartesian_tree_);
    } else if (splay_screen_active_) {
        Node* node = ::find(Splay_tree_, x, y);
        if (!node) {
            return;
        }
        int64_t key = node->val;
        del_splay(Splay_tree_, key);
        splay_canvas_->DrawSplayTree(Splay_tree_);
    } else if (rb_screen_active_) {

    }
}
