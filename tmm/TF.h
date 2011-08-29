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
    @brief Конструктор класса
    */
    TF();

    /**
    @brief Устанавливает ПФ0
    */
    void SetTF0(double tf0);

    /**
    @return true, если ПФ0 вычеслена
    */
    bool IsCalculatedTF0();

    /**
    @return ПФ0
    */
    double GetTF0();

    /**
    @brief Устанавливает ПФ1
    */
    void SetTF1(double tf1);

    /**
    @return true, если ПФ1 вычеслена
    */
    bool IsCalculatedTF1();

    /**
      @return ПФ1
    */
    double GetTF1();

    /**
    @brief Устанавливает ПФ2
    */
    void SetTF2(double tf2);

    /**
    @return true, если ПФ2 вычеслена
    */
    bool IsCalculatedTF2();

    /**
    @return ПФ2
    */
    double GetTF2();

    /**
    @brief Убирает признак вычисления
    */
    void UnsetCalculated();
};

#endif // TF_H_INCLUDED
