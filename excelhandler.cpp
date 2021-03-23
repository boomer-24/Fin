#include "excelhandler.h"

ExcelHandler::ExcelHandler(QObject *parent) : QObject(parent)
{
    this->excelApp_ = new QAxObject("Excel.Application", 0);
    this->workbooks_ = this->excelApp_->querySubObject("Workbooks");
    
    this->mNumberMonth_.insert(1, "января");
    this->mNumberMonth_.insert(2, "февраля");
    this->mNumberMonth_.insert(3, "марта");
    this->mNumberMonth_.insert(4, "апреля");
    this->mNumberMonth_.insert(5, "мая");
    this->mNumberMonth_.insert(6, "июня");
    this->mNumberMonth_.insert(7, "июля");
    this->mNumberMonth_.insert(8, "августа");
    this->mNumberMonth_.insert(9, "сентября");
    this->mNumberMonth_.insert(10, "октября");
    this->mNumberMonth_.insert(11, "ноября");
    this->mNumberMonth_.insert(12, "декабря");
}

ExcelHandler::ExcelHandler(QObject *parent, const QString &_excelPath)
{
    Q_UNUSED(parent)
    this->excelApp_ = new QAxObject("Excel.Application", 0);
    this->workbooks_ = this->excelApp_->querySubObject("Workbooks");
    
    this->mNumberMonth_.insert(1, "января");
    this->mNumberMonth_.insert(2, "февраля");
    this->mNumberMonth_.insert(3, "марта");
    this->mNumberMonth_.insert(4, "апреля");
    this->mNumberMonth_.insert(5, "мая");
    this->mNumberMonth_.insert(6, "июня");
    this->mNumberMonth_.insert(7, "июля");
    this->mNumberMonth_.insert(8, "августа");
    this->mNumberMonth_.insert(9, "сентября");
    this->mNumberMonth_.insert(10, "октября");
    this->mNumberMonth_.insert(11, "ноября");
    this->mNumberMonth_.insert(12, "декабря");
}

ExcelHandler::~ExcelHandler()
{
    this->workbooks_->dynamicCall("Close()");
    this->excelApp_->dynamicCall("Quit()");
    delete this->excelApp_;
}

void ExcelHandler::Read(const QString _excelPath)
{
    QString strFileName("logReadFile_");
    strFileName.append(_excelPath.split("/").last().split(".").first().append(".txt"));
    QFile logFile(strFileName);
    
    //    if (logFile.open(QIODevice::WriteOnly))
    //        logFile.write("\n");
    
    QString bankName = _excelPath.split("/").last();
    //    if (bankName.contains("остатки") && bankName.contains(".xlsx"))
    //    {
    this->workbook_ = this->workbooks_->querySubObject("Open(const QString&)", _excelPath);
    bankName.remove(QRegExp("[Оо][Сс][Тт][Аа][Тт][Кк][Ии] "));
    bankName.remove(bankName.indexOf("счета"), bankName.length() - bankName.indexOf("счета"));
    if (bankName.at(bankName.size() - 1) == ' ')
        bankName.remove(bankName.size() - 1);
    QAxObject* sheets = this->workbook_->querySubObject("Worksheets");
    int countSheets = sheets->property("Count").toInt();
    OneBankAccounts bank(bankName); //                       ДО СОЗДАНИЯ ЭТОГО ОБЪЕКТА ПРОВЕРИТЬ ВНУТРЕННОСТИ ДОКУМЕНТА ПО ИМЕНАМ СТОЛБЦОВ
    
    QString countSheet("count sheet: ");
    countSheet.append(QString::number(countSheets));
    if (logFile.isOpen())
        logFile.write(countSheet.toLocal8Bit().append("\n"));
    
    for(int i = 1; i <= countSheets; i++)
    {
        QAxObject* sheet = sheets->querySubObject("Item(int)", i);
        QAxObject* usedRange = sheet->querySubObject("UsedRange");
        QAxObject* rows = usedRange->querySubObject("Rows");
        int countRows = rows->property("Count").toInt();
        int rowNumber;
        bool isAccountClosed(false);
        for (rowNumber = countRows; rowNumber > 2; rowNumber--)
        {
            QVariant val1 = sheet->querySubObject("Cells(int, int)", rowNumber, 1)->property("Value");
            QString str1 = val1.toString();
            
            if (str1.contains("закрыт") || str1.contains("ЗАКРЫТ"))
            {
                isAccountClosed = true;
                break;
            }
            
            QVariant val4 = sheet->querySubObject("Cells(int, int)", rowNumber, 4)->property("Value");
            QVariant val5 = sheet->querySubObject("Cells(int, int)", rowNumber, 5)->property("Value");
            QString str4 = val4.toString();
            QString str5 = val5.toString();
            
            if (str4.isEmpty() && str5.isEmpty())
                continue;
            else
                break;
        }
        if (isAccountClosed)
            continue;
        
        if (rowNumber == 2)
            rowNumber++;
        
        QAxObject* cellAccountNumber = sheet->querySubObject("Cells(int, int)", rowNumber, 2);
        QVariant valAccountNumber = cellAccountNumber->property("Value");
        QAxObject* cellTarget = sheet->querySubObject("Cells(int, int)", rowNumber, 6);
        QVariant valTarget = cellTarget->property("Value");
        
        QString str(valAccountNumber.toString());
        str.append(" - toDouble -> ");
        str.append(QString::number(valTarget.toDouble(), 'f', 2));
        str.append(" - toString -> ");
        str.append(QString(valTarget.toString()));
        if (logFile.isOpen())
            logFile.write(str.toLocal8Bit().append("\n"));
        
        double getS = valTarget.toDouble();
        double s = getS * std::pow(10, this->coefficientHead_);

        bank.Push(QPair<QString, double>(valAccountNumber.toString(), s));
    }
    if (bank.getNumberOfAccounts())
        this->vBankAccounts_.push_back(bank);
    
    if (logFile.isOpen())
        logFile.close();
    
    this->workbook_->dynamicCall("Save()");
    this->workbook_->dynamicCall("Close()");
    //    }
}

void ExcelHandler::ReadBrunchesFile(const QString _excelPath)
{
//    QString strFileName("logReadBrunchesFile_");
//    strFileName.append(_excelPath.split("/").last().split(".").first().append(".txt"));
//    QFile logFile(strFileName);
    
    //    if (logFile.open(QIODevice::WriteOnly))
    //        logFile.write("\n");
    
    QString name = _excelPath.split("/").last();
    //    QString name = _excelPath.split("/").last().toLower();
    //    if (name.contains("остатки") && name.contains("филиалы") && name.contains(".xlsx"))
    //    {
    this->workbook_ = this->workbooks_->querySubObject("Open(const QString&)", _excelPath);
    QAxObject* sheets = this->workbook_->querySubObject("Worksheets");
    int countSheets = sheets->property("Count").toInt();
    
    QString countSheet("count sheet: ");
    countSheet.append(QString::number(countSheets));
//    if (logFile.isOpen())
//        logFile.write(countSheet.toLocal8Bit().append("\n"));
    
    for(int i = 1; i <= countSheets; i++)
    {
        QAxObject* sheet = sheets->querySubObject("Item(int)", i);
        QAxObject* usedRange = sheet->querySubObject("UsedRange");
        QAxObject* rows = usedRange->querySubObject("Rows");
        int countRows = rows->property("Count").toInt();
        int rowNumber;
        
        for (rowNumber = countRows; rowNumber > 2; rowNumber--)
        {
            QVariant column_5 = sheet->querySubObject("Cells(int, int)", rowNumber, 5)->property("Value");
            QVariant column_6 = sheet->querySubObject("Cells(int, int)", rowNumber, 6)->property("Value");
            QString str5 = column_5.toString();
            QString str6 = column_6.toString();
            
            if (str5.isEmpty() && str6.isEmpty())
                continue;
            else
                break;
        }
        
        QAxObject* cellAccountNumber = sheet->querySubObject("Cells(int, int)", rowNumber, 3);
        QVariant valAccountNumber = cellAccountNumber->property("Value");
        QString accNumber = valAccountNumber.toString();
        accNumber.remove("№");
        
        QAxObject* cellReminder = sheet->querySubObject("Cells(int, int)", rowNumber, 7);
        QVariant valReminder = cellReminder->property("Value");

        double getS = valReminder.toDouble();
        double s = getS * std::pow(10, this->coefficientBrunch_);
//        QString reminder = QString::number(s, 'f', 2);
        
//        QString str(accNumber);
//        str.append(" - ");
//        str.append(reminder);
//        if (logFile.isOpen())
//            logFile.write(str.toLocal8Bit().append("\n"));
        
//        this->vBrunchesFromExcel_.push_back(QPair<QString, QString>(accNumber, reminder));
        this->vBrunchesFromExcel_.push_back(QPair<QString, double>(accNumber, s));
    }
    
//    if (logFile.isOpen())
//        logFile.close();
    
    this->workbook_->dynamicCall("Save()");
    this->workbook_->dynamicCall("Close()");
    //    }
}

void ExcelHandler::CreateRemaindersXLSFromTemplate(QString _savePath)
{
    this->FromVectorToMap();

    QString appPath(QCoreApplication::applicationDirPath());
    appPath.append("/").append("template.xls");

    QFile src(appPath);
    if (src.exists())
    {
        if (!QFile::exists(_savePath))
            if (src.copy(_savePath))
                qDebug() << "copy_true";
            else
                qDebug() << "copy_false";
        else
            qDebug() << "lol";

        QString textTitle("Входящий остаток денежных средств на счетах на ");
        QDate today(QDate::currentDate());
        textTitle.append(QString::number(today.day())).append(" ").append(this->MonthName(today.month())).append(" ").append(QString::number(today.year())).append(" года");


        this->workbook_ = this->workbooks_->querySubObject("Open(const QString&)", _savePath);
        QAxObject* sheets = this->workbook_->querySubObject("Worksheets");
        int countSheets = sheets->property("Count").toInt();
        for(int i = 1; i <= countSheets; i++)
        {
            QAxObject* sheet = sheets->querySubObject("Item(int)", i);

            QAxObject* usedRange = sheet->querySubObject("UsedRange");
            QAxObject* rows = usedRange->querySubObject("Rows");
            int countRows = rows->property("Count").toInt();
            if (countRows > 1)
            {
                QAxObject* cellInsTitle = sheet->querySubObject("Cells(int, int)", 1, 1);
                cellInsTitle->setProperty("Value", QVariant(textTitle));
            }
            for (int rowNumber = 1; rowNumber  < countRows; rowNumber++)
            {
                QVariant val = sheet->querySubObject("Cells(int, int)", rowNumber, 2)->property("Value");
                QString str = val.toString();
                if (this->mapAccountReminder_.contains(str))
                {
                    double d = this->mapAccountReminder_.value(str);
                    QAxObject* cellIns = sheet->querySubObject("Cells(int, int)", rowNumber, 3);
                    cellIns->setProperty("Value", QVariant(d));
                }
            }
        }
        this->workbook_->dynamicCall("Save()");
        this->workbook_->dynamicCall("Close()");
    }
    else
        qDebug() << "template not exist";
}

QString ExcelHandler::MakeTextForMerge(int _row)
{
    QString base("A");
    base.append(QString::number(_row).append(":").append("C").append(QString::number(_row)));
    return base;
}

QString ExcelHandler::MonthName(int _n)
{
    return this->mNumberMonth_.value(_n);
}

void ExcelHandler::ClearBankAccounts()
{
    this->vBankAccounts_.clear();
}

void ExcelHandler::FromVectorToMap()
{
    this->mapAccountReminder_.clear();
    for (int i = 0; i < this->vBankAccounts_.size(); i++)
    {
        const QVector<QPair<QString, double>> &vAccs(this->vBankAccounts_.at(i).vAccountNumberAndRemainder());
        for (int j = 0; j < vAccs.size(); j++)
        {
            this->mapAccountReminder_.insert(vAccs.at(j).first, vAccs.at(j).second);
        }
    }

    foreach (auto _pair, this->vBrunchesFromExcel_)
    {
        this->mapAccountReminder_.insert(_pair.first, _pair.second);
    }
}

void ExcelHandler::setCoefficientHead(int _coefficientHead)
{
    coefficientHead_ = _coefficientHead;
}

void ExcelHandler::setCoefficientBrunch(int _coefficientBrunch)
{
    coefficientBrunch_ = _coefficientBrunch;
}
