#include <string>
#include <vector>

#define MAX_MAP_SIZE 100000

using namespace std;

typedef struct slot{
    string key;
    int value;
} Slot; 

vector<Slot> map[MAX_MAP_SIZE];

int Hash(string key){
    int idx = 0;
    
    for (int i=0; i < key.length(); i++){
        idx += key[i] * (i+1);
        idx %= MAX_MAP_SIZE;
    }
    
    return idx;
}

vector<Slot>::iterator SearchOnChainWithKey(int idx, string key){
    if (map[idx].size() == 0)
        return map[idx].end();
    
    vector<Slot>::iterator iter;
    for (iter = map[idx].begin(); iter != map[idx].end(); iter++){
        if (iter->key == key)
            break;
    }
    
    return iter;
}

void Insert(string key, int value){
    int idx = Hash(key);
    
    Slot slot = { key, value };
    
    vector<Slot>::iterator iter = SearchOnChainWithKey(idx, key);
    
    if (iter == map[idx].end()){
        map[idx].push_back(slot);
    }
    else{
    	iter->value = value;
	}
}

void Delete(string key){
    int idx = Hash(key);
    
    vector<Slot>::iterator iter = SearchOnChainWithKey(idx, key);
    
    if (iter == map[idx].end())
        return;
    
    map[idx].erase(iter);
}

int GetValue(string key){
    int idx = Hash(key);
    
    vector<Slot>::iterator iter = SearchOnChainWithKey(idx, key);
    
    if (iter == map[idx].end())
        return 2000000000; // infinity
    
    return iter->value;
}

void PrintMap(){
    vector<Slot>::iterator iter;
    
    for (int i=0; i < MAX_MAP_SIZE; i++){
        for (iter = map[i].begin(); iter != map[i].end(); iter++){
            cout << iter->key << '/' << iter->value << "->";
        }
        
        cout << '\n';
    }
}
