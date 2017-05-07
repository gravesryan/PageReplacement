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
int clockReplacement(vector<vector<int>> & table, int idx, int ppn);
void replaceIndex(vector<vector<int>> & table, int idx, int ppn);

int virtAddrBits, physAddrBits, numBytes;

int main (int argc, const char * argv []) {
    // build page table
    vector< vector<int> > table = buildPageTable(argv[1]);
    printPageTable(table); // print formatted page table
    
    // create vars needed
    int clockIdx = 0, va = 0;
    string virtualAddress = "";
    
    while (getline(cin, virtualAddress)) {
        
        if (virtualAddress[1] == 'x')   // input is hex
            va = stoi(virtualAddress, nullptr, 16);
        else if (virtualAddress == "") { continue; } // catch input error
        else    // input is decimal
            va = stoi(virtualAddress, nullptr, 10);
        
        int indexBits = log2(numBytes); // get num of index bits
        int idx = va >> (virtAddrBits - indexBits); // right shift to get index
        cout << "index: " << idx << endl;
        int ppn = 0, offset = 0;
        if (idx < table.size() && table[idx][0] == 0) { // if bit is invalid
            if (table[idx][1] == 1) { // check permission bit
#ifdef PROB1
                cout << "DISK" << endl;
#else
                cout << "PAGE FAULT" << endl;
                clockIdx = clockReplacement(table, clockIdx, table[idx][2]);
                cout << table[clockIdx][2] << endl;
//                clockIdx = (clockIdx + 1) % table.size();
#endif
            }
            else
                cout << "SEGFAULT" << endl; // no permission
        }
        else if (idx < table.size()) { // if valid == true
            ppn = table[idx][2];    // get phys page num
            table[idx][3] = 1;
            offset = va - idx;      // get offset
            cout << (ppn + offset) << endl; // physical address
        }
        printPageTable(table);
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

int clockReplacement(vector<vector<int>> & table, int idx, int ppn) {
    cout << endl << "clockReplacement called with index " << idx << endl;
    int i;
    for (i = idx; i < table.size(); i++) {
        if (table[i][3] == 0) {
            cout << "Found use bit zero at idx " << idx << endl;
            replaceIndex(table, i, ppn);
            return i;
        }
        else {
            cout << "Setting index " << i << " use bit to 0" << endl;
            table[i][3] = 0;
        }
    }
    table[i][3] = 0;
    replaceIndex(table, 0, ppn);
    return 0;
}

void replaceIndex(vector<vector<int>> & table, int idx, int ppn) {
    table[idx][0] = 1;
    table[idx][1] = 1;
//    table[idx][2] = ppn;
    table[idx][3] = 1;
    
    cout << "replacing idx " << idx << endl;
}
