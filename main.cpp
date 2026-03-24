#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include "stack.h"

struct Point2D {
    int x, y;

    Point2D() : x(0), y(0) {}
    Point2D(int x_, int y_) : x(x_), y(y_) {}

    bool operator==(const Point2D& other) const {
        return x == other.x && y == other.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point2D& p) {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Point2D& p) {
        char c;
        is >> c >> p.x >> c >> p.y >> c;
        return is;
    }
};

#define TEST(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "[FAIL] " << msg << std::endl; \
            errors++; \
        } else { \
            std::cout << "[OK]   " << msg << std::endl; \
        } \
    } while(0)

template <typename ExcType, typename Func>
bool throws(Func f) {
    try {
        f();
        return false;
    } catch (const ExcType&) {
        return true;
    } catch (...) {
        return false;
    }
}

int test_push_pop_basic(int errors) {
    std::cout << "\n--- Test push/pop (int) ---\n";
    Stack<int> s;

    TEST(s.empty(), "Stack vuoto dopo costruzione");
    TEST(s.size() == 0, "size() == 0 inizialmente");

    s.push(1);
    s.push(2);
    s.push(3);

    TEST(s.size() == 3,      "size() == 3 dopo 3 push");
    TEST(!s.empty(),         "!empty() dopo push");
    TEST(s.top() == 3,       "top() == 3 (ultimo inserito)");

    TEST(s.pop() == 3, "pop() ritorna 3");
    TEST(s.pop() == 2, "pop() ritorna 2");
    TEST(s.pop() == 1, "pop() ritorna 1");
    TEST(s.empty(),    "Stack vuoto dopo tutti i pop");

    return errors;
}

int test_clear(int errors) {
    std::cout << "\n--- Test clear() ---\n";
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.clear();
    TEST(s.empty(),      "Stack vuoto dopo clear()");
    TEST(s.size() == 0,  "size() == 0 dopo clear()");
    s.push(99);
    TEST(s.top() == 99,  "Posso riusare lo stack dopo clear()");
    return errors;
}

int test_copy_constructor(int errors) {
    std::cout << "\n--- Test copy constructor ---\n";
    Stack<int> s1;
    s1.push(1); s1.push(2); s1.push(3);

    Stack<int> s2(s1);
    TEST(s2.size() == s1.size(), "Copia ha stessa dimensione");
    TEST(s2.top() == s1.top(),   "Copia ha stessa cima");

    s2.pop();
    TEST(s1.size() == 3, "s1 non modificato dopo pop su s2");
    TEST(s2.size() == 2, "s2 ha un elemento in meno");
    return errors;
}

int test_assignment_operator(int errors) {
    std::cout << "\n--- Test operatore di assegnazione ---\n";
    Stack<int> s1;
    s1.push(10); s1.push(20);

    Stack<int> s2;
    s2.push(99);
    s2 = s1;

    TEST(s2.size() == 2,   "Dimensione corretta dopo assegnazione");
    TEST(s2.pop() == 20,   "Cima corretta dopo assegnazione");
    TEST(s1.size() == 2,   "s1 non modificato dopo assegnazione su s2");

    s1 = s1;
    TEST(s1.size() == 2,   "Auto-assegnazione non danneggia lo stack");
    return errors;
}

int test_iterator_constructor(int errors) {
    std::cout << "\n--- Test costruttore da iteratori ---\n";
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    Stack<int> s(v.begin(), v.end());
    TEST(s.size() == 3, "Stack creato da iteratori ha 3 elementi");
    TEST(s.top() == 3,  "Cima = ultimo elemento del vettore");
    TEST(s.pop() == 3,  "Pop ritorna 3");
    TEST(s.pop() == 2,  "Pop ritorna 2");
    TEST(s.pop() == 1,  "Pop ritorna 1");
    return errors;
}

int test_add(int errors) {
    std::cout << "\n--- Test add() ---\n";
    Stack<int> s;
    s.push(0);
    std::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    s.add(v.begin(), v.end());

    TEST(s.size() == 3,  "size() == 3 dopo add");
    TEST(s.top() == 20,  "Cima == 20 (ultimo aggiunto)");
    return errors;
}

int test_readonly_iterator(int errors) {
    std::cout << "\n--- Test iteratore di sola lettura ---\n";
    Stack<int> s;
    s.push(1); s.push(2); s.push(3);

    int expected[] = {3, 2, 1};
    int i = 0;
    bool ok = true;
    for (Stack<int>::const_iterator it = s.begin(); it != s.end(); ++it) {
        if (*it != expected[i++]) { ok = false; }
    }
    TEST(ok,          "Iteratore restituisce elementi in ordine cima->fondo");
    TEST(i == 3,      "Iteratore ha visitato 3 elementi");

    Stack<int> empty;
    TEST(empty.begin() == empty.end(), "begin()==end() su stack vuoto");
    return errors;
}

int test_removeif(int errors) {
    std::cout << "\n--- Test removeif() ---\n";
    Stack<int> s;
    for (int i = 1; i <= 6; ++i) s.push(i);

    struct IsPari {
        bool operator()(const int& n) const { return n % 2 == 0; }
    };
    s.removeif(IsPari());

    TEST(s.size() == 3, "size() == 3 dopo removeif(pari)");
    TEST(s.pop() == 5,  "Cima == 5");
    TEST(s.pop() == 3,  "Successivo == 3");
    TEST(s.pop() == 1,  "Fondo == 1");

    Stack<int> s2;
    s2.push(2); s2.push(4);
    s2.removeif(IsPari());
    TEST(s2.empty(), "Stack vuoto dopo removeif che rimuove tutto");

    Stack<int> s3;
    s3.removeif(IsPari());
    TEST(s3.empty(), "removeif su stack vuoto non causa errori");
    return errors;
}

int test_find(int errors) {
    std::cout << "\n--- Test find() ---\n";
    Stack<int> s;
    s.push(10); s.push(20); s.push(30);

    TEST(s.find(10),  "find(10) == true (nel fondo)");
    TEST(s.find(20),  "find(20) == true (in mezzo)");
    TEST(s.find(30),  "find(30) == true (in cima)");
    TEST(!s.find(99), "find(99) == false (non presente)");

    Stack<int> empty;
    TEST(!empty.find(1), "find su stack vuoto == false");
    return errors;
}

int test_operator_stream(int errors) {
    std::cout << "\n--- Test operator<< ---\n";
    Stack<int> s;
    s.push(1); s.push(2); s.push(3);

    std::ostringstream oss;
    oss << s;
    std::string result = oss.str();
    TEST(result == "[cima] 3 2 1 [fondo]", "operator<< produce output corretto");

    Stack<int> empty;
    std::ostringstream oss2;
    oss2 << empty;
    TEST(oss2.str() == "[cima]  [fondo]", "operator<< su stack vuoto");
    return errors;
}

int test_save_load(int errors) {
    std::cout << "\n--- Test save()/load() ---\n";
    Stack<int> s;
    s.push(1); s.push(2); s.push(3);

    const std::string filename = "test_stack.txt";
    s.save(filename);

    Stack<int> s2;
    s2.push(99);
    s2.load(filename);

    TEST(s2.size() == 3, "size() == 3 dopo load");
    TEST(s2.pop() == 3,  "Cima == 3 dopo load");
    TEST(s2.pop() == 2,  "Secondo == 2 dopo load");
    TEST(s2.pop() == 1,  "Fondo == 1 dopo load");

    TEST(
        throws<std::runtime_error>([](){
            Stack<int> tmp;
            tmp.load("file_non_esistente_xyz.txt");
        }),
        "load() lancia runtime_error su file mancante"
    );
    return errors;
}

int test_exceptions(int errors) {
    std::cout << "\n--- Test eccezioni casi limite ---\n";

    TEST(
        throws<std::underflow_error>([](){
            Stack<int> s;
            s.pop();
        }),
        "pop() su stack vuoto lancia underflow_error"
    );

    TEST(
        throws<std::underflow_error>([](){
            Stack<int> s;
            (void)s.top();
        }),
        "top() su stack vuoto lancia underflow_error"
    );

    TEST(
        throws<std::runtime_error>([](){
            Stack<int> s;
            s.push(1);
            s.save("/percorso/inesistente/file.txt");
        }),
        "save() lancia runtime_error su percorso non valido"
    );
    return errors;
}

int test_string_type(int errors) {
    std::cout << "\n--- Test su tipo std::string ---\n";
    Stack<std::string> s;
    s.push("alpha");
    s.push("beta");
    s.push("gamma");

    TEST(s.top() == "gamma",    "top() == 'gamma' (stringa)");
    TEST(s.find("alpha"),       "find('alpha') == true");
    TEST(!s.find("delta"),      "find('delta') == false");
    TEST(s.pop() == "gamma",    "pop() == 'gamma'");

    const std::string fname = "test_stack_str.txt";
    s.save(fname);
    Stack<std::string> s2;
    s2.load(fname);
    TEST(s2.size() == 2,        "Dimensione corretta dopo load (string)");
    TEST(s2.pop() == "beta",    "Cima corretta dopo load (string)");
    return errors;
}

int test_custom_type(int errors) {
    std::cout << "\n--- Test su tipo custom Point2D ---\n";
    Stack<Point2D> s;
    s.push(Point2D(1, 2));
    s.push(Point2D(3, 4));
    s.push(Point2D(5, 6));

    TEST(s.size() == 3,                  "size() == 3 (Point2D)");
    TEST(s.top() == Point2D(5, 6),       "top() == (5,6)");
    TEST(s.find(Point2D(1, 2)),          "find((1,2)) == true");
    TEST(!s.find(Point2D(9, 9)),         "find((9,9)) == false");

    struct XGreaterThan2 {
        bool operator()(const Point2D& p) const { return p.x > 2; }
    };
    s.removeif(XGreaterThan2());
    TEST(s.size() == 1,                  "size() == 1 dopo removeif (Point2D)");
    TEST(s.top() == Point2D(1, 2),       "Rimasto solo (1,2)");

    const std::string fname = "test_stack_point.txt";
    Stack<Point2D> s2;
    s2.push(Point2D(10, 20));
    s2.push(Point2D(30, 40));
    s2.save(fname);

    Stack<Point2D> s3;
    s3.load(fname);
    TEST(s3.size() == 2,                 "size() == 2 dopo load (Point2D)");
    TEST(s3.pop() == Point2D(30, 40),    "Cima corretta dopo load (Point2D)");
    TEST(s3.pop() == Point2D(10, 20),    "Fondo corretto dopo load (Point2D)");

    Stack<Point2D> s4;
    s4.push(Point2D(1, 1));
    s4.push(Point2D(2, 2));
    int cnt = 0;
    for (Stack<Point2D>::const_iterator it = s4.begin(); it != s4.end(); ++it) {
        cnt++;
    }
    TEST(cnt == 2, "Iteratore su Point2D visita 2 elementi");

    std::vector<Point2D> vp;
    vp.push_back(Point2D(7, 7));
    vp.push_back(Point2D(8, 8));
    Stack<Point2D> s5(vp.begin(), vp.end());
    TEST(s5.size() == 2,               "Costruttore da iteratori (Point2D)");
    TEST(s5.top() == Point2D(8, 8),    "Cima corretta da costruttore iteratori (Point2D)");

    return errors;
}

int test_operator_stream_custom(int errors) {
    std::cout << "\n--- Test operator<< con Point2D ---\n";
    Stack<Point2D> s;
    s.push(Point2D(1, 2));
    s.push(Point2D(3, 4));
    std::ostringstream oss;
    oss << s;
    TEST(oss.str() == "[cima] (3,4) (1,2) [fondo]",
         "operator<< corretto su Point2D");
    return errors;
}

int main() {
    std::cout << "=== Test Stack<T> ===" << std::endl;

    int errors = 0;

    errors = test_push_pop_basic(errors);
    errors = test_clear(errors);
    errors = test_copy_constructor(errors);
    errors = test_assignment_operator(errors);
    errors = test_iterator_constructor(errors);
    errors = test_add(errors);
    errors = test_readonly_iterator(errors);
    errors = test_removeif(errors);
    errors = test_find(errors);
    errors = test_operator_stream(errors);
    errors = test_save_load(errors);
    errors = test_exceptions(errors);
    errors = test_string_type(errors);
    errors = test_custom_type(errors);
    errors = test_operator_stream_custom(errors);

    std::cout << "\n=== Risultato: ";
    if (errors == 0) {
        std::cout << "TUTTI I TEST PASSATI ===" << std::endl;
    } else {
        std::cout << errors << " TEST FALLITI ===" << std::endl;
    }

    return errors == 0 ? 0 : 1;
}