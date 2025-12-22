#include <QJsonObject>
#include <QJsonDocument>
#include <QRandomGenerator>

#include "Task1.h"
#include "Task1_UI.h"

// Initialize static member
int Task1::count = 0;

Task1::Task1
(
    Bico_DataQueue *qin,
    uint8_t qin_owner,
    Bico_DataQueue *qout,
    uint8_t qout_owner,
    QString obj_name,
    Bico_QWindowThread_UI *ui,
    QThread* parent
) : Bico_QWindowThread(qin, qin_owner, qout, qout_owner, obj_name, ui, parent)
{
    // Initialize message handler map
    message_handlers["terminate"] = &Task1::_handle_terminate;
    message_handlers["mess_from_ui"] = &Task1::_handle_mess_from_ui;
    message_handlers["create"] = &Task1::_handle_create;
    message_handlers["create_child"] = &Task1::_handle_create_child;
    message_handlers["mess_to_ui"] = &Task1::_handle_mess_to_ui;
    message_handlers["from_another_thread"] = &Task1::_handle_from_another_thread;
}

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

        // Use the message handler map
        auto handler_it = message_handlers.find(mess);
        if (handler_it != message_handlers.end())
        {
            continue_to_run = (this->*handler_it.value())(data, input);
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

uint8_t Task1::_handle_terminate(QVariant& data, Bico_QMessData& input)
{
    cleanupChildren();
    return 0;  // Signal to stop running
}

uint8_t Task1::_handle_mess_from_ui(QVariant& data, Bico_QMessData& input)
{
    qDebug() << "From UI: " << objectName() << " mess_from_ui " << data.value<QString>();
    emit toUI("change_button_text", QString::number(QRandomGenerator::global()->generate()));
    return 1;
}

uint8_t Task1::_handle_create(QVariant& data, Bico_QMessData& input)
{
    qDebug() << objectName() << " create";
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
    if (thread != nullptr)
    {
        thread->start();
    }
    return 1;
}

uint8_t Task1::_handle_create_child(QVariant& data, Bico_QMessData& input)
{
    qDebug() << objectName() << " create_child";
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
    if (thread != nullptr)
    {
        thread->start();
    }
    return 1;
}

uint8_t Task1::_handle_mess_to_ui(QVariant& data, Bico_QMessData& input)
{
    QJsonObject json_obj = QJsonDocument::fromJson(data.value<QString>().toUtf8()).object();
    emit toUI(json_obj["mess"].toString(), json_obj["data"].toString());
    return 1;
}

uint8_t Task1::_handle_from_another_thread(QVariant& data, Bico_QMessData& input)
{
    qDebug() << objectName() << "from_another_thread: " << input.src() << data.value<int>();
    return 1;
}
