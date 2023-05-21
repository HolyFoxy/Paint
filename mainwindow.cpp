#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Drawer");
    resize(900, 600);
    d_zone = new Drowing_Zone(this);

    Create_menu_bar();
    Create_tool_bar();

    statusBar()->showMessage("temp color: black");

    setCentralWidget(d_zone);
}

void MainWindow::Create_menu_bar(){
    QMenu* file_menu = menuBar()->addMenu("File");

    menuBar()->addSeparator();

    QIcon newIcon ("images/new.png");
    QAction* new_act = new QAction(newIcon, "New...", this);
    new_act->setShortcut(QKeySequence::New);
    connect(new_act, &QAction::triggered, this, &MainWindow::new_file);
    file_menu->addAction(new_act);

    QIcon openIcon ("images/open.png");
    QAction* open_act = new QAction(openIcon, "Open...", this);
    open_act->setShortcut(QKeySequence::Open);
    connect(open_act, &QAction::triggered, this, &MainWindow::open_file);
    file_menu->addAction(open_act);

    QIcon saveIcon ("images/save.png");
    QAction* save_act = new QAction(saveIcon, "Save...", this);
    save_act->setShortcut(QKeySequence::Save);
    connect(save_act, &QAction::triggered, d_zone, &Drowing_Zone::save);
    file_menu->addAction(save_act);

    QAction* save_as_act = new QAction(saveIcon, "Save as...", this);
    save_as_act->setShortcut(QKeySequence::SaveAs);
    connect(save_as_act, &QAction::triggered, d_zone, &Drowing_Zone::save_as);
    file_menu->addAction(save_as_act);

    file_menu->addSeparator();

    QAction* close_act = new QAction("close", this);
    connect(close_act, &QAction::triggered, this, &QWidget::close);
    file_menu->addAction(close_act);

    QMenu* sec_menu = menuBar()->addMenu("sec_menu");
    sec_menu->addAction(close_act);
}

void MainWindow::Create_tool_bar(){
    QToolBar* tool_bar = addToolBar("Drowing tools");
    QAction* pencil_t = tool_bar->addAction("pencil");
    pencil_t->setObjectName("pencil");
    connect(pencil_t, &QAction::triggered, d_zone, &Drowing_Zone::change_state);

    QAction* pen_t = tool_bar->addAction("brush");
    pen_t->setObjectName("pen");
    connect(pen_t, &QAction::triggered, d_zone, &Drowing_Zone::change_state);

    tool_bar->addSeparator();

    QAction* line_t = tool_bar->addAction("line");
    line_t->setObjectName("line");
    connect(line_t, &QAction::triggered, d_zone, &Drowing_Zone::change_state);

    QAction* curve_line_t = tool_bar->addAction("brocken line");
    curve_line_t->setObjectName("curve line");
    connect(curve_line_t, &QAction::triggered, d_zone, &Drowing_Zone::change_state);

    QAction* ellipse_t = tool_bar->addAction("ellipse");
    ellipse_t->setObjectName("ellipse");
    connect(ellipse_t, &QAction::triggered, d_zone, &Drowing_Zone::change_state);

    QAction* rectangle_t = tool_bar->addAction("rectangle");
    rectangle_t->setObjectName("rectangle");
    connect(rectangle_t, &QAction::triggered, d_zone, &Drowing_Zone::change_state);

    tool_bar->addSeparator();

    QAction* eraser_t = tool_bar->addAction("eraser");
    eraser_t->setObjectName("eraser");
    connect(eraser_t, &QAction::triggered, d_zone, &Drowing_Zone::change_state);

    QAction* text_t = tool_bar->addAction("text");
    text_t->setObjectName("text");
    connect(text_t, &QAction::triggered, d_zone, &Drowing_Zone::change_state);

    tool_bar->addSeparator();

    QSlider* width_slider = new QSlider (Qt::Horizontal);
    width_slider->setMinimum(1);
    width_slider->setMaximum(21);
    width_slider->setMaximumWidth(100);
    width_slider->setSingleStep(3);
    width_slider->setToolTip("Width");
    tool_bar->addWidget(width_slider);
    connect(width_slider, &QSlider::valueChanged, d_zone, &Drowing_Zone::change_width);

    tool_bar->addSeparator();
    QAction* hand = tool_bar->addAction("hand");
    hand->setObjectName("hand");
    connect(hand, &QAction::triggered, d_zone, &Drowing_Zone::change_state);

    tool_bar->addSeparator();

    tool_bar->addWidget(Create_color_table_tool());

    tool_bar->addSeparator();
    QSlider* zoom_slider = new QSlider (Qt::Horizontal);
    zoom_slider->setMinimum(50);
    zoom_slider->setMaximum(250);
    zoom_slider->setMaximumWidth(100);
    zoom_slider->setSingleStep(10);
    zoom_slider->setSliderPosition(100);
    zoom_slider->setToolTip("Zoom");
    tool_bar->addWidget(zoom_slider);
    connect(zoom_slider, &QSlider::valueChanged, d_zone, &Drowing_Zone::change_zoom);
}

QGroupBox* MainWindow::Create_color_table_tool()
{
    QGroupBox* test = new QGroupBox(this);
    QGridLayout*layout = new QGridLayout(test);

    QList <QString> buttons;
    buttons << "black"
            << "white"
            << "gray"
            << "red"
            << "orange"
            << "yellow"
            << "green"
            << "light blue"
            << "blue"
            << "violet";

    for (int i = 0; i < buttons.size() ; i++) {
        QPushButton* button = new QPushButton("", this);
        button->setObjectName(buttons[i]);
        connect(button, &QPushButton::clicked, this, &MainWindow::change_color);

        QPixmap a (15,15);
        a.fill(QColor(buttons[i]));
        button->setIcon(a);

        layout->addWidget(button, 0, i);
    }

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    test->setMaximumSize(200, 20);
    return test;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu (this);
    QAction* cansel_act = menu.addAction("Cansel");
    cansel_act->setShortcut(QKeySequence::Undo);
    connect(cansel_act, &QAction::triggered, d_zone, &Drowing_Zone::cansel);

    QAction* clear_act = menu.addAction("Clear_all");
    connect(clear_act, &QAction::triggered, d_zone, &Drowing_Zone::clear_sheet);
    menu.exec(event->globalPos());
}

void MainWindow::change_color()
{
    statusBar()->showMessage("temp color: "+sender()->objectName());
    d_zone->change_color(sender()->objectName());
}

void MainWindow::open_file()
{
    Open_Window*w = new Open_Window();
    connect(w, &Open_Window::get_file_name, d_zone, &Drowing_Zone::open_image);
    w->setWindowModality(Qt::ApplicationModal);
    w->show();
}

void MainWindow::new_file()
{
    New_File_Window* w = new New_File_Window();
    connect(w, &New_File_Window::Generate_New_File, d_zone, &Drowing_Zone::new_image);
    w->setWindowModality(Qt::ApplicationModal);
    w->show();
}

MainWindow::~MainWindow()
{

}
