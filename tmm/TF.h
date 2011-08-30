#ifndef TF_H_INCLUDED
#define TF_H_INCLUDED

struct TF
{
private:
    double TF0;
    double TF1;
    double TF2;
    bool calculatedTF0;
    bool calculatedTF1;
    bool calculatedTF2;
public:
    /**
    @brief ����������� ������
    */
    TF();

    /**
    @brief ������������� ��0
    */
    void SetTF0(double tf0);

    /**
    @return true, ���� ��0 ���������
    */
    bool IsCalculatedTF0();

    /**
    @return ��0
    */
    double GetTF0();

    /**
    @brief ������������� ��1
    */
    void SetTF1(double tf1);

    /**
    @return true, ���� ��1 ���������
    */
    bool IsCalculatedTF1();

    /**
      @return ��1
    */
    double GetTF1();

    /**
    @brief ������������� ��2
    */
    void SetTF2(double tf2);

    /**
    @return true, ���� ��2 ���������
    */
    bool IsCalculatedTF2();

    /**
    @return ��2
    */
    double GetTF2();

    /**
    @brief ������� ������� ����������
    */
    void UnsetCalculated();
};

#endif // TF_H_INCLUDED
