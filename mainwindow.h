#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 * Файл заголовка MainWindow.h
 *
 * Описывает класс MainWindow, который является главным окном приложения.
 * Отвечает за создание и управление пользовательским интерфейсом,
 * включая графики, таблицы, поля ввода и кнопку.
 *
 * Включает необходимые заголовочные файлы:
 * - <QMainWindow>: Базовый класс для главного окна.
 * - <QTableWidget>: Для отображения табличных данных.
 * - <QComboBox>: Для выпадающего списка выбора задачи.
 * - <QLineEdit>: Для ввода размера сетки.
 * - <QTextEdit>: Для вывода текстовой информации (справка).
 * - <QPushButton>: Для кнопки запуска расчета.
 * - "qcustomplot.h": Для построения графиков.
 * - "schema.h": Для классов, реализующих расчетные схемы.
 */

#include <QMainWindow>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include "qcustomplot.h"
#include "schema.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
/*
 * Класс MainWindow
 *
 * Является наследником QMainWindow и представляет собой главное окно приложения.
 * Отвечает за создание и управление пользовательским интерфейсом,
 * обработку пользовательского ввода и запуск расчетов.
 *
 * Public методы:
 * - MainWindow(QWidget *parent = nullptr): Конструктор класса.
 * - ~MainWindow(): Деструктор класса.
 *
 * Private методы:
 * - createCharts(): Создает и настраивает графики.
 * - createTable(): Создает и настраивает таблицу результатов.
 * - calculate(): Запускает расчеты и обновляет графики и таблицу.
 * - createOutputElements(): Создает и настраивает элементы вывода (например, placeholder для gridSizeEdit).
 *
 * Private поля:
 * - ui: Указатель на объект Ui::MainWindow, сгенерированный Qt Designer.
 * - chartView1: Указатель на QCustomPlot для первого графика.
 * - chartView2: Указатель на QCustomPlot для второго графика.
 * - tableWidget: Указатель на QTableWidget для таблицы результатов.
 * - taskComboBox: Указатель на QComboBox для выбора типа задачи.
 * - gridSizeEdit: Указатель на QLineEdit для ввода размера сетки.
 * - outputTextBox: Указатель на QTextEdit для вывода текстовой информации.
 * - calculateButton: Указатель на QPushButton для запуска расчетов.
 * - shema: Объект класса Scheme, реализующий расчетные схемы.
 */
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QCustomPlot *chartView1;
    QCustomPlot *chartView2;
    QTableWidget *tableWidget;
    QComboBox *taskComboBox;
    QLineEdit *gridSizeEdit;
    QTextEdit *outputTextBox;
    QPushButton *calculateButton;

    void createCharts();
    void createTable();
    void calculate();
    void createOutputElements();
    Scheme shema;
};
#endif // MAINWINDOW_H
