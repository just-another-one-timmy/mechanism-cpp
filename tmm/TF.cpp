#include"TF.h"

TF::TF()
{
    calculatedTF0=false;
    calculatedTF1=false;
    calculatedTF2=false;

}

void TF::SetTF0(double tf0)
{
    TF0=tf0;
    calculatedTF0=true;
}

bool TF::IsCalculatedTF0()
{
   return calculatedTF0;
}

double TF::GetTF0()
{
    if (!calculatedTF0)
        throw "TF: GetTF0 : TF0 not calculated";
    return TF0;
}


void TF::SetTF1(double tf1)
{
    TF1=tf1;
    calculatedTF1=true;
}

bool TF::IsCalculatedTF1()
{
    return calculatedTF1;
}

double TF::GetTF1()
{
    if (!calculatedTF1)
        throw "TF: GetTF1 : TF1 not calculated";
    return TF1;
}


void TF::SetTF2(double tf2)
{
    TF2=tf2;
    calculatedTF2=true;
}

bool TF::IsCalculatedTF2()
{
    return calculatedTF2;
}

double TF::GetTF2()
{
    if (!calculatedTF2)
        throw "TF: GetTF2 : TF2 not calculated";
    return TF2;
}

void TF::UnsetCalculated()
{
    calculatedTF0 = false;
    calculatedTF1 = false;
    calculatedTF2 = false;
}
