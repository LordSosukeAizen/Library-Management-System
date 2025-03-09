#include <bits/stdc++.h>
#include <ctime>
#include <chrono>


using namespace std;

vector<string> Read_From_File(const string &filename){ 
    vector<string> lines;
    ifstream data(filename);
    // data.open(filename);
    if(!data.is_open()){
        cerr<<"File \'"<<filename<<"\' could not be read.\n";
    }
    string temp_line;
    while(data){
        getline(data,temp_line);
        lines.push_back(temp_line);
    }
    data.close();
    return lines;
}


vector<int> create_list(string s) {
    vector<int> list;
    stringstream ss(s);
    string word;
    try {
    while (ss >> word) {
        list.push_back(stoi(word));
    }
    return list;
}catch(...) {
    cout << "Invalid conversion of string to int in create list\n";
}
}


