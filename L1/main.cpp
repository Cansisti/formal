#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Matcher {
	public:
		Matcher(string text, string pattern) :
			text(text),
			pattern(pattern)
		{}
		virtual int find_next() = 0;
	protected:
		const string text;
		const string pattern;
};

class FiniteAutomataMatcher: public Matcher {
	public:
		FiniteAutomataMatcher(string text, string pattern, string alphabet) :
			Matcher(text, pattern),
			alphabet(alphabet),
			n(text.size()),
			m(pattern.size())
		{
			for(int q = 0; q <= m; q++) {
				for(char a: alphabet) {
					int k = min(m + 1, q + 2);
					do k--; while(!ends_with(pattern.substr(0, q) + a, pattern.substr(0, k)));
					delta[q][a] = k;
				}
			}
		}

		int q = 0;
		int i = 0;

		virtual int find_next() override {
			for(; i < n; i++) {
				q = delta[q][text.at(i)];
				if(q == m) {
					return i - m + 1;
				}
			}
			return -1;
		}
	private:
		const string alphabet;
		map<int, map<char, int>> delta;

		const int n, m;

		bool ends_with(string const & value, string const & ending) const {
			if(ending.size() > value.size()) return false;
			return equal(ending.rbegin(), ending.rend(), value.rbegin());
		}
};

class KMPMatcher: public Matcher {
	public:
		KMPMatcher(string text, string pattern) :
			Matcher(text, pattern),
			n(text.size()),
			m(pattern.size())
		{
			pi[0] = 0;
			pi[1] = 0;
			int k = 0;
			for(int q = 2; q <= m; q++) {
				while(k > 0 and pattern.at(k) != pattern.at(q-1)) k = pi[k];
				if(pattern.at(k) == pattern.at(q-1)) k++;
				pi[q] = k;
			}
		}

		int q = 0;
		int i = 0;

		virtual int find_next() override {
			for(; i < n; i++) {
				while(q > 0 and pattern.at(q) != text.at(i)) q = pi[q];
				if(pattern.at(q) == text.at(i)) q++;
				if(q == m) {
					q = pi[q];
					return i - m + 1;
				}
			}
			return -1;
		}

	private:
		map<int, int> pi;
		const int n, m;
};

int main(int argc, char ** argv) {

	auto usage = [&]() {
		cout << argv[0] << " fa|kmp text pattern [alphabet]" << endl;
	};

	if(argc < 4) {
		usage();
		return 1;
	}

	string mode = argv[1];
	string text = argv[2];
	string pattern = argv[3];
	string alphabet = argc >= 5 ? argv[4] : "";

	Matcher* matcher = nullptr;
	if(mode == "fa") {
		matcher = new FiniteAutomataMatcher(text, pattern, alphabet);
		if(alphabet.size() == 0) cout << "warning: no alphabet" << endl;
	}
	else if(mode == "kmp") matcher = new KMPMatcher(text, pattern);
	else {
		usage();
		return 1;
	}

	for(int p = matcher->find_next(); p != -1; p = matcher->find_next()) {
		cout << p << " ";
	}
	cout << endl;

	return 0;
}