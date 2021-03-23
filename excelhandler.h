#ifndef EXCELHANDLER_H
#define EXCELHANDLER_H

#include "onebankaccounts.h"
#include "brunch.h"
#include <QObject>
#include <QAxObject>
#include <QDebug>
#include <QDate>
#include <QColor>
#include <QRegExp>
#include <QFile>
#include <math.h>
#include <QMap>
#include <QCoreApplication>

class ExcelHandler : public QObject
{
    Q_OBJECT
private:
    QAxObject* excelApp_;
    QAxObject* workbooks_;
    QAxObject* workbook_;
    QVector<OneBankAccounts> vBankAccounts_;
    QMap<int, QString> mNumberMonth_;
    QVector<QPair<QString, double>> vBrunchesFromExcel_;
    int coefficientHead_;
    int coefficientBrunch_;

    QMap<QString, double> mapAccountReminder_;

public:
    explicit ExcelHandler(QObject *parent = nullptr);
    ExcelHandler(QObject *parent, const QString& _excelPath);
    ~ExcelHandler();
    void Read(const QString _excelPath);
    void ReadBrunchesFile(const QString _excelPath);
    void CreateRemaindersXLSFromTemplate(QString _savePath);
    QString MakeTextForMerge(int _row);
    QString MonthName(int _n);
    void ClearBankAccounts();

    void FromVectorToMap();
    void setCoefficientHead(int _coefficientHead);
    void setCoefficientBrunch(int _coefficientBrunch);
};

#endif // EXCELHANDLER_H
