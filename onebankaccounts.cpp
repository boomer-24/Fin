#include "onebankaccounts.h"

OneBankAccounts::OneBankAccounts()
{
    qDebug() << "Default constructor";
}

OneBankAccounts::OneBankAccounts(QString _bankName)
{
    this->bankName_ = _bankName;
}

void OneBankAccounts::Push(const QPair<QString, double> _pair)
{
    this->vAccountNumberAndRemainder_.push_back(_pair);
}

QVector<QPair<QString, double> > OneBankAccounts::vAccountNumberAndRemainder() const
{
    return vAccountNumberAndRemainder_;
}

QString OneBankAccounts::bankName() const
{
    return bankName_;
}

int OneBankAccounts::getNumberOfAccounts() const
{
    return this->vAccountNumberAndRemainder_.size();
}
