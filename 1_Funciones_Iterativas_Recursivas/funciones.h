#ifndef FUNCIONES
#define FUNCIONES

class Funciones{
    public:
        Funciones(){};
        int sumaIterativa(int);
        int sumaRecursiva(int);
        int sumaDirecta(int);
};

int Funciones::sumaIterativa(int n){
    int acum = 0;
    for(int i = 0; i <= n; i++){
        acum += i;
    }
    return acum;
}

int Funciones::sumaRecursiva(int n){
    if(n == 0){
        return 0;
    }
    return n + sumaRecursiva(n - 1);
}

int Funciones::sumaDirecta(int n){
    return (n != 0)? (n * (n + 1)) / 2 : 0;
}

#endif // FUNCIONES