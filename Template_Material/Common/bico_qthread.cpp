#include "bico_qthread.h"

Bico_QThread::Bico_QThread(Bico_DataQueue *qin, uint8_t qin_owner, Bico_DataQueue *qout, uint8_t qout_owner)
{
    _qin = qin;
    _qout = qout;
    _qin_owner = qin_owner;
    _qout_owner = qout_owner;
}

Bico_QThread::~Bico_QThread()
{
    if (_qin_owner == 1)
    {
        delete _qin;
    }
    if (_qout_owner == 1)
    {
        delete _qout;
    }
}




Bico_DataQueue *Bico_QThread::qin() const
{
    return _qin;
}

void Bico_QThread::setQin(Bico_DataQueue *qin)
{
    _qin = qin;
}

Bico_DataQueue *Bico_QThread::qout() const
{
    return _qout;
}

void Bico_QThread::setQout(Bico_DataQueue *qout)
{
    _qout = qout;
}




uint8_t Bico_QThread::qin_owner() const
{
    return _qin_owner;
}

void Bico_QThread::setQin_owner(const uint8_t qin_owner)
{
    _qin_owner = qin_owner;
}

uint8_t Bico_QThread::qout_owner() const
{
    return _qout_owner;
}

void Bico_QThread::setQout_owner(const uint8_t qout_owner)
{
    _qout_owner = qout_owner;
}




int Bico_QThread::qinEnqueue(Bico_QMessData &input)
{
    if (_qin != nullptr)
    {
//        Bico_QMessData mess_data(input.mess(), input.data());
//        Bico_QMessData &x = mess_data;
        _qin->enqueue(input);
        return 1;
    }

    return 0;
}

int Bico_QThread::qinDequeue(Bico_QMessData &output)
{
    if (_qin != nullptr)
    {
        if (!_qin->isEmpty())
        {
            Bico_QMessData mess_data = _qin->dequeue();
            output = mess_data;
            return 1;
        }
    }

    return 0;
}

int Bico_QThread::qinenqueueToBack(Bico_QMessData &input)
{
    if (_qin != nullptr)
    {
        _qin->enqueueToBack(input);
        return 1;
    }

    return 0;
}

int Bico_QThread::qinDequeueFromFront(Bico_QMessData &output)
{
    if (_qin != nullptr)
    {
        if (!_qin->isEmpty())
        {
            Bico_QMessData mess_data = _qin->dequeueFromFront();
            output = mess_data;
            return 1;
        }
    }

    return 0;
}

int Bico_QThread::qoutEnqueue(Bico_QMessData &input)
{
    if (_qout != nullptr)
    {
        _qout->enqueue(input);
        return 1;
    }

    return 0;
}

int Bico_QThread::qoutenqueueToBack(Bico_QMessData &input)
{
    if (_qout != nullptr)
    {
        _qout->enqueueToBack(input);
        return 1;
    }

    return 0;
}
