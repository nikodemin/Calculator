#pragma once

#include <QWidget>
#include <QStack>
#include <QLCDNumber>
#include <QPushButton>
#include <QLabel>

class Calculator : public QWidget
{
    Q_OBJECT

    QLCDNumber*         m_plcd;
    QStack<QString>    m_stk;
    QString                     m_strDisplay;
    QLabel *                   m_msgBox;

public:
    Calculator(QWidget* parent = nullptr, QLabel* msgBox= nullptr);

    QPushButton* CreateButton(const QString& str);
    void Calculate();
    void printStack();          // print stack for debug

public slots:
    void slotButtonClicked();
};
