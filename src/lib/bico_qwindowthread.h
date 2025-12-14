#ifndef BICO_QWINDOWTHREAD_H
#define BICO_QWINDOWTHREAD_H

#include <QApplication>
#include <QThread>
#include <QDebug>
#include <QHash>
#include <QObject>
#include <QMetaObject>
#include <QCoreApplication>
#include <functional>

#include "bico_qthread.h"
#include "bico_qwindowthread_ui.h"

class Bico_QWindowThread_UI;

// Forward declarations
class ThreadFactory;
class UIShower;

/**
 * @brief Helper class that lives in the main thread to create new threads safely.
 */
class ThreadFactory : public QObject
{
    Q_OBJECT

public:
    explicit ThreadFactory(QObject* parent = nullptr);
    
    Bico_QWindowThread* created_thread;
    
    // Pending parameters to avoid Q_ARG type issues
    struct PendingParams {
        Bico_DataQueue* qin;
        uint8_t qin_owner;
        Bico_DataQueue* qout;
        uint8_t qout_owner;
        QString obj_name;
        Bico_QWindowThread_UI* ui;
        QThread* parent;
        std::function<Bico_QWindowThread*(Bico_DataQueue*, uint8_t, Bico_DataQueue*, uint8_t, QString, Bico_QWindowThread_UI*, QThread*)> creator;
    };
    
    PendingParams* pending_params;

public slots:
    void createThread();
};

/**
 * @brief Helper class to show UI widgets in the main thread.
 */
class UIShower : public QObject
{
    Q_OBJECT

public:
    explicit UIShower(QObject* parent = nullptr);
    
    Bico_QWindowThread_UI* pending_ui;

public slots:
    void showUI();
};

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
            // Check if we're in the main thread
            QThread* main_thread = QCoreApplication::instance()->thread();
            QThread* current_thread = QThread::currentThread();
            
            if (current_thread == main_thread)
            {
                // We're in the main thread, create directly
                T* thread = new T(qin, qin_owner, qout, qout_owner, obj_name, ui, parent);
                return thread;
            }
            else
            {
                // We're in a worker thread, use QMetaObject::invokeMethod to create in main thread
                // Store parameters in the factory object first (avoids Q_ARG type issues)
                getThreadFactory()->created_thread = nullptr;
                getThreadFactory()->pending_params = new ThreadFactory::PendingParams{
                    qin, qin_owner, qout, qout_owner, obj_name, ui, parent,
                    [](Bico_DataQueue* qin, uint8_t qin_owner, Bico_DataQueue* qout, uint8_t qout_owner, 
                       QString obj_name, Bico_QWindowThread_UI* ui, QThread* parent) -> Bico_QWindowThread* {
                        return new T(qin, qin_owner, qout, qout_owner, obj_name, ui, parent);
                    }
                };
                
                // Check if the factory is in the same thread (would cause deadlock with BlockingQueued)
                QThread* factory_thread = getThreadFactory()->thread();
                Qt::ConnectionType connection_type = (current_thread == factory_thread) 
                    ? Qt::DirectConnection 
                    : Qt::BlockingQueuedConnection;
                
                // Use BlockingQueuedConnection to wait for the thread to be created
                QMetaObject::invokeMethod(
                    getThreadFactory(),
                    "createThread",
                    connection_type
                );
                
                T* result = static_cast<T*>(getThreadFactory()->created_thread);
                return result;
            }
        }
        else
        {
            return nullptr;
        }
    }

    static QHash<QString, Bico_QWindowThread *> getThreadHash();
    static QApplication* getMainApp();
    static void setMainApp(QApplication* app);
    static void initializeFactories();  // Must be called from main thread
    static ThreadFactory* getThreadFactory();
    static UIShower* getUIShower();

protected:
    static QHash<QString, Bico_QWindowThread*> thread_hash;
    static QMutex thread_hash_mutex;
    static QApplication* main_app;
    static ThreadFactory* thread_factory;
    static UIShower* ui_shower;
    Bico_QWindowThread_UI* _ui;


signals:
    void toUI(QString mess, QVariant data);
public slots:
    void fromUI(QString mess, QVariant data);
    static void selfRemove(QString obj_name);
};

#endif // BICO_QWINDOWTHREAD_H
