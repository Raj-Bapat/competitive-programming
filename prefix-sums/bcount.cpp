#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <fstream>
using namespace std;

struct breednode {
    int h,g,j;
};

struct interval {
    int start,end;
};

int line[100001];
breednode runningTotal[100001];
interval q[100001];

int N,Q;


int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("bcount.in");
    fout.open("bcount.out");
    fin >> N;
    fin >> Q;
    line[0] = 0;
    for (int i = 1; i<=N; i++) {
        fin >> line[i];
    }
    runningTotal[0].h = 0;
    runningTotal[0].g = 0;
    runningTotal[0].j = 0;
    for (int i = 1; i<=N; i++) {
        runningTotal[i] = runningTotal[i-1];
        if (line[i] == 1) {
            runningTotal[i].h++;
        } else if (line[i]==2) {
            runningTotal[i].g++;
        } else if (line[i]==3) {
            runningTotal[i].j++;
        }
    }
    for (int i = 0; i<Q; i++) {
        fin >> q[i].start;
        fin >> q[i].end;
    }
    for (int i = 0; i<Q; i++) {
        int start = q[i].start;
        int end = q[i].end;
        fout << runningTotal[end].h-runningTotal[start-1].h << " ";
        fout << runningTotal[end].g-runningTotal[start-1].g << " ";
        fout << runningTotal[end].j-runningTotal[start-1].j << endl;
    }
    return 0;
}
