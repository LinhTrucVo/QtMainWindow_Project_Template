#ifndef BICO_QWINDOWTHREAD_UI_H
#define BICO_QWINDOWTHREAD_UI_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QHash>
#include <QObject>
#include <QMetaObject>
#include <QCoreApplication>
#include <QThread>
#include <QMutex>
#include <functional>

#define UI_NAME_PREFIX QString("ui_")

// Forward declarations only - avoid circular include
class Bico_QWindowThread;
class Bico_QWindowThread_UI;
class UIFactory_UI;

/**
 * @brief Helper class that lives in the main thread to create UI instances safely.
 */
class UIFactory_UI : public QObject
{
    Q_OBJECT

public:
    explicit UIFactory_UI(QObject* parent = nullptr);
    
    Bico_QWindowThread_UI* created_ui;
    
    // Pending parameters to avoid Q_ARG type issues
    struct PendingParams {
        QString obj_name;
        Bico_QWindowThread* thread;
        QWidget* parent;
        std::function<Bico_QWindowThread_UI*(QString, Bico_QWindowThread*, QWidget*)> creator;
    };
    
    PendingParams* pending_params;

public slots:
    void createUI();
};

class Bico_QWindowThread_UI : public QMainWindow
{
    Q_OBJECT

public:
    Bico_QWindowThread_UI(QString obj_name = "", Bico_QWindowThread* thread = nullptr, QWidget* parent = nullptr);
    ~Bico_QWindowThread_UI();

    void show();
    void closeEvent(QCloseEvent *event);

    // This method is implemented by subclass
    virtual void fromThreadHandling(QString mess, QVariant data) = 0;

    Bico_QWindowThread *getThread() const;
    void setThread(Bico_QWindowThread *thread);

    template<typename T>
    static T* createNew(QString obj_name = "", Bico_QWindowThread* thread = nullptr, QWidget* parent = nullptr)
    {
        if (ui_thread_hash.find(UI_NAME_PREFIX + obj_name) == ui_thread_hash.end())
        {
            // Check if we're in the main thread
            QThread* main_thread = QCoreApplication::instance()->thread();
            QThread* current_thread = QThread::currentThread();
            
            if (current_thread == main_thread)
            {
                // We're in the main thread, create directly
                T* ui = new T(obj_name, thread, parent);
                return ui;
            }
            else
            {
                // We're in a worker thread, use QMetaObject::invokeMethod to create in main thread
                // Store parameters in the factory object first (avoids Q_ARG type issues)
                getUIFactory()->created_ui = nullptr;
                getUIFactory()->pending_params = new UIFactory_UI::PendingParams{
                    obj_name, thread, parent,
                    [](QString obj_name, Bico_QWindowThread* thread, QWidget* parent) -> Bico_QWindowThread_UI* {
                        return new T(obj_name, thread, parent);
                    }
                };
                
                // Check if the factory is in the same thread (would cause deadlock with BlockingQueued)
                QThread* factory_thread = getUIFactory()->thread();
                Qt::ConnectionType connection_type = (current_thread == factory_thread) 
                    ? Qt::DirectConnection 
                    : Qt::BlockingQueuedConnection;
                
                // Use BlockingQueuedConnection to wait for the UI to be created
                QMetaObject::invokeMethod(
                    getUIFactory(),
                    "createUI",
                    connection_type
                );
                T* result = static_cast<T*>(getUIFactory()->created_ui);
                return result;
            }
        }
        else
        {
            return nullptr;
        }
    }

    static QHash<QString, Bico_QWindowThread_UI *> getUIThreadHash();
    static void initializeFactory();  // Must be called from main thread
    static UIFactory_UI* getUIFactory();

protected:
    static QHash<QString, Bico_QWindowThread_UI*> ui_thread_hash;
    static QMutex ui_thread_hash_mutex;
    static UIFactory_UI* ui_factory;
    Bico_QWindowThread* _thread;

signals:
    void toThread(QString mess, QVariant data);
    void TERMINATE();
public slots:
    void fromThread(QString mess, QVariant data);
    static void selfRemove(QString obj_name);

};

#endif // BICO_QWINDOWTHREAD_UI_H
