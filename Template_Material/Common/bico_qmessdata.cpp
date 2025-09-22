#include "bico_qmessdata.h"

Bico_QMessData::Bico_QMessData()
{

}

Bico_QMessData::Bico_QMessData(QString mess, QVariant data)
{
    _mess = mess;
    _data = data;
}

Bico_QMessData::Bico_QMessData(QString src, QString dst, QString mess, QVariant data)
{
    _src = src;
    _dst = dst;
    _mess = mess;
    _data = data;
}

QString Bico_QMessData::mess()
{
    return _mess;
}

void Bico_QMessData::setMess(QString mess)
{
    _mess = mess;
}

QVariant Bico_QMessData::data()
{
    return _data;
}

void Bico_QMessData::setData(QVariant data)
{
    _data = data;
}

QString Bico_QMessData::src()
{
    return _src;
}

void Bico_QMessData::setSrc(QString src)
{
    _src = src;
}

QString Bico_QMessData::dst()
{
    return _dst;
}

void Bico_QMessData::setDst(QString dst)
{
    _dst = dst;
}
