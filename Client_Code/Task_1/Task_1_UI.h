#ifndef TASK_1_UI_H
#define TASK_1_UI_H

#include <QMainWindow>
#include <QCloseEvent>

#include "../../Template_Material/bico_qwindowthread_ui.h"
#include "Task_1.h"
#include "ui_Task_1_UI.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Task_1_UI; }
QT_END_NAMESPACE

class Task_1_UI : public Bico_QWindowThread_UI
{
    Q_OBJECT

public:
    Task_1_UI
    (
        QString obj_name, Bico_QWindowThread* thread, 
        QWidget* parent
    ) : Bico_QWindowThread_UI(obj_name, thread, parent), ui(new Ui::Task_1_UI)
    {
        ui->setupUi(this);
        moreUISetup();
    }

    void moreUISetup();
    void fromThreadHandling(QString mess, QVariant data);

private:
    Ui::Task_1_UI *ui;

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};
#endif // TASK_1_UI_H
