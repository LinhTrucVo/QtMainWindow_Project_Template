#include <QApplication>

#include "Client_Code/Bico_QWindowThread_Sample/Bico_QWindowThread_Sample_UI.h"
#include "Client_Code/Task_1/Task_1_UI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    Bico_QWindowThread::setMainApp(&app);

// -----------------------------------------------------------------------------------------------------------------------------------------------
     Bico_QWindowThread_Sample_UI* ui = Bico_QWindowThread_UI::createNew<Bico_QWindowThread_Sample_UI>
             (
                 "task_0",
                 Bico_QWindowThread::createNew<Bico_QWindowThread_Sample>
                 (
                     new Bico_DataQueue,
                     1,
                     new Bico_DataQueue,
                     1,
                     "task_0"
                 )
             );

     Bico_QWindowThread_Sample_UI* ui1 = Bico_QWindowThread_UI::createNew<Bico_QWindowThread_Sample_UI>
             (
                 "task_1",
                 Bico_QWindowThread::createNew<Bico_QWindowThread_Sample>
                 (
                     new Bico_DataQueue,
                     1,
                     new Bico_DataQueue,
                     1,
                     "task_1"
                 )
             );

     ui->show();
     ui1->show();

// -----------------------------------------------------------------------------------------------------------------------------------------------


// // -----------------------------------------------------------------------------------------------------------------------------------------------
//     Task_1_UI* ui = Bico_QWindowThread_UI::createNew<Task_1_UI>
//         (
//             "task_0",
//             Bico_QWindowThread::createNew<Bico_QWindowThread_Sample>
//             (
//                 new Bico_DataQueue,
//                 1,
//                 new Bico_DataQueue,
//                 1,
//                 "task_0"
//                 )
//             );

//     Task_1_UI* ui1 = Bico_QWindowThread_UI::createNew<Task_1_UI>
//         (
//             "task_1",
//             Bico_QWindowThread::createNew<Bico_QWindowThread_Sample>
//             (
//                 new Bico_DataQueue,
//                 1,
//                 new Bico_DataQueue,
//                 1,
//                 "task_1"
//                 )
//             );

//     ui->show();
//     ui1->show();

// // -----------------------------------------------------------------------------------------------------------------------------------------------

//    Bico_QWindowThread_Sample* thread = Bico_QWindowThread_Sample::createNew<Bico_QWindowThread_Sample>
//            (
//                new Bico_DataQueue,
//                1,
//                new Bico_DataQueue,
//                1,
//                "task_0",
//                Bico_QWindowThread_Sample_UI::createNew<Bico_QWindowThread_Sample_UI>("task_0")
//            );

//    Bico_QWindowThread_Sample* thread1 = Bico_QWindowThread_Sample::createNew<Bico_QWindowThread_Sample>
//            (
//                new Bico_DataQueue,
//                1,
//                new Bico_DataQueue,
//                1,
//                "task_1",
//                Bico_QWindowThread_Sample_UI::createNew<Bico_QWindowThread_Sample_UI>("task_1")
//            );

//    thread->start();
//    thread1->start();
// -----------------------------------------------------------------------------------------------------------------------------------------------





// -----------------------------------------------------------------------------------------------------------------------------------------------
//    Bico_QWindowThread_Sample_UI* ui = Bico_QWindowThread_Sample_UI::createNew<Bico_QWindowThread_Sample_UI>("task_0");
//    Bico_QWindowThread_Sample_UI* ui1 = Bico_QWindowThread_Sample_UI::createNew<Bico_QWindowThread_Sample_UI>("task_1");

//    ui->show();
//    ui1->show();

// -----------------------------------------------------------------------------------------------------------------------------------------------

//   Bico_QWindowThread_Sample* thread = Bico_QWindowThread_Sample::createNew<Bico_QWindowThread_Sample>(new Bico_DataQueue, 1, new Bico_DataQueue, 1, "task_0");
//   Bico_QWindowThread_Sample* thread1 = Bico_QWindowThread_Sample::createNew<Bico_QWindowThread_Sample>(new Bico_DataQueue, 1, new Bico_DataQueue, 1, "task_1");

//   thread->start();
//   thread1->start();
// -----------------------------------------------------------------------------------------------------------------------------------------------

    return app.exec();
}
