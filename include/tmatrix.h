﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if ((sz <= 0) || (sz > MAX_VECTOR_SIZE))
            throw out_of_range("Vector size should be greater than zero and less than max_size of vector");
        pMem = new T[sz]{};// У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if ((sz <= 0) || (sz > MAX_VECTOR_SIZE))
            throw out_of_range("Vector size should be greater than zero and less than max_size of vector");
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v) return *this;
        if (sz != v.sz) {
            T* p = new T[v.sz];
            delete[] pMem;
            sz = v.sz;
            pMem = p;
        }
        std::copy(v.pMem, v.pMem + v.sz, pMem);
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        sz = 0;
        delete[] pMem;
        pMem = nullptr;
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }


    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind < 0 || ind >= sz) throw out_of_range("incorrect index");
        else return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind < 0 || ind >= sz) throw out_of_range("incorrect index");
        else return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return 0;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) return 0;
        }
        return 1;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(*this);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] += val;
        }
        return tmp;
    }
    TDynamicVector operator-(double val)
    {
        TDynamicVector tmp(*this);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] -= val;
        }
        return tmp;
    }
    TDynamicVector operator*(double val)
    {
        TDynamicVector tmp(*this);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] *= val;
        }
        return tmp;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) throw out_of_range("Unequal sizes");
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] + v.pMem[i];
        }
        return tmp;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) throw out_of_range("Unequal sizes");
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] - v.pMem[i];
        }
        return tmp;
    }
    T operator*(const TDynamicVector& v) 
    {
        if (sz != v.sz) throw out_of_range("Unequal sizes");
        T res = 0;
        for (size_t i = 0; i < sz; i++) {
            res += pMem[i] * v.pMem[i];
        }
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz > MAX_MATRIX_SIZE) throw out_of_range("size should be less than max size of matrix");
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }

    size_t size() noexcept { return sz; }

    T& at(int ind1, int ind2) {
        if ((ind1 < 0 || ind1 >= sz) || (ind2 < 0 || ind2 >= sz)) throw out_of_range("incorrect index");
        else return pMem[ind1][ind2];
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator==(m);
    }

    // матрично-скалярные операции
    TDynamicMatrix<T> operator*(const T& val)
    {
        TDynamicMatrix<T> tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] * val;
        }
        return tmp;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        TDynamicVector<T> tpm(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] * v;
        }
        return tmp;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        TDynamicMatrix<T> tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] + m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        TDynamicMatrix<T> tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] - m.pMem[i];
        }
        return tmp;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw out_of_range("Unequal sizes");
        TDynamicMatrix<T> tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                for (size_t k = 0; k < sz; k++) {
                    tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
                }
            }
        }
        return tmp;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            for (size_t j = 0; j < v.sz; j++) {
                istr >> v.pMem[i][j];
            }
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            for (size_t j = 0; j < v.sz; j++) {
                ostr << v.pMem[i][j] << ' ';
            }
            ostr << '\n';
        }
        return ostr;
    }
};

#endif
