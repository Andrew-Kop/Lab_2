#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget> // Для таблицы
#include <QComboBox> // Для выбора задачи
#include <QLineEdit> // Для ввода размера сетки
#include <QTextEdit> // Для вывода текста
#include <QPushButton> // Для кнопки
#include "qcustomplot.h"
#include "schema.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QCustomPlot *chartView1; // Первый график
    QCustomPlot *chartView2; // Второй график
    QTableWidget *tableWidget; // Таблица
    QComboBox *taskComboBox; // Выбор задачи
    QLineEdit *gridSizeEdit; // Ввод размера сетки
    QTextEdit *outputTextBox; // Вывод текста
    QPushButton *calculateButton; // Кнопка расчета

    void createCharts(); // Функция для создания графиков
    void createTable(); // Функция для создания таблицы
    void calculate();
    void createOutputElements(); // Функция для создания элементов вывода
    Scheme shema;
};
#endif // MAINWINDOW_H
