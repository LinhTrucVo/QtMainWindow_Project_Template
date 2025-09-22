#include "Bico_QWindowThread_Sample_Data.h"



Bico_QWindowThread_Sample_Data::Bico_QWindowThread_Sample_Data()
{
    data_1 = 50;
    data_2 = 100;
}

int Bico_QWindowThread_Sample_Data::getData_1() const
{
    return data_1;
}

void Bico_QWindowThread_Sample_Data::setData_1(int value)
{
    data_1 = value;
}

float Bico_QWindowThread_Sample_Data::getData_2() const
{
    return data_2;
}

void Bico_QWindowThread_Sample_Data::setData_2(float value)
{
    data_2 = value;
}
