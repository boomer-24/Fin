#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "xmlhandler.h"
#include "excelhandler.h"
#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QStringList>
#include <QDateTime>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void TraverseDir(QString _dirPath);
    void setDirPath(const QString &value);
    bool isOnlySpaces(const QString& _string) const;

private slots:
    void on_pushButton_run_clicked();
    void on_pushButton_template_clicked();

private:
    Ui::MainWindow *ui;
    QString dirPath;

    QString numberFormatRur_;
    QString numberFormatUsd_;
    QString numberFormatEur_;
    int coefficientHead_;
    int coefficientBrunch_;

    QVector<QString> vOrder_;
    QVector<QPair<QString, QString>> vStrangeAccounts_;
    QVector<QPair<QString, QString>> vPairAccountLinks_;


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H
