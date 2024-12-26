#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QStringList>
#include <QTabWidget>
#include <QGridLayout>

const QString TASK_TEST = "Тестовая";
const QString TASK_MAIN = "Основная";


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
/*
 * Конструктор класса MainWindow.
 *
 * Инициализирует пользовательский интерфейс, создает виджеты,
 * устанавливает связи между сигналами и слотами, применяет стили.
 *
 * Параметры:
 * - parent: Указатель на родительский виджет.
 */
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    chartView1 = new QCustomPlot(this);
    chartView2 = new QCustomPlot(this);
    tableWidget = new QTableWidget(this);
    taskComboBox = new QComboBox(this);
    gridSizeEdit = new QLineEdit(this);
    outputTextBox = new QTextEdit(this);
    calculateButton = new QPushButton("Рассчитать", this);
    taskComboBox->addItem(TASK_TEST);
    taskComboBox->addItem(TASK_MAIN);

    QWidget *mainContentWidget = new QWidget(this);
    QVBoxLayout *mainContentLayout = new QVBoxLayout(mainContentWidget);


    QWidget *chartsWidget = new QWidget(this);
    QGridLayout *chartsLayout = new QGridLayout(chartsWidget);
    chartView1->setMinimumSize(400, 300);
    chartView2->setMinimumSize(400, 300);
    chartView1->setMaximumSize(600, 450);
    chartView2->setMaximumSize(600, 450);
    chartsLayout->addWidget(chartView1, 0, 0);
    chartsLayout->addWidget(chartView2, 0, 1);
    chartsWidget->setLayout(chartsLayout);
    mainContentLayout->addWidget(chartsWidget, 2);
    mainContentLayout->addWidget(tableWidget, 1);

    QTabWidget *tabWidget = new QTabWidget(this);

    QWidget *reportWidget = new QWidget(this);
    QVBoxLayout *reportLayout = new QVBoxLayout(reportWidget);
    reportLayout->addWidget(outputTextBox);
    reportWidget->setLayout(reportLayout);

    tabWidget->addTab(mainContentWidget, "Данные");
    tabWidget->addTab(reportWidget, "Справка");

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainWindowLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(new QLabel("Задача:"));
    inputLayout->addWidget(taskComboBox);
    inputLayout->addWidget(new QLabel("Размер сетки:"));
    inputLayout->addWidget(gridSizeEdit);

    mainWindowLayout->addLayout(inputLayout);
    mainWindowLayout->addWidget(calculateButton);
    mainWindowLayout->addWidget(tabWidget);

    setCentralWidget(centralWidget);

    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculate);
    calculateButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   border: none;"
        "   color: white;"
        "   padding: 8px 16px; /* Уменьшаем отступы */"
        "   text-align: center;"
        "   text-decoration: none;"
        "   display: inline-block;"
        "   font-size: 14px; /* Уменьшаем размер шрифта */"
        "   margin: 2px;"
        "   cursor: pointer;"
        "   border-radius: 4px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
        );

    outputTextBox->setStyleSheet(
        "QTextEdit {"
        "   background-color: #FAF8F6; /* Белый фон */"
        "   border: 1px solid #ddd; /* Оставляем или убираем рамку по желанию */"
        "   font-family: 'Arial', 'Verdana', sans-serif; /* Приятный шрифт без засечек */"
        "   padding: 6px;"
        "   color: #000000; /* Черный цвет текста */"
        "   font-size: 16px; /* Размер шрифта */"
        "   line-height: 1.4; /* Межстрочный интервал */"
        "}"
        );
}


void MainWindow::createOutputElements()
/*
 * Метод createOutputElements.
 *
 * Устанавливает placeholder для поля ввода размера сетки и делает
 * текстовое поле вывода доступным только для чтения.
 */
{

    gridSizeEdit->setPlaceholderText("Введите размер");
    outputTextBox->setReadOnly(true);
}


MainWindow::~MainWindow()
/*
 * Деструктор класса MainWindow.
 *
 * Освобождает выделенную память для виджетов.
 */
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
/*
 * Метод calculate.
 *
 * Выполняет расчеты на основе введенных пользователем данных,
 * обновляет графики, таблицу и формирует отчет.
 */
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

    QList<double> x_list;
    for (double val : shema.x) {
        x_list.append(val);
    }

    QList<double> v_list;
    for (double val : shema.v) {
        v_list.append(val);
    }

    QList<double> v2_list;
    for (double val : shema.v2) {
        v2_list.append(val);
    }

    QList<double> diff_list;
    for (double val : shema.diff) {
        diff_list.append(val);
    }

    chartView1->clearGraphs();
    QCPGraph *graph1_v = chartView1->addGraph();
    QCPGraph *graph1_v2 = chartView1->addGraph();

    graph1_v->setData(QVector<double>::fromList(x_list), QVector<double>::fromList(v_list));
    graph1_v2->setData(QVector<double>::fromList(x_list), QVector<double>::fromList(v2_list));

    QPen pen;
    pen.setColor(Qt::red);
    graph1_v2->setPen(pen);
    chartView1->xAxis->setLabel("x");
    chartView1->yAxis->setLabel("v(x), v2(x)");
    graph1_v->setName("v(x)");
    graph1_v2->setName("v2(x)");
    chartView1->legend->setVisible(true);
    chartView1->rescaleAxes();
    chartView1->replot();

    chartView2->clearGraphs();
    QCPGraph *graph2_diff = chartView2->addGraph();

    graph2_diff->setData(QVector<double>::fromList(x_list), QVector<double>::fromList(diff_list));

    chartView2->yAxis->setNumberFormat("g");
    chartView2->yAxis->setNumberPrecision(1);
    QLocale locale = QLocale::c();
    chartView2->xAxis->setLabel("x");
    chartView2->yAxis->setLabel("|v(x) - v2(x)|");
    chartView2->rescaleAxes();
    chartView2->replot();

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
        QTableWidgetItem *xItem = new QTableWidgetItem(QString::number(shema.x[i], 'f', 6));
        QTableWidgetItem *vItem = new QTableWidgetItem(QString::number(shema.v[i], 'f', 10));
        QTableWidgetItem *v2Item = new QTableWidgetItem(QString::number(shema.v2[i], 'f', 10));
        QTableWidgetItem *diffItem = new QTableWidgetItem(QString::number(shema.diff[i], 'e', 6));

        tableWidget->setItem(i, 0, xItem);
        tableWidget->setItem(i, 1, vItem);
        tableWidget->setItem(i, 2, v2Item);
        tableWidget->setItem(i, 3, diffItem);
    }


    QStringList report;
    report << QString("Тип задачи: %1").arg(taskType);

    report << QString("Для решения задачи использована равномерная сетка с числом разбиений n = %1;").arg(n);
    report << QString("Задача должна быть решена с погрешностью не более ε = 0.5⋅10⁻⁶;");

    double maxDiff = 0.0;
    double maxX = 0.0;


    for (int i = 0; i < shema.diff.size(); ++i) {
        if (shema.diff[i] > maxDiff) {
            maxDiff = shema.diff[i];
            maxX = shema.x[i];
        }
    }

    QString formattedMaxDiff = locale.toString(maxDiff, 'e', 1);

    report << QString("Задача решена с погрешностью ε1 = %1;").arg(formattedMaxDiff);

    QString formattedMaxX = locale.toString(maxX, 'f', 6);
    report << QString("Максимальное отклонение аналитического и численного решений наблюдается в точке x = %1").arg(formattedMaxX);

    outputTextBox->clear();
    outputTextBox->append(report.join("\n"));
}
