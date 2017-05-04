// Eli Simmonds
// Homework 4
// CS450

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

vector< vector<int> > buildPageTable(const char * fname);
void printPageTable(vector< vector<int> > pageTable);
int clockReplacement(& vector<vector<int>> table, int idx, int ppn);

int virtAddrBits, physAddrBits, numBytes;

int main (int argc, const char * argv []) {
    vector< vector<int> > table = buildPageTable(argv[1]);
    printPageTable(table);
    int clockIdx = 0;
    
    string virtualAddress = "";
    int va = 0;
    while (getline(cin, virtualAddress)) {
        bool isHex = false;
        
        if (virtualAddress[1] == 'x')
            isHex = true;
        
        if (!isHex)
            va = stoi(virtualAddress, nullptr, 10);
        else
            va = stoi(virtualAddress, nullptr, 16);
        
        int bits = log2(table.size());
        int idx = va;
        idx >> (virtAddrBits - bits);
        int ppn = 0;
        int offset = 0;
        //cout << idx << endl;
        if (table[idx][0] == 0) {
            if (table[idx][1] == 1) {
#ifdef PROB1
                cout << "DISK" << endl;
#else
                cout << "PAGE FAULT" << endl;
                clockIdx = clockReplacement(table, clockIdx,)
                cout << table[clockIdx][2] << endl;
                clockIdx = (clockIdx + 1) % table.size();
            }
            else
                cout << "SEGFAULT" << endl;
        }
        else {
            ppn = table[idx][2];
            idx << (virtAddrBits - bits);
            offset = va - idx;
            ppn << (virtAddrBits - bits);
            cout << (ppn + offset) << endl;
        }
        
    }
    
    
    
    return 0;
}

vector< vector<int> > buildPageTable(const char * fname) {
    ifstream in(fname);
    virtAddrBits, physAddrBits, numBytes = 0;
    in >> virtAddrBits >> physAddrBits >> numBytes;
    int valid, permission, physPageNum, useBit = 0;
    vector< vector<int> > pgTable;
    
    while (!in.eof()) {
        in >> valid >> permission >> physPageNum >> useBit;
        vector<int> pgLine;
        pgLine.push_back(valid);
        pgLine.push_back(permission);
        pgLine.push_back(physPageNum);
        pgLine.push_back(useBit);
        
        pgTable.push_back(pgLine);
    }
    return pgTable;
}

void printPageTable(vector< vector<int> > pageTable) {
    for (int i = 0; i < pageTable.size() - 1; i++) {
        for (int j = 0; j < pageTable[i].size(); j++) {
            cout << pageTable[i][j] << " ";
        }
        cout << endl;
    }
}

void clockReplacement(& vector<vector<int>> table, int idx, int ppn) {
    table[idx][0] = 1;
    table[idx][1] = 1;
    table[idx][2] = ppn;
    
    return;
}
