#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include "Player.hpp"

const int MAX_PLAYERS = 100000;

class Matchmaking {
private:
    Player players[MAX_PLAYERS]; // Array estático
    int size;

    // Auxiliares para o Merge Sort
    void merge(int left, int mid, int right);
    void mergeSort(int left, int right);
    
    // Auxiliar para comparação (score -> timestamp)
    bool comesBefore(Player p1, Player p2);

public:
    Matchmaking();
    ~Matchmaking();

    bool insert(Player player);
    bool removePlayer(int id);

    void sortByScoreInsertion();
    void sortByScoreMerge();

    // Retorna array dinâmico (delete[] obrigatório no main)
    Player* formGroup(int groupSize, int delta, int* n);
    Player* getWaitingPlayers(int* n);

    void printWaitingPlayers();
};

#endif