#ifndef BRUNCH_H
#define BRUNCH_H

#include <QString>

class Brunch
{
public:
    Brunch();
    Brunch(const QString &_name, const QString &_number, const QString &_remainder);
    ~Brunch();

    QString name() const;
    void setName(const QString &_name);

    QString number() const;
    void setNumber(const QString &_number);

    QString remainder() const;
    void setRemainder(const QString &_remainder);

private:
    QString name_;
    QString number_;
    QString remainder_;
};

#endif // BRUNCH_H
