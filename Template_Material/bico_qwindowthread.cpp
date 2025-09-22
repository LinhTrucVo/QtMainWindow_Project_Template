#include "bico_qwindowthread.h"

QHash<QString, Bico_QWindowThread*> Bico_QWindowThread::thread_hash;
QMutex Bico_QWindowThread::thread_hash_mutex;
QApplication* Bico_QWindowThread::main_app = nullptr;

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
    if (_ui != nullptr)
    {
        _ui->setThread(nullptr);
        emit toUI("terminate", "");

        QObject::disconnect(this, SIGNAL(toUI(QString,QVariant)), _ui, SLOT(fromThread(QString,QVariant)));
        QObject::disconnect(_ui, SIGNAL(toThread(QString,QVariant)), this, SLOT(fromUI(QString,QVariant)));
    }

    thread_hash_mutex.lock();
    thread_hash.remove(this->objectName());
    thread_hash_mutex.unlock();

    if (thread_hash.count() < 1)
    {
        if (main_app != nullptr)
        {
            main_app->exit(0);
        }
    }
}

void Bico_QWindowThread::start(QThread::Priority priority)
{
    QThread::start(priority);

    if (_ui != nullptr)
    {
        if (((QMainWindow*)_ui)->isHidden() == true)
        {
            _ui->show();
        }
    }
}


void Bico_QWindowThread::run()
{
    do
    {

    } while (MainTask());

    deleteLater();
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
