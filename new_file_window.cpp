#include "new_file_window.h"
#include <QIntValidator>

New_File_Window::New_File_Window(QWidget *parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    setWindowTitle("Создание нового файла");

    QLabel* width_l = new QLabel("Ширина: ", this);
    layout->addWidget(width_l, 0, 0, 1, 1);

    QLabel* height_l = new QLabel("Высота: ", this);
    layout->addWidget(height_l, 1, 0, 1, 1);

    width = new QLineEdit(this);
    width->setValidator(new QIntValidator(this));
    layout->addWidget(width, 0, 1, 1, 1);

    height = new QLineEdit(this);
    height->setValidator(new QIntValidator(this));
    layout->addWidget(height, 1, 1, 1, 1);

    QLabel* text_fnl = new QLabel ("Имя файла без расширения:", this);
    layout->addWidget(text_fnl, 2, 0, 1, 2);

    file_name_l = new QLineEdit(this);
    layout->addWidget(file_name_l, 3, 0, 1, 2);

    QPushButton* apply_b = new QPushButton("Создать", this);
    apply_b->setObjectName("Apply_b");
    layout->addWidget(apply_b, 4, 0, 1, 1);
    connect(apply_b, &QPushButton::clicked, this, &New_File_Window::On_Apply_b_clicked);
}

New_File_Window::~New_File_Window()
{

}

void New_File_Window::On_Apply_b_clicked()
{
    if ((width->text().toDouble() >= 1) && (height->text().toDouble() >= 1) && (file_name_l->text().size() >= 1)){
        emit Generate_New_File(width->text().toDouble(), height->text().toDouble(), file_name_l->text());
        close();
    }
}
