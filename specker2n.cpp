#include <iostream>

using namespace std;

#define MIN 10000010

class Player {
public:
    Player(const string &n) {
        name = n;
    };

    virtual ~Player() {};

    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream & operator << (ostream &out, const Player &player) {
        out << player.getType() << " player " << player.name;
        return out;
    };
private:
    string name;
};

class GreedyPlayer : public Player {
public:
    GreedyPlayer(const string &n) : Player(n) {
        type = "Greedy";
    };

    virtual const string & getType() const override {
        return type;
    };

    virtual Move play(const State &s) {
        int max = 0, maxpos = 0;
        for (int i = 0; i < s.getHeaps(); i++) {
            if (s.getCoins(i) > max) {
                max = s.getCoins(i); maxpos = i;
            }
        }
        return Move(maxpos, max, 0, 0);
    };
private:
    string type;
};

class SpartanPlayer : public Player {
public:
    SpartanPlayer (const string &n) : Player(n) {
        type = "Spartan";
    };

    virtual const string & getType() const override {
        return type;
    };

    virtual Move play(const State &s) {
        int max = 0, maxpos = 0;
        for (int i = 0; i < s.getHeaps(); i++) {
            if (s.getCoins(i) > max) {
                max = s.getCoins(i); maxpos = i;
            }
        }
        return Move(maxpos, 1, 0, 0);
    };
private:
    string type;
};

class SneakyPlayer : public Player {
public:
    SneakyPlayer(const string &n) : Player(n) {
        type = "Sneaky";
    };

    virtual const string & getType() const override {
        return type;
    };

    virtual Move play(const State &s) {
        int min = MIN, minpos = 0;
        for (int i = 0; i < s.getHeaps(); i++) {
            if (s.getCoins(i) < min && s.getCoins(i) > 0) {
                min = s.getCoins(i); minpos = i;
            }
        }
        return Move(minpos, min, 0, 0);
    };
private:
    string type;
};

class RighteousPlayer : public Player {
public:
    RighteousPlayer(const string &n) : Player(n) {
        type = "Righteous";
    };

    virtual const string & getType() const override {
        return type;
    };

    virtual Move play(const State &s) {
        int max = 0, maxpos = 0, min = MIN, minpos = 0;
        for (int i = 0; i < s.getHeaps(); i++) {
            if (s.getCoins(i) > max) {
                max = s.getCoins(i); maxpos = i;
            }
        }
        for (int i = 0; i < s.getHeaps(); i++) {
            if (s.getCoins(i) < min) {
                min = s.getCoins(i); minpos = i;
            }
        }
        return Move(maxpos, (max + 1)/2, minpos, (max + 1)/2 - 1);
    };
private:
    string type;
};