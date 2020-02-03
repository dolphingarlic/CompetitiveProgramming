#include "device.h"
#include <vector>
#include <stdlib.h>

std::vector<int> minmax;

int quickselect(int pos, std::vector<int> candidates) {
	if (candidates.size() == 1) return candidates[0];
	
	int pivot = candidates[rand() % candidates.size()];
	std::vector<int> l, g;
	l.push_back(pivot);
	for (int i : candidates) {
	    if (i == pivot) continue;
		if (Med3(minmax[0], i, pivot) == pivot) g.push_back(i);
		else l.push_back(i);
	}
	
	if (l.size() >= pos) return quickselect(pos, l);
	else return quickselect(pos - l.size(), g);
}

int Median(int N) {
    for (int i = 1; i <= N; i++) {
    	minmax.push_back(i);
    	while (minmax.size() > 2) {
    		int med = Med3(minmax[0], minmax[1], minmax[2]);
    		if (med == minmax[0]) minmax.erase(minmax.begin());
    		else if (med == minmax[1]) minmax.erase(minmax.begin() + 1);
    		else minmax.erase(minmax.begin() + 2);
    	}
    }
    
    std::vector<int> candidates;
    for (int i = 1; i <= N; i++) if (i != minmax[0] && i != minmax[1])
    	candidates.push_back(i);
    
    return quickselect(N / 2, candidates);
}