#ifndef BICO_QTHREAD_H
#define BICO_QTHREAD_H

#include "bico_qmutexqueue.h"
#include "bico_qmessdata.h"

typedef Bico_QMutexQueue<Bico_QMessData> Bico_DataQueue ;

class Bico_QThread
{
public:

    Bico_QThread(Bico_DataQueue *qin = nullptr, uint8_t qin_owner = 0, Bico_DataQueue *qout = nullptr, uint8_t qout_owner = 0);
    ~Bico_QThread();

    Bico_DataQueue *qin() const;
    void setQin(Bico_DataQueue *qin);

    Bico_DataQueue *qout() const;
    void setQout(Bico_DataQueue *qout);

    uint8_t qin_owner() const;
    void setQin_owner(const uint8_t qin_owner);

    uint8_t qout_owner() const;
    void setQout_owner(const uint8_t qout_owner);

    int qinEnqueue(Bico_QMessData &input);
    int qinDequeue(Bico_QMessData &output);
    int qinenqueueToBack(Bico_QMessData &input);
    int qinDequeueFromFront(Bico_QMessData &output);
    int qoutEnqueue(Bico_QMessData &input);
    int qoutenqueueToBack(Bico_QMessData &input);

protected:
    Bico_DataQueue *_qin;
    Bico_DataQueue *_qout;
    uint8_t _qin_owner;
    uint8_t _qout_owner;
};

#endif // BICO_QTHREAD_H




// Tested code ------------------------------------------------------------------------------------------------

//Bico_QThread bc_thr_1(new Bico_DataQueue, 1, new Bico_DataQueue, 1);
//Bico_QMessData md_in("m1", "d1");
//bc_thr_1.qinEnqueue(md_in);
//md_in = Bico_QMessData("m2", "d2");
//bc_thr_1.qinenqueueToBack(md_in);
//md_in = Bico_QMessData("m3", "d3");
//bc_thr_1.qinenqueueToBack(md_in);
//md_in = Bico_QMessData("m4", "d4");
//bc_thr_1.qinEnqueue(md_in);


//Bico_QThread bc_thr_2(new Bico_DataQueue, 1, new Bico_DataQueue, 1);
//md_in = Bico_QMessData("m5", "d5");
//bc_thr_2.qinEnqueue(md_in);
//md_in = Bico_QMessData("m6", "d6");
//bc_thr_2.qinEnqueue(md_in);
//md_in = Bico_QMessData("m7", "d7");
//bc_thr_2.qinenqueueToBack(md_in);
//md_in = Bico_QMessData("m8", "d8");
//bc_thr_2.qinEnqueue(md_in);


//Bico_QMessData md_out;
//bc_thr_1.qinDequeue(md_out);
//qDebug() << md_out.mess() << " " << md_out.data() << Qt::endl;
//bc_thr_1.qinDequeueFromFront(md_out);
//qDebug() << md_out.mess() << " " << md_out.data() << Qt::endl;
//bc_thr_1.qinDequeue(md_out);
//qDebug() << md_out.mess() << " " << md_out.data() << Qt::endl;
//bc_thr_1.qinDequeue(md_out);
//qDebug() << md_out.mess() << " " << md_out.data() << Qt::endl;

//bc_thr_2.qinDequeue(md_out);
//qDebug() << md_out.mess() << " " << md_out.data() << Qt::endl;
//bc_thr_2.qinDequeueFromFront(md_out);
//qDebug() << md_out.mess() << " " << md_out.data() << Qt::endl;
//bc_thr_2.qinDequeue(md_out);
//qDebug() << md_out.mess() << " " << md_out.data() << Qt::endl;
//bc_thr_2.qinDequeue(md_out);
//qDebug() << md_out.mess() << " " << md_out.data() << Qt::endl;

// Tested code ------------------------------------------------------------------------------------------------
