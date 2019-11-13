#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H
#include "node.h"
#include <stdexcept>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root;
    unsigned rows, columns;
    

    void column_insert(unsigned posy,T &data, Node<T> *& temp);
    void row_insert(unsigned posx,T &data, Node<T> *& temp);


public:
    vector<Node<T>*> Ro,Co;
    Matrix(unsigned rows, unsigned columns);
    unsigned get_rows(){return rows;}
    unsigned get_columns(){return columns;}
    //con el set 0 se elimina el nodo, no se inserta el 0;
    void set(unsigned, unsigned, T);//listo
    T operator()(unsigned, unsigned) const;//listo
    Matrix<T> operator*(T scalar) const;//listo
    Matrix<T> operator*(Matrix<T> &other) const;//listo
    Matrix<T> operator+(Matrix<T> &other) const;//listo
    Matrix<T> operator-(Matrix<T> &other) const;//listo
    Matrix<T> operator=(Matrix<T> *other) const;
    Matrix<T> transpose();//listo
    void print() const;//listo

    ~Matrix();
};



template <typename T>
Matrix<T>::~Matrix(){

    for(auto itRo : Ro){
        //cout<<itRo->get_data()<<endl;
        itRo->killSelf();
    }
    Ro.clear();
    Co.clear();
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> &other) const{
    Matrix<T> Temp = Matrix<T>(this->rows,this->columns);
    Node<T>*const*itRo = nullptr;
    Node<T>*const*itCo = nullptr;
    for(int i=0;i<(this->Ro).size();i++){

        for(int j=0;j<(this->Co).size();j++){

            itCo = &((this->Co)[j]);
            itRo = &((this->Ro)[i]);
        
            T valor = 0;

            while((*itRo)!=nullptr and (*itCo)!=nullptr){
                
                if((*itRo)->get_posy()==(*itCo)->get_posx()){

                    valor += ((*itRo)->get_data())*((*itCo)->get_data());
                    
                    itRo = &(*itRo)->next;
                    itCo = &(*itCo)->down;
                    continue;

                }
                itRo = &(*itRo)->next;
                while(((*itRo)!=nullptr and (*itCo)!=nullptr) and (*itRo)->get_posy()>(*itCo)->get_posx()){
                    itCo = &(*itCo)->down;
                
                }
            }
            if(valor!=0){
                itRo = &((this->Ro)[i]);
                itCo = &((this->Co)[j]);

                Temp.set((*itRo)->get_posx(),(*itCo)->get_posy(),valor);

            }
            
                
        }
    }
    return Temp;
}


template <typename T>
Matrix<T> Matrix<T>::transpose(){
    Matrix<T> Temp = Matrix<T>(this->columns,this->rows);
    for(auto it : Ro){
        while(it!=nullptr){
            Temp.set(it->get_posy(),it->get_posx(),(it->get_data()));
            it=it->next;
        }
    }
    return Temp;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const{
    Matrix<T> Temp = Matrix(this->rows,this->columns);
    for(auto it : Ro){
        
        while(it!=nullptr){
            Temp.set(it->get_posx(),it->get_posy(),(scalar*(it->get_data())));
            it=it->next;
        }
    }
    return Temp;

}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> &other) const{
    if((this->rows != other.get_rows())or(this->columns != other.get_columns())) throw exception();
    Matrix<T> Temp = Matrix<T>(this->rows,this->columns);
    Node<T>*const*it1 = nullptr;
    Node<T>*const*it2 = nullptr;
    for(int i=0;i<(this->Ro).size();i++){
    
        it1 = &((this->Ro)[i]);
        it2 = &((other.Ro)[i]);

        while((*it1)!=nullptr or (*it2)!=nullptr){

            

            if((*it1)==nullptr){
                
                Temp.set((*it2)->get_posx(),(*it2)->get_posy(),(*it2)->get_data());
                it2 = &(*it2)->next;
                continue;

            }

            if((*it2)==nullptr){
                
                Temp.set((*it1)->get_posx(),(*it1)->get_posy(),(*it1)->get_data());
                it1 = &(*it1)->next;
                continue;
            }

            if((*it1)->get_posy()==(*it2)->get_posy()){
                
                
                Temp.set((*it1)->get_posx(),(*it1)->get_posy(),((*it1)->get_data()+(*it2)->get_data()));
                it1 = &(*it1)->next;
                it2 = &(*it2)->next;
                continue;

            }

            if((*it1)->get_posy()<(*it2)->get_posy())
            {
                Temp.set((*it1)->get_posx(),(*it1)->get_posy(),(*it1)->get_data());
                it1 = &(*it1)->next;  
            }
            else{
                while(((*it2)!=nullptr) and (*it1)->get_posy()>(*it2)->get_posy()){
                    Temp.set((*it2)->get_posx(),(*it2)->get_posy(),(*it2)->get_data());
                    it2 = &(*it2)->next;
                  
                }
            }
            
            

        }
    }

    return Temp;

}


template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> &other) const{
    if((this->rows != other.get_rows())or(this->columns != other.get_columns())) throw exception();
    Matrix<T> Temp =  Matrix<T>(this->rows,this->columns);
    Node<T>*const*it1 = nullptr;
    Node<T>*const*it2 = nullptr;
    for(int i=0;i<(this->Ro).size();i++){
    
        it1 = &((this->Ro)[i]);
        it2 = &((other.Ro)[i]);

        while((*it1)!=nullptr or (*it2)!=nullptr){

            //cout<<&(*it1)<<"-"<<&(*it2)<<endl;

            if((*it1)==nullptr){
                //cout<<"entro en lo primero"<<endl;
                Temp.set((*it2)->get_posx(),(*it2)->get_posy(),-(*it2)->get_data());
                it2 = &(*it2)->next;
                continue;

            }

            if((*it2)==nullptr){
                //cout<<"entro en lo segundo"<<endl;
                Temp.set((*it1)->get_posx(),(*it1)->get_posy(),(*it1)->get_data());
                it1 = &(*it1)->next;
                continue;
            }

            if((*it1)->get_posy()==(*it2)->get_posy()){
                //cout<<"entro aca"<<endl;
                //cout<<(*it1)->get_posx()<<" - "<<(*it1)->get_posy()<<" "<<(*it1)->get_data()<<" "<<(*it2)->get_data()<<endl;
                Temp.set((*it1)->get_posx(),(*it1)->get_posy(),((*it1)->get_data()-(*it2)->get_data()));
                it1 = &(*it1)->next;
                it2 = &(*it2)->next;
                continue;

            }

            if((*it1)->get_posy()<(*it2)->get_posy())
            {
                Temp.set((*it1)->get_posx(),(*it1)->get_posy(),(*it1)->get_data());
                it1 = &(*it1)->next;  
            }
            else{
                while(((*it2)!=nullptr) and (*it1)->get_posy()>(*it2)->get_posy()){
                    Temp.set((*it2)->get_posx(),(*it2)->get_posy(),-(*it2)->get_data());
                    it2 = &(*it2)->next;
                  
                }
            }


            

        }
    }

    return Temp;

}



template <typename T>
Matrix<T>::Matrix(unsigned rows, unsigned columns) : rows(rows), columns(columns){
    Ro.resize(rows,nullptr);
    Co.resize(columns,nullptr);
    
}

template <typename T>
void Matrix<T>::column_insert(unsigned posy,T &data,Node<T> *& temp){
    bool insert_co = false;
    if(Co[posy]==nullptr){

        Co[posy]=temp;
        insert_co = true;
    }

    if(!insert_co){
        Node<T> **findCol = &(Co[posy]);

        while((*findCol)  and (temp->get_posx()>(*findCol)->get_posx()) ){

            findCol = &(*findCol)->down;
        }
        if(temp->get_data()==0){
            if(*findCol==nullptr or temp->get_posx()!=(*findCol)->get_posx() )throw exception();
            Node<T> *del = (*findCol);
            (*findCol)=(*findCol)->down;
            delete del;
            return;
        }

        temp->down = (*findCol);
        (*findCol) =  temp;
    }

}

template <typename T>
void Matrix<T>::row_insert(unsigned posx,T &dat,Node<T> *& temp){
    bool insert_ro = false;
    if(Ro[posx]==nullptr){
        Ro[posx]=temp;
        insert_ro = true;
    }

    if(!insert_ro){
        Node<T> **findRow = &(Ro[posx]);
        

        while((*findRow)  and (temp->get_posy()>(*findRow)->get_posy())) {
            findRow = &(*findRow)->next;
        }

        if(temp->get_data()==0){
            if(*findRow==nullptr or temp->get_posy()!=(*findRow)->get_posy() )throw exception();
            Node<T> *del = (*findRow);
            (*findRow)=(*findRow)->next;
            return;
        }

        if(*findRow!=nullptr){

            if(temp->get_posy()==(*findRow)->get_posy()){
                ((*findRow)->set_data(temp->get_data()));
                delete temp;
                temp=nullptr;
                return;

            }
        }

        temp->next = (*findRow);
        (*findRow) = temp;
    }

}


template <typename T>
void Matrix<T>::set(unsigned posx, unsigned posy, T data){
    Node<T> *temp = new Node<T>(posx,posy,data);
    
    row_insert(posx,data,temp);
    if(temp!=nullptr){
        column_insert(posy,data,temp);
    
    }
    
    
    

}

template <typename T>
void Matrix<T>::print() const{
    int posact=0;
    for(auto it : Ro){
        posact=0;
        while(it!=nullptr){
            for(;posact<it->get_posy();posact++){
                cout<<setw(6)<<"0";
            }
            posact=it->get_posy() + 1;
            cout<<setw(6)<<it->get_data();
            it = it->next;

        }
        for(;posact<columns;posact++){
            cout<<setw(6)<<"0";
        }
        cout<<endl;
    }
}


template <typename T>
T Matrix<T>::operator()(unsigned posx, unsigned posy) const{

    if(Ro[posx]==nullptr or Co[posy]==nullptr) throw exception();

    for(Node<T>* valor_ro = Ro[posx], *valor_co = Co[posy]; valor_ro!=nullptr and valor_co!=nullptr;valor_co=valor_co->down, valor_ro=valor_ro->next){
        
        if(valor_ro->get_posy()==posy){

            return valor_ro->get_data();
        }
        if(valor_co->get_posx()==posx){
            return valor_co->get_data();
        }
    }
    return false;
}



#endif //SPARSE_MATRIX_MATRIX_H