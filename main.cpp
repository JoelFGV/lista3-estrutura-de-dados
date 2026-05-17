#include <iostream>
#include <chrono>
#include "Matchmaking.hpp"
#include "Player.hpp"

using namespace std;

void printDivider(string title) {
    cout << "\n==================== " << title << " ====================\n";
}

int main() {
    Matchmaking* sistemaPtr = new Matchmaking();
    Matchmaking& sistema = *sistemaPtr;
    int n;


    printDivider("1. INSERCAO DE JOGADORES");
    sistema.insert(Player(1, "Ana", 1000, 5));
    sistema.insert(Player(2, "Bruno", 900, 2));
    sistema.insert(Player(3, "Carla", 1000, 1));
    sistema.insert(Player(4, "Diego", 900, 4));
    sistema.insert(Player(5, "Eduarda", 1050, 6));
    
    cout << "Jogadores na fila:" << endl;
    sistema.printWaitingPlayers();


    printDivider("2. REMOCAO DE JOGADORES");
    cout << "Tentando remover ID 2 (Bruno)... ";
    if (sistema.removePlayer(2)) {
        cout << "Sucesso!" << endl;
    } else {
        cout << "Falha!" << endl;
    }
    sistema.printWaitingPlayers();


    printDivider("3. INSERTION SORT");
    sistema.insert(Player(2, "Bruno", 900, 2)); 
    cout << "Fila antes do Insertion Sort:" << endl;
    sistema.printWaitingPlayers();

    cout << "\nOrdenando com Insertion Sort..." << endl;
    sistema.sortByScoreInsertion();
    sistema.printWaitingPlayers();


    printDivider("4. MERGE SORT");
    sistema.insert(Player(6, "Fabio", 800, 10));
    cout << "Fila antes do Merge Sort:" << endl;
    sistema.printWaitingPlayers();
    
    cout << "\nOrdenando com Merge Sort..." << endl;
    sistema.sortByScoreMerge();
    sistema.printWaitingPlayers();


    printDivider("5. FORMACAO DE GRUPO (SEM SUCESSO)");
    cout << "Tentando formar grupo: tamanho 3 e delta 10..." << endl;
    Player* grupoS = sistema.formGroup(3, 10, &n);

    if (grupoS != nullptr) {
        cout << "Grupo formado com sucesso (" << n << " jogadores):" << endl;
        for (int i = 0; i < n; i++) {
            cout << " - " << grupoS[i].getName() << " (Score: " << grupoS[i].getScore() << ")" << endl;
        }
        delete[] grupoS;
    } else {
        cout << "Nenhum grupo foi formado." << endl;
    }


    printDivider("6. FORMACAO DE GRUPO (SUCESSO)");
    cout << "Tentando formar grupo: tamanho 3, delta 100..." << endl;
    Player* grupoF = sistema.formGroup(3, 100, &n);

    if (grupoF != nullptr) {
        cout << "Grupo formado com sucesso (" << n << " jogadores):" << endl;
        for (int i = 0; i < n; i++) {
            cout << " - " << grupoF[i].getName() << " (Score: " << grupoF[i].getScore() << ")" << endl;
        }
        delete[] grupoF;
    } else {
        cout << "Nenhum grupo foi formado." << endl;
    }


    printDivider("7. RECUPERACAO COM getWaitingPlayers");
    Player* lista = sistema.getWaitingPlayers(&n);
    cout << "Jogadores recuperados da fila:" << endl;
    if (lista != nullptr) {
        for(int i = 0; i < n; i++) {
            cout << i+1 << ". " << lista[i].getName() << endl;
        }
        delete[] lista; // Deletando a cópia
    }


    printDivider("8. TESTE DE PERFORMANCE COM 10 TAMANHOS DIFERENTES");

    int test_sizes[6] = {500, 1000, 2000, 4000, 8000, 16000};

    for(int t = 0; t < 6; t++) {
        int current_size = test_sizes[t];
        cout << "\n>>> TESTANDO COM " << current_size << " JOGADORES <<<" << endl;

        // --- TESTE MERGE SORT ---
        Matchmaking* perfMerge = new Matchmaking();
        for(int i = 0; i < current_size; i++) {
            perfMerge->insert(Player(i, "Bot", rand() % 5000, i));
        }
        
        auto startM = chrono::high_resolution_clock::now();
        perfMerge->sortByScoreMerge();
        auto endM = chrono::high_resolution_clock::now();
        
        chrono::duration<double, milli> tMerge = endM - startM;
        cout << "Tempo Merge Sort:    " << tMerge.count() << " ms" << endl;
        delete perfMerge;

        // --- TESTE INSERTION SORT ---
        Matchmaking* perfInsert = new Matchmaking();
        for(int i = 0; i < current_size; i++) {
            perfInsert->insert(Player(i, "Bot", rand() % 5000, i));
        }
        
        auto startI = chrono::high_resolution_clock::now();
        perfInsert->sortByScoreInsertion();
        auto endI = chrono::high_resolution_clock::now();
        
        chrono::duration<double, milli> tInsert = endI - startI;
        cout << "Tempo Insertion Sort: " << tInsert.count() << " ms" << endl;
        delete perfInsert;
        
        cout << "-----------------------------------------------" << endl;
    }

    // LIMPEZA FINAL
    delete sistemaPtr;
    printDivider("FIM DOS TESTES");

    return 0;
}
