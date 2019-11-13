#include <iostream>

#include "tester/tester.h"

int main() {
	//Tester::execute();
	Matrix<int> sparse(3,3);
    
    
    sparse.set(2,1,20);

    sparse.set(1,0,5);

    sparse.set(2,1,550);

  
    sparse.set(2,2,22);

    Matrix<int> scalar = sparse*2;
    sparse.set(0,1,20);
    scalar.set(1,2,88);
    scalar.set(0,2,15);
    cout<<"------------------MATRIZ 1-------------"<<endl;
   	scalar.print();
    cout<<"------------------MATRIZ 2-------------"<<endl;
    sparse.print();
    

    cout<<"-------------------SUMA---------------"<<endl;
    Matrix<int> nuevo = scalar + sparse;
    nuevo.print();
    cout<<"-------------------RESTA--------------"<<endl;
    Matrix<int> nuevoResta = scalar - sparse;
    nuevoResta.print();
    cout<<"--------------TRANSPUESTA-------------"<<endl;
    Matrix<int> nuevoTranspuesta = nuevoResta.transpose();
    nuevoTranspuesta.print();
    cout<<"------------MULTIPLICACION-------------"<<endl;
    Matrix<int> nuevoMult = nuevoTranspuesta*nuevoTranspuesta;
    nuevoMult.print();
    return 0;
}

