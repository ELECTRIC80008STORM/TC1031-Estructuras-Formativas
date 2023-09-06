#ifndef SORTS
#define SORTS

#include <vector>

using namespace std;

template <typename T> class Sorts{
    private:
        void swap(vector<T>&, int, int);
        void copiarArreglo(vector<T>&, std::vector<T>&, int, int);
        void juntarArreglo(vector<T>&, std::vector<T>&, int, int, int);
        void divisionMerge(vector<T>&, std::vector<T>&, int, int);
        T busqBinariAux(vector<T>&, int, int, T);

    public:
        void ordenaSeleccion(vector<T>&);
        void ordenaBurbuja(vector<T>&);
        void ordenaMerge(vector<T>&);
        T busqSecuencial(vector<T>&, T);
        T busqBinaria(vector<T>&, T);
};

template <typename T> void Sorts<T>::swap(vector<T>& vect, int a, int b){
    T aux = vect[a];
    vect[a] = vect[b];
    vect[b] = aux;
}


template <typename T> void Sorts<T>::ordenaSeleccion(vector<T>& vect){
    int aux;
    for(int i = 0; i < vect.size() - 1; i ++){
        aux = i;
        for(int j = i; j < vect.size() - 1; j ++){
            if(vect[aux] > vect[j + 1]){
                aux = j + 1;
            }
        }
        if(i != aux){
            swap(vect,i,aux);
        }
    }
}

template <typename T>
void Sorts<T>::ordenaBurbuja(vector<T>& vect){
    for(int i = vect.size() - 1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(vect[j] > vect[j + 1]){
                swap(vect,j,j + 1);
            }
        }
    }
}

template <typename T>
void Sorts<T>::copiarArreglo(vector<T>& A, std::vector<T>& B, int low, int high){
    for(int i = low; i <= high; i++){
        A[i] = B[i];
    }
}

template <typename T>
void Sorts<T>::juntarArreglo(vector<T>& A, std::vector<T>& B, int low, int mid, int high){
    int i, j, k;
    i = low;
    j = mid + 1;
    k = low;
    while (i <= mid && j <= high){
        if(A[i] < A[j]){
            B[k] = A[i];
            i++;
        } else{
            B[k] = A[j];
            j++;
        }
        k++;
    }
    if(i > mid){
        for(; j <= high; j++){
            B[k++] = A[j];
        }
    } else{
        for(; i <= mid; i++){
            B[k++] = A[i];
        }
    }
}

template <typename T>
void Sorts<T>::divisionMerge(vector<T>& A, std::vector<T>& B, int low, int high){
    if(low == high){
        return;
    } else{
        int mid = (low + high) / 2;
        divisionMerge(A, B, low, mid);
        divisionMerge(A, B, mid + 1, high);
        juntarArreglo(A, B, low, mid, high);
        copiarArreglo(A, B, low, high);
    }
}

template <typename T>
void Sorts<T>::ordenaMerge(vector<T>& vect){
    vector<T> temp(vect.size());
    divisionMerge(vect, temp, 0, vect.size() - 1);
}

template <typename T>
T Sorts<T>::busqSecuencial(vector<T>& vect, T element){
    for(int i = 0; i < vect.size(); i ++){
        if (vect[i] == element){
            return i;
        }
    }
    return -1;
}

template <typename T>
T Sorts<T>::busqBinariAux(vector<T>& vect, int low, int high, T val){
    if(low <= high){
        int mid = (low + high) / 2;
        if(vect[mid] == val){
            return mid;
        } else if(vect[mid] > val){
            return busqBinariAux(vect, low, mid - 1, val);
        } else{
            return busqBinariAux(vect, mid + 1, high, val);
        }
    }
    if(vect[low] != val){
        return -1;
    }
    return low;
}

template <typename T>
T Sorts<T>::busqBinaria(vector<T>& vect, T val){
    return busqBinariAux(vect, 0, vect.size() - 1, val);
}

#endif