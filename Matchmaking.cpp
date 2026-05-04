#include <iostream>
#include "Matchmaking.hpp"

using namespace std;

// Construtor / Destrutor
Matchmaking::Matchmaking() : size(0) {}

Matchmaking::~Matchmaking() {}

// Auxiliares
bool Matchmaking::comesBefore(Player p1, Player p2) {
    if (p1.getScore() < p2.getScore()) {
        return true;
    }

    if (p1.getScore() == p2.getScore()) {
        return p1.getTimestamp() < p2.getTimestamp();
    }
    
    return false;
};

void Matchmaking::merge(int left, int mid, int right) {
    int sizeL = mid - left + 1;
    int sizeR = right - mid;

    Player* L = new Player[sizeL];
    for (int i = 0; i < sizeL; i++) {
        L[i] = players[left + i];
    }

    Player* R = new Player[sizeR];
    for (int j = 0; j < sizeR; j++) {
        R[j] = players[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < sizeL && j < sizeR) {
        if (comesBefore(L[i], R[j])) {
            players[k] = L[i];
            i++;
        } else {
            players[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < sizeL) {
        players[k] = L[i];
        i++;
        k++;
    }

    while (j < sizeR) {
        players[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
};

void Matchmaking::mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
};

// Funções principais
bool Matchmaking::insert(Player player) {
    if (size >= MAX_PLAYERS) {
        return false;
    }
    
    players[size++] = player;
    return true;
};

bool Matchmaking::removePlayer(int id) {
    for (int i = 0; i < size; i++) {
        if (players[i].getId() == id) {
            size--;
            for (int j = i; j < size; j++) {
                players[j] = players[j+1];
            }
            return true;
        }
    }

    return false;
};

void Matchmaking::sortByScoreInsertion() {
    for (int i = 1; i < size; i++) {
        Player actual_player = players[i];

        int j = i - 1;
        while (j >= 0 && comesBefore(actual_player, players[j])) {
            players[j + 1] = players[j];
            j--;
        }
        players[j + 1] = actual_player;
    }
};

void Matchmaking::sortByScoreMerge() {
    mergeSort(0, size - 1);
};

Player* Matchmaking::formGroup(int groupSize, int delta, int* n) {
    if (size < groupSize || groupSize <= 0 || n == nullptr) {
        return nullptr;
    }

    // Supor que já está ordenado: Score -> TimeStamp
    int group_i = -1;
    for (int i = 0; i < size - groupSize + 1; i++) {
        if (players[i + groupSize - 1].getScore() - players[i].getScore() <= delta) {
            group_i = i;
            break;
        }
    }

    if (group_i == -1) {
        *n = 0;
        return nullptr;
    }

    *n = groupSize;

    // Copia
    Player* group = new Player[groupSize];
    for (int i = 0; i < groupSize; i++) {
        group[i] = players[group_i + i];
    }

    // Remoção
    size -= groupSize;
    for (int i = group_i; i < size; i++) {
        players[i] = players[i + groupSize];
    }

    return group;
};

Player* Matchmaking::getWaitingPlayers(int* n) {
    if (n != nullptr) {
        *n = size;
    }

    if (size == 0) {
        return nullptr;
    }

    Player* waitingPlayers = new Player[size];
    for (int i = 0; i < size; i++) {
        waitingPlayers[i] = players[i];
    }

    return waitingPlayers;
};

void Matchmaking::printWaitingPlayers() {
    cout << "Waiting Players:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "["
        << players[i].getId() << " | "
        << players[i].getName() << " | "
        << players[i].getScore() << " | "
        << players[i].getTimestamp()
        << "]"
        << endl;
    }
};
