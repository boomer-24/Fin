#include "brunch.h"

Brunch::Brunch()
{

}

Brunch::Brunch(const QString &_name, const QString &_number, const QString &_remainder)
{
    this->name_ = _name;
    this->number_ = _number;
    this->remainder_ = _remainder;
}

Brunch::~Brunch()
{

}

QString Brunch::name() const
{
    return this->name_;
}

void Brunch::setName(const QString &_name)
{
    this->name_ = _name;
}

QString Brunch::number() const
{
    return this->number_;
}

void Brunch::setNumber(const QString &_number)
{
    this->number_ = _number;
}

QString Brunch::remainder() const
{
    return this->remainder_;
}

void Brunch::setRemainder(const QString &_remainder)
{
    this->remainder_ = _remainder;
}
