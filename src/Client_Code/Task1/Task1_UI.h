#ifndef TASK1_UI_H
#define TASK1_UI_H

#include <QMainWindow>
#include <QCloseEvent>

#include "bico_qwindowthread_ui.h"
#include "Task1.h"
#include "ui_Task1_UI.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Task1_UI; }
QT_END_NAMESPACE

class Task1_UI : public Bico_QWindowThread_UI
{
    Q_OBJECT

public:
    Task1_UI
    (
        QString obj_name, Bico_QWindowThread* thread, 
        QWidget* parent
    ) : Bico_QWindowThread_UI(obj_name, thread, parent), ui(new Ui::Task1_UI)
    {
        ui->setupUi(this);
        moreUISetup();
    }

    void moreUISetup();
    void fromThreadHandling(QString mess, QVariant data);

private:
    Ui::Task1_UI *ui;

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};
#endif // TASK1_UI_H
