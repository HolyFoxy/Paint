#include "open_window.h"

Open_Window::Open_Window(QWidget *parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    QLabel* text_on_screen = new QLabel ("Input file path (replace \\ by /):", this);
    layout->addWidget(text_on_screen, 0, 0, 1, 2);
    input_line = new QLineEdit (this);
    layout->addWidget(input_line, 1, 0, 1, 2);
    QPushButton* acc_b = new QPushButton("Open", this);
    acc_b->setObjectName("Accept_b");
    connect(acc_b, &QPushButton::clicked, this, &Open_Window::on_Accept_b_clicked);
    layout->addWidget(acc_b, 1, 3, 1, 1);

    setWindowTitle("Open file");
    resize(300, 50);
}

Open_Window::~Open_Window()
{

}


void Open_Window::on_Accept_b_clicked(){
    file_name = input_line->text();
    if ((file_name == "") || (file_name == " ")){

    }else{
        emit get_file_name(file_name);
        close();
    }
}
