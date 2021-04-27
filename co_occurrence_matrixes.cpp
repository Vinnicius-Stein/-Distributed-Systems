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


void insertUnique (vector<vector<string> > &data, string token, int k, vector<vector<int> > &cont) {

    int i = 0;

    for(i = 0; i < data[k].size(); i++) {
        if ((data[k][i].compare(token) == 0)) {
                cont[k][i] += 1;
                return;
            }
    }
    data[k].push_back(token); // Nao encontrou nenhum valor igual ao token
    cont[k].push_back(1);
}



/*  Imprime as matrizes de co-ocorrencia de cada coluna
    data -> vector de elementos unicos
    header -> cabeçalho do dataset
    cont -> vector de contador
    n -> numero de colunas
*/


void printOcurrenceMatrix (vector<vector<string> > data, vector<string> header, vector< vector<int> > cont, int n) {

    string outputFile;
    for (int i = 0; i < n; i++){
            outputFile = header[i] + ".csv";
            std::ofstream fout (outputFile.c_str());
            fout << "index," << header[i] << ",ocorrencia" << endl;

            for (int j = 0; j < data[i].size() ; j++) { // print all string in first vector of 'arr'

                fout << j << ","; //index
                fout << data[i][j] << ",";
                fout << cont[i][j] << endl;
            }
    }
    cout << "Terminada a impressao!" << endl;

    idMatrixes(vector<vector<string> > data, vector<string> header, int n)
}

void idMatrixes(vector<vector<string> > data, vector<string> header, int n) {

    string outputFile;
    for(int i = 0 ; i < n ; i++){
        outputFile = header[i] + ".csv";
        std::ofstream fout(outputFile.c_str());
        fout << ""
    }
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
    int n = 0; //contador de quantidade de headers (ou colunas)


    cout << "Indentificando colunas do dataset..." << endl;
    while (getline(h, head, ','))
        {
            n++;
            header.push_back(head);
        }

    // Criacao dos vectors para armazenar valores unicos

    cout << "Colunas identificadas, processando entradas..." << endl;
    vector<vector<string> > data(n);
    vector<vector<int> > cont(n);


    while (getline(database, str))
    {
        std::istringstream iss(str);
        string token;

        while (getline(iss, token, ','))
        {
            insertUnique(data, token, k, cont);
            k++;
        }
        k = 0;
    }

    cout << "Imprimindo matrizes de co-ocorrencia das colunas!" << endl;

    printOcurrenceMatrix(data, header, cont, n);



    return 0;
}

/**TO DO
    Substituição dos valores em arquivo (em arquivo novo)
 */
