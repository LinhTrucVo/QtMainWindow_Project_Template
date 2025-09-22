#include "bico_qwindowthread_ui.h"

QHash<QString, Bico_QWindowThread_UI*> Bico_QWindowThread_UI::ui_thread_hash;
QMutex Bico_QWindowThread_UI::ui_thread_hash_mutex;

Bico_QWindowThread_UI::Bico_QWindowThread_UI(QString obj_name, Bico_QWindowThread* thread, QWidget* parent) : QMainWindow(parent)
{
    setObjectName(UI_NAME_PREFIX + obj_name);

    ui_thread_hash_mutex.lock();
    ui_thread_hash.insert(UI_NAME_PREFIX + obj_name, this);
    ui_thread_hash_mutex.unlock();

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
    if (_thread != nullptr)
    {
        QObject::disconnect(this, SIGNAL(toThread(QString,QVariant)), _thread, SLOT(fromUI(QString,QVariant)));
        QObject::disconnect(_thread, SIGNAL(toUI(QString,QVariant)), this, SLOT(fromThread(QString,QVariant)));
    }

    ui_thread_hash_mutex.lock();
    ui_thread_hash.remove(this->objectName());
    ui_thread_hash_mutex.unlock();
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
