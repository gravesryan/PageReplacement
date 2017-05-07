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
void clockReplacement(vector<vector<int>> & table, int idx, int ppn);

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
        
        int indexBits = log2(numBytes);
        cout << "idx bits: " << indexBits << endl;
        int idx = va;
        idx = idx >> (virtAddrBits - indexBits); // right shift to get index
        int ppn = 0, offset = 0;
        if (idx < table.size() && table[idx][0] == 0) { // if bit is invalid
            if (table[idx][1] == 1) { // check permission bit
#ifdef PROB1
                cout << "DISK" << endl;
#else
                cout << "PAGE FAULT" << endl;
                clockReplacement(table, clockIdx, table[idx][2]);
                cout << table[clockIdx][2] << endl;
                clockIdx = (clockIdx + 1) % table.size();
#endif
            }
            else
                cout << "SEGFAULT" << endl; // no permission
        }
        else if (idx < table.size()) { // if valid == true and index is in table
            ppn = table[idx][2];    // get phys page num
            offset = va - idx;      // get offset
            cout << (ppn + offset) << endl; // physical address
        }
        else {
            cout << "Index not in page table" << endl;
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
    cout << "idx" << '\t' << "valid" << '\t' << "per" << '\t' << "ppn" << '\t' << "use" << endl;
    for (int i = 0; i < pageTable.size() - 1; i++) {
        cout << i << '\t';
        for (int j = 0; j < pageTable[i].size(); j++) {
            cout << pageTable[i][j] << '\t';
        }
        cout << endl;
    }
}

void clockReplacement(vector<vector<int>> & table, int idx, int ppn) {
//    table[idx][0] = 1;
//    table[idx][1] = 1;
//    table[idx][2] = ppn;
    
    return;
}
