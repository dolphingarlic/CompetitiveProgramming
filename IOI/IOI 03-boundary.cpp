#include <bits/stdc++.h>
#define x first
#define y second
typedef long long ll;
using namespace std;

const double PI = 4 * atan(1);

struct Event {
	short type, id;
	pair<ll, ll> loc;
};

pair<ll, ll> origin, polygon[22];

// Cross product
ll cross(pair<ll, ll> a, pair<ll, ll> b) {
	return (a.y - origin.y) * (b.x - origin.x) - (a.x - origin.x) * (b.y - origin.y);
}

// Which half of the plane some point lies in
int half(pair<ll, ll> p) {
	if (p.x != origin.x) return (p.x < origin.x) - (p.x > origin.x);
	return (p.y < origin.y) - (p.y > origin.y);
}

// Custom comparator to sort by bearing
bool operator<(Event a, Event b) {
	int ah = half(a.loc), bh = half(b.loc);
	if (ah == bh) {
		ll c = cross(a.loc, b.loc);
		if (c == 0) return a.type > b.type;
		return c > 0;
	}
	return ah < bh;
}

// Generates the next fence post in clockwise order
Event get_next_post(Event curr, int n) {
	if (curr.loc.x == n) {
		if (curr.loc.y) return {0, 0, {n, curr.loc.y - 1}};
		return {0, 0, {n - 1, 0}};
	} else if (!curr.loc.x) {
		if (curr.loc.y != n) return {0, 0, {0, curr.loc.y + 1}};
		return {0, 0, {1, n}};
	} else if (curr.loc.y == n) {
		if (curr.loc.x != n) return {0, 0, {curr.loc.x + 1, n}};
		return {0, 0, {n, n - 1}};
	} else {
		if (curr.loc.x) return {0, 0, {curr.loc.x - 1, 0}};
		return {0, 0, {0, 1}};
	}
}

vector<Event> events;
bool before[44444];

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, r;
	cin >> n >> r >> origin.x >> origin.y;

	for (int i = 0; i < r; i++) {
		int m;
		cin >> m;
		for (int j = 0; j < m; j++) cin >> polygon[j].x >> polygon[j].y;
		// Sort the polygon's vertices to find the 2 "tangents" from the origin
		sort(polygon, polygon + m, [](pair<ll, ll> a, pair<ll, ll> b) {
			return cross(a, b) > 0;
		});
		events.push_back({1, i, polygon[0]});
		events.push_back({-1, i, polygon[m - 1]});
	}
	sort(events.begin(), events.end());

	int active = 0;
	// Do an initial sweep to handle rocks containing the ray with bearing 0
	// This way, `active` won't be messed up
	for (Event i : events) {
		if (i.type == 1) before[i.id] = true;
		if (i.type == -1 && !before[i.id]) active++;
	}

	int ans = 0, ptr = 0;
	Event curr_post = {0, 0, {origin.x, n}};
	for (Event i : events) {
		while (ptr != 4 * n && curr_post < i) {
			// If there are no rocks that our current ray intersects...
			if (!active) ans++;
			ptr++;
			curr_post = get_next_post(curr_post, n);
		}

		if (i.type == 1) active++;
		else active--;
	}
	if (!active) ans += 4 * n - ptr;

	cout << ans;
	return 0;
}
