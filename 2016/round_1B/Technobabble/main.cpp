#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <string>

#if 0
 AA BB
 AA DD
 CC DD
 CC BB <-
-------
 AA BB
 CC DD
 AA DD <-
 CC BB <-
-------
 AA DD
 CC BB
 AA BB <-
 CC DD <-


 AA BB
 AA DD
 CC BB
 CC DD

 AA BB
 AA DD
 CC BB
-------
 X0 Y0
 X1 Y1
 X2 Y2

 X0 Y1
 X1 Y2

 X1 Y0
-------> 3
 X0 Y1
 X1 Y2

 X0 Y0
 X1 Y1 <-
 X2 Y2
 X1 Y0 <-
-------> 3 !!

 X0 Y1
 X0 Y0
 X1 Y2
 X1 Y1
 X1 Y0
 X2 Y2

 {X0, X1, X2}
 {Y0, Y1, Y2}

-------

X1 Y0
X0 Y0
X1 Y1

   Y0 Y1
X1  1  1
X0  1  0

 
#endif

int do_test() {

	 std::set<std::string> s1;
	 std::set<std::string> s2;

	 int N;
	 std::cin >> N;

	 std::vector<std::string> v1;
	 std::vector<std::string> v2;

	 for (int i = 0; i < N; i++) {
		 std::string w1, w2;
		 std::cin >> w1;
		 std::cin >> w2;

		 if (s1.find(w1) == s1.end() &&
		     s2.find(w1) == s2.end()) {
			 s1.insert(w1);
			 s2.insert(w2);
		 } else {
			 v1.push_back(w1);
			 v2.push_back(w2);
		 }

	 }

	 int length = v1.size();

	 int count = 0;
	 for (int i = 0; i < length; i++) {
		 if (s1.find(v1[i]) == s1.end()) {
			 s1.insert(v1[i]);
		 } else if (s2.find(v2[i]) == s2.end()) {
			 s2.insert(v2[i]);
		 } else {
			 count++;
		 }
	 }

	 return count;
}

int main() {

	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++) {
		printf("Case #%d: %d\n", i + 1, do_test());
	}


	return 0;
}
