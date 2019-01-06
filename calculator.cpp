#include "calculator.h"
#include <QLayout>
#include <iostream>

Calculator::Calculator(QWidget *parent, QLabel * msgBox) : QWidget(parent), m_msgBox(msgBox)
{
    m_plcd  = new QLCDNumber(12);
    m_plcd  -> setSegmentStyle(QLCDNumber::Flat);
    m_plcd -> setMinimumSize(150, 50);
    m_msgBox->setText("empty");
    m_msgBox->setAlignment(Qt::AlignCenter);

    QChar  aButtons[4][4] = {{'7', '8', '9', '/'},
                                              {'4', '5', '6', '*'},
                                              {'1', '2', '3', '-'},
                                              {'0', '.', '=', '+'}};
    QGridLayout*  pTopLayout = new QGridLayout;

    pTopLayout -> addWidget(m_plcd, 0, 0, 1, 4);
    pTopLayout ->addWidget (CreateButton("CE") , 1, 3);

    for (int i =0; i<4; ++i)
        for (int j = 0; j<4; ++j)
        {
            pTopLayout -> addWidget(CreateButton(aButtons[i][j]), i+2, j);
        }

   setLayout(pTopLayout);
}

QPushButton* Calculator:: CreateButton(const QString& str)
{
    QPushButton* pcmd = new QPushButton(str);
    pcmd -> setMinimumSize(40,40);
    connect(pcmd, &QPushButton::clicked, this, &Calculator::slotButtonClicked);

    return pcmd;
}

void Calculator:: Calculate()
{
    double dOperand2 = m_stk.pop().toDouble();
    QString strOperation = m_stk.pop();
    double dOperand1 = m_stk.pop().toDouble();
    double dResult = 0;

    if ( strOperation == "+")
        dResult = dOperand1 + dOperand2;
    else if ( strOperation == "-")
        dResult = dOperand1 - dOperand2;
    else if ( strOperation == "*")
        dResult = dOperand1 * dOperand2;
    else if ( strOperation == "/")
        dResult = dOperand1 / dOperand2;

    m_plcd->display(dResult);
}

void Calculator:: printStack()
{
    QString res;
    for (auto s : m_stk)
        res+=s+" : ";
    m_msgBox->setText(res);
}

void Calculator:: slotButtonClicked()
{
    QString str = ((QPushButton*) sender()) ->text();

    if ( str == "CE")
    {
        printStack();
        m_stk.clear();
        m_strDisplay = "";
        m_plcd ->display("0");

        return;
    }

    if (str.contains(QRegExp("[0-9]")))
    {
        m_strDisplay +=  str;
        m_plcd->display(m_strDisplay.toDouble());
    }
    else if (str==".")
    {
        m_strDisplay +=  str;
        m_plcd->display(m_strDisplay);
    }
    else
    {
        if (m_stk.count() >= 2)
        {
            m_stk.push(QString().setNum(m_plcd->value()));
            Calculate();

            m_stk.clear();
            m_stk.push(QString().setNum(m_plcd->value()));
            printStack();
        }
        else
        {
            m_stk.push(QString ().setNum(m_plcd->value ())) ;
            m_stk.push(str);
            m_strDisplay = "";
            m_plcd->display ( "0" ) ;
        }
    }

}
