#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <random>
#include <ctype.h>
using namespace std;
ifstream f("Text.txt");
ifstream g("Text1.txt");
string Stats;

class Card
{
private:
    int strength;
    string name;
    int row;
public:
    Card();
    Card(string u_name, int u_strength, int u_row) {
        strength = u_strength;
        name = u_name;
        row = u_row;
    }
    int GetStrength();
    string GetName();
    int GetRow();
    void setName(string u_name);

};
Card::Card()
{
    strength = 0;
    name = "";
    row = 0;

}
void Card::setName(string u_name)
{
    name = u_name;
}
int Card::GetStrength()
{
    return strength;
}
string Card::GetName()
{
    return name;
}
int Card::GetRow()
{
    return row;
}



class Character {
protected:
    string playerName;
    int lifepoints;
    int playerId;

public:
    Character()
    {
        playerName = "";
        lifepoints = 2;
        playerId = 0;
    }
    Character(string name, int id)
    {
        playerName = name;
        lifepoints = 2;
        playerId = id;
    }

    int getlifepoints()
    {
        return lifepoints;
    }
    int getplayerId()
    {
        return playerId;
    }
    void setlifepoints()
    {
        lifepoints--;
    }
    string getName()
    {
        return playerName;
    }
};

class Player : public Character {
public:
    bool hasPlayedCardThisRound = false;
    Card hand[10];
    Card deck[22];
    int total[10];
    int total1 = 0, total2 = 0;

private:
    int cnt = 0, x = 0;
    int j, k;
    string i;

public:
    Player();
    Player(string u_name, int Id) : Character(u_name, Id) {}
    void InitializeDeck(ifstream& u_f);
    void ShowDeck();
    void ShowHand();
    char chooseAction(Player& u_player);
    void taketurn(Player& u_player);
    void storehand(Player& u_player);
    int calculateScore();
    void roundRestart(Player& u_player);
    void roundwinner(Player& opponent, int myScore, int opponentScore);
};

Player::Player() {}

void Player::roundwinner(Player& opponent, int myScore, int opponentScore) {
    if (myScore > opponentScore) {
        opponent.setlifepoints();
        cout << playerName << " wins the round!" << endl;
    }
    else if (opponentScore > myScore) {
        setlifepoints();
        cout << opponent.playerName << " wins the round!" << endl;
    }
    else {
        cout << "Round is a draw. No lifepoints lost." << endl;
    }
}
void Player::InitializeDeck(ifstream& u_f)
{
    while (u_f >> Stats)
    {
        if (cnt == 0)
            i = Stats;
        else if (cnt == 1)
            j = stoi(Stats);
        else if (cnt == 2)
            k = stoi(Stats);
        cnt++;
        if (cnt == 3) {
            cnt = 0;
            deck[x] = Card(i, j, k);
            x++;
        }
    }
}
void Player::ShowDeck()
{
    cout << "Cards in Deck: " << endl;
    for (int i = 0; i <= 16; i++)
    {
        cout << deck[i].GetName() << " " << deck[i].GetStrength() << " " << deck[i].GetRow() << endl;
    }
    cout << endl;
}
void Player::taketurn(Player& u_player)
{
    int n, x;
    j = 0;
    cout << "Choose how many cards do you want to place down: ";
    cout << endl;
    cin >> n;
    cout << "Choose what cards to place down (by index):" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        while (u_player.hand[x].GetName() == "used")
        {
            cout << "Invalid card, pick another: ";
            cin >> x;
        }
        u_player.total[j] = u_player.hand[x].GetStrength();
        u_player.hand[x].setName("used");
        j++;
    }

    u_player.hasPlayedCardThisRound = true;
}
int Player::calculateScore()
{
    int score = 0;
    for (int i = 0; i < j; i++) {
        score += total[i];
    }
    return score;
    cout << endl;

}
void Player::roundRestart(Player& u_player)
{
    int x = 0;
    for (int i = 0; i < 10; i++) {
        if (u_player.hand[i].GetName() == "used") {
            x = rand() % 17;
            u_player.hand[i] = u_player.deck[x];
        }
    }

}
char Player::chooseAction(Player& u_player) {
    char answer;
    while (true) {
        cout << "Choose action (Y - play / N - pass): ";
        cout << endl;
        cin >> answer;
        answer = toupper(answer);
        int usedCount = 0;
        for (int i = 0; i < 10; i++) {
            if (u_player.hand[i].GetName() == "used")
                usedCount++;
        }

        if (usedCount == 10) {
            cout << "All cards used. Passing automatically." << endl;
            return 'N';
        }

        if (answer == 'N' && !u_player.hasPlayedCardThisRound) {
            cout << "You cannot pass without playing any cards first." << endl;
            continue;
        }

        if (answer == 'Y') {
            taketurn(u_player);
            int score = calculateScore();
            cout << "Current score: " << score << endl;
            return 'Y';
        }
        else if (answer == 'N') {
            cout << "Player passed the round." << endl;
            return 'N';
        }
        else {
            cout << "Invalid input, please enter Y or N." << endl;
        }
    }
}

void Player::storehand(Player& u_player) {
    int x = 0;
    for (int i = 0; i < 10; i++) {
        x = rand() % 17;
        u_player.hand[i] = u_player.deck[x];
    }
}
void Player::ShowHand()
{
    cout << "Cards in " << playerName << " 's hand (name/ strenght/ lane)" << endl;
    for (int i = 0; i < 10; i++)
    {
        if (hand[i].GetName() != "used") {
            cout << hand[i].GetName() << "  " << hand[i].GetStrength() << "  " << hand[i].GetRow() << endl;
        }
    }

}

class Board
{
public:
    int V1mellee[10] = {};
    int V1ranged[10] = {};
    int V1siege[10] = {};
    int V2mellee[10] = {};
    int V2ranged[10] = {};
    int V2siege[10] = {};
    char tabla[6][14];
    int lifepoints1 = 2, lifepoints2 = 2;
    void Boardaddcard(Player u_player);
    void printboard();
    string board;
    Board() {}
    void clearboard();
    void updateboard();
    void updatelifepoints(Player u_player);
    void matchwinner(Player u_player);
    void resetCardArrays();
};
void Board::updatelifepoints(Player u_player)
{
    if (u_player.getplayerId() == 1)
        lifepoints1 = u_player.getlifepoints();
    else lifepoints2 = u_player.getlifepoints();
}
void Board::matchwinner(Player u_player)
{
    if (lifepoints1 == 0)
        cout << "PLAYER 2 WINS!";
    else if (lifepoints2 == 0)
        cout << "PLAYER 1 WINS!";
}
void Board::clearboard()
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 14; j++)
            tabla[i][j] = '_';
}
void Board::Boardaddcard(Player u_player)
{
    if (u_player.getplayerId() == 1)
        for (int i = 0; i < 10; i++) {
            if (u_player.hand[i].GetName() == "used")
                if (u_player.hand[i].GetRow() == 0)
                    V1mellee[i] = u_player.hand[i].GetStrength();
                else if (u_player.hand[i].GetRow() == 1)
                    V1ranged[i] = u_player.hand[i].GetStrength();
                else if (u_player.hand[i].GetRow() == 2)
                    V1siege[i] = u_player.hand[i].GetStrength();
        }
    else for (int i = 0; i < 10; i++) {
        if (u_player.hand[i].GetName() == "used")
            if (u_player.hand[i].GetRow() == 0)
                V2mellee[i] = u_player.hand[i].GetStrength();
            else if (u_player.hand[i].GetRow() == 1)
                V2ranged[i] = u_player.hand[i].GetStrength();
            else if (u_player.hand[i].GetRow() == 2)
                V2siege[i] = u_player.hand[i].GetStrength();
    }
}
void Board::updateboard()
{
    for (int i = 0, j = 0; i < 10; i++, j += 2)
        if (V2siege[i] != 0)
            tabla[0][j] = '0' + V2siege[i];

    for (int i = 0, j = 0; i < 10; i++, j += 2)
        if (V2ranged[i] != 0)
            tabla[1][j] = '0' + V2ranged[i];

    for (int i = 0, j = 0; i < 10; i++, j += 2)
        if (V2mellee[i] != 0)
            tabla[2][j] = '0' + V2mellee[i];

    for (int i = 0, j = 0; i < 10; i++, j += 2)
        if (V1mellee[i] != 0)
            tabla[3][j] = '0' + V1mellee[i];

    for (int i = 0, j = 0; i < 10; i++, j += 2)
        if (V1ranged[i] != 0)
            tabla[4][j] = '0' + V1ranged[i];

    for (int i = 0, j = 0; i < 10; i++, j += 2)
        if (V1siege[i] != 0)
            tabla[5][j] = '0' + V1siege[i];
}
void Board::printboard()
{
    cout << "lifepoints: " << lifepoints2 << "        PLAYER 2" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "          ";
        for (int j = 0; j < 14; j++)
            cout << tabla[i][j];
        cout << endl;
        cout << endl;
    }
    cout << "lifepoints: " << lifepoints1 << "       PLAYER 1" << endl;
}
void Board::resetCardArrays() {
    for (int i = 0; i < 10; i++) {
        V1mellee[i] = 0;
        V1ranged[i] = 0;
        V1siege[i] = 0;
        V2mellee[i] = 0;
        V2ranged[i] = 0;
        V2siege[i] = 0;
    }
}
int main()
{
    cout << "   WELCOME TO GWENT   ";
    cout << endl;
    srand(time(0));
    Player p1("Player 1", 1);
    Player p2("Player 2", 2);
    Board b1;
    b1.clearboard();
    p1.InitializeDeck(f);
    p2.InitializeDeck(g);
    p1.storehand(p1);
    p2.storehand(p2);

    while (p1.getlifepoints() > 0 && p2.getlifepoints() > 0) {
        cout << "\n--- NEW ROUND ---\n";
        p1.hasPlayedCardThisRound = false;
        p2.hasPlayedCardThisRound = false;
        b1.clearboard();

        bool p1Passed = false;
        bool p2Passed = false;

        while (!p1Passed && !p2Passed) {
            p1.ShowHand();
            char p1Action = p1.chooseAction(p1);
            if (p1Action == 'N') {
                p1Passed = true;
                cout << "Player 1 passed. Round ends.\n";
                break;
            }
            b1.Boardaddcard(p1);
            b1.updateboard();
            b1.printboard();

            p2.ShowHand();
            char p2Action = p2.chooseAction(p2);
            if (p2Action == 'N') {
                p2Passed = true;
                cout << "Player 2 passed. Round ends.\n";
                break;
            }
            b1.Boardaddcard(p2);
            b1.updateboard();
            b1.printboard();
        }

        int score1 = p1.calculateScore();
        int score2 = p2.calculateScore();

        cout << "\nScores:\nPlayer 1: " << score1 << " vs Player 2: " << score2 << "\n";
        p1.roundwinner(p2, score1, score2);
        b1.updatelifepoints(p1);
        b1.updatelifepoints(p2);
        b1.printboard();
        p1.roundRestart(p1);
        p2.roundRestart(p2);
        b1.resetCardArrays();
    }

    b1.matchwinner(p1);
    return 0;
}