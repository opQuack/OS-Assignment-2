```
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class cust{
  public: 
    string id;
    float cols[2];
};

void bin_by_mean(vector<cust>& data, int c){
  int i, j;
  float avg;
  for(i=0; i<100;){
    avg = 0;
    for(j=i; j<i+5 and j<100; j++){
      avg += data[j].cols[c];
    }
    avg /= 5;
    while(i<j){
      data[i].cols[c] = avg;
      i++;
    }
  }
}

// data extraction
vector<cust> read_records(){
  fstream fin;
  int i=0, j;
  vector<cust> data;
  cust t;
  fin.open("data.csv", ios::in);
  vector<string> row;
  string word, temp;
  
  // header 
  getline(fin, temp);

  while (fin >> temp) {
      j=0;
      if(i==100) break;
      row.clear();
      stringstream s(temp);
      while (getline(s, word, ',')) {
          if(j==0) t.id = word;
          if(j==1) t.cols[0] = stof(word);
          if(j==3) t.cols[1] = stof(word);
          if(j==4) break;
          j++;
      }
      data.push_back(t);
      i++;
    }
  return data;
}

int main(){
  
  // extract data
  vector<cust> data = read_records();
  
  // sort on basis of balance.
  sort(data.begin(), data.end(), [](cust a, cust b){
    return a.cols[0] < b.cols[0];
  });

  bin_by_mean(data,0);
  // sort on basis of balance.
  sort(data.begin(), data.end(), [](cust a, cust b){
    return a.cols[1] < b.cols[1];
  });
  bin_by_mean(data,1);
  
  for(int i=0; i<100; i++){
    cout << data[i].id << " " << data[i].cols[0] << " " << data[i].cols[1] << endl;
  }
  return 0;
}
```
