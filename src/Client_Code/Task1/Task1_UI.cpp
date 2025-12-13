#include "Task1_UI.h"

void Task1_UI::closeEvent(QCloseEvent *event)
{
    // Handle the window close event by requesting thread termination
    event->ignore();
    emit toThread("terminate", "");
}

void Task1_UI::moreUISetup()
{
    // more setting up when the ui started
    
    ui->pushButton->resize(QSize(100, 50));
}

void Task1_UI::fromThreadHandling(QString mess, QVariant data)
{
    if(mess == "show")
    {
        show();
    }
    else if (mess == "hide")
    {
        hide();
    }
    else if (mess == "terminate")
    {
        // Close the window when thread terminates
        close();
    }
    else if(mess == "change_button_text")
    {
        ui->pushButton->setText(data.value<QString>());
    }
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// Send data to thread thread
void Task1_UI::on_pushButton_clicked()
{
    qDebug() << "Task1_UI: Button clicked, sending message to thread.";
    emit toThread("mess_from_ui", "button_clicked");
}


void Task1_UI::on_pushButton_2_clicked()
{
    emit toThread("create", "");
}

void Task1_UI::on_pushButton_3_clicked()
{
    emit toThread("create_child", "");
}
