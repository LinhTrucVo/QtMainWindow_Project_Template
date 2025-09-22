#ifndef BICO_QWINDOWTHREAD_SAMPLE_H
#define BICO_QWINDOWTHREAD_SAMPLE_H

#include <QtDebug>

#include "../../Template_Material/bico_qwindowthread.h"
#include "Bico_QWindowThread_Sample_UI.h"
#include "Data_Object/Bico_QWindowThread_Sample_Data.h"


class Bico_QWindowThread_Sample : public Bico_QWindowThread
{
    Q_OBJECT

public:
    Bico_QWindowThread_Sample
    (
        Bico_DataQueue *qin, 
        uint8_t qin_owner, 
        Bico_DataQueue *qout, 
        uint8_t qout_owner, 
        QString obj_name, 
        Bico_QWindowThread_UI *ui, 
        QThread* parent
    ) : Bico_QWindowThread(qin, qin_owner, qout, qout_owner, obj_name, ui, parent)
    {}

    virtual uint8_t MainTask();

private:
    Bico_QWindowThread_Sample_Data ex_data_obj;
};

#endif // BICO_QWINDOWTHREAD_SAMPLE_H
