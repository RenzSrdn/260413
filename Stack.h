#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cassert>

template <typename T>
class Stack{
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n) : data(d), next(n) {}
    };

    Node* _top;
    int _size;

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

    void copy(const Stack<T>& other) {
        if (other._top == nullptr){
            _top = nullptr;
            _size = 0;
        }

        _top = new Node(other._top->data, nullptr);
        _size = other._size;

        Node* src = other._top->next;
        Node* dest = _top;

        while(src != nullptr) {
            dest->next = new Node(src->data, nullptr);
            dest = dest->next;
            src = src->next;
        }
    }

public:
    Stack() : _top(nullptr), _size(0) {}

    template <typename Iter>
    Stack(Iter begin, Iter end) : _top(nullptr), size(0) {
        add(begin, end);
    }

    Stack(const Stack<T>& other) : _top(nullptr), _size(0) {
        copy(other);
    }

    Stack<T>& operator=(const Stack<T>& other) {
        if (this != &other) {
            Stack<T> tmp(other);
            std::swap(_top, tmp._top);
            std::swap(_size, other._size);
        }
        return *this;
    }

    ~Stack(){
        destroy();
    }

    void push(const T& value) {
        _top = new Node(value, _top);
        ++_size;
    }


    T pop(){
        if (empty()) {
            throw std::underflow_error("Satck::pop() - stack vuoto");
        }
        Node* tmp = _top;
        T val = tmp->data;
        _top = _top->next;
        delete tmp;
        --_size;
        return val;
    }

    void clear() {
        destroy();
    }

    bool empty() const {
        return _top == nullptr;
    }

    int size() const() {
        return _size;
    }

    const T& top() const() {
        if (empty()) {
            throw std::underflow_error("Stack::top() - stack vuoto");
        }
        return _top->data;
    }

    template <typename Iter>
    void add(Iter begin, Iter end) {
        for (Iter it = begin; it != end; it++) {
            push(*it);
        }
    }

    class const_iterator {
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;

        explicit const_iterator(Node* n) : _current(n) {}

        const T& operator*() const {
            assert(_current != nullptr);
            return _current->data;
        }

        const T* operator->() const {
            assert(_current != nullptr);
            return &_current->data;
        }

        const_iterator& operator++() {
            assert(_current != nullptr);
            _current = _current->next;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const const_iterator& other) const {
            return _current == other._current;
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }

    private:
        Node* _current;
    };

    const_iterator begin() const {
        return const_iterator(_top);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

    template <typename Pred>
    void removeif(Pred pred) {
        Node dummy(T(), _top);
        Node* prev = &dummy;
        Node* curr = _top;

        while (curr != nullptr) {
            if (pred(curr->data)) {
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
                --_size;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        _top = dummy.next;
    }

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

    friend std::ostream& operator<<(std::ostream& os, const Stack<T>& s) {
        os << "[cima] ";
        Node* curr = s.top;
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
            for (int = 0; i < count; ++i) {
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