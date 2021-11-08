```
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

float min_sup = 0.2;
unordered_set<string> partition_frequent;
unordered_set<string> final_frequent;

// Structure of the transaction data to be read
class Transaction {
  public: 
    string id;
    bool items[5];
    Transaction (string _id, string _a, string _b, string _c, string _d, string _e) {
      id = _id;
      items[0] = _a == "1" ? true : false;
      items[1] = _b == "1" ? true : false;
      items[2] = _c == "1" ? true : false;
      items[3] = _d == "1" ? true : false;
      items[4] = _e == "1" ? true : false;
    }
};

vector<Transaction> read_data();
void second_scan(vector<Transaction>& transactions);
int count_freq(vector<Transaction>& transactions, string str);
void apriori(vector<Transaction>& transactions);


int main() {
  vector<Transaction> transactions = read_data();
  second_scan(transactions);

  for(const auto& freq: final_frequent) {
    cout << freq << endl;
  }

  return 0;
} 

void second_scan(vector<Transaction>& transactions) {
  int i, n = transactions.size();
  
  for(const auto& freq: partition_frequent) {
    int count = count_freq(transactions, freq);
    if(count >= min_sup*n)
      final_frequent.insert(freq);
  }
}

void apriori(vector<Transaction>& transactions) {
  int i, n = transactions.size();
  queue<string> partition;
  string str = "";
  partition.push("");
  
  while(!partition.empty()) {
    string freq = partition.front(); partition.pop();

    i = freq==""? 0: (freq[freq.length()-1]-'A'+1);

    for(; i<5; i++) {
      str = freq + (char)('A'+i);
      if(partition_frequent.find(str)!=partition_frequent.end())
        continue;
      int count = count_freq(transactions, str);
      // the item set is frequent in partition
      if(count >= min_sup*n) {
        partition.push(str);
        partition_frequent.insert(str);
      }
    }
  }
}

// returns count of frequency
int count_freq(vector<Transaction>& transactions, string str) {
  int i, n = transactions.size(), count = 0;
  bool present;
  for(i=0;i<n; i++) {
    present = true;
    for(const char& c: str) {
      if(!transactions[i].items[c-'A']){
        present = false;
        break;
      }
    }
    if(present) count++;
  }
  return count;
}

// function to read data
vector<Transaction> read_data(){
  int i;
  string word, temp, _id, _a, _b, _c, _d, _e;
  vector<Transaction> transactions, transactions_copy;
  fstream fin;

  fin.open("transactions.csv", ios::in);

  // transactions file not found.
  if(!fin.is_open()) {
    cout << "Transactions file not found.\n";
    return {};
  }

  // getting rid of the title row.
  getline(fin, temp);

  i = 0;
  while(fin >> temp) {
    stringstream s(temp);
    int j = 0;
    while (getline(s, word, ',')) {
      if(j==0) _id = word;
      if(j==1) _a = word;
      if(j==2) _b = word;
      if(j==3) _c = word;
      if(j==4) _d = word;
      if(j==5) _e = word;
      j++;
    }
    j = 0;
    Transaction t(_id, _a, _b, _c, _d, _e);
    i++;
    transactions_copy.push_back(t);
    if(i%5==0) {
      apriori(transactions_copy);
      transactions_copy.clear();
    }
    transactions.push_back(t);
  }

  return transactions;
}
```
