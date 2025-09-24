#include "Task_1_Data.h"



Task_1_Data::Task_1_Data()
{
    data_1 = 50;
    data_2 = 100;
}

int Task_1_Data::getData_1() const
{
    return data_1;
}

void Task_1_Data::setData_1(int value)
{
    data_1 = value;
}

float Task_1_Data::getData_2() const
{
    return data_2;
}

void Task_1_Data::setData_2(float value)
{
    data_2 = value;
}
