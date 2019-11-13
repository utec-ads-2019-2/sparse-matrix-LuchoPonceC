#include <iostream>
#include "matrix.h"

int main() {

	Matrix<int> sparse;
    Matrix<int> sparse2;
    Matrix<int> pruebas;


    //READ FROM A TXT;
    sparse<<"matrix1.txt";

    sparse2<<"matrix2.txt";

    cout<<"------------------MATRIZ 1-------------"<<endl;

   	cout<<sparse;
    cout<<"------------------MATRIZ 2-------------"<<endl;

    cout<<sparse2;
    cout<<"-------------------SUMA---------------"<<endl;
    pruebas = sparse + sparse2;

    cout<<pruebas;
    cout<<"-------------------RESTA--------------"<<endl;
    pruebas = sparse - sparse2;
    cout<<pruebas;
    
    cout<<"--------------TRANSPUESTA-------------"<<endl;
    pruebas = sparse.transpose();
    cout<<pruebas;
    
    cout<<"------------MULTIPLICACION-------------"<<endl;
    //pruebas = sparse * sparse2;
    //cout<<pruebas;

    cout<<"-------MULTIPLICACION ESCALAR----------"<<endl;
    pruebas = sparse*2;
    cout<<pruebas;
    return 0;
}

