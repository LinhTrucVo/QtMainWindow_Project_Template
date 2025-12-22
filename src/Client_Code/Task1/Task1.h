#ifndef TASK1_H
#define TASK1_H

#include <QtDebug>

#include "bico_qwindowthread.h"
#include "Task1_UI.h"
#include "Data_Object/Task1_Data.h"


class Task1 : public Bico_QWindowThread
{
    Q_OBJECT

public:
    Task1
    (
        Bico_DataQueue *qin, 
        uint8_t qin_owner, 
        Bico_DataQueue *qout, 
        uint8_t qout_owner, 
        QString obj_name, 
        Bico_QWindowThread_UI *ui, 
        QThread* parent
    );

    virtual uint8_t MainTask();
    void cleanupChildren();

private:
    Task1_Data ex_data_obj;
    static int count;  // Counter for thread naming
    
    // Message handler function type
    typedef uint8_t (Task1::*MessageHandler)(QVariant&, Bico_QMessData&);
    QMap<QString, MessageHandler> message_handlers;
    
    // Message handler methods
    uint8_t _handle_terminate(QVariant& data, Bico_QMessData& input);
    uint8_t _handle_mess_from_ui(QVariant& data, Bico_QMessData& input);
    uint8_t _handle_create(QVariant& data, Bico_QMessData& input);
    uint8_t _handle_create_child(QVariant& data, Bico_QMessData& input);
    uint8_t _handle_mess_to_ui(QVariant& data, Bico_QMessData& input);
    uint8_t _handle_from_another_thread(QVariant& data, Bico_QMessData& input);
};

#endif // TASK1_H
