#include "grader.h"
#include "cluedo.h"
#include <vector>

void Solve() {
   std::vector<int> suspect = {0, 1, 1, 1};
   while (true) {
      int r = Theory(suspect[1], suspect[2], suspect[3]);
      if (r == 0) return;
      else suspect[r]++;
   }
}
