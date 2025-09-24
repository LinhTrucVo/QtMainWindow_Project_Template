#ifndef BICO_QWINDOWTHREAD_SAMPLE_UI_H
#define BICO_QWINDOWTHREAD_SAMPLE_UI_H

#include <QMainWindow>
#include <QCloseEvent>

#include "bico_qwindowthread_ui.h"
#include "Bico_QWindowThread_Sample.h"
#include "ui_Bico_QWindowThread_Sample_UI.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Bico_QWindowThread_Sample_UI; }
QT_END_NAMESPACE

class Bico_QWindowThread_Sample_UI : public Bico_QWindowThread_UI
{
    Q_OBJECT

public:
    Bico_QWindowThread_Sample_UI
    (
        QString obj_name, Bico_QWindowThread* thread, 
        QWidget* parent
    ) : Bico_QWindowThread_UI(obj_name, thread, parent), ui(new Ui::Bico_QWindowThread_Sample_UI)
    {
        ui->setupUi(this);
        moreUISetup();
    }

    void moreUISetup();
    void fromThreadHandling(QString mess, QVariant data);

private:
    Ui::Bico_QWindowThread_Sample_UI *ui;

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};
#endif // BICO_QWINDOWTHREAD_SAMPLE_UI_H
