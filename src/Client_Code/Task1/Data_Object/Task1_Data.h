#ifndef TASK1_DATA_H
#define TASK1_DATA_H

class Task1_Data
{
public:
    Task1_Data();
    

    int getData_1() const;
    void setData_1(int value);

    float getData_2() const;
    void setData_2(float value);

private:
    int data_1;
    float data_2;
};

#endif // TASK1_H
