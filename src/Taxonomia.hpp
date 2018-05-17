#include <sstream>

// Métodos de Taxonomia (ya implementados por la cátedra):

template<class T>
int Taxonomia<T>::_espiarProximoCaracter(istream& is) const {
	int c = is.peek();
	while (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
		is.get();
		c = is.peek();
	}
	return is.peek();
}

template<class T>
typename Taxonomia<T>::Nodo* Taxonomia<T>::_leerDe(istream& is) {
	Taxonomia<T>::Nodo* nodo = new Taxonomia<T>::Nodo();
	is >> nodo->valor;
	if (_espiarProximoCaracter(is) == '{') {
		is.get();
		while (_espiarProximoCaracter(is) != '}') {
			nodo->hijos.push_back(_leerDe(is));
		}
		is.get();
	}
	return nodo;
}

template<class T>
Taxonomia<T>::Taxonomia(const string& input) {
	istringstream is(input);
	_raiz = _leerDe(is);
}

template<class T>
void Taxonomia<T>::_borrar(Taxonomia<T>::Nodo* nodo) {
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
void Taxonomia<T>::_identar(ostream& os, int tab) const {
	for (int i = 0; i < tab; i++) {
		os << "  ";
	}
}

template<class T>
void Taxonomia<T>::_mostrarEn(
		ostream& os, Taxonomia<T>::Nodo* nodo, int tab) const {
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
void Taxonomia<T>::mostrar(ostream& os) const {
	_mostrarEn(os, _raiz, 0);
}

////////////////////////////////////////

// Métodos para implementar el iterador de Taxonomia<T> (para completar)

// Devuelve un iterador válido al principio de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::begin() {
	assert(false);
}

// Devuelve un iterador válido al final de la taxonomía.
template<class T>
typename Taxonomia<T>::iterator Taxonomia<T>::end() {
	assert(false);
}

// Constructor por defecto del iterador.
// (Nota: puede construir un iterador inválido).
template<class T>
Taxonomia<T>::iterator::iterator() {
	assert(false);
}

// Referencia mutable al nombre de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
T& Taxonomia<T>::iterator::operator*() const {
	assert(false);
}

// Cantidad de subcategorías de la categoría actual.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
int Taxonomia<T>::iterator::cantSubcategorias() const {
	assert(false);
}

// Ubica el iterador sobre la i-ésima subcategoría.
// Pre: el iterador está posicionado sobre una categoría
// y además 0 <= i < cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::subcategoria(int i) {
	assert(false);
}

// Devuelve true sii la categoría actual es la raíz. 
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
bool Taxonomia<T>::iterator::esRaiz() const {
	assert(false);
}

// Ubica el iterador sobre la supercategoría de la categoría
// actual.
// Pre: el iterador está posicionado sobre una categoría
// y además !esRaiz()
template<class T>
void Taxonomia<T>::iterator::supercategoria() {
	assert(false);
}

// Compara dos iteradores por igualdad.
// Pre: deben ser dos iteradores de la misma taxonomía.
template<class T>
bool Taxonomia<T>::iterator::operator==(
		const Taxonomia<T>::iterator& otro) const {
	assert(false);
}

// Ubica el iterador sobre la categoría siguiente a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la última categoría de la taxonomía,
// el iterador resultante debe ser igual al iterador end()
// de la taxonomía.
template<class T>
void Taxonomia<T>::iterator::operator++() {
	assert(false);
}

// Ubica el iterador sobre la categoría anterior a la actual
// en el recorrido *preorder* de la taxonomía.
// Si se trata de la raíz de la taxonomía el iterador
// resultante debe ser igual al iterador end() de la taxonomía.
// Pre: el iterador está posicionado sobre una categoría.
template<class T>
void Taxonomia<T>::iterator::operator--() {
	assert(false);
}

// Inserta una subcategoría con el nombre indicado
// en el lugar i-ésimo.
// Observación: esta operación modifica la taxonomía y
// puede invalidar otros iteradores.
// Pre: el iterador está posicionado sobre una categoría,
// y además 0 <= i <= cantSubcategorias().
template<class T>
void Taxonomia<T>::iterator::insertarSubcategoria(int i, const T& nombre) {
	assert(false);
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
	assert(false);
}

