#ifndef BICO_QMUTEXQUEUE_H
#define BICO_QMUTEXQUEUE_H

#include <QQueue>
#include <QMutex>

template <class T>
class Bico_QMutexQueue : public QQueue<T>
{
public:
    Bico_QMutexQueue() = default;
    ~Bico_QMutexQueue() = default;
    Bico_QMutexQueue(const Bico_QMutexQueue &) = default;
    Bico_QMutexQueue &operator=(const Bico_QMutexQueue &) = default;

    void enqueueToBack(const T &t);
    void enqueue(const T &t);
    T dequeue();
    T dequeueFromFront();

private:
    QMutex mutex;
};

// -------------------------------------------------------------------------------------------------------------------

template<class T>
void Bico_QMutexQueue<T>::enqueueToBack(const T &t)
{
    mutex.lock();
    QQueue<T>::prepend(t);
    mutex.unlock();
}

template<class T>
void Bico_QMutexQueue<T>::enqueue(const T &t)
{
    mutex.lock();
    QQueue<T>::append(t);
    mutex.unlock();
}

template<class T>
T Bico_QMutexQueue<T>::dequeue()
{
    mutex.lock();
    T value = QQueue<T>::takeFirst();
    mutex.unlock();

    return value;
}

template<class T>
T Bico_QMutexQueue<T>::dequeueFromFront()
{
    mutex.lock();
    T value = QQueue<T>::takeLast();
    mutex.unlock();

    return value;
}



#endif // BICO_QMUTEXQUEUE_H
