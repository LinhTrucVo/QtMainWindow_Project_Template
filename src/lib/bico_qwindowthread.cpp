#include "bico_qwindowthread.h"

// ThreadFactory implementation
ThreadFactory::ThreadFactory(QObject* parent)
    : QObject(parent), created_thread(nullptr), pending_params(nullptr)
{
}

void ThreadFactory::createThread()
{
    if (pending_params == nullptr)
        return;
    
    // Create thread directly (we're already in main thread)
    // Note: We pass nullptr as parent initially to avoid "Cannot set parent, 
    // new parent is in a different thread" error. The parent will be set later
    // if needed, after the thread is properly initialized.
    created_thread = pending_params->creator(
        pending_params->qin,
        pending_params->qin_owner,
        pending_params->qout,
        pending_params->qout_owner,
        pending_params->obj_name,
        pending_params->ui,
        pending_params->parent
    );
    
    // Clear pending params
    delete pending_params;
    pending_params = nullptr;
}

// UIShower implementation
UIShower::UIShower(QObject* parent)
    : QObject(parent), pending_ui(nullptr)
{
}

void UIShower::showUI()
{
    if (pending_ui != nullptr && pending_ui->isHidden())
    {
        pending_ui->show();
        pending_ui = nullptr;
    }
}

// Static member initialization
QHash<QString, Bico_QWindowThread*> Bico_QWindowThread::thread_hash;
QMutex Bico_QWindowThread::thread_hash_mutex;
QApplication* Bico_QWindowThread::main_app = nullptr;
ThreadFactory* Bico_QWindowThread::thread_factory = nullptr;
UIShower* Bico_QWindowThread::ui_shower = nullptr;

Bico_QWindowThread::Bico_QWindowThread
    (
        Bico_DataQueue *qin,
        uint8_t qin_owner,
        Bico_DataQueue *qout,
        uint8_t qout_owner,
        QString obj_name,
        Bico_QWindowThread_UI* ui,
        QThread* parent
    )
    : QThread(parent), Bico_QThread(qin, qin_owner, qout, qout_owner)
{
    setObjectName(obj_name);
            
    thread_hash_mutex.lock();
    thread_hash.insert(obj_name, this);
    thread_hash_mutex.unlock();

    // Connect finished signal to selfRemove slot for automatic cleanup
    QObject::connect(this, &QThread::finished, [obj_name]() {
        Bico_QWindowThread::selfRemove(obj_name);
    });

    _ui = ui;
    if (_ui != nullptr)
    {
        if(_ui->getThread() == nullptr)
        {
            _ui->setThread(this);
        }

        QObject::connect(this, SIGNAL(toUI(QString,QVariant)), _ui, SLOT(fromThread(QString,QVariant)));
        QObject::connect(_ui, SIGNAL(toThread(QString,QVariant)), this, SLOT(fromUI(QString,QVariant)));
    }
}

Bico_QWindowThread::~Bico_QWindowThread()
{
    // Destructor is now minimal - cleanup is handled by selfRemove slot
    // which is called when the 'finished' signal is emitted
}

void Bico_QWindowThread::start(QThread::Priority priority)
{
    QThread::start(priority);

    if (_ui != nullptr)
    {
        if (((QMainWindow*)_ui)->isHidden() == true)
        {
            // Check if we're in the main thread
            QThread* main_thread = QCoreApplication::instance()->thread();
            QThread* current_thread = QThread::currentThread();
            
            if (current_thread == main_thread)
            {
                // We're in main thread, show directly
                _ui->show();
            }
            else
            {
                // We're in a worker thread, use QMetaObject::invokeMethod to show in main thread
                getUIShower()->pending_ui = _ui;
                QMetaObject::invokeMethod(
                    getUIShower(),
                    "showUI",
                    Qt::BlockingQueuedConnection
                );
            }
        }
    }
}


void Bico_QWindowThread::run()
{
    do
    {

    } while (MainTask());
}


QHash<QString, Bico_QWindowThread *> Bico_QWindowThread::getThreadHash()
{
    return thread_hash;
}

QApplication *Bico_QWindowThread::getMainApp()
{
    return main_app;
}

void Bico_QWindowThread::setMainApp(QApplication *app)
{
    main_app = app;
}

void Bico_QWindowThread::initializeFactories()
{
    // Initialize global factory instances (they live in main thread)
    // This MUST be called from the main thread before any worker threads are created
    if (thread_factory == nullptr)
    {
        thread_factory = new ThreadFactory();
    }
    if (ui_shower == nullptr)
    {
        ui_shower = new UIShower();
    }
}

ThreadFactory* Bico_QWindowThread::getThreadFactory()
{
    return thread_factory;
}

UIShower* Bico_QWindowThread::getUIShower()
{
    return ui_shower;
}

Bico_QWindowThread_UI *Bico_QWindowThread::getUi() const
{
    return _ui;
}

void Bico_QWindowThread::setUi(Bico_QWindowThread_UI *ui)
{
    _ui = ui;
}


void Bico_QWindowThread::fromUI(QString mess, QVariant data)
{
    Bico_QMessData mess_data;
    mess_data.setMess(mess);
    mess_data.setData(data);

    qinEnqueue(mess_data);
}

void Bico_QWindowThread::selfRemove(QString obj_name)
{
    Bico_QWindowThread* thread = thread_hash.value(obj_name);
    if (thread == nullptr)
        return;
    
    // Clean up UI connection
    if (thread->_ui != nullptr)
    {
        thread->_ui->setThread(nullptr);
        emit thread->_ui->TERMINATE();
        thread->_ui = nullptr;
    }
    
    // Remove from hash and schedule for deletion
    thread_hash_mutex.lock();
    thread_hash.remove(obj_name);
    thread_hash_mutex.unlock();
    
    thread->deleteLater();
    
    // Exit app if no more threads
    if (thread_hash.count() < 1)
    {
        if (main_app != nullptr)
        {
            main_app->exit(0);
        }
    }
}
