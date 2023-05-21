#ifndef NEW_FILE_WINDOW_H
#define NEW_FILE_WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class New_File_Window : public QWidget
{
    Q_OBJECT
public:
    explicit New_File_Window(QWidget *parent = nullptr);
    ~New_File_Window();

signals:
    void Generate_New_File (int width, int height, QString name);

private slots:
    void On_Apply_b_clicked();

private:
    QLineEdit* width;
    QLineEdit* height;
    QLineEdit* file_name_l;
    QString file_name;
};

#endif // NEW_FILE_WINDOW_H
