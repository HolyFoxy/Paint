#ifndef OPEN_WINDOW_H
#define OPEN_WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class Open_Window : public QWidget
{
    Q_OBJECT
public:
    explicit Open_Window(QWidget *parent = nullptr);
    ~Open_Window();

signals:
    void get_file_name (QString);

private slots:
    void on_Accept_b_clicked();

private:
    QString file_name;
    QLineEdit* input_line;

};

#endif // OPEN_WINDOW_H
