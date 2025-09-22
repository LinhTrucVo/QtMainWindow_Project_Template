#ifndef BICO_QMESSDATA_H
#define BICO_QMESSDATA_H

#include <QString>
#include <QVariant>

class Bico_QMessData
{
public:
    Bico_QMessData();
    Bico_QMessData(QString mess, QVariant data);
    Bico_QMessData(QString src, QString dst, QString mess, QVariant data);

    QString src();
    void setSrc(QString src);

    QString dst();
    void setDst(QString dst);

    QString mess();
    void setMess(QString mess);

    QVariant data();
    void setData(QVariant data);

private:
    QString _src;
    QString _dst;
    QString _mess;
    QVariant _data;
};

#endif // BICO_QMESSDATA_H
