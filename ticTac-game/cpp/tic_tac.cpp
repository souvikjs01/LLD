#include<iostream>
#include<vector>
#include<deque>
#include<string>
using namespace std;

class IObserver {
public:
    virtual void update(string msg) = 0;
    virtual ~IObserver() {}
};

class Symbol {
private:
    char mark;
public:
    Symbol(char mark) {
        this->mark = mark;
    }
    char getMark() {
        return mark;
    }
};

class Board {
private:
    vector<vector<Symbol*>> grid;
    int size;
    Symbol* emptyCell;
public:
    Board(int s) {
        this->size = s;
        emptyCell = new Symbol('-');
        grid = vector<vector<Symbol*>>(size, vector<Symbol*>(size, emptyCell));
    }

    bool isCellEmpty(int row, int col) {
        if(row < 0 || row >= size || col < 0 || col >= size) return false;
        return grid[row][col] == emptyCell;
    }

    bool placeMark(int row, int col, Symbol* s) {
        if(row < 0 || row >= size || col < 0 || col >= size) {
            return false;
        }

        if(!isCellEmpty(row, col)) {
            return false;
        }

        grid[row][col] = s;
        return true;
    }

    Symbol* getCell(int row, int col) {
        if(row < 0 || row >= size || col < 0 || col >= size) {
            return emptyCell;
        }

        return grid[row][col];
    }

    int getSize() {
        return size;
    }

    Symbol* getEmptyCell() {
        return emptyCell;
    }

    void display() {
        cout << "\n ";
        for(int i=0; i<size; i++) {
            cout << i << " ";
        }
        cout << endl;

        for(int i=0; i<size; i++) {
            cout << i << " ";
            for(int j =0 ; j < size; j++) {
                cout << grid[i][j]->getMark() << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

class TicTacPlayer {
private:
    int playerId;
    string name;
    Symbol* symbol;
    int score;
public:
    TicTacPlayer(int id, string n, Symbol* s) {
        this->playerId = id;
        this->name = n;
        this->symbol = s;
        this->score = 0;
    }

    string getName() {
        return name;
    }
    int getPlayerId() {
        return playerId;
    }
    int getScore() {
        return score;
    }
    Symbol* getSymbol() {
        return symbol;
    }
    void incrementScore() {
        score++;
    }
    ~TicTacPlayer() {
        delete symbol;
    }
};

class TicTacRules {
public:
    virtual bool isValidMove(Board* b, int row, int col) = 0;
    virtual bool checkWinCondition(Board* b, Symbol* s) = 0;
    virtual bool checkDrawCondition(Board* b, Symbol* s) = 0;
    virtual ~TicTacRules() {}
};

class StandardTicTacRules : public TicTacRules {
public:
    bool isValidMove(Board* b, int row, int col) override {
        if(b->isCellEmpty(row, col)) {
            return true;
        }
        return false;
    }

    bool checkWinCondition(Board* b, Symbol* s) {
        int size = b->getSize();

        // check rows
        for(int i=0; i<size; i++) {
            bool win = true;
            for(int j = 0; j < size; j++) {
                if(b->getCell(i, j) != s) {
                    win = false;
                    break;
                }
            }
            if(win) {
                return true;
            }
        }

        // check col
        for(int i=0; i<size; i++) {
            bool win = true;
            for(int j=0; j<size; j++) {
                if(b->getCell(j, i) != s) {
                    win = false;
                    break;
                }
            }
            if(win){
                return true;
            }
        }

        // check diagonal
        bool win = true;
        for(int i=0; i<size; i++) {
            if(b->getCell(i, i) != s) {
                win = false;
                break;
            }
        }
        if(win) {
            return true;
        }

        // check anti- diagonal
        win = true;
        for(int i=0; i<size; i++) {
            if(b->getCell(i, size-1-i) != s) {
                win = false;
                break;
            }
        }
        if(win) {
            return true;
        }

        return false;
    }

    bool checkDrawCondition(Board* b, Symbol* s) {
        int size = b->getSize();
        for(int i=0; i<size; i++) {
            for(int j=0; j<size; j++) {
                if(b->getCell(i, j) == b->getEmptyCell()) {
                    return false;
                }
            }
        }
        return true;
    }
};

// game class
class TicTacGame {
private:
    Board* board;
    deque<TicTacPlayer*> players;
    TicTacRules* rules;
    vector<IObserver*> observers;
    bool gameOver;
public:
    TicTacGame(int boardSize) {
        board = new Board(boardSize);
        this->gameOver = false;
    }

    void addPlayer(TicTacPlayer* player) {
        players.push_back(player);
    }

    void addObserver(IObserver* obs) {
        observers.push_back(obs);
    }

    void notify(string msg) {
        for(auto obs : observers) {
            obs->update(msg);
        }
    }

    void setRule(TicTacRules* rule) {
        this->rules = rule;
    }

    void play() {
        if(players.size() < 2) {
            cout << "Need at least two players" << endl;
            return;
        }

        notify("TicTac game is started");

        while(!gameOver) {
            board->display();

            TicTacPlayer* currentPlayer = players.front();
            cout << currentPlayer->getName() << " (" << currentPlayer->getSymbol()->getMark() << ") - Enter row and col: " << endl;

            int row, col;
            cin >> row >> col;

            if(rules->isValidMove(board, row, col)) {
                board->placeMark(row, col, currentPlayer->getSymbol());
                notify(currentPlayer->getName() + " played (" + to_string(row) + "," + to_string(col) + ")");

                if(rules->checkWinCondition(board, currentPlayer->getSymbol())) {
                    board->display();
                    cout << currentPlayer->getName() << " wins!" << endl;
                    currentPlayer->incrementScore();

                    notify(currentPlayer->getName() + " wins!");

                    gameOver = true;

                } else if(rules->checkDrawCondition(board, currentPlayer->getSymbol())) {
                    board->display();
                    cout << "Its a draw!" << endl;
                    notify("Game is draw!");
                    gameOver = true;
                } else {
                    players.pop_front();
                    players.push_back(currentPlayer);
                }
            } else {
                cout << "Invalid move! try again." << endl;
            }
        }
    }

    ~TicTacGame() {
        delete board;
        delete rules;
    }
};

enum GmaeType {
    STANDARD
};

class TicTacGameFactory {
public:
    static TicTacGame* createGame(GmaeType gt, int boardSize) {
        TicTacGame* game = new TicTacGame(boardSize);
        if(GmaeType::STANDARD == gt) {
            game->setRule(new StandardTicTacRules());
            return game;
        }
        return nullptr;
    }
};

class ConsoleNotifier : public IObserver {
public:
    void update(string msg) override {
        cout << "[Notification] " << msg << endl;
    }
};

int main() {
    cout << "=== TIC TAC GAME ====" << endl;

    int boardSize;
    cout << "Enter board size (ex- for 3*3):" << endl;
    cin >> boardSize;

    TicTacGame* game = TicTacGameFactory::createGame(GmaeType::STANDARD, boardSize);

    // add boserver:
    IObserver* notifier = new ConsoleNotifier();
    game->addObserver(notifier);

    // create players:
    TicTacPlayer* player1 = new TicTacPlayer(1, "Alex", new Symbol('X'));
    TicTacPlayer* player2 = new TicTacPlayer(1, "John", new Symbol('O'));

    game->addPlayer(player1);
    game->addPlayer(player2);

    game->play();

    delete game;
    delete notifier;
    delete player1;
    delete player2;

    return 0;
}