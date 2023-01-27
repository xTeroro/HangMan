#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <map>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <string>

using namespace std;

ifstream fin("words.txt");

// Main Components
map<int, string> words;
bool wordRemov = false, DEBUGMODE = false, CustomMode = false;
int words_count, max_word = 0;
// In-Game Components
int moves_left, letters_left, spaces;
string letters[8];
char answer;
string game_word, answer_mid;
map<int, string> playing_word;
bool win, correct_ans, space;

// Here I declared everything I need

// Declaring Frequently Used Functions
void LoadingBar(int full)
{
    for (int i = 0; i < full; i++)
    {
        cout << '\r' << "Loading elements... [" << i << "]";
    }
    cout << "\n\n";
}
void RemoveMap(int id)
{
    words.erase(id);
    words_count--;
}
int Randomizer(int n)
{
    srand(time(NULL));
    int r;
    r = (rand() % n);
    return r;
}
bool Check(char y, char n, string error, string msg)
{
    char x;
    string p;
    bool status = true;
    while (true)
    {
        cout << msg << " ";
        getline(cin, p);
        cout << '\n';
        if (p[1] != '\0')
        {
            cout << error << '\n';
        }
        else
        {
            x = p[0];
            if (x == y || x == y - 32)
            {
                status = true;
                break;
            }
            else if (x == n || x == n - 32)
            {
                status = false;
                break;
            }
            else
            {
                cout << error << "\n\n";
            }
        }
    }
    return status;
}
bool CheckWin()
{
    for (int i = 0; i < playing_word.size(); i++)
    {
        if (playing_word[i] == "_")
        {
            return false;
        }
    }
    return true;
}
void Load_Words()
{
    int i = 0;
    string x;
    while (getline(fin, x))
    {
        words[i] = x;
        cout << '\r' << "Loading elements... [" << i << "]";
        i++;
        if (max_word < x.length())
        {
            max_word = x.length();
        }
    }
    words_count = i;
    cout << "\n\n";
}
void Choosing()
{
    space = false;
    spaces = 0;
    if (CustomMode == false)
    {
        cout << "Choosing a random word... ";
        for (int i = 1; i <= 3; i++)
        {
            cout << i << " ";
            Sleep(1000);
        }
        cout << "\n\n";
        int x = Randomizer(words_count);
        game_word = words[x];
        if (wordRemov == false)
        {
            RemoveMap(x);
            words_count--;
        }
    }
    else
    {
        cout << "Please enter a word to play with. ";
        getline(cin, game_word);
        for (int m = 0; m < 50; m++)
        {
            cout << '\n';
        }
        max_word = game_word.length();
    }
    for (int i = 0; i < game_word.length(); i++)
    {
        if (game_word[i] == ' ')
        {
            playing_word[i] = " ";
            spaces++;
            space = true;
        }
        else
        {
            playing_word[i] = "_";
        }
    }
    letters_left = playing_word.size() - spaces;
    if (DEBUGMODE == true)
    {
        cout << game_word << "\n\n";
    }
}
void ShowWord()
{
    for (int i = 0; i < playing_word.size(); i++)
    {
        cout << playing_word[i] << ' ';
    }
}
// Declaring Special Functions
void RemovWord()
{
    if (Check('y', 'n', "Invalid Input! Try again Y/N ", "Do you want the words to repeat? Y/N: ") == true)
    {
        wordRemov = true;
    }
}
void CustomWords()
{
    if (Check('y', 'n', "Invalid Input! Try again Y/N ", "Do you want to input the words yourself? Y/N: ") == true)
    {
        CustomMode = true;
    }
}
void ShowStats()
{
    cout << "Your word is: ";
    ShowWord();
    cout << '\n'
         << "You have " << moves_left << " moves left." << '\n'
         << "Your answers: ";
    for (int i = 0; i < 8 - moves_left; i++)
    {
        cout << letters[i] << ", ";
    }
    cout << "\n\n";
}
void GameSetUp()
{
    moves_left = 8;
    playing_word.clear();
    for(int i = 0; i < 8; i++)
    {
        letters[i].clear();
    }
    win = false;
    if (CustomMode == false)
    {
        LoadingBar(words_count);
    }
    Choosing();
}
void Start()
{
    cout << "Press any key to start the game...\n\n";
    int debug = getch();
    if (debug == '|')
    {
        DEBUGMODE = true;
        cout << "\n\n DEBUGMODE IS ACTIVATED! \n\n";
    }
    CustomWords();
    if (CustomMode == false)
    {
        Load_Words();
        RemovWord();
    }
    else
    {
        DEBUGMODE = false;
    }
}
void Game()

{
    GameSetUp();
    while (true)
    {
        if (win == true)
        {
            cout << "\nYou win! Slabule. The word was: " << game_word << "\n\n";
            break;
        }
        ShowStats();
        cout << "Input your answer from a to z or a word. \n\n";
        while (true)
        {
            getline(cin, answer_mid);
            cout<<'\n';
            if (answer_mid.length() <= max_word)
            {
                if (answer_mid[1] == '\0')
                {
                    answer = answer_mid[0];
                    if ((answer >= 'a' && answer <= 'z') || (answer >= 'A' && answer <= 'Z'))
                    {
                        correct_ans = false;
                        bool alreadyInp = false;
                        for (int m = 0; m < 8; m++)
                        {
                            if (letters[m] == answer_mid)
                            {
                                alreadyInp = true;
                                cout << "Please input a new letter. You already choosed this one.\n\n";
                                break;
                            }
                        }
                        if (alreadyInp == false)
                        {
                            letters[8 - moves_left] = answer;
                            for (int i = 0; i < playing_word.size(); i++)
                            {
                                if (letters[8 - moves_left][0] == game_word[i])
                                {
                                    correct_ans = true;
                                    if (playing_word[i] == letters[8 - moves_left])
                                    {
                                        cout << "Please input a new letter. You already choosed this one.\n\n";
                                    }
                                    else
                                    {

                                        playing_word[i] = letters[8 - moves_left];
                                    }
                                }
                                if (CheckWin() == true)
                                {
                                    win = true;
                                }
                            }
                            if (correct_ans != true)
                            {
                                moves_left--;
                            }
                        }
                        break;
                    }
                    else
                    {
                        cout << "\n"
                             << "Input a valid answer from a to z: \n\n";
                    }
                }
                else
                {
                    if (game_word == answer_mid)
                    {
                        win = true;
                        break;
                    }
                    else
                    {
                        letters[8 - moves_left] = answer_mid;
                        moves_left--;
                        break;
                    }
                }
            }
            else
            {
                cout << "A word can't be longer than " << max_word << " characters. \n\n";
            }
        }
        if (moves_left <= 0)
        {
            cout << "You Loose! Slabule! The word was: " << game_word << "\n\n";
            win == false;
            break;
        }
    }
    if (Check('y', 'n', "Input a valid answer! y/n ", "Would you like to play again? y/n ") == true)
    {
        Game();
    }
}

int main()
{
    cout<<"=======\n|| B ||\n|| Y ||\n||   ||\n|| T ||\n|| E ||\n|| R ||\n|| O ||\n|| R ||\n|| O ||\n======= \n\n\n\n";
    if(!fin)
    {
        cout<<"\n\n\n\n\n\n\n\n\nThe file words.txt doesn't exist! check the README file for instructions.";
        cout<<"\n\n\n\n\nBecause the file doesn't exist you can still play HangMan but with words set by you!\nStarting...\n";
        for(int i = 1; i <= 3; i++)
        {
            Sleep(3000);
            cout<<i<<'\n';
        }
        cout<<'\n';
        CustomMode = true;
        Game();
    }else
    {
            Start();
            Game();
    }

    cout << "\n\n"<< "Game Terminated! This window will automaticly close in 10 seconds.\n\n";

    for(int i = 1; i <= 10; i++)
    {
        Sleep(1000);
        cout<<i<<'\n';
    }
}