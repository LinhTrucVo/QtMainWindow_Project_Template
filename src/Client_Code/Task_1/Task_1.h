#ifndef TASK_1_H
#define TASK_1_H

#include <QtDebug>

#include "bico_qwindowthread.h"
#include "Task_1_UI.h"
#include "Data_Object/Task_1_Data.h"


class Task_1 : public Bico_QWindowThread
{
    Q_OBJECT

public:
    Task_1
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
    Task_1_Data ex_data_obj;
};

#endif // TASK_1_H
