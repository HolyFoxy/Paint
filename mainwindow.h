#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "drowing_zone.h"
#include "open_window.h"
#include "new_file_window.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

protected:
    void contextMenuEvent (QContextMenuEvent*) override;

private slots:

    /**
     * @brief Функция изменения цвета пера
     */
    void change_color();

    /**
     * @brief Функция открытия изображения
     */
    void open_file();

    /**
     * @brief Функция создания нового изображения
     */
    void new_file();

private:

    /**
     * @brief Функция создания меню
     */
    void Create_menu_bar();

    /**
     * @brief Функция создания инструментальной панели
     */
    void Create_tool_bar();

    /**
     * @brief Функция создания таблицы выбора цвета
     */
    QGroupBox* Create_color_table_tool();

    /**
     * @brief Объект класса зоны рисования
     */
    Drowing_Zone* d_zone;
};
#endif // MAINWINDOW_H
