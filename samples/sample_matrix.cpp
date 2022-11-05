// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include <ctime>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void Rand_Add_M(TDynamicMatrix<int>& a) {
    srand(time(0) + clock());
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            a[i][j] = rand() % 301;
        }
    }
}

void test_for_matrix(TDynamicMatrix<int> a, TDynamicMatrix<int> b, TDynamicMatrix<int> c) {
    int choice;
    cout << "Выберите операцию: 1) сложение, 2) вычитание, 3) умножение, 4) умножение на скаляр " << endl;
    cin >> choice;
    switch (choice) {
    case 1:
        cout << "c = a + b :" << "\n";
        c = a + b;
        cout << c << endl;
        break;

    case 2:
        cout << "c = a - b :" << "\n";
        c = a - b;
        cout << c << endl;
        break;
    case 3:
        cout << "c = a * b :" << "\n";
        c = a * b;
        cout << c << endl;
        break;
    case 4:
        int l, choice2;

        cout << "Введите '1', если хотите произвести операцию с матрицей 'a', и '2', если с матрицей 'b'" << endl;
        cin >> choice2;
        cout << "Введите скаляр, на который будет умножена матрица" << endl;
        cin >> l;
        switch (choice2) {
        case 1:
            cout << "c = a * скаляр :" << "\n";
            c = a * l;
            cout << c << endl;
            break;
        case 2:
            cout << "c = b * скаляр :" << "\n";
            c = b * l;
            cout << c << endl;
            break;
        default:
            cout << "Введено неверное значение" << endl;
            break;
        }
        break;
    default:
        cout << "Введено неверное значение" << endl;
        break;
    }

}

void main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Тестирование класс работы с матрицами" << endl;
    int size;
    cout << "Введите размер матриц" << endl;
    cin >> size;
    TDynamicMatrix<int> a(size), b(size), c(size);
    int choice;
    cout << "Введите '1', чтобы задать матрицу рандомно, или '2', чтобы задать ее вручную" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        Rand_Add_M(a);
        cout << "Matrix a = " << endl << a << endl;
        Rand_Add_M(b);
        cout << "Matrix b = " << endl << b << endl;
        test_for_matrix(a, b, c);
        break;
    case 2:
        cout << "Введите матрицу 'a'" << endl;
        cin >> a;
        cout << "Matrix a = " << endl << a << endl;
        cout << "Введите матрицу 'b'" << endl;
        cin >> b;
        cout << "Matrix b = " << endl << b << endl;
        test_for_matrix(a, b, c);
        break;
    default:
        cout << "Введено неверное значение" << endl;
        break;
    }
}
//---------------------------------------------------------------------------
