#include "xmlhandler.h"

XmlHandler::XmlHandler()
{
    this->coefficientHead_ = 0;
    this->coefficientBrunch_ = 0;
}

XmlHandler::~XmlHandler()
{

}

void XmlHandler::InitializeBrunches(const QString &_xmlPath)
{
    QDomDocument domDoc;
    QString appPath(QCoreApplication::applicationDirPath());
    appPath.append("/").append(_xmlPath);
    //    QFile file(_xmlPath);
    QFile file(appPath);
    if(file.open(QIODevice::ReadOnly))
    {
        if(domDoc.setContent(&file))
        {
            QDomElement domElement = domDoc.documentElement();
            QDomNode node = domElement.firstChild();
            TraverseNode(node);
        }
        file.close();
    } else qDebug() << "XML brunch NOT OPEN " << appPath;
}

void XmlHandler::SetNumberFormat(const QString &_xmlPath)
{
    QDomDocument domDoc;
    QString appPath(QCoreApplication::applicationDirPath());
    appPath.append("/").append(_xmlPath);
    QFile file(appPath);
    if(file.open(QIODevice::ReadOnly))
    {
        if(domDoc.setContent(&file))
        {
            QDomElement domElement = domDoc.documentElement();
            QDomNode node = domElement.firstChild();
            TraverseNodeNumberFormat(node);
        }
        file.close();
    } else qDebug() << "XML order NOT OPEN  " << appPath;
}

void XmlHandler::SetCoefficient(const QString &_xmlPath)
{
    QDomDocument domDoc;
    QString appPath(QCoreApplication::applicationDirPath());
    appPath.append("/").append(_xmlPath);
    QFile file(appPath);
    if(file.open(QIODevice::ReadOnly))
    {
        if(domDoc.setContent(&file))
        {
            QDomElement domElement = domDoc.documentElement();
            QDomNode node = domElement.firstChild();
            TraverseNodeShift(node);
        }
        file.close();
    } else qDebug() << "XML order NOT OPEN  " << appPath;
}

void XmlHandler::SetOrder(const QString &_xmlPath)
{
    QDomDocument domDoc;
    QString appPath(QCoreApplication::applicationDirPath());
    appPath.append("/").append(_xmlPath);
    QFile file(appPath);
    if(file.open(QIODevice::ReadOnly))
    {
        if(domDoc.setContent(&file))
        {
            QDomElement domElement = domDoc.documentElement();
            QDomNode node = domElement.firstChild();
            TraverseNodeOrder(node);
        }
        file.close();
    } else qDebug() << "XML order NOT OPEN  " << appPath;
}

void XmlHandler::SetStrangeAccounts(const QString &_xmlPath)
{
    QDomDocument domDoc;
    QString appPath(QCoreApplication::applicationDirPath());
    appPath.append("/").append(_xmlPath);
    QFile file(appPath);
    if(file.open(QIODevice::ReadOnly))
    {
        if(domDoc.setContent(&file))
        {
            QDomElement domElement = domDoc.documentElement();
            QDomNode node = domElement.firstChild();
            TraverseNodeStrangeAccount(node);
        }
        file.close();
    } else qDebug() << "XML order NOT OPEN  " << appPath;
}

void XmlHandler::SetLinks(const QString &_xmlPath)
{
    QDomDocument domDoc;
    QString appPath(QCoreApplication::applicationDirPath());
    appPath.append("/").append(_xmlPath);
    QFile file(appPath);
    if(file.open(QIODevice::ReadOnly))
    {
        if(domDoc.setContent(&file))
        {
            QDomElement domElement = domDoc.documentElement();
            QDomNode node = domElement.firstChild();
            TraverseNodeLink(node);
        }
        file.close();
    } else qDebug() << "XML order NOT OPEN  " << appPath;
}

void XmlHandler::TraverseNodeNumberFormat(const QDomNode &_node)
{
    QDomNode domNode = _node;
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull())
            {
                if(domElement.tagName() == "number_format_rur")
                {
                    QString str(domElement.text());
                    this->numberFormatRur_ = str;
                }
                else if(domElement.tagName() == "number_format_usd")
                {
                    QString str(domElement.text());
                    this->numberFormatUsd_ = str;
                }
                else if(domElement.tagName() == "number_format_eur")
                {
                    QString str(domElement.text());
                    this->numberFormatEur_ = str;
                }
            }
        }
        TraverseNodeNumberFormat(domNode.firstChild());
        domNode = domNode.nextSibling();
    }
}

void XmlHandler::TraverseNodeShift(const QDomNode &_node)
{
    QDomNode domNode = _node;
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull())
            {
                if(domElement.tagName() == "shift_head")
                {
                    this->coefficientHead_ = domElement.text().toInt();
                }
                else if(domElement.tagName() == "shift_brunch")
                {
                    this->coefficientBrunch_ = domElement.text().toInt();
                }
            }
        }
        TraverseNodeShift(domNode.firstChild());
        domNode = domNode.nextSibling();
    }
}

void XmlHandler::TraverseNodeOrder(const QDomNode &_node)
{
    QDomNode domNode = _node;
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull())
            {
                if(domElement.tagName() == "bank")
                {
                    QString str(domElement.text());
                    this->vOrder_.push_back(str);
                    //                    qDebug() << "order: " << domElement.text();
                }
            }
        }
        TraverseNodeOrder(domNode.firstChild());
        domNode = domNode.nextSibling();
    }
}

void XmlHandler::TraverseNode(const QDomNode& _node)
{
    QDomNode domNode = _node;
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull())
            {
                if(domElement.tagName() == "bank") {
                    QString str(domElement.attribute("name", ""));
                    Brunch brunch;
                    brunch.setName(str);
                    this->vBrunchesFromXML_.push_back(brunch);
                    qDebug() << "Attr: " << domElement.attribute("name", "");
                }
                else {
                    if (domElement.tagName() == "account_number")
                        this->vBrunchesFromXML_.last().setNumber(domElement.text());
                    if (domElement.tagName() == "reminder")
                        this->vBrunchesFromXML_.last().setRemainder(domElement.text());
                    qDebug() << "TagName: " << domElement.tagName() << "\tText: " << domElement.text();
                }
            }
        }
        TraverseNode(domNode.firstChild());
        domNode = domNode.nextSibling();
    }
}

void XmlHandler::TraverseNodeStrangeAccount(const QDomNode &_node)
{
    QDomNode domNode = _node;
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull())
            {
                if(domElement.tagName() == "account")
                {
                    QString str(domElement.attribute("account_number", ""));
                    QPair<QString, QString> pair;
                    pair.first = str;
                    pair.second = "";
                    this->vStrangeAccounts_.push_back(pair);
                }
                else {
                    if (domElement.tagName() == "type")
                        this->vStrangeAccounts_.last().second = domElement.text();
                }
            }
        }
        TraverseNodeStrangeAccount(domNode.firstChild());
        domNode = domNode.nextSibling();
    }
}

void XmlHandler::TraverseNodeLink(const QDomNode &_node)
{
    QDomNode domNode = _node;
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull())
            {
                if(domElement.tagName() == "account")
                {
                    QString str(domElement.attribute("account_number", ""));
                    QPair<QString, QString> pair;
                    pair.first = str;
                    pair.second = "";
                    this->vPairAccountLink_.push_back(pair);
                }
                else {
                    if (domElement.tagName() == "link")
                        this->vPairAccountLink_.last().second = domElement.text();
                }
            }
        }
        TraverseNodeLink(domNode.firstChild());
        domNode = domNode.nextSibling();
    }
}

QVector<Brunch> XmlHandler::vBrunches() const
{
    return this->vBrunchesFromXML_;
}

void XmlHandler::SaveXmlBrunches(const QString &_saveXmlPath, const QVector<Brunch> &_vBrunches) const
{
    QString xmlPath(QCoreApplication::applicationDirPath());
    xmlPath.append("/").append(_saveXmlPath);

    QFile file(xmlPath);
     if (file.open(QIODevice::WriteOnly))
     {
         QXmlStreamWriter xmlWriter(&file);
         xmlWriter.setAutoFormatting(true);
         xmlWriter.writeStartDocument();
         xmlWriter.writeStartElement("content");

         for (int i = 0; i < _vBrunches.size(); i++)
         {
             xmlWriter.writeStartElement("bank");
             xmlWriter.writeAttribute("name", _vBrunches.at(i).name());

             xmlWriter.writeStartElement("account_number");
             xmlWriter.writeCharacters(_vBrunches.at(i).number());
             xmlWriter.writeEndElement();

             xmlWriter.writeStartElement("reminder");
             xmlWriter.writeCharacters(_vBrunches.at(i).remainder());
             xmlWriter.writeEndElement();

             xmlWriter.writeEndElement();
         }

         xmlWriter.writeEndElement();
         xmlWriter.writeEndDocument();
         file.close();
     } else qDebug() << "saveXml not open";
}

QString XmlHandler::numberFormatRur() const
{
    return this->numberFormatRur_;
}

QString XmlHandler::numberFormatUsd() const
{
    return numberFormatUsd_;
}

QString XmlHandler::numberFormatEur() const
{
    return numberFormatEur_;
}

int XmlHandler::coefficientHead() const
{
    return this->coefficientHead_;
}

int XmlHandler::coefficientBrunch() const
{
    return coefficientBrunch_;
}

QVector<QString> XmlHandler::vOrder() const
{
    return this->vOrder_;
}

QVector<QPair<QString, QString> > XmlHandler::vStrangeAccounts() const
{
    return vStrangeAccounts_;
}

QVector<QPair<QString, QString> > XmlHandler::vPairAccountLink() const
{
    return vPairAccountLink_;
}


