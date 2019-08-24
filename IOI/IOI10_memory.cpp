#include <vector>
#include "grader.h"
#include "memory.h"

bool visited[25];
std::vector<int> pos[25];

void play() {
   int i;
   char a, b;
   for (int i = 1; i <= 25; i++) {
      a = faceup(2 * i - 1);
      b = faceup(2 * i);
      if (a == b) visited[a - 'A'] = true;
      else {
         pos[a - 'A'].push_back(2 * i - 1);
         pos[b - 'A'].push_back(2 * i);
      }
   }
   for (int i = 0; i < 25; i++) if (!visited[i]) {
      a = faceup(pos[i][0]);
      b = faceup(pos[i][1]);
   }
}
