/** Pre processamento - Ocorrencias em database
    Programacao Paralela e Concorrente
    Autores:
    Mauricio Freire
    Victor Gabriel
    Vinnicius Stein
    Vitor Oliveira
*/


#include <iostream>
#include <omp.h>
#include <fstream>
using namespace std;
#include <string>
using std::getline;
#include <vector>
#include <sstream>
#include <cstdlib>


/*  Insere elementos unicos
    data -> vector de strings dos valores da coluna X colunas
    token -> elemento a ser inseridp
    k -> contador da linha respectiva (coluna do dataset > elemento)
*/


void contar(vector<vector<string> > &data, string token, vector<vector<int>> &vet, int k) {
    int i, count = 0, linha = 0;

    cout << "func contar";
    for(i = 0; i < data[k].size(); i++) {
        if ((data[k][i].compare(token) == 0)) {
            count += 1;
            return;
        }
    }
    vet[linha++].push_back(count);   
}


void insertUnique (vector<vector<string> > &data, string token, int k) {

    int i = 0;

    for(i = 0; i < data[k].size(); i++) {
        if ((data[k][i].compare(token) == 0)) {
                // Contagem? - Encontra um repetido
             return;
            }
    }
    data[k].push_back(token); // Nao encontrou nenhum valor igual ao token
    // cont[k].push_back(0);
}


int main(int argc, char *argv[]) {

    ifstream database;

    database.open("dataset_00_1000_v3.csv");
     if (!database.is_open())
    {
        std::exit(EXIT_FAILURE);
    }


    int k = 0;
    string str;


    getline(database, str); // Insere o header em um vetor
    vector<string> header;
    string head;
    std::istringstream h(str);
    int n = 0; //contador de quantidade de headers
    while (getline(h, head, ','))
        {
            n++;
            header.push_back(head);
        }

    // Criacao dos vectors para armazenar valores unicos
    vector<vector<string> > data(n);
    vector<vector<int> > cont(n);


    while (getline(database, str))
    {
        std::istringstream iss(str);
        string token;

        while (getline(iss, token, ','))
        {
            insertUnique(data, token, k);
            contar(data, token, k, cont);
            k++;
        }
        k = 0;
    }
    

/*
    //gravacao
    ofstream myFile;
        myFile.open("output.csv");
        for(int i =0; i < 20; i++){
              myFile << i << "," << i*i << end1;
        }
*/


   // Print de testes
    for (int q = 0; q < n; q++){
            cout << header[q] << ": ";
            for (int t = 0; t < data[q].size() ; t++) { // print all string in first vector of 'arr'

                cout << data[q][t] << ", ";
            }
            cout << endl << endl;
    }
        return 0;
}

/**TO DO
    Contagem de ocorrencias
    Escrita de arquivos de ocorrencias
    Substituição dos valores em arquivo (em arquivo novo)
 */

 //ALGORITMO UNIQUE
  // IF VECTOR contem ELEMENTO
    // ACRESCENTA NO CONTADOR
 //ELSE
    //PUSH.BACK(ELEMENTO)
    //PUSH.BACK(CONTADOR)

    // THREAD ESCRITA MATRIZ OCORRENCIA;
    // THREADS PARA CONTAGEM
