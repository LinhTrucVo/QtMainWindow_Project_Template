#ifndef BICO_QWINDOWTHREAD_H
#define BICO_QWINDOWTHREAD_H

#include <QApplication>
#include <QThread>
#include <QDebug>
#include <QHash>

#include "../Template_Material/Common/bico_qthread.h"
#include "bico_qwindowthread_ui.h"

class Bico_QWindowThread_UI;

class Bico_QWindowThread : public QThread, public Bico_QThread
{
    Q_OBJECT

public:
    Bico_QWindowThread
        (
            Bico_DataQueue *qin = nullptr,
            uint8_t qin_owner = 0,
            Bico_DataQueue *qout = nullptr,
            uint8_t qout_owner = 0,
            QString obj_name = "",
            Bico_QWindowThread_UI* ui = nullptr,
            QThread* parent = nullptr
        );
    ~Bico_QWindowThread();

    void start(QThread::Priority priority = InheritPriority);
    void run();

    // This method is implemented by subclass
    virtual uint8_t MainTask() = 0;

    Bico_QWindowThread_UI *getUi() const;
    void setUi(Bico_QWindowThread_UI *ui);

    template<typename T>
    static T* createNew
        (
            Bico_DataQueue *qin = nullptr,
            uint8_t qin_owner = 0,
            Bico_DataQueue *qout = nullptr,
            uint8_t qout_owner = 0,
            QString obj_name = "",
            Bico_QWindowThread_UI* ui = nullptr,
            QThread* parent = nullptr
        )
    {
        if (thread_hash.find(obj_name) == thread_hash.end())
        {
            T* thread = new T(qin, qin_owner, qout, qout_owner, obj_name, ui, parent);
            return thread;
        }
        else
        {
            return nullptr;
        }
    }

    static void remove(QString thread_name)
    {
        if (thread_hash.contains(thread_name))
        {
            Bico_QMessData mess_data("terminate", "");
            getThreadHash().value(thread_name)->qinEnqueue(mess_data);
        }
    }

    static QHash<QString, Bico_QWindowThread *> getThreadHash();
    static QApplication* getMainApp();
    static void setMainApp(QApplication* app);

protected:
    static QHash<QString, Bico_QWindowThread*> thread_hash;
    static QMutex thread_hash_mutex;
    static QApplication* main_app;
    Bico_QWindowThread_UI* _ui;


signals:
    void toUI(QString mess, QVariant data);
public slots:
    void fromUI(QString mess, QVariant data);
};

#endif // BICO_QWINDOWTHREAD_H
