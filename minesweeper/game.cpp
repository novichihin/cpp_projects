#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper
{
private:
    int rows;
    int cols;
    int numMines;
    vector<vector<char> > board;
    vector<vector<bool> > revealed;
    vector<vector<bool> > mines;

public:
    Minesweeper(int r, int c, int minesCount) : rows(r), cols(c), numMines(minesCount)
    {
        board.resize(rows, vector<char>(cols, '.'));
        revealed.resize(rows, vector<bool>(cols, false));
        mines.resize(rows, vector<bool>(cols, false));
        generateMines();
    }

    void generateMines()
    {
        srand(time(0));
        int count = 0;
        while (count < numMines)
        {
            int row = rand() % rows;
            int col = rand() % cols;
            if (!mines[row][col])
            {
                mines[row][col] = true;
                count++;
            }
        }
    }

    bool isValid(int row, int col)
    {
        return (row >= 0 && row < rows && col >= 0 && col < cols);
    }

    int countAdjacentMines(int row, int col)
    {
        int count = 0;
        for (int i = row - 1; i <= row + 1; i++)
        {
            for (int j = col - 1; j <= col + 1; j++)
            {
                if (isValid(i, j) && mines[i][j])
                {
                    count++;
                }
            }
        }
        return count;
    }

    void revealCell(int row, int col)
    {
        if (!isValid(row, col) || revealed[row][col])
        {
            return;
        }

        revealed[row][col] = true;
        if (mines[row][col])
        {
            gameOver();
        }
        else
        {
            int count = countAdjacentMines(row, col);
            board[row][col] = '0' + count;

            if (count == 0)
            {
                for (int i = row - 1; i <= row + 1; i++)
                {
                    for (int j = col - 1; j <= col + 1; j++)
                    {
                        revealCell(i, j);
                    }
                }
            }
        }
    }

    void printBoard(bool showMines)
    {
        cout << "Поле сапёра:" << endl;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (revealed[i][j])
                {
                    cout << board[i][j] << ' ';
                }
                else if (showMines && mines[i][j])
                {
                    cout << "* ";
                }
                else
                {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }

    void gameOver()
    {
        cout << "Game Over!" << endl;
        printBoard(true);
        exit(0);
    }

    bool gameWon()
    {
        int count = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (!mines[i][j] && revealed[i][j])
                {
                    count++;
                }
            }
        }
        return count == (rows * cols - numMines);
    }

    void play()
    {
        while (true)
        {
            printBoard(false);

            int row, col;
            cout << "Введите ряд и столбец (нулевая индексации): ";
            cin >> row >> col;

            if (!isValid(row, col))
            {
                cout << "Неверный формат ввода! Повторите еще раз." << endl;
                continue;
            }

            revealCell(row, col);

            if (gameWon())
            {
                cout << "Поздравляю! Вы победили!" << endl;
                printBoard(true);
                break;
            }
        }
    }
};

int main()
{
    int rows, cols, numMines;
    cout << "Введите количество рядов: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;
    cout << "Введите количество мин: ";
    cin >> numMines;

    Minesweeper game(rows, cols, numMines);
    game.play();

    return 0;
}