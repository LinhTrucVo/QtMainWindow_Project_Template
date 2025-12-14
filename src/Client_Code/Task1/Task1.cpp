#include <QJsonObject>
#include <QJsonDocument>
#include <QRandomGenerator>

#include "Task1.h"
#include "Task1_UI.h"

// Initialize static member
int Task1::count = 0;

void Task1::cleanupChildren()
{
    // Get all children from this QObject's children() and terminate them
    QObjectList child_list = children();
    for (QObject* child : child_list)
    {
        Bico_QWindowThread* thread = qobject_cast<Bico_QWindowThread*>(child);
        if (thread != nullptr)
        {
            qDebug() << "Cleaning up child thread:" << thread->objectName();
            Bico_QMessData mess_data("terminate", "");
            thread->qinEnqueue(mess_data);
            
            // Wait for child thread to finish
            if (thread->isRunning())
            {
                thread->wait(5000);  // Wait up to 5 seconds
            }
        }
    }
}

uint8_t Task1::MainTask()
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
            cleanupChildren();
        }
        else if (mess == QString("mess_from_ui"))
        {
            qDebug() << "From UI: " << objectName() << " " << mess << " " << data.value<QString>();
            emit toUI("change_button_text", QString::number(QRandomGenerator::global()->generate()));
        }
        else if (mess == QString("create"))
        {
            qDebug() << objectName() << " " << mess;
            // Create and start a new window thread with its UI (as sibling)
            count++;
            QString thread_name = "task_" + QString::number(count);
            Task1* thread = Bico_QWindowThread::createNew<Task1>
                    (
                        new Bico_DataQueue,
                        1,
                        new Bico_DataQueue,
                        1,
                        thread_name,
                        Bico_QWindowThread_UI::createNew<Task1_UI>(thread_name)
                    );
            Bico_QWindowThread::getThreadHash().value(thread_name)->start();
            if (thread != nullptr)
            {
                thread->start();
            }
        }
        else if (mess == QString("create_child"))
        {
            qDebug() << objectName() << " " << mess;
            // Create and start a new window thread with its UI (as child of this thread)
            count++;
            QString thread_name = "child_task_" + QString::number(count);
            Task1* thread = Bico_QWindowThread::createNew<Task1>
                    (
                        new Bico_DataQueue,
                        1,
                        new Bico_DataQueue,
                        1,
                        thread_name,
                        Bico_QWindowThread_UI::createNew<Task1_UI>(thread_name),
                        this
                    );
            Bico_QWindowThread::getThreadHash().value(thread_name)->start();
            if (thread != nullptr)
            {
                thread->start();
            }
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
    msleep(100);

    if ((objectName() == "task_1") && (getThreadHash().value("task_0") != nullptr))
    {
        static int i = 0;
        Bico_QMessData mess_data("from_another_thread", i++);
        mess_data.setSrc(objectName());
        getThreadHash().value("task_0")->qinEnqueue(mess_data);
        msleep(236);
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
