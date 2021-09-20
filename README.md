```
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

// strcuture to store file data
class cust{
  public:
    string id;
    float cols[2];
};

// sorting algorithms
struct sort_balance{
    inline bool operator()(const cust& a, const cust& b){
        return a.cols[0] < b.cols[0];
    }
};
struct sort_purchases{
    inline bool operator()(const cust& a, const cust& b){
        return a.cols[1] < b.cols[1];
    }
};
struct sort_ids{
    inline bool operator()(const cust& a, const cust& b){
        return a.id < b.id;
    }
};

// binning by mean function
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

// binning by mean function
void bin_by_boundaries(vector<cust>& data, int c){
  int i, j, k, mid;
  for(i=0; i<100;){
      k = i;
      j = i+5>99?99:i+5;
      mid = k + (j-k)/2;
      while(i<=j){
          if(i<mid) data[i].cols[c] = data[k].cols[c];
          else data[i].cols[c] = data[j].cols[c];
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
  fin.open("raw_data.csv", ios::in);
  vector<string> row;
  string word, temp;
  
  // getting rid of the header row
  getline(fin, temp);

  while (fin >> temp) {
      j=0;
      if(i==100) break;
      row.clear();
      stringstream s(temp);
      while (getline(s, word, ',')) {
          // handling the empty NULL values.
          if(word=="NULL") word = "-1";
          
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

void print(vector<cust>& data){
    sort(data.begin(), data.end(), sort_ids());
    for(int i=0; i<100; i++){
      cout << data[i].id << " " << data[i].cols[0] << " " << data[i].cols[1] << endl;
    }
}

int main(){
    // extract data
    vector<cust> data = read_records();
    vector<cust> data_mean = data;

   // sort on basis of balance.
   sort(data_mean.begin(), data_mean.end(), sort_balance());
   bin_by_mean(data_mean,0);

   // sort on basis of purchases.
     sort(data_mean.begin(), data_mean.end(), sort_purchases());
     bin_by_mean(data_mean,1);

   // printing after binning using mean
   cout << "\n\nResult after binning by mean: \n\n";
   print(data_mean);

   // sort on basis of balance.
   sort(data.begin(), data.end(), sort_balance());
   bin_by_boundaries(data,0);

   // sort on basis of purchases.
   sort(data.begin(), data.end(), sort_purchases());
   bin_by_boundaries(data,1);

   // printing after binning using boundaries
   cout << "\n\nResult after binning by boundaries: \n\n";
   print(data);
    
    return 0;
}
```
