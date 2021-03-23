#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <QString>
#include <QVector>
#include <QDebug>

class OneBankAccounts
{
private:
    QString bankName_;
    QVector<QPair<QString, double>> vAccountNumberAndRemainder_;

public:
    OneBankAccounts();
    OneBankAccounts(QString _bankName);
    void Push(const QPair<QString, double> _pair);
    QVector<QPair<QString, double>> vAccountNumberAndRemainder() const;
    QString bankName() const;
    int getNumberOfAccounts() const;
};

#endif // BANKACCOUNT_H
