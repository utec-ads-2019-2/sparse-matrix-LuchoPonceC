#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    
    T data;
    unsigned posx,posy;
public:
	Node<T> *next, *down;
    explicit Node(unsigned, unsigned, T);
    unsigned get_posx(){return posx;}
    unsigned get_posy(){return posy;}
    void set_data(T data){this->data = data;}
    T get_data(){return data;}
    void killSelf();
    ~Node(){}
    friend class Matrix<T>;
};

template <typename T>
void Node<T>::killSelf(){
	if(next){
		next->killSelf();
	}
	//cout<<"elimino un nodo"<<this->get_data()<<endl;
	delete this;
}

template <typename T>
Node<T>::Node(unsigned posx, unsigned posy, T data) : posx(posx), posy(posy), data(data){
	next=nullptr;
	down=nullptr;
}

#endif //SPARSE_MATRIX_NODE_H
