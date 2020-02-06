#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
    void KeyPressedEvent(QKeyEvent* event);

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeNumberSign();
    void ClearButton();
    void ClearAllButton();
    void PointButton();
    void DeleteButton();
    void MemoryClear();
    void MemoryStore();
    void MemoryAdd();
    void MemorySub();
    void MemoryGet();

};
#endif // CALCULATOR_H
