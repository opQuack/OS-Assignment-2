```
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

// Structure of the transaction data to be read
class Transaction {
  public: 
    string id;
    bool items[3];
    Transaction (string _id, string _a, string _b, string _c) {
      id = _id;
      items[0] = _a == "1" ? true : false;
      items[1] = _b == "1" ? true : false;
      items[2] = _c == "1" ? true : false;
    }
};
unordered_map<string, pair<int, int>> map;
vector<string> frequent;
int min_sup = 0;

// function to read data
vector<Transaction> read_data(){
  int i;
  string word, temp, _id, _a, _b, _c;
  vector<Transaction> transactions;
  fstream fin;

  fin.open("transactions.csv", ios::in);

  // transactions file not found.
  if(!fin.is_open()) {
    cout << "Transactions file not found.\n";
    return {};
  }

  // getting rid of the title row.
  getline(fin, temp);

  while(fin >> temp) {
    stringstream s(temp);
    int j = 0;
    while (getline(s, word, ',')) {
      if(j==0) _id = word;
      if(j==1) _a = word;
      if(j==2) _b = word;
      if(j==3) _c = word;
      j++;
    }
    j = 0;
    Transaction t(_id, _a, _b, _c);
    transactions.push_back(t);
  }

  return transactions;
}

bool isItemPresent(string str, Transaction t) {
  for(const char& c: str) {
    if(!t.items[c-'A']) return false;
  }
  return true;
}

void DICHelper(vector<Transaction>& transactions, string str, int start) {
  int i, n = transactions.size(), j;
  i = start%n;
  // loop is broken only if:
  //    1. all transactions have been visited
  //    2. its a frequent itemset
  for(; map[str].second < n; ){
    // itemset exists in transaction[i]
    if(isItemPresent(str, transactions[i])) {
      map[str].first++;
      // this item is frequent
      if(map[str].first>=min_sup){
        frequent.push_back(str);
        j = str[str.length()-1]-'A'+1;
        for(;j<2;j++){
          string temp = str + (char)('A'+j);
          DICHelper(transactions, temp, i+1);
        }
        break;
      }
    }
    // increment the number of transactions accessed.
    map[str].second++;
    i = (i+1)%n;
  }
}

void DICAlgorithm(vector<Transaction>& transactions) {
  string cur_trans = "";
  for(int i=0; i<3; i++) {
    string temp = cur_trans + (char)('A'+i);
    DICHelper(transactions, temp, 0);
  }
}


int main() {
  cout << "Reading transactions...\n";
  // Read transactions from the csv file
  vector<Transaction> transactions = read_data();

  // Check for empty datset
  if(transactions.size()==0) return 0;

  // Calculate the min. support
  min_sup = ((float)transactions.size()*0.25);

  // calling the DIC Algorithm
  cout << "Running DIC Algorithm...\n";
  DICAlgorithm(transactions);

  // printing the frequent transactions.
  ofstream output_file;
  output_file.open("output.txt");

  cout << "Writing to output file...\n";
  output_file << "Frequent Itemsets:\n";
  
  for(const string& f: frequent) {
    output_file << f << "\t";
  }

  cout << "\n\n\n";
  return 0;
}
```
