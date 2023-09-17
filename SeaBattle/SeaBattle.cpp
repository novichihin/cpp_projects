#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Ship
{

private:
    int size;
    int hits;

public:
    Ship(int size) : size(size), hits(0) {}

    bool checkHit()
    {
        hits++;
        return (hits == size);
    }

    bool isSunk() const
    {
        return (hits == size);
    }
};

class Board
{
private:
    int size;
    vector<vector<char> > board;
    vector<Ship> ships;

public:
    Board(int size) : size(size)
    {
        board.resize(size, vector<char>(size, '-'));
    }

    void placeShips()
    {
        for (int i = 0; i < 3; ++i)
        {
            Ship s(3);
            ships.push_back(s);
        }

        for (int i = 0; i < 2; ++i)
        {
            Ship s(2);
            ships.push_back(s);
        }
    }

    void printBoard()
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
    void shoot(int row, int col)
    {
        if (row >= 0 && row < size && col >= 0 && col < size)
        {
            char &cell = board[row][col];
            if (cell == '-')
            {
                cell = 'O';
                cout << "Промах!" << endl;
            }
            else if (cell == 'O' || cell == 'X')
            {
                cout << "Вы уже стреляли в данную клетку!" << endl;
            }
            else
            {
                cell = 'X';
                cout << "Попадание!" << endl;
                int shipIndex = cell - '0' - 1;
                if (ships[shipIndex].checkHit())
                {
                    cout << "Корабль потоплен!" << endl;
                }
            }
        }
        else
        {
            cout << "Неправильные координаты!" << endl;
        }
    }

    bool allShipsSunk() const
    {
        for (const Ship &ship : ships)
        {
            if (!ship.isSunk())
            {
                return false;
            }
        }
        return true;
    }

    int getSize() const
    {
        return size;
    }
};

class Player
{
private:
    string name;

public:
    Player(const string &name) : name(name) {}

    void makeMove(Board &board)
    {
        int row, col;
        cout << "Ход игрока " << name << endl;
        cout << "Введите координаты для выстрела (в формате строка столбец): ";
        cin >> row >> col;
        board.shoot(row, col);
    }
};

class Game
{
private:
    Board board;
    Player player;
    Player computer;

public:
    Game(int boardSize) : board(boardSize), player("Игрок"), computer("Компьютер") {}

    void run()
    {
        board.placeShips();
        while (true)
        {
            cout << "Текущее состояние поля игрока:" << endl;
            board.printBoard();
            player.makeMove(board);
            if (board.allShipsSunk())
            {
                cout << "Вы победили!" << endl;
                break;
            }

            cout << "Текущее состояние поля компьютера:" << endl;
            computer.makeMove(board);
            if (board.allShipsSunk())
            {
                cout << "Компьютер победил!" << endl;
                break;
            }
        }
    }
};

int main()
{
    Game game(5);
    game.run();
    return 0;
}