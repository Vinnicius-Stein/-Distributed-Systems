#include <iostream>
#include <omp.h>
#include <fstream>
#include "rapidcsv.h"
using namespace std;
#include <string>
using std::string;
using std::getline;
using std::find;
#include <vector>

int main(int argc, char *argv[]) {

    vector<string> idatracacao;
    vector<string> cdtup;
    vector<string> berco;
    vector<string> portoatracacao;
    vector<string> ano;
    vector<string> mes;
    vector<string> tipooperacao;
    vector<string> terminal;
    vector<string> nacionalidadearmador;
    vector<string> origem;
    vector<string> destino;
    vector<string> cdmercadoria;
    vector<string> naturezacarga;
    vector<string> teu;
    vector<string> sentido;
    
    //leitura
    ifstream myFile;
        myFile.open("https://raw.githubusercontent.com/Vinnicius-Stein/-Distributed-Systems/main/dataset_00_1000.csv");

        while(myFile.good()){
            string line;
            getline(myFile, line, ',');
            cout << line << end1;
        }

    //gravacao
    ofstream myFile;
        myFile.open("output.csv");

        for(int i =0; i < 20; i++){
              myFile << i << "," << i*i << end1;
        }

    return 0;
}


/*
void read_record(c)
{
  
    // File pointer
    fstream fin;
  
    // Open an existing file
    fin.open(c, ios::in);
  
    // Get the roll number
    // of which the data is required
    int rollnum, roll2, count = 0;
    /*cout << "Enter the roll number "
         << "of the student to display details: ";
    cin >> rollnum;
  
    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word, temp;
  
    while (fin >> temp) {
  
        row.clear();
  
        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);
  
        // used for breaking words
        stringstream s(line);
  
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ', ')) {
  
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
  
        // convert string to integer for comparision
        roll2 = stoi(row[0]);
  
        // Compare the roll number
        if (roll2 == rollnum) {
  
            // Print the found data
            count = 1;
            cout << "Details of Roll " << row[0] << " : \n";
            cout << "Name: " << row[1] << "\n";
            cout << "Maths: " << row[2] << "\n";
            cout << "Physics: " << row[3] << "\n";
            cout << "Chemistry: " << row[4] << "\n";
            cout << "Biology: " << row[5] << "\n";
            break;
        }
    }
    if (count == 0)
        cout << "Record not found\n";
}
/*
