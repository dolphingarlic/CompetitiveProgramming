#include <iostream>
using namespace std;
 
int cnt[26];
 
int main() {
	string s;
	cin >> s;
	for (char i : s) cnt[i - 'A']++;
	
	string res = "";
	char odd = '.';
	for (int i = 0; i < 26; i++) {
		if (cnt[i] & 1) {
			if (odd == '.') odd = i + 'A';
			else return cout << "NO SOLUTION", 0;
		}
		
		for (int j = 0; j < cnt[i] / 2; j++) res += i + 'A';
	}
	
	if (odd != '.') res += odd;
	for (int i = 25; ~i; i--) {
		for (int j = 0; j < cnt[i] / 2; j++) res += i + 'A';
	}
	
	cout << res;
	return 0;
}