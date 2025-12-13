#include "bico_qwindowthread_ui.h"
#include "bico_qwindowthread.h"

// UIFactory_UI implementation
UIFactory_UI::UIFactory_UI(QObject* parent)
    : QObject(parent), created_ui(nullptr), pending_params(nullptr)
{
}

void UIFactory_UI::createUI()
{
    if (pending_params == nullptr)
        return;

    int thread_check = 5;
    // Check if we're in the main thread
    QThread* main_thread = QCoreApplication::instance()->thread();
    QThread* current_thread = QThread::currentThread();
    thread_check = (current_thread == main_thread);
    
    // Create UI directly (we're already in main thread)
    created_ui = pending_params->creator(
        pending_params->obj_name,
        pending_params->thread,
        pending_params->parent
    );
    
    // Clear pending params
    delete pending_params;
    pending_params = nullptr;
}

// Static member initialization
QHash<QString, Bico_QWindowThread_UI*> Bico_QWindowThread_UI::ui_thread_hash;
QMutex Bico_QWindowThread_UI::ui_thread_hash_mutex;
UIFactory_UI* Bico_QWindowThread_UI::ui_factory = nullptr;

Bico_QWindowThread_UI::Bico_QWindowThread_UI(QString obj_name, Bico_QWindowThread* thread, QWidget* parent) : QMainWindow(parent)
{
    setObjectName(UI_NAME_PREFIX + obj_name);

    int thread_check = 5;
    // Check if we're in the main thread
    QThread* main_thread = QCoreApplication::instance()->thread();
    QThread* current_thread = QThread::currentThread();
    thread_check = (current_thread == main_thread);

    ui_thread_hash_mutex.lock();
    ui_thread_hash.insert(UI_NAME_PREFIX + obj_name, this);
    ui_thread_hash_mutex.unlock();

    // Connect TERMINATE signal to selfRemove slot for automatic cleanup
    QObject::connect(this, &Bico_QWindowThread_UI::TERMINATE, [obj_name]() {
        Bico_QWindowThread_UI::selfRemove(UI_NAME_PREFIX + obj_name);
    });

    _thread = thread;
    if (_thread != nullptr)
    {
        if(_thread->getUi() == nullptr)
        {
            _thread->setUi(this);
        }

        QObject::connect(this, SIGNAL(toThread(QString,QVariant)), _thread, SLOT(fromUI(QString,QVariant)));
        QObject::connect(_thread, SIGNAL(toUI(QString,QVariant)), this, SLOT(fromThread(QString,QVariant)));
    }
}

Bico_QWindowThread_UI::~Bico_QWindowThread_UI()
{
    // Destructor is now minimal - cleanup is handled by selfRemove slot
    // which is called when the TERMINATE signal is emitted
}

void Bico_QWindowThread_UI::show()
{
    QMainWindow::show();

    if (_thread != nullptr)
    {
        if (((QThread*)_thread)->isRunning() == false)
        {
            _thread->start();
        }
    }
}

void Bico_QWindowThread_UI::closeEvent(QCloseEvent *event)
{
    event->ignore();
    emit toThread("terminate", "");
}


QHash<QString, Bico_QWindowThread_UI *> Bico_QWindowThread_UI::getUIThreadHash()
{
    return ui_thread_hash;
}

void Bico_QWindowThread_UI::initializeFactory()
{
    // Initialize UI factory in main thread
    // This MUST be called from the main thread before any worker threads are created
    if (ui_factory == nullptr)
    {
        ui_factory = new UIFactory_UI();
    }
}

UIFactory_UI* Bico_QWindowThread_UI::getUIFactory()
{
    return ui_factory;
}

Bico_QWindowThread *Bico_QWindowThread_UI::getThread() const
{
    return _thread;
}

void Bico_QWindowThread_UI::setThread(Bico_QWindowThread *thread)
{
    _thread = thread;
}


void Bico_QWindowThread_UI::fromThread(QString mess, QVariant data)
{
    fromThreadHandling(mess, data);
}

void Bico_QWindowThread_UI::selfRemove(QString obj_name)
{
    Bico_QWindowThread_UI* ui = ui_thread_hash.value(obj_name);
    if (ui == nullptr)
        return;
    
    // Remove from hash and schedule for deletion
    ui_thread_hash_mutex.lock();
    ui_thread_hash.remove(obj_name);
    ui_thread_hash_mutex.unlock();
    
    ui->deleteLater();
}
