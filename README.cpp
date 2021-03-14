#include <iostream>     //Definite integral calculator
#include <algorithm>
#include <cmath>

int   fn_GCD(int int_Num1, int int_Num2);   // 最大公因數
int   fn_LCM(int int_Num1, int int_Num2);   // 最小公倍數

struct Coefficient  // 係數結構
{
    int int_Numer = 0;      //分子
    int int_Denomin = 1;    //分母

    void operator-= (Coefficient &coef_Num) //定義此結構的複合指定減號運算子
    {
        int int_TempNumer = coef_Num.int_Numer;
        int int_TempDenom = coef_Num.int_Denomin;

        int int_LCM = fn_LCM(this->int_Denomin, coef_Num.int_Denomin);

        this->int_Numer *= int_LCM / this->int_Denomin;         // 通分過程
        this->int_Denomin = int_LCM;
        coef_Num.int_Numer *= int_LCM / coef_Num.int_Denomin;
        coef_Num.int_Denomin = int_LCM;

        this->int_Numer -= coef_Num.int_Numer; // 分數相減

        int int_GCD = fn_GCD(this->int_Numer, this->int_Denomin);

        this->int_Numer /= int_GCD;     // 約分過程
        this->int_Denomin /= int_GCD;

        coef_Num.int_Numer = int_TempNumer;
        coef_Num.int_Denomin = int_TempDenom;
    }
};

int int_Deg;    // 此多項式之最高次數
Coefficient coef_MaxRes, coef_MinRes; // 上極限函數值, 下極限函數值

int   fn_Pow(int int_Num, int int_Times);
void  fn_Calculate(int int_Max, int int_Min, Coefficient* coefptr_Arr); // 函數值計算
void  fn_Preset(int &int_Max, int &int_Min, Coefficient* coefptr_Arr);  // 初值輸入
void  fn_Antiderivative(Coefficient* coefptr_Arr);  // 求反導函數

int main()
{
    std::cout<< "deg f(x) = ";
    std::cin>> int_Deg;

    int int_Max, int_Min;   // 積分上下極限
    Coefficient* coefptr_Arr = new Coefficient[int_Deg + 2];

    fn_Preset(int_Max, int_Min, coefptr_Arr);
    fn_Antiderivative(coefptr_Arr);
    fn_Calculate(int_Max, int_Min, coefptr_Arr);

    delete [] coefptr_Arr;

    coef_MaxRes -= coef_MinRes; // 上極限函數值 - 下極限函數值

    if(coef_MaxRes.int_Denomin == 1) std::cout<< "Ans: " << coef_MaxRes.int_Numer;
    else std::cout<< "Ans: " << coef_MaxRes.int_Numer << '/' << coef_MaxRes.int_Denomin;

    return 0;
}

int   fn_GCD(int int_Num1, int int_Num2)
{
    int_Num1 = std::abs(int_Num1);
    int_Num2 = std::abs(int_Num2);

    while(int_Num1 % int_Num2)
    {
        int_Num1 %= int_Num2;
        int_Num1 ^= int_Num2 ^= int_Num1 ^= int_Num2;
    }

    return int_Num2;
}

int   fn_LCM(int int_Num1, int int_Num2)
{
    int_Num1 = std::abs(int_Num1);
    int_Num2 = std::abs(int_Num2);

    return int_Num1 * int_Num2 / fn_GCD(int_Num1, int_Num2);
}

int   fn_Pow(int int_Num, int int_Times)
{
    int int_Result = int_Num;

    while(--int_Times) int_Result *= int_Num;

    return int_Result;
}

void  fn_Preset(int &int_Max, int &int_Min, Coefficient* coefptr_Arr)
{
    std::cout<< "\n\n積分上限：";
    std::cin>> int_Max;

    std::cout<< "積分下限：";
    std::cin>> int_Min;

    std::cout<< "\n\n";

    for(int i = int_Deg; i >= 0; i--)
    {
        std::cout<< "x " << i << "次方的系數(分子)：";
        std::cin>> (coefptr_Arr + i)->int_Numer;

        std::cout<< "x " << i << "次方的系數(分母)：";
        std::cin>> (coefptr_Arr + i)->int_Denomin;

        std::cout<< '\n';
    }

    return;
}

void  fn_Antiderivative(Coefficient* coefptr_Arr)
{
    for(int i = int_Deg; i >= 0; i--)
    {
        (coefptr_Arr + i)->int_Denomin *= i + 1;

        if((coefptr_Arr + i)->int_Denomin < 0)
        {
            (coefptr_Arr + i)->int_Denomin *= -1;
            (coefptr_Arr + i)->int_Numer *= -1;
        }

        int int_GCD = fn_GCD((coefptr_Arr + i)->int_Numer,
                             (coefptr_Arr + i)->int_Denomin);

        (coefptr_Arr + i)->int_Numer /= int_GCD;
        (coefptr_Arr + i)->int_Denomin /= int_GCD;

        std::swap(*(coefptr_Arr + i), *(coefptr_Arr + i + 1));
    }

    int_Deg++;

    return;
}

void  fn_Calculate(int int_Max, int int_Min, Coefficient* coefptr_Arr)
{
    int int_TempNumer, int_TempDenom;
    int int_GCD, int_LCM;

    for(int i = int_Deg; i >= 1; i--)
    {
        if((coefptr_Arr + i)->int_Denomin < 0)
        {
            (coefptr_Arr + i)->int_Denomin *= -1;
            (coefptr_Arr + i)->int_Numer *= -1;
        }

        int_TempNumer = (coefptr_Arr + i)->int_Numer;
        int_TempDenom = (coefptr_Arr + i)->int_Denomin;

        (coefptr_Arr + i)->int_Numer *= fn_Pow(int_Max, i);

        int_GCD = fn_GCD((coefptr_Arr + i)->int_Numer, (coefptr_Arr + i)->int_Denomin);

        (coefptr_Arr + i)->int_Numer /= int_GCD;
        (coefptr_Arr + i)->int_Denomin /= int_GCD;

        int_LCM = fn_LCM(coef_MaxRes.int_Denomin, (coefptr_Arr + i)->int_Denomin);

        coef_MaxRes.int_Numer *= int_LCM / coef_MaxRes.int_Denomin;
        coef_MaxRes.int_Denomin = int_LCM;
        (coefptr_Arr + i)->int_Numer *= int_LCM / (coefptr_Arr + i)->int_Denomin;
        (coefptr_Arr + i)->int_Denomin = int_LCM;

        coef_MaxRes.int_Numer += (coefptr_Arr + i)->int_Numer;

        (coefptr_Arr + i)->int_Numer = int_TempNumer;
        (coefptr_Arr + i)->int_Denomin = int_TempDenom;

        int_GCD = fn_GCD(coef_MaxRes.int_Numer, coef_MaxRes.int_Denomin);

        coef_MaxRes.int_Numer /= int_GCD;
        coef_MaxRes.int_Denomin /= int_GCD;
    }

    for(int i = int_Deg; i >= 1; i--)
    {
        if((coefptr_Arr + i)->int_Denomin < 0)
        {
            (coefptr_Arr + i)->int_Denomin *= -1;
            (coefptr_Arr + i)->int_Numer *= -1;
        }

        int_TempNumer = (coefptr_Arr + i)->int_Numer;
        int_TempDenom = (coefptr_Arr + i)->int_Denomin;

        (coefptr_Arr + i)->int_Numer *= fn_Pow(int_Min, i);

        int_GCD = fn_GCD((coefptr_Arr + i)->int_Numer, (coefptr_Arr + i)->int_Denomin);

        (coefptr_Arr + i)->int_Numer /= int_GCD;
        (coefptr_Arr + i)->int_Denomin /= int_GCD;

        int_LCM = fn_LCM(coef_MinRes.int_Denomin, (coefptr_Arr + i)->int_Denomin);

        coef_MinRes.int_Numer *= int_LCM / coef_MinRes.int_Denomin;
        coef_MinRes.int_Denomin = int_LCM;
        (coefptr_Arr + i)->int_Numer *= int_LCM / (coefptr_Arr + i)->int_Denomin;
        (coefptr_Arr + i)->int_Denomin = int_LCM;

        coef_MinRes.int_Numer += (coefptr_Arr + i)->int_Numer;

        (coefptr_Arr + i)->int_Numer = int_TempNumer;
        (coefptr_Arr + i)->int_Denomin = int_TempDenom;

        int_GCD = fn_GCD(coef_MinRes.int_Numer, coef_MinRes.int_Denomin);

        coef_MinRes.int_Numer /= int_GCD;
        coef_MinRes.int_Denomin /= int_GCD;
    }

    return;
}
