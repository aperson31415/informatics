#include "beam.h"
 
void findCoins(int a, int b, int count) {
    if (count == 0) return;
 
    if (a == b) {
        collect(a);
        return;
    }
 
    int mid = a + (b - a) / 2;
    
    int leftCount = shine(a, mid);
    
    // Left
    if (leftCount > 0) {
        findCoins(a, mid, leftCount);
    }
    
    // Right
    int rightCount = count - leftCount;
    if (rightCount > 0) {
        findCoins(mid + 1, b, rightCount);
    }
}
 
void init() {
    int n = machineWidth();
    // Initial query to get the total number of coins
    int totalCoins = shine(1, n);
    if (totalCoins > 0) {
        findCoins(1, n, totalCoins);
    }
}