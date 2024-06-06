#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std;

class ChessBoardArray {
protected:
    class Row {
    public:
        Row(ChessBoardArray &a, int i): array(a), row(i) {}
        int & operator [] (int i) const {
            return array.select(row, i);
        };
    private:
        int row;
        ChessBoardArray &array;
    };

    class ConstRow {
    public:
        ConstRow(const ChessBoardArray &a, int i): array(a), row(i) {}
        int operator [] (int i) const {
            return array.select(row, i);
        };
    private:
        const ChessBoardArray &array;
        int row;
    };

public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0) {
        data = new int[(size*size + 1)/2];
        sizea = size;
        baseCBA = base;
    };
    ChessBoardArray(const ChessBoardArray &a) {
        data = new int[(a.sizea*a.sizea + 1)/2];
        sizea = a.sizea;
        baseCBA = a.baseCBA;
        for (unsigned i = 0; i < (sizea*sizea + 1)/2; i++) {
            data[i] = a.data[i];
        }
    };
    ~ChessBoardArray() {
        delete [] data;
    };

    ChessBoardArray & operator = (const ChessBoardArray &a) {
        delete [] data;
        sizea = a.sizea;
        baseCBA = a.baseCBA;
        data = new int[(sizea*sizea + 1)/2];
        for (unsigned i = 0; i < (sizea*sizea + 1)/2; i++) {
            data[i] = a.data[i];
        }
        return *this;
    };

    int & select (int i, int j) {
        return data[loc(i, j)];
    };

    int select(int i, int j) const {
        return data[loc(i, j)];
    };

    const Row operator [] (int i) {
        return Row(*this, i);
    };

    const ConstRow operator [] (int i) const {
        return ConstRow(*this, i);
    };

    friend ostream & operator << (ostream &out, const ChessBoardArray &a) {
        for (int i = a.baseCBA; i < a.baseCBA + a.sizea; i++) {
            for (int j = a.baseCBA; j < a.baseCBA + a.sizea; j++) {
                out << setw(4);
                if ((i + j - 2 * a.baseCBA) % 2 == 0) {
                    out << a.select(i, j);
                }
                else out << 0;
            }
            out << endl;
        }
        return out;
    };

private:
    unsigned int loc(int i, int j) const throw(out_of_range) {
        int di = i - baseCBA, dj = j - baseCBA;
        if (di < 0 || dj < 0 || di >= sizea || dj >= sizea || (i + j)%2 == 1) {
            throw out_of_range("BROKEN ARROW");
        }
        return (di*sizea + dj)/2;
    };
    int *data;
    unsigned sizea, baseCBA;
};