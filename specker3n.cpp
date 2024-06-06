#include <stdexcept>
#include <iostream>

using namespace std;

class Game {
public:
    Game(int heaps, int players) {
        gameHeaps = heaps; gamePlayers = players;
        heapFill = 0; playerFill = 0;
        heap = new int[gameHeaps];
        players1 = new Player*[gamePlayers];
    };

    ~Game() {
        delete [] heap;
        delete [] players1;
    };

    void addHeap(int coins) throw(logic_error) {
        if (coins < 0) {
            throw logic_error("XRAY");
        }
        *(heap + heapFill) = coins;
        heapFill++;
    };

    void addPlayer(Player *player) throw(logic_error) {
        *(players1 + playerFill) = player;
        playerFill++;;
    };

    void play(ostream &out) throw(logic_error) {
        State s(gameHeaps, heap, gamePlayers);

        while (!s.winning()) {
            out << "State: " << s << endl;
            out << *getPlayer(s.getPlaying()) << " ";
            out << (**(players1 + s.getPlaying())).play(s) << endl;
            s.next((**(players1 + s.getPlaying())).play(s));
        }
        out << "State: " << s << endl;
        int w;
        if (s.getPlaying() == 0) {
            w = gamePlayers - 1;
        }
        else {
            w = s.getPlaying() - 1;
        }
        out << **(players1 + w) << " wins" << endl;
    };

    int getPlayers() const {
        return gamePlayers;
    };

    const Player *getPlayer(int p) const throw(logic_error) {
        if (p < 0 || p >= gamePlayers) {
            throw logic_error("ZULU");
        }
        return *(players1 + p);
    }

private:
    int gameHeaps, gamePlayers, playerFill, heapFill;
    int *heap;
    Player **players1;
};