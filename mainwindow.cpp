#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QStringList>
#include <QTabWidget> // Для вкладок
#include <QGridLayout> // Для расположения графиков

const QString TASK_TEST = "Тестовая";
const QString TASK_MAIN = "Основная";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chartView1 = new QCustomPlot(this);
    chartView2 = new QCustomPlot(this);
    tableWidget = new QTableWidget(this);
    taskComboBox = new QComboBox(this);
    gridSizeEdit = new QLineEdit(this);
    outputTextBox = new QTextEdit(this);
    calculateButton = new QPushButton("Рассчитать", this);
    taskComboBox->addItem(TASK_TEST);
    taskComboBox->addItem(TASK_MAIN);
    // *** Главный виджет для графиков и таблицы ***
    QWidget *mainContentWidget = new QWidget(this);
    QVBoxLayout *mainContentLayout = new QVBoxLayout(mainContentWidget);

    // Виджет для графиков
    QWidget *chartsWidget = new QWidget(this);
    QGridLayout *chartsLayout = new QGridLayout(chartsWidget);
    chartView1->setMinimumSize(400, 300);
    chartView2->setMinimumSize(400, 300);
    chartView1->setMaximumSize(600, 450);
    chartView2->setMaximumSize(600, 450);
    chartsLayout->addWidget(chartView1, 0, 0);
    chartsLayout->addWidget(chartView2, 0, 1);
    chartsWidget->setLayout(chartsLayout);

    // Добавляем графики и таблицу в главный виджет
    mainContentLayout->addWidget(chartsWidget);
    mainContentLayout->addWidget(tableWidget);

    // *** TabWidget для вкладок ***
    QTabWidget *tabWidget = new QTabWidget(this);

    // Виджет для справки
    QWidget *reportWidget = new QWidget(this);
    QVBoxLayout *reportLayout = new QVBoxLayout(reportWidget);
    reportLayout->addWidget(outputTextBox);
    reportWidget->setLayout(reportLayout);

    // Добавляем вкладки в TabWidget
    tabWidget->addTab(mainContentWidget, "Данные"); // Главная вкладка с графиками и таблицей
    tabWidget->addTab(reportWidget, "Справка");

    // Главный layout окна
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainWindowLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(new QLabel("Задача:"));
    inputLayout->addWidget(taskComboBox);
    inputLayout->addWidget(new QLabel("Размер сетки:"));
    inputLayout->addWidget(gridSizeEdit);

    mainWindowLayout->addLayout(inputLayout);
    mainWindowLayout->addWidget(calculateButton);
    mainWindowLayout->addWidget(tabWidget); // Добавляем TabWidget в главный layout окна

    setCentralWidget(centralWidget);

    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculate);
}


void MainWindow::createOutputElements()
{

    gridSizeEdit->setPlaceholderText("Введите размер");
    outputTextBox->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chartView1;
    delete chartView2;
    delete tableWidget;
    delete taskComboBox;
    delete gridSizeEdit;
    delete outputTextBox;
    delete calculateButton;
}

void MainWindow::calculate()
{
    bool ok;
    int n = gridSizeEdit->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Ошибка ввода", "Некорректный размер сетки.");
        return;
    }

    QString taskType = taskComboBox->currentText();

    if (taskType == TASK_TEST) {
        shema.calculate_test(n);
    } else if (taskType == TASK_MAIN) {
        shema.calculate_main(n);
    }

    // Очистка графиков
    chartView1->clearGraphs();
    chartView2->clearGraphs();

    // Создание графиков (как в предыдущем примере)
    QCPGraph *graph1 = chartView1->addGraph();
    // ... (код для graph1)
    chartView1->replot();

    QCPGraph *graph2 = chartView2->addGraph();
    // ... (код для graph2)
    chartView2->replot();

    // Очистка и настройка таблицы
    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    tableWidget->setRowCount(n + 1);
    tableWidget->setColumnCount(4);
    QStringList headerLabels;

    if (taskType == TASK_TEST) {
        headerLabels << "x" << "v(x)" << "u(x)"<<"|v(x)-u(x)|";
    }else
    {
        headerLabels << "x" << "v(x)" << "v2(x)"<<"|v(x)-v2(x)|";
    }
    tableWidget->setHorizontalHeaderLabels(headerLabels);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < n + 1; ++i) {
        QTableWidgetItem *xItem = new QTableWidgetItem(QString::number(shema.x[i]));
        QTableWidgetItem *vItem = new QTableWidgetItem(QString::number(shema.v[i]));
        QTableWidgetItem *v2Item = new QTableWidgetItem(QString::number(shema.v2[i]));
        QTableWidgetItem *diffItem = new QTableWidgetItem(QString::number(shema.diff[i]));

        tableWidget->setItem(i, 0, xItem);
        tableWidget->setItem(i, 1, vItem);
        tableWidget->setItem(i, 2, v2Item);
        tableWidget->setItem(i, 3, diffItem);
    }

    // *** Формирование справки ***
    QStringList report; // Используем QStringList для удобства формирования строк

    report << QString("Тип задачи: %1").arg(taskType);
    report << QString("Размер сетки: %2").arg(n);

    // Добавляем информацию о графиках (пример)
    report << QString("График 1: Парабола y = x^2");
    report << QString("График 2: Синусоида y = sin(πx)");

    // Добавляем информацию о таблице (пример)
    report << QString("Таблица: %1 строк, %2 столбцов").arg(tableWidget->rowCount()).arg(tableWidget->columnCount());

    // Очищаем outputTextBox перед выводом новой справки
    outputTextBox->clear();

    // Выводим справку в outputTextBox
    outputTextBox->append(report.join("\n")); // Объединяем строки с помощью символа новой строки
}
