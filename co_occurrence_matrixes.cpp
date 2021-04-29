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
#include <chrono>
using namespace std::chrono;


/*  Insere elementos unicos do dataset no 'data' e insere no vetor de contagem 'cont', e/ou retorna o id respectivo do elemento
    data -> vector de strings dos valores da coluna X colunas unicos
    token -> elemento a ser inseridp
    k -> contador da linha respectiva (coluna do dataset > elemento)
    cont -> vetor de contador
*/



 long long int insertUnique (vector<vector<string> > &data, string token, int k, vector<vector<int> > &cont) {


    long long int i;


    #pragma openmp parallel
    {
        for(i = 0; i < data[k].size(); i++) {
            if ((data[k][i].compare(token) == 0)) {
                #pragma omp atomic update
                cont[k][i] += 1;

                return i;
            }
        }

        #pragma omp critical
        {
            data[k].push_back(token); // Nao encontrou nenhum valor igual ao token
            cont[k].push_back(1);
        }
    }
    return i;

}


/*  Imprime as matrizes de co-ocorrencia de cada coluna
    data -> vector de strings dos valores da coluna X colunas unicos
    header -> cabeçalho do dataset
    cont -> vector de contador
    n -> numero de colunas
*/


void printOcurrenceMatrix (vector<vector<string> > data, vector<string> header, vector<vector<int> > cont, int n) {

    string outputFile;

    for (int i = 0; i < n; i++){
            outputFile = header[i] + ".csv";
            ofstream fout (outputFile.c_str());
            fout << "index," << header[i] << ",ocorrencia" << endl;

            for (int j = 0; j < data[i].size() ; j++) {
                    fout << j << ",";
                    fout << data[i][j] << ",";
                    fout << cont[i][j] << endl;
            }
    }

}


int main(int argc, char *argv[]) {

    ifstream database;
    ofstream ffout ("CodeMatrix.csv");
    string filename;


    cout << "Informe o nome do dataset (com extensao): ";
    getline(cin, filename);
    cout << endl;
    auto start = high_resolution_clock::now();

    database.open(filename.c_str());
    if (!database.is_open())
    {
        cout << "Nao foi possivel abrir o arquivo!";
        std::exit(EXIT_FAILURE);
    }


    string str;

    getline(database, str);
    vector<string> header;
    string head;
    std::istringstream h(str);
    int n = 0; //contador de quantidade de elementos no header (ou colunas)


    cout << "Indentificando colunas do dataset..." << endl;
    while (getline(h, head, ','))
        {
            n++;
            header.push_back(head);
        }

    ffout << str << endl; // Insere o header no arquivo de codificacao

    // Criacao dos vectors para armazenar valores unicos

    cout << "Colunas identificadas, processando entradas..." << endl;
    vector<vector<string> > data(n);
    vector<vector<int> > cont(n);


    int k = 0;
    cout << "Imprimindo matrizes de codificacao das colunas!" << endl;
    while (getline(database, str))
    {
        std::istringstream iss(str);
        string token;

        while (getline(iss, token, ','))
        {
            ffout << insertUnique(data, token, k, cont) << ";";
            k++;
        }
        ffout << endl;
        k = 0;
    }
    cout << "Terminada a matriz de codificacao!" << endl;
    cout << "Imprimindo matrizes de co-ocorrencia das colunas!" << endl;
    printOcurrenceMatrix(data, header, cont, n);
    cout << "Terminada a impressao!" << endl;


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Tempo total: " << duration.count() << "ms" << endl;

    return 0;
}
