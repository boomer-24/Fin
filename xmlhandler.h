#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include "brunch.h"
#include <QtXml>

class XmlHandler
{
public:
    XmlHandler();
    ~XmlHandler();
    void InitializeBrunches(const QString& _xmlPath);
    void SetNumberFormat(const QString& _xmlPath);
    void SetCoefficient(const QString& _xmlPath);
    void SetOrder(const QString& _xmlPath);
    void SetStrangeAccounts(const QString& _xmlPath);
    void SetLinks(const QString& _xmlPath);
    void TraverseNodeNumberFormat(const QDomNode &_node);
    void TraverseNodeShift(const QDomNode &_node);
    void TraverseNodeOrder(const QDomNode &_node);
    void TraverseNode(const QDomNode &_node);
    void TraverseNodeStrangeAccount(const QDomNode &_node);
    void TraverseNodeLink(const QDomNode &_node);
    QVector<Brunch> vBrunches() const;
    void SaveXmlBrunches(const QString& _saveXmlPath, const QVector<Brunch>& _vBrunches) const;

    QString numberFormatRur() const;
    QString numberFormatUsd() const;
    QString numberFormatEur() const;

    int coefficientHead() const;
    int coefficientBrunch() const;

    QVector<QString> vOrder() const;

    QVector<QPair<QString, QString> > vStrangeAccounts() const;
    QVector<QPair<QString, QString> > vPairAccountLink() const;


private:
    QVector<Brunch> vBrunchesFromXML_;
    QString numberFormatRur_;
    QString numberFormatUsd_;
    QString numberFormatEur_;
    int coefficientHead_;
    int coefficientBrunch_;
    QVector<QString> vOrder_;
    QVector<QPair<QString, QString>> vStrangeAccounts_;
    QVector<QPair<QString, QString>> vPairAccountLink_;
};

#endif // XMLHANDLER_H
