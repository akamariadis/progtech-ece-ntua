#include <iostream>
#include <cmath>
using namespace std;

class Polynomial {
protected:
    class Term {
    protected:
        int exponent;
        int coefficient;
        Term *next;

        Term(int exp, int coeff, Term *n) {
            exponent = exp;
            coefficient = coeff;
            next = n;
        }
        friend class Polynomial;
        friend Polynomial operator + (const Polynomial &p, const Polynomial &q);
        friend Polynomial operator * (const Polynomial &p, const Polynomial &q);
        friend ostream & operator << (ostream &out, const Polynomial &p);
    };
    Term *head;

public:
    Polynomial() {
        head = NULL;
    };

    Polynomial(const Polynomial &p) {
        Term *q = p.head;
        while (q != NULL) {
            addTerm(q->exponent, q->coefficient);
            q = q->next;
        }
    };

    ~Polynomial() {};

    Polynomial & operator = (const Polynomial &p) {
        this->~Polynomial();
        head = NULL;
        Term *q = p.head;
        while (q != NULL) {
            addTerm(q->exponent, q->coefficient);
            q = q->next;
        }
        return *this;
    }

    void addTerm(int expon, int coeff) {
        Term *p, *r;
        Term *q = new Term(expon, coeff, NULL);

        if (coeff == 0) {
            delete q;
            return;
        }

        if (head == NULL) {
            head = q;
            head->next = NULL;
            return;
        }

        if (head->exponent == expon) {
            head->coefficient += coeff;
            if (head->coefficient == 0) {
                p = head;
                head = head->next;
                delete p;
            }
            delete q;
            return;
        }
        p = head;
        r = p->next;
        while (r != NULL && r->exponent > expon) {
            p = r;
            r = r->next;
        }
        if (r != NULL && r->exponent == expon) {
            r->coefficient += coeff;
            if (r->coefficient == 0) {
                p->next = r->next;
                delete r;
            }
            delete q;
        }
        else {
            if (q->exponent < p->exponent) {
                q->next = p->next;
                p->next = q;
            }
            else {
                q->next = p;
                head = q;
            }
        }
    }

    double evaluate(double x) {
        double res = 0;
        Term *p;
        p = head;
        while (p != NULL) {
            res += (p->coefficient)*pow(x, p->exponent);
            p = p->next;
        }
        return res;
    };

    friend Polynomial operator + (const Polynomial &p, const Polynomial &q) {
        Polynomial res;
        Term *r, *z, *t;
        r = p.head;
        z = q.head;

        while (r != NULL && z != NULL) {
            if (r->exponent > z->exponent) {
                res.addTerm(r->exponent, r->coefficient);
                r = r->next;
            }
            else if (r->exponent < z->exponent) {
                res.addTerm(z->exponent, z->coefficient);
                z = z->next;
            }
            else {
                res.addTerm(r->exponent, z->coefficient + r->coefficient);
                r = r->next;
                z = z->next;
            }
        }
        if (z == NULL) {
            t = r;
        }
        else if (r == NULL) {
            t = z;
        }
        while (t != NULL) {
            res.addTerm(t->exponent, t->coefficient);
            t = t->next;
        }
        return res;
    };

    friend Polynomial operator * (const Polynomial &p, const Polynomial &q) {
        Polynomial res;
        for (Term *pTerm = p.head; pTerm != NULL; pTerm = pTerm->next) {
            for (Term *qTerm = q.head; qTerm != NULL; qTerm = qTerm->next) {
                int expon = pTerm->exponent + qTerm->exponent;
                int coeffee = pTerm->coefficient * qTerm->coefficient;
                res.addTerm(expon, coeffee);
            }
        }
        return res;
    };

    friend ostream & operator << (ostream &out, const Polynomial &p) {
        Term *q = p.head;
        if (q == NULL) {
            out << "0";
            return out;
        }
        if (q->coefficient < 0) {
            out << "- ";
        }
        if (abs(q->coefficient) != 1) {
            out << abs(q->coefficient);
        }
        if (q->exponent == 0 && abs(q->coefficient) == 1) {
            out << "1";
        }
        if (q->exponent == 1) {
            out << "x";
        }
        else if (q->exponent > 1) {
            out << "x^" << q->exponent;
        }
        q = q->next;
        while (q != NULL) {
            if (q->coefficient < 0) {
                out << " - ";
            }
            else {
                out << " + ";
            }
            if (abs(q->coefficient) != 1 || q->exponent == 0) {
                out << abs(q->coefficient);
            }
            if (q->exponent == 1) {
                out << "x";
            }
            else if (q->exponent > 1) {
                out << "x^" << q->exponent;
            }
            q = q->next;
        }
        return out;
    }
};