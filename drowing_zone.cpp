#include "drowing_zone.h"
#include <QDebug>
#include <QInputDialog>

Drowing_Zone::Drowing_Zone(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    m_file_name = "";
}

Drowing_Zone::~Drowing_Zone()
{

}

//------------------------------------------------------------------------------

void Drowing_Zone::new_image(int width, int height, QString name)
{
    QImage newImage (width, height, QImage::Format_RGB32);
    newImage.fill(Qt::white);
    image = newImage;
    image.save("~temp_image.png");
    real_size = image.size();
    m_file_name = name + ".png";
    t_state = OPEN;
    memory.push(image);
    update();
}

//------------------------------------------------------------------------------

void Drowing_Zone::open_image(QString filename)
{
    if (m_file_name == ""){
        QImage loaded_image;
        loaded_image.load(filename);
        image = loaded_image;
        image.save("~temp_image.png");
        real_size = image.size();
    }
    m_file_name = filename;
    t_state = OPEN;
    memory.push(image);
    update();
}

//------------------------------------------------------------------------------

void Drowing_Zone::change_color(QString new_color)
{
    t_color = QColor(new_color);
    if (t_state == PEN){
        QPixmap a (t_width, t_width);
        a.fill(t_color);
        setCursor(QCursor(a));
    }
}

//------------------------------------------------------------------------------

void Drowing_Zone::paintEvent(QPaintEvent * key){
    QPainter painter(this);
    painter.end();

        switch (t_state){
            case NOPE:
                break;
            case HAND:
                move = QPoint(stay.x() + temp_x - start_x, stay.y() + temp_y - start_y);
                painter.begin(this);
                painter.drawImage(move, image);
                painter.end();
                break;

            case PENCIL:
                painter.begin(&image);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.setPen(QPen(Qt::black, 1));
                painter.drawPoint(temp_x - move.x(), temp_y - move.y());
                painter.end();

                painter.begin(this);
                painter.drawImage(move, image);
                painter.end();
                break;

            case PEN:
                painter.begin(&image);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.setPen(QPen(t_color, t_width));
                painter.drawPoint(temp_x - move.x(), temp_y - move.y());
                painter.end();

                painter.begin(this);
                painter.drawImage(move, image);
                painter.end();
                break;

            case LINE:
                painter.begin(&image);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.setPen(QPen(t_color, t_width));
                painter.drawLine(start_x - move.x(), start_y - move.y(), temp_x - move.x(), temp_y - move.y());
                painter.end();

                painter.begin(this);
                painter.drawImage(move, image);
                painter.end();
                break;

            case ELLIPSE:
                painter.begin(&image);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.setPen(QPen(t_color, t_width));
                painter.setBrush(Qt::NoBrush);
                painter.drawEllipse(QPoint(start_x - move.x(), start_y - move.y()), temp_x-start_x, temp_y-start_y);
                painter.end();

                painter.begin(this);
                painter.drawImage(move, image);
                painter.end();
                break;

            case RECTANGLE:
                painter.begin(&image);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.setPen(QPen(t_color, t_width));
                painter.setBrush(Qt::NoBrush);
                painter.drawRect(start_x - move.x(), start_y - move.y(), temp_x-start_x, temp_y-start_y);
                painter.end();

                painter.begin(this);
                painter.drawImage(move, image);
                painter.end();
                break;

            case ERASER:
                painter.begin(&image);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.setPen(QPen(Qt::white, t_width));
                painter.drawPoint(temp_x - move.x(), temp_y - move.y());
                painter.end();

                painter.begin(this);
                painter.drawImage(move, image);
                painter.end();
                break;

            case CURVE_LINE:
                painter.begin(&image);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.setPen(QPen(t_color, t_width));
                painter.drawLine(temp_x - move.x(), temp_y - move.y(), start_x - move.x(), start_y - move.y());
                painter.end();

                painter.begin(this);
                painter.drawImage(move, image);
                painter.end();
                break;

            case TEXT:
                painter.begin(&image);
                painter.setPen(QPen(t_color, t_width));
                painter.drawText(QPoint(temp_x - move.x(), temp_y - move.y()), text_on_draw);
                painter.end();

                text_on_draw = "";

                painter.begin(this);
                painter.drawImage(move, image);
                painter.end();
                break;

            case CLEAR:
                painter.begin(this);
                painter.drawImage(move, image);
                painter.end();
                break;

            case OPEN:
                painter.begin(this);
                painter.drawImage(move, image);
                painter.end();
                t_state = NOPE;
                break;
        }
}

//------------------------------------------------------------------------------

void Drowing_Zone::mousePressEvent(QMouseEvent *key)
{
    if ((key->button() == Qt::LeftButton)&&(t_state != HAND)){
        start_x = key->x();
        start_y = key->y();
        if ((t_state == PEN)||(t_state == PENCIL)||(t_state == ERASER)){
            temp_x = key->x();
            temp_y = key->y();
            update();
        }
        setMouseTracking(true);
        key->accept();
    }else if ((key->button() == Qt::LeftButton)&&(t_state == HAND)){
        is_moving = true;
        setCursor(Qt::ClosedHandCursor);
        start_x = key->x();
        start_y = key->y();
        key->accept();
    }else{
        key->ignore();
    }
}

//------------------------------------------------------------------------------

void Drowing_Zone::mouseMoveEvent(QMouseEvent *key)
{
    if ((t_state == PEN)||(t_state == PENCIL)||(t_state == ERASER)){
        temp_x = key->x();
        temp_y = key->y();
        update();
    }
    if ((t_state == HAND)&&(is_moving)){
        temp_x = key->x();
        temp_y = key->y();
        update();
    }
}

//------------------------------------------------------------------------------

void Drowing_Zone::mouseReleaseEvent(QMouseEvent *key)
{
    if ((key->button() == Qt::LeftButton)&&(t_state!=HAND)){
        if ((t_state == LINE)||(t_state == ELLIPSE)||(t_state == RECTANGLE)){
            temp_x = key->x();
            temp_y = key->y();
            update();
        }
        if (t_state == CURVE_LINE){
            if (!is_curve_drawing)
                is_curve_drawing = true;
            else
                update();

            int i = temp_x;
            temp_x = start_x;
            start_x = i;
            i = temp_y;
            temp_y = start_y;
            start_y = i;

            setMouseTracking(false);

            key->accept();
        }
        if (t_state == TEXT){
            temp_x = key->x();
            temp_y = key->y();

            QInputDialog* dialog = new QInputDialog(this);
            dialog->setLabelText("Введите текст:");
            dialog->setInputMode(QInputDialog::TextInput);
            dialog->setWindowModality(Qt::WindowModal);
            dialog->exec();

            text_on_draw = dialog->textValue();
            update();
        }
        memory.push(image);
        setMouseTracking(false);
        key->accept();
    }else{
        if ((key->button() == Qt::LeftButton)&&(t_state == HAND)){
            is_moving = false;
            setCursor(Qt::OpenHandCursor);
            stay = move;
            key->accept();
        }
        else
            key->ignore();
    }
}

//------------------------------------------------------------------------------

void Drowing_Zone::change_state(){
    if (sender()->objectName() == "pen"){
        t_state = PEN;
        QPixmap a (t_width, t_width);
        a.fill(t_color);
        setCursor(QCursor(a));
    }
    if (sender()->objectName() == "pencil"){
        t_state = PENCIL;
        QPixmap a (1, 1);
        a.fill(Qt::black);
        setCursor(QCursor(a));
    }
    if (sender()->objectName() == "line"){
        t_state = LINE;
        unsetCursor();
    }
    if (sender()->objectName() == "ellipse"){
        t_state = ELLIPSE;
        unsetCursor();
    }
    if (sender()->objectName() == "rectangle"){
        t_state = RECTANGLE;
        unsetCursor();
    }
    if (sender()->objectName() == "curve line"){
        t_state = CURVE_LINE;
        unsetCursor();
    }
    if (sender()->objectName() == "text"){
        t_state = TEXT;
        unsetCursor();
    }
    if (sender()->objectName() == "eraser"){
        t_state = ERASER;
        QPixmap a (t_width, t_width);
        a.fill(Qt::white);
        setCursor(QCursor(a));
    }
    if (sender()->objectName() == "hand"){
        t_state = HAND;
        setCursor(Qt::OpenHandCursor);
    }
    if (sender()->objectName() == ""){
        t_state = NOPE;
        unsetCursor();
    }
    is_curve_drawing = false;
}

//------------------------------------------------------------------------------

void Drowing_Zone::clear_sheet(){
    image.fill(Qt::white);
    States help = t_state;
    t_state = CLEAR;
    start_x = 0;    start_y = 0;    temp_x = 0;     temp_y = 0;
    update();
    memory.push(image);
    t_state = help;
}

void Drowing_Zone::change_zoom(int new_zoom)
{
    float zoom = new_zoom/100.0;
    if (m_file_name != ""){
        image = image.scaled(real_size * zoom, Qt::KeepAspectRatio);
        t_state = OPEN;
        unsetCursor();
        update();
    }
}

void Drowing_Zone::cansel()
{
    if (!memory.isEmpty()){
        image = memory.pop();
        t_state = OPEN;
        unsetCursor();
        update();
    }
    if (memory.isEmpty())
        memory.push(image);
}

void Drowing_Zone::save()
{
    if (m_file_name != ""){
        image.scaled(real_size, Qt::KeepAspectRatio);
        image.save(m_file_name + ".png");
    }
}

void Drowing_Zone::save_as()
{
    QInputDialog* dialog = new QInputDialog(this);
    dialog->setLabelText("Введите имя файла:");
    dialog->setInputMode(QInputDialog::TextInput);
    dialog->setWindowModality(Qt::WindowModal);
    dialog->exec();
    m_file_name = dialog->textValue() + ".png";
    image.scaled(real_size, Qt::KeepAspectRatio);
    image.save(m_file_name);
}

//------------------------------------------------------------------------------

void Drowing_Zone::change_width(int i)
{
    t_width = i;
    if (t_state == PEN){
        QPixmap a (t_width, t_width);
        a.fill(t_color);
        setCursor(QCursor(a));
    }
    if (t_state == ERASER){
        QPixmap a (t_width, t_width);
        a.fill(Qt::white);
        setCursor(QCursor(a));
    }
}

