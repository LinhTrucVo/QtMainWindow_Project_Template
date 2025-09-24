#ifndef BICO_QWINDOWTHREAD_UI_H
#define BICO_QWINDOWTHREAD_UI_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QHash>

#include "bico_qwindowthread.h"

#define UI_NAME_PREFIX QString("ui_")
#define TERMINATE deleteLater()

class Bico_QWindowThread;

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
            T* ui = new T(obj_name, thread, parent);
            return ui;
        }
        else
        {
            return nullptr;
        }
    }

    static QHash<QString, Bico_QWindowThread_UI *> getUIThreadHash();

protected:
    static QHash<QString, Bico_QWindowThread_UI*> ui_thread_hash;
    static QMutex ui_thread_hash_mutex;
    Bico_QWindowThread* _thread;

signals:
    void toThread(QString mess, QVariant data);
public slots:
    void fromThread(QString mess, QVariant data);

};

#endif // BICO_QWINDOWTHREAD_UI_H
