/**
 * @file stack.h
 * 
 * @brief Implementazione di uno stack generico LIFO tramite lista concatenata.
 */
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cassert>

/**
 * @brief Classe template che implementa uno stack LIFO generico.
 * 
 * Gli elementi sono organizzati in una pila: l'ultimo inserito con push() e' il primo ad essere estratto con pop().
 * La struttura interna e' una lista concatenata di nodi, la cima dello stack corrisponde alla testa della lista.
 * 
 * @tparam T Tipo degli elementi contenuti nello stack.
 */

template <typename T>
class Stack{
private:
    /**
     * @brief Nodo interno della lista concatenata
     * 
     * Ogni nodo memorizza un valore di tipo T e un puntatore al nodo successivo verso il fondo dello stack.
     */
    struct Node {
        T data;     ///< Valore memorizzato nel nodo.
        Node* next; ///< Puntatore al nodo successivo (verso il fondo).
        /**
         * @brief Costruttore del nodo.
         * 
         * @param d Valore da memorizzare.
         * @param  n Puntatore al nodo successivo.
         * 
         * @post this->data == d
         * @post this->next == n
         */
        Node(const T& d, Node* n) : data(d), next(n) {}
    };

    Node* _top; ///< Puntatore alla cima dello stack (testa della lista).
    int _size;  ///< Numero di elementi attualmente nello stack.

    /**
     * @brief Dealloca tutti i nodi della lista e reimposta lo stack vuoto.
     * 
     * Metodo privato riutilizzato da clear() e dal distruttore.
     * 
     * @post _top == nullptr
     * @post _size == 0
     */
    void destroy() {
        Node* curr = _top;
        while (curr != nullptr){
            Node* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
        _top = nullptr;
        _size = 0;
    }

    /**
     * @brief Esegue una copia di un altro stack.
     * 
     * Preserva l'ordine degli elementi (dalla cima al fondo).
     * In caso di eccezione durante l'allocazione, lo stato parziale viene deallocato e l'eccezione viene ripropagata.
     * 
     * @param other Stack da copiare.
     * 
     * @post _size == other._size
     * @post ogni elemento e' una copia indipendente di other
     * 
     * @throw std::bad_alloc in caso di fallimento dell'allocazione.
     */
    void copy(const Stack<T>& other) {
        _top = nullptr;
        _size = 0;
        if (other._top == nullptr) return;

        try {
            _top = new Node(other._top->data, nullptr);
            _size = 1;
            Node* src = other._top->next;
            Node* dest = _top;

            while (src != nullptr) {
                dest->next = new Node(src->data, nullptr);
                dest = dest->next;
                src = src->next;
                _size++;
            }
        } catch (...) {
            destroy();
            throw;
        }
    }

public:

    /**
     * @brief Costruttore di default. Crea uno stack vuoto.
     * 1° METODO FONDAMENTALE DI UNA CLASSE C++
     * 
     * @post _top == nullptr
     * @post _size == 0
     */
    Stack() : _top(nullptr), _size(0) {}

    /**
     * @brief Costruttore che riempie lo stack da una coppia di iteratori.
     * 
     * Gli elementi sono inseriti nell'ordine restituito dagli iteratori:
     * il primo elemento dell'intervallo diventa il fondo dello stack,
     * l'ultimo diventa la cima.
     * 
     * @tparam Iter Tipo degli iteratori (input iterator).
     * @param begin Iteratore che punta all'inizio della sequenza.
     * @param end Iteratore che punta alla fine della sequenza.
     * 
     * @post size() == distanza(begin, end)
     */
    template <typename Iter>
    Stack(Iter begin, Iter end) : _top(nullptr), _size(0) {
        add(begin, end);
    }

    /**
     * @brief Costruttore di copia
     * 3° METODO FONDAMENTALE DI UNA CLASSE C++
     * 
     * Crea uno stack indipendente con gli stessi elementi e lo stesso ordine dello stack sorgente.
     * 
     * @param other Stack da copiare.
     * 
     * @post _size == other._size
     * @post top() == other.top()
     * 
     * @throw std::bad_alloc in caso di fallimento dell'allocazione.
     */
    Stack(const Stack<T>& other) : _top(nullptr), _size(0) {
        copy(other);
    }

    /**
     * @brief Operatore di assegnamento
     * 4° METODO FONDAMENTALE DI UNA CLASSE C++
     * 
     * Garantisce la sicurezza alle eccezioni: in caso di fallimento durante la copia, lo stato di *this rimane invariato.
     * L'auto-assegnazione e' gestita correttamente.
     * 
     * @param other Stack sorgente.
     * 
     * @return Riferimento a *this.
     * 
     * @post _size == other._size
     * @post top() == other.top()
     * 
     * @throw std::bad_alloc in caso di fallimento dell'allocazione.
     */
    Stack<T>& operator=(const Stack<T>& other) {
        if (this != &other) {
            Stack<T> tmp(other);
            std::swap(_top, tmp._top);
            std::swap(_size, tmp._size);
        }
        return *this;
    }

    /**
     * @brief Distruttore. Dealloca tutti i nodi della lista.
     * 2° METODO FONDAMENTALE DI UNA CLASSE C++
     * 
     * @post _top == nullptr
     * @post _size == 0;
     */
    ~Stack(){
        destroy();
    }

    /**
     * @brief Inserisce un elemento in cima allo stack
     * 
     * @param value Valore da inserire
     * 
     * @post top() == value
     * @post _size aumenta di 1
     * 
     * @throw std::bad_alloc in caso di fallimento dell'allocazione.
     */
    void push(const T& value) {
        _top = new Node(value, _top);
        ++_size;
    }

    /**
     * @brief Rimuove e resituisce l'elemento in cima allo stack.
     * 
     * @return Valore dell'elemento rimosso.
     * 
     * @pre !empty()
     * 
     * @post _size diminuisce di 1
     * 
     * @throw std::underflow_error se lo stack e' vuoto.
     */
    T pop(){
        if (empty()) {
            throw std::underflow_error("Stack::pop() - stack vuoto");
        }
        Node* tmp = _top;
        T val = tmp->data;
        _top = _top->next;
        delete tmp;
        --_size;
        return val;
    }

    /**
     * @brief Svuota lo stack rimuovendo tutti gli elementi.
     * 
     * @post empty() == true
     * @post size() == 0
     */
    void clear() {
        destroy();
    }

    /**
     * @brief Controlla se lo stack e' vuoto.
     * 
     * @return true se lo stack non contiene elementi, false altrimenti.
     */
    bool empty() const {
        return _top == nullptr;
    }

    /**
     * @brief Restituisce il numero di elementi nello stack.
     * 
     * @return Numero di elementi presenti.
     */
    int size() const {
        return _size;
    }

    /**
     * @brief Restituisce il valore in cima allo stack senza rimuoverlo.
     * 
     * @return Riferimento costante all'elemento in cima
     * 
     * @pre !empty()
     * 
     * @throw std::underflow_error se lo stack e' vuoto.
     */
    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Stack::top() - stack vuoto");
        }
        return _top->data;
    }

    /**
     * @brief Aggiunge elementi allo stack da una coppia di iteratori.
     * 
     * Gli elementi sono inseriti nell'ordine restituito dagli iteratori:
     * il primo elemento dell'intervallo finisce piu' in fondo rispetto agli elementi inseriti successivamente.
     * 
     * @tparam Iter Tipo degli iteratori.
     * @param begin Iteratore che punta all'inizio della sequenza.
     * @param end Iteratore che punta alla fine della sequenza.
     * 
     * @post size() == size() + distanza tra begin ed end
     */
    template <typename Iter>
    void add(Iter begin, Iter end) {
        for (Iter it = begin; it != end; it++) {
            push(*it);
        }
    }

    /**
     * @brief Iteratore di sola lettura per Stack<T>.
     * 
     * Scorre gli elementi dalla cima verso il fondo dello stack.
     * Implementa i requisiti di un forward iterator.
     */
    class const_iterator {
    public:
        typedef std::forward_iterator_tag iterator_category;    ///< Categoria dell'iteratore.
        typedef T value_type;                                   ///< Tipo del valore puntato.
        typedef ptrdiff_t difference_type;                      ///< Tipo della differenza tra iteratori.
        typedef const T* pointer;                               ///< Tipo del puntatore al valore.
        typedef const T& reference;                             ///< Tipo del riferimento al valore.

        /**
         * @brief Costruttore.
         * 
         * @param n Puntatore al nodo corrente.
         */
        explicit const_iterator(Node* n) : _current(n) {}

        /**
         * @brief Operatore di dereferenziazione.
         * 
         * @return Riferimento costante al valore del nodo corrente.
         * 
         * @pre _current != nullptr
         */
        const T& operator*() const {
            assert(_current != nullptr);
            return _current->data;
        }

        /**
         * @brief Operatore freccia per accesso ai memebri del valore corrente.
         * 
         * @return Puntatore costante al valore del nodo corrente.
         * 
         * @pre _current != nullptr
         */
        const T* operator->() const {
            assert(_current != nullptr);
            return &_current->data;
        }

        /**
         * @brief Pre-incremento: avanza l'iteratore al nodo successivo.
         * 
         * @return Riferimento all'iteratore aggiornato.
         * 
         * @pre _current != nullptr
         */
        const_iterator& operator++() {
            assert(_current != nullptr);
            _current = _current->next;
            return *this;
        }

        /**
         * @brief Post-incremento: avanza l'iteratore al nodo successivo.
         * 
         * @return Copia dell'iteratore prima dell'avanzamento.
         */
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        /**
         * @brief Confronto di uguaglianza tra due iteratori.
         * 
         * @param other Iteratore con cui confrontare.
         * 
         * @return true se i due iteratori puntano allo stesso nodo.
         */
        bool operator==(const const_iterator& other) const {
            return _current == other._current;
        }

        /**
         * @brief Confronto di disuguaglianza tra due iteratori.
         * 
         * @param other Iteratore con cui confrontare.
         * 
         * @return true se i due iteratori puntano a nodi diversi.
         */
        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }

    private:
        Node* _current; ///< Puntatore al nodo corrente dell'iterazione.
    };

    /**
     * @brief Restituisce un iteratore che punta alla cima dello stack.
     * 
     * @return const_iterator all'elemento in cima allo stack.
     */
    const_iterator begin() const {
        return const_iterator(_top);
    }

    /**
     * @brief Restituisce un iteratore che punta alla fine dello stack.
     * 
     * @return const_iterator oltre l'ultimo elemento
     */
    const_iterator end() const {
        return const_iterator(nullptr);
    }

    /**
     * @brief Rimuove tutti gli elementi che soddisfano il predicato P.
     * 
     * @tparam Pred Tipo del predicato: funzione o functor con firma bool.
     * 
     * @param pred Predicato da applicare a ciascun elemento.
     * 
     * @post Nessun elemento rimasto soddisfa pred.
     */
    template <typename Pred>
    void removeif(Pred pred) {
        Node** ptr = &_top;
        while (*ptr != nullptr){
            if (pred((*ptr)->data)) {
                Node* to_delete = *ptr;
                *ptr = (*ptr)->next;
                delete to_delete;
                --_size;
            } else {
                ptr = &(*ptr)->next;
            }
        }
    }

    /**
     * @brief Cerca un elemento nello stack.
     * 
     * La ricerca scorre la lista dalla cima al fondo.
     * 
     * @param value Valore da cercare.
     * 
     * @return true se l'elemento e' presente, false altrimenti.
     */
    bool find(const T& value) const {
        Node* curr = _top;
        while (curr != nullptr) {
            if (curr->data == value) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    /**
     * @brief Stampa il contenuto dello stack su uno stream di output.
     * 
     * Gli elementi sono stampati dalla cima al fondo nel formato:
     * "[cima] e1 e2 ... eN [fondo]"
     * 
     * @param os Stream di output.
     * @param s Stack da stampare.
     * 
     * @return Riferimento allo stream di output.
     */
    friend std::ostream& operator<<(std::ostream& os, const Stack<T>& s) {
        os << "[cima] ";
        Node* curr = s._top;
        while (curr != nullptr) {
            os << curr->data;
            if (curr->next != nullptr) {
                os << " ";
            }
            curr = curr->next;
        }
        os << " [fondo]";
        return os;
    }

    /**
     * @brief Salva il contenuto dello stack in un file di testo.
     * 
     * Il formato del file e':
     * - Prima riga: numero di elementi
     * - Righe successive: un elemento per riga, dalla cima al fondo
     * 
     * @param filename Percorso del file di destinazione.
     * 
     * @throw std::runtime_error se il file non puo' essere aperto.
     */
    void save(const std::string& filename) const {
        std::ofstream ofs(filename.c_str());
        if (!ofs.is_open()) {
            throw std::runtime_error("Stack::save() - impossibile aprire il file: " + filename);
        }
        ofs << _size << "\n";
        Node* curr = _top;
        while (curr != nullptr) {
            ofs << curr->data << "\n";
            curr = curr->next;
        }
    }

    /**
     * @brief Carica il contenuto dello stack da un file di testo.
     * 
     * @param filename Percorso del file sorgente.
     * 
     * @post Il contenuto dello stack rispecchia quello salvato nel file.
     * 
     * @throw std::runtime_error se il file non puo' essere aperto o e' malformato.
     */
    void load(const std::string& filename) {
        std::ifstream ifs(filename.c_str());
        if (!ifs.is_open()) {
            throw std::runtime_error("Stack::load() - impossibile aprire il file: " + filename);
        }

        int count = 0;
        if (!(ifs >> count)) {
            throw std::runtime_error("Stack::load() - file malformato: numero elementi mancante");
        }
        if (count < 0) {
            throw std::runtime_error("Stack::load() - file malformato: numero elementi negativo");
        }

        Node* tmp_head = nullptr;
        int loaded = 0;

        try {
            for (int i = 0; i < count; ++i) {
                T value;
                if (!(ifs >> value)) {
                    throw std::runtime_error("Stack::load() - file malformato: dati insufficienti");
                }
                tmp_head = new Node(value, tmp_head);
                ++loaded;
            }
        } catch (...) {
            Node* curr = tmp_head;
            while (curr != nullptr) {
                Node* next = curr->next;
                delete curr;
                curr = next;
            }
            throw;
        }
        clear();
        Node* curr = tmp_head;
        while (curr != nullptr) {
            Node* next = curr->next;
            push(curr->data);
            delete curr;
            curr = next;
        }
        (void)loaded;
    }
};


#endif