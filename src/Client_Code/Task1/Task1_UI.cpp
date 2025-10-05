#include "Task1_UI.h"

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
        TERMINATE;
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
    emit toThread("mess_from_ui", "button_clicked");
}


void Task1_UI::on_pushButton_2_clicked()
{
    emit toThread("1", "111");
}

void Task1_UI::on_pushButton_3_clicked()
{
    emit toThread("2", "222");
}
