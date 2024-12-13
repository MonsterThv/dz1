#include <iostream>
#include <vector>
#include<string>

using namespace std;

class TextField
{
	string condition = "";

public:
	string get_str() {
		input_condition();
		erase_spaces();
		return condition;
	}

private:
	void input_condition() {
		getline(cin, condition);
	}

	void erase_spaces() {
		for (int i = 0; i < condition.length(); i++) {
			if (condition[i] == ' ') {
				condition.erase(condition.begin() + i);
			}
		}
	}
};

