/*
Базовый класс – массив вещественных чисел, производный класс – массив вещественных 
чисел,  представленных в  виде  пар  чисел  x=M*10^e,  где  M  – мантисса  числа,  e  – 
экспонента (например, число 15.432=1.5432*10^(1), то есть: M=1.5432 e=1). Определите в нем конструктор, деструктор, конструктор копирования, оператор присваивания. 
Переопределите  операции  вставки,  удаления  элемента,  а  также  операторы:  [ ], +=, -=, *=, /=. 
Арифметические операторы применяются поэлементно.
*/


#include <iostream>
#include <tuple>

using namespace std;

class RealNumbers
{
    protected:
        double* pointer;
        int length;
    public:
        RealNumbers(int size = 0): pointer(NULL), length(0)
        {
            if (size > 0)
                pointer = new double [size];
            if (pointer) length = size;
        }
        RealNumbers(const RealNumbers & original_array): pointer(NULL), length(0)
        {
            if (original_array.length > 0)
                pointer = new double [original_array.length];
            if (pointer)
            {
                length = original_array.length;
                for (int i = 0; i < length; i++)
                {
                    pointer[i] = original_array.pointer[i];
                }
                
            }
        }
        ~RealNumbers()
        {
            delete [] pointer;
        }

        int size() const
        {
            return length;
        }
        double* GetPointer() const
        {
            return this->pointer;
        }
        
        double& operator[] (int index)
        {
            return pointer[index];
        }
        double operator[] (int index) const
        {
            return pointer[index];
        }

        void Insert(double number)
        {          
            double* temp = new double[this->length + 1];
            for (int i = 0; i < this->length; i++)
            {
                temp[i] = (*this)[i];
            }
            temp[this->length] = number;
            delete [] this->pointer;
            this->pointer = temp;
            this->length++;
        }
        void Erase(int index)
        {
            double* temp = new double[this->length + 1];
            for (int i = 0; i < index; i++)
            {
                temp[i] = (*this)[i];
            }
            for (int i = index; i < this->length - 1; i++)
            {
                temp[i] = (*this)[i + 1];
            }            
            delete [] this->pointer;
            this->pointer = temp;
            this->length--;
        }
};

ostream& operator<<(ostream& os, RealNumbers vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        os << vector[i] << ' ';
    }
    return os;
}

class NormalForm: public RealNumbers
{
    public:
        NormalForm(int size = 0)
        {
            pointer = NULL;
            length = 0;
            if (size > 0)
                pointer = new double [size];
            if (pointer) length = size;
        }
        NormalForm(const NormalForm& original_array)
        {
            if (original_array.length > 0)
                pointer = new double [original_array.length];
            if (pointer)
            {
                length = original_array.length;
                for (int i = 0; i < length; i++)
                {
                    pointer[i] = original_array.pointer[i];
                }
            }
        }
        ~NormalForm()
        {
            delete [] pointer;
        }

        tuple<double, int> GetBoth(int index)
        {
            double mantissa = pointer[index];
            int exponent = 0;
            while (mantissa < 1 || mantissa >= 10)
            {
                if(mantissa < 1)
                {
                    mantissa *= 10;
                    exponent--;
                }
                else
                {
                    mantissa /= 10;
                    exponent++;
                }
            }
            return {mantissa, exponent};
        }
        
        tuple<double, int> operator[] (int index)
        {
            return GetBoth(index);
        }
        double& operator() (int index)
        {
            return pointer[index];
        }
        NormalForm& operator= (NormalForm original)
        {
            if(this->length != original.length)
            {
                cout << "Error!!!";
                return;
            }
            else
            {
                for (int i = 0; i < this->length; i++)
                {
                    this->pointer[i] = original.pointer[i];
                }
            }
        }
        void operator+= (const NormalForm array)
        {
            if(this->length != array.length)
            {
                cout << "Error!!!" << endl;
            }
            else 
            {
                for (int i = 0; i < length; i++)
                {
                    this->pointer[i] += array.pointer[i];
                }
            }            
        }
        void operator-= (const NormalForm array)
        {
            if(this->length != array.length)
            {
                cout << "Error!!!" << endl;
            }
            else 
            {
                for (int i = 0; i < length; i++)
                {
                    this->pointer[i] -= array.pointer[i];
                }
            }            
        }
        void operator*= (const NormalForm array)
        {
            if(this->length != array.length)
            {
                cout << "Error!!!" << endl;
            }
            else 
            {
                for (int i = 0; i < length; i++)
                {
                    this->pointer[i] *= array.pointer[i];
                }
            }            
        }
        void operator/= (const NormalForm array)
        {
            if(this->length != array.length)
            {
                cout << "Error!!!" << endl;
            }
            else 
            {
                for (int i = 0; i < length; i++)
                {
                    this->pointer[i] /= array.pointer[i];
                }
            }            
        }

        void Insert(double number)
        {
            cout << "Overloaded function Insert was used" << endl;          
            double* temp = new double[this->length + 1];
            for (int i = 0; i < this->length; i++)
            {
                temp[i] = (*this)(i);
            }
            temp[this->length] = number;
            delete [] this->pointer;
            this->pointer = temp;
            this->length++;
        }
        void Erase(int index)
        {
            cout << "Overloaded function Erase was used" << endl;  
            double* temp = new double[this->length + 1];
            for (int i = 0; i < index; i++)
            {
                temp[i] = (*this)(i);
            }
            for (int i = index; i < this->length - 1; i++)
            {
                temp[i] = (*this)(i + 1);
            }            
            delete [] this->pointer;
            this->pointer = temp;
            this->length--;
        }
};

int main()
{

}