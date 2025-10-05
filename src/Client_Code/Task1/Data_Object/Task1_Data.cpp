#include "Task1_Data.h"



Task1_Data::Task1_Data()
{
    data_1 = 50;
    data_2 = 100;
}

int Task1_Data::getData_1() const
{
    return data_1;
}

void Task1_Data::setData_1(int value)
{
    data_1 = value;
}

float Task1_Data::getData_2() const
{
    return data_2;
}

void Task1_Data::setData_2(float value)
{
    data_2 = value;
}
