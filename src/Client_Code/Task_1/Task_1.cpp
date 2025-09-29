#include <QJsonObject>
#include <QJsonDocument>
#include <QRandomGenerator>

#include "Task_1.h"


uint8_t Task_1::MainTask()
{
    // continue_to_run is used to terminate the thread by reset it to 0
    uint8_t continue_to_run = 1;

    Bico_QMessData input;
    if (qinDequeue(input))
    {
        QString mess = input.mess();
        QVariant data = input.data();

        // Don't delete/change this "terminate" case, it is used to terminate safety
        if (mess == QString("terminate"))
        {
            continue_to_run = 0;
        }
        else if (mess == QString("mess_from_ui"))
        {
            qDebug() << "From UI: " << objectName() << " " << mess << " " << data.value<QString>();
            emit toUI("change_button_text", QString::number(QRandomGenerator().generate()));
        }
        else if (mess == QString("mess_to_ui"))
        {
            QJsonObject json_obj = QJsonDocument::fromJson(data.value<QString>().toUtf8()).object();
            emit toUI(json_obj["mess"].toString(), json_obj["data"].toString());
        }
        // --------------------------------------------------------------------------------
        else if (mess == QString("1"))
        {
            qDebug() << objectName() << mess << data.value<int>() << "\t" << ex_data_obj.getData_1();
        }
        else if (mess == QString("2"))
        {
            qDebug() << objectName() << mess << data.value<QString>() << "\t" << ex_data_obj.getData_2();
        }
        else if (mess == QString("from_another_thread"))
        {
            qDebug() << objectName() << mess << ": "  << input.src() << data.value<int>();
        }
    }


    // Default work - begin --------------------------------------------------------------
    qDebug() << QString("Hello from ") + objectName();
    qDebug() << "Num of running thread: " << getThreadHash().count();
    qDebug() << "Num of running ui thread: " << Bico_QWindowThread_UI::getUIThreadHash().count();
    msleep(1000);

    if ((objectName() == "task_1") && (getThreadHash().value("task_0") != nullptr))
    {
        static int i = 0;
        Bico_QMessData mess_data("from_another_thread", i++);
        mess_data.setSrc(objectName());
        getThreadHash().value("task_0")->qinEnqueue(mess_data);
        msleep(2365);
    }

    qDebug() << Qt::endl;
    // Default work - end--------------------------------------------------------------

    // This block of code is to test the remove method
    // Test the remove method - begin --------------------------------------------------------------
    // if (objectName() == "task_0")
    // {
    //     Bico_QWindowThread::remove(objectName());
    // }
    // Test the remove method - end --------------------------------------------------------------

    return continue_to_run;
}
