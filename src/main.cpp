#include <QApplication>

#include "Client_Code/Task1/Task1_UI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    Bico_QWindowThread::setMainApp(&app);

// // -----------------------------------------------------------------------------------------------------------------------------------------------
    Task1_UI* ui = Bico_QWindowThread_UI::createNew<Task1_UI>
        (
            "task_0",
            Bico_QWindowThread::createNew<Task1>
            (
                new Bico_DataQueue,
                1,
                new Bico_DataQueue,
                1,
                "task_0"
                )
            );
    ui->show();

//     Task1_UI* ui1 = Bico_QWindowThread_UI::createNew<Task1_UI>
//         (
//             "task_1",
//             Bico_QWindowThread::createNew<Task1>
//             (
//                 new Bico_DataQueue,
//                 1,
//                 new Bico_DataQueue,
//                 1,
//                 "task_1"
//                 )
//             );

//     ui1->show();

// // -----------------------------------------------------------------------------------------------------------------------------------------------

//    Task1* thread = Task1::createNew<Task1>
//            (
//                new Bico_DataQueue,
//                1,
//                new Bico_DataQueue,
//                1,
//                "task_0",
//                Task1_UI::createNew<Task1_UI>("task_0")
//            );
//    thread->start();

//    Task1* thread1 = Task1::createNew<Task1>
//            (
//                new Bico_DataQueue,
//                1,
//                new Bico_DataQueue,
//                1,
//                "task_1",
//                Task1_UI::createNew<Task1_UI>("task_1")
//            );

//    thread1->start();
// -----------------------------------------------------------------------------------------------------------------------------------------------





// -----------------------------------------------------------------------------------------------------------------------------------------------
//    Task1_UI* ui = Task1_UI::createNew<Task1_UI>("task_0");
//    ui->show();

//    Task1_UI* ui1 = Task1_UI::createNew<Task1_UI>("task_1");
//    ui1->show();

// -----------------------------------------------------------------------------------------------------------------------------------------------

//   Task1* thread = Task1::createNew<Task1>(new Bico_DataQueue, 1, new Bico_DataQueue, 1, "task_0");
//   thread->start();

//   Task1* thread1 = Task1::createNew<Task1>(new Bico_DataQueue, 1, new Bico_DataQueue, 1, "task_1");
//   thread1->start();
// -----------------------------------------------------------------------------------------------------------------------------------------------

    return app.exec();
}
