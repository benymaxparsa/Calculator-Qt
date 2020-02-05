#include "calculator.h"
#include "ui_calculator.h"

double calval = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calval));
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; ++i)
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearButton()));
    connect(ui->ClearAll, SIGNAL(released()), this, SLOT(ClearAllButton()));
    connect(ui->Point, SIGNAL(released()), this, SLOT(PointButton()));
    connect(ui->Delete, SIGNAL(released()), this, SLOT(DeleteButton()));


}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if (((displayVal.toDouble() == 0)|| (displayVal.toDouble() == 0.0)) && !displayVal.contains("." , Qt::CaseInsensitive))
    {
        ui->Display->setText(butVal);
    }
    else
    {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed()
{
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calval = displayVal.toDouble();
    QPushButton* button = (QPushButton* )sender();
    QString butVal = button->text();
    if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
    {
        multTrigger = true;
    }
    else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }
    else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0)
    {
        subTrigger = true;
    }
    ui->Display->setText("");

}

void Calculator::EqualButton()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if (addTrigger || subTrigger || divTrigger || multTrigger)
    {
        if (addTrigger)
        {
            solution = calval + dblDisplayVal;
        }
        else if (subTrigger)
        {
            solution = calval - dblDisplayVal;
        }
        else if (multTrigger)
        {
            solution = calval * dblDisplayVal;
        }
        else
        {
            solution = calval / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));

}

void Calculator::ChangeNumberSign()
{
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if (reg.exactMatch(displayVal))
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }

}

void Calculator::ClearButton()
{
    ui->Display->setText("");
}

void Calculator::ClearAllButton()
{
    calval = 0.0;
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    ui->Display->setText(QString::number(calval));
}

void Calculator::PointButton()
{
    QString displayVal = ui->Display->text();
    ui->Display->setText(displayVal+".");
}

void Calculator::DeleteButton()
{
    QString displayVal = ui->Display->text();
    displayVal.chop(1);
    ui->Display->setText(displayVal);
}
