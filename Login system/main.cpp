#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool LoggingIN()
{
    string username, password, user_un, user_pw;

    cout << "Enter username:   ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream read("data\\" + username + ".txt");
    getline(read, user_un);
    getline(read, user_pw);

    if (user_un == username && user_pw == password)
    {
        return true;
    }

    else
    {
        return false;
    }
}

int main()
{
    int choice;

    cout << "1: Register\n2: Register\nYour choice:  ";
    cin >> choice;

    if (choice == 1)
    {
        string username, password;

        cout << " Select username:  ";
        cin >> username;
        cout << " Select password:  ";
        cin >> password;

        ofstream file;
        file.open("data\\" + username + ".txt");
        file << username << endl << password << endl;
        file.close();

        main();
    }

    else if (choice == 2)
    {
        bool status = LoggingIN();

        if (!status)
        {
            cout << "False login" << endl;
            system("PAUSE");
            return 0;
        }

        else {
            cout << "Success! You are logged in!" << endl;
            system("PAUSE");
            return 1;
        }
    }
}