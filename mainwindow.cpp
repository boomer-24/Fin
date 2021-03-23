#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(250, 80);
    this->setMaximumSize(750, 120);
    this->setWindowTitle("Fin138");

    XmlHandler xh;
    xh.SetCoefficient("shift.xml");
    this->coefficientHead_ = xh.coefficientHead();
    this->coefficientBrunch_ = xh.coefficientBrunch();
}

MainWindow::~MainWindow()
{
    delete ui;

    //ДОБАВИТЬ ЗАКРЫТИЕ EXCEL ЕСЛИ НЕ ШТАТНО ВСЕ
}

void MainWindow::TraverseDir(QString _dirPath)
{
    _dirPath.remove("\"");
    QDir dir(_dirPath);
    QStringList filters;
    filters.append("*.xlsx");
    filters.append("*.xls");
    QStringList files(dir.entryList(filters));
    files.removeOne(".");
    files.removeOne("..");

    ExcelHandler excelHandler;
    excelHandler.setCoefficientHead(this->coefficientHead_);
    excelHandler.setCoefficientBrunch(this->coefficientBrunch_);

    for (QString document : files)
    {
        QString doc = document;
        doc = doc.toLower();
        if (doc.contains("остатки") && doc.contains("филиал"))
        {
            excelHandler.ReadBrunchesFile(dir.path().append("/").append(document));
        }
        else if (doc.contains("остатки") && !doc.contains("остатки в банках"))
        {
            excelHandler.Read(dir.path().append("/").append(document));
        }
    }
    QString savePath(_dirPath);
    savePath.append("/").append("Остатки в банках ");
    savePath.append(QDateTime::currentDateTime().toString("yyyy-MM-dd").append("_").append(QDateTime::currentDateTime().time().toString("HH-mm-ss"))).append(".xls");

    excelHandler.CreateRemaindersXLSFromTemplate(savePath);
}

void MainWindow::on_pushButton_run_clicked()
{
    this->TraverseDir(this->dirPath);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    this->ui->label->setFixedWidth(this->ui->centralwidget->width() - 20);
    this->ui->pushButton_template->move(this->width() - this->ui->pushButton_template->width() - 10, this->ui->pushButton_template->y());
}

void MainWindow::setDirPath(const QString &value)
{
    this->dirPath = value;
    this->ui->label->setText(value);
}

bool MainWindow::isOnlySpaces(const QString &_string) const
{
    foreach (const QChar &character, _string)
    {
        if (character.isSpace())
            continue;
        else
            return false;
    }
    return true;
}

void MainWindow::on_pushButton_template_clicked()
{
    QProcess process(this);
    QString batPath(QCoreApplication::applicationDirPath());
    batPath.append("/").append("template.bat");
    process.startDetached(batPath);
}
