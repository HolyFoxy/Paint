#ifndef DROWING_ZONE_H
#define DROWING_ZONE_H

#include <QtEvents>
#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QImage>
#include <QPicture>
#include <QStack>

enum States{

    NOPE = 0,
    OPEN,
    PENCIL,
    PEN,
    LINE,
    ELLIPSE,
    RECTANGLE,
    ERASER,
    CURVE_LINE,
    TEXT,
    CLEAR,
    HAND

};

class Drowing_Zone : public QWidget
{
    Q_OBJECT
public:
    Drowing_Zone(QWidget *parent = nullptr);
    ~Drowing_Zone();

    /**
     * @brief Функция создания нового изображения
     * @param int - ширинаб int - высота, QString - имя файла
     */
    void new_image(int, int, QString);

    /**
     * @brief Функция открытия файла изображения
     * Значение по умолчанию является примером
     */
    void open_image(QString filename = "C:/Users/Home/Desktop/Test");

    /**
     * @brief Функция изменения цвета пера
     */
    void change_color(QString new_color);



protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent (QMouseEvent*) override;
    void mouseMoveEvent (QMouseEvent*) override;
    void mouseReleaseEvent (QMouseEvent*) override;

signals:

public slots:

    /**
     * @brief Функция изменения пера
     */
    void change_state();

    /**
     * @brief Функция изменения толщины пера
     */
    void change_width(int);

    /**
     * @brief Функция полной очистки изображения
     */
    void clear_sheet();

    /**
     * @brief Функция изменения масштаба изображения
     */
    void change_zoom(int);

    /**
     * @brief Функция отмены последнего изменения
     */
    void cansel();

    /**
     * @brief Функция сохранения зображения с заданным именем
     */
    void save();

    /**
     * @brief Функция сохранения изображения с другим именем
     */
    void save_as();

private:
    /**
     * @brief Файл изображения
     */
    QImage image;
    /**
     * @brief Имя открытого или созданного файла
     */
    QString m_file_name = "";
    /**
     * @brief Состояние пера
     */
    States t_state = NOPE;

    /**
     * @brief Стак памяти изменений изображения
     */
    QStack <QImage> memory;

    //-------------------------------------------------
    //Вспомогательные переменные для корректной отрисовки
    //-------------------------------------------------
    int start_x;
    int start_y;

    int temp_x;
    int temp_y;

    bool is_curve_drawing = false;
    bool is_moving = false;
    int t_width = 1;
    QColor t_color;

    QPoint move = QPoint(0, 0);
    QPoint stay = QPoint(0, 0);

    QSize real_size;

    QString text_on_draw = "";
};

#endif // DROWING_ZONE_H
