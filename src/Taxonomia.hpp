#include <sstream>

// Métodos de Taxonomia (ya implementados por la cátedra):

template<class T>
int Taxonomia<T>::_espiarProximoCaracter(istream &is) const {
    int c = is.peek();
    while (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
        is.get();
        c = is.peek();
    }
    return is.peek();
}

template<class T>
typename Taxonomia<T>::Nodo *Taxonomia<T>::_leerDe(istream &is) {
    Taxonomia<T>::Nodo *nodo = new Taxonomia<T>::Nodo();
    is >> nodo->valor;
    if (_espiarProximoCaracter(is) == '{') {
        is.get();
        int pos = 0;
        while (_espiarProximoCaracter(is) != '}') {
            _leerConPadreYPos(is, nodo, pos);
            pos++;
        }
        is.get();
    }
    return nodo;
}

template<class T>
typename Taxonomia<T>::Nodo *Taxonomia<T>::_leerConPadreYPos(istream &is, Taxonomia<T>::Nodo *padre, int pos) {
    Taxonomia<T>::Nodo *nodo = _leerDe(is);
    nodo->padre = padre;
    nodo->pos = pos;
    padre->hijos.push_back(nodo);
}

template<class T>
Taxonomia<T>::Taxonomia(const string &input) {
    istringstream is(input);
    _raiz = _leerDe(is);
}

template<class T>
void Taxonomia<T>::_borrar(Taxonomia<T>::Nodo *nodo) {
    for (int i = 0; i < nodo->hijos.size(); i++) {
        _borrar(nodo->hijos[i]);
    }
    delete nodo;
}

template<class T>
Taxonomia<T>::~Taxonomia() {
    _borrar(_raiz);
}

template<class T>
void Taxonomia<T>::_identar(ostream &os, int tab) const {
    for (int i = 0; i < tab; i++) {
        os << "  ";
    }
}

template<class T>
void Taxonomia<T>::_mostrarEn(
        ostream &os, Taxonomia<T>::Nodo *nodo, int tab) const {
    _identar(os, tab);
    os << nodo->valor;
    if (nodo->hijos.size() == 0) {
        os << "\n";
    } else {
        os << " {\n";
        for (int i = 0; i < nodo->hijos.size(); i++) {
            _mostrarEn(os, nodo->hijos[i], tab + 1);
        }
        _identar(os, tab);
        os << "}\n";
    }
}

template<class T>
void Taxonomia<T>::mostrar(ostream &os) const {
    _mostrarEn(os, _raiz, 0);
}

////////////////////////////////////////

// Métodos para implementar el iterador de Taxonomia<T> (para completar)

// Devuelve un iterador válido al principio de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::begin() {
    return iterator(_raiz);
}

// Devuelve un iterador válido al final de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::end() {
    return iterator(nullptr);
}

// Constructor por defecto del iterador.
// (Nota: puede construir un iterador inválido).
template<class T>
Taxonomia<T>::iterator::iterator() {}

template<class T>
Taxonomia<T>::iterator::iterator(Nodo *raiz) {
    _actual = raiz;
    _raiz = raiz;
}

// Referencia mutable al nombre de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
T &Taxonomia<T>::iterator::operator*() const {
    return _actual->valor;
}

// Cantidad de subcategorías de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
int Taxonomia<T>::iterator::cantSubcategorias() const {
    return _actual->hijos.size();
}

// Ubica el iterador sobre la i-ésima subcategoría.
// Pre: el iterador está posicionado sobre una categoría
// y además 0 <= i < cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::subcategoria(int i) {
    _actual = _actual->hijos[i];
}

// Devuelve true sii la categoría actual es la raíz. 
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
bool Taxonomia<T>::iterator::esRaiz() const {
    return _actual == _raiz;
}

// Ubica el iterador sobre la supercategoría de la categoría
// actual.
// Pre: el iterador está posicionado sobre una categoría
// y además !esRaiz()
template<class T>
void Taxonomia<T>::iterator::supercategoria() {
    _actual = _actual->padre;
}

// Compara dos iteradores por igualdad.
// Pre: deben ser dos iteradores de la misma taxonomía.
template<class T>
bool Taxonomia<T>::iterator::operator==(
        const Taxonomia<T>::iterator &otro) const {
    return _actual == otro._actual;
}

// Ubica el iterador sobre la categoría siguiente a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la última categoría de la taxonomía,
// el iterador resultante debe ser igual al iterador end()
// de la taxonomía.
template<class T>
void Taxonomia<T>::iterator::operator++() {
    if (cantSubcategorias() > 0)
        _actual = _actual->hijos[0];
    else if (_actual->pos < _actual->padre->hijos.size() - 1)
        _actual = _actual->padre->hijos[_actual->pos + 1];
    else
        subir();
}

// _actual->pos = _actual->padre->hijos.size() - 1
template<class T>
void Taxonomia<T>::iterator::subir() {
    if(esRaiz())
        _actual = nullptr;
    else if(_actual->padre!= _raiz && _actual->padre->pos < _actual->padre->padre->hijos.size()-1)
        _actual = _actual->padre->padre->hijos[_actual->padre->pos +1];
    else {
        _actual = _actual->padre;
        subir();
    }
}

// Ubica el iterador sobre la categoría anterior a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la raíz de la taxonomía el iterador
// resultante debe ser igual al iterador end() de la taxonomía.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
void Taxonomia<T>::iterator::operator--() {
    if(esRaiz())
        _actual== nullptr;
    else if(_actual->pos == 0)
        _actual = _actual->padre;
    else {
        _actual = _actual->padre->hijos[_actual->pos - 1];
        while(_actual->hijos.size()>0)
            _actual=_actual->hijos[_actual->hijos.size()-1];
    }
}

// Inserta una subcategoría con el nombre indicado
// en el lugar i-ésimo.
// Observación: esta operación modifica la taxonomía y
// puede invalidar otros iteradores.
// Pre: el iterador está posicionado sobre una categoría,
// y además 0 <= i <= cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::insertarSubcategoria(int i, const T &nombre) {
    Nodo *nodo = new Nodo();
    nodo->valor = nombre;
    nodo->padre = _actual;
    _actual->hijos.push_back(nodo);
    for (int j = _actual->hijos.size()-1; j>i; --j) {
        Nodo *tmp = _actual->hijos[j];
        _actual->hijos[j-1]->pos ++;
        _actual->hijos[j] =_actual->hijos[j-1];
        tmp->pos--;
        _actual->hijos[j-1] =tmp;
    }
}

// Elimina la categoría actual de la taxonomía
// (y todas sus subcategorías).
// Observación: esta operación modifica la taxonomía y
// puede invalidar otros iteradores. Debe encargarse de
// liberar la memoria.
// Pre: el iterador está posicionado sobre una categoría,
// y además !esRaiz().
template<class T>
void Taxonomia<T>::iterator::eliminarCategoria() {
    Nodo *padre = _actual->padre;
    for (int i = _actual->pos; i < padre->hijos.size()-1; ++i) {
        Nodo *tmp = padre->hijos[i];
        padre->hijos[i+1]->pos--;
        padre->hijos[i] = padre->hijos[i+1];
        tmp->pos++;
        padre->hijos[i+1]=tmp;
    }
    eliminarNodo(padre->hijos[padre->hijos.size()-1]);
    padre->hijos.pop_back();
    _actual=padre;
}

template<class T>
void Taxonomia<T>::iterator::eliminarNodo(Taxonomia<T>::Nodo *nodo) {
    while(nodo->hijos.size()>0){
        eliminarNodo(nodo->hijos[nodo->hijos.size()-1]);
        nodo->hijos.pop_back();
    }
    delete(nodo);
}