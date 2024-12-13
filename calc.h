#include "TextField.h"
#include "ErrorFinder.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Calc{

	TextField text_field;
	string inp_condition;
	string res = "";
	string err = "";

public : 
	void run() {
		cout << "input condition" << endl; 
		inp_condition = text_field.get_str();
		ErrorFinder errors(inp_condition);
		err = errors.find_errors();

		if (err == "") {
			find_x(inp_condition);
			find_negatives(inp_condition);
			run_functions(inp_condition);
			output(inp_condition);
			if (find(inp_condition.begin(), inp_condition.end(), '(') == inp_condition.end() && find(inp_condition.begin(), inp_condition.end(), ')') == inp_condition.end()) {
				cout << inp_condition << endl;
			}
			else
			{
				cout << inp_condition << endl;
				cout << "error" << endl;
			}

		}
		else {
			cout << err << endl;
		}

	}

private :

	void output(string& condition) {
		if (condition[0] == '"') {
			condition.erase(condition.begin());
			condition.erase(condition.end() - 1);
			condition.insert(condition.begin(), '-');
		}
	}

	void find_x(string& condition) {
		vector<int> poses;
		condition.insert(condition.begin(), ' ');
		for (int i = 1; i < condition.length(); i++) {
			if (condition[i] == 'x' && condition[i - 1] != 'e') {
				poses.push_back(i);
			}
		}
		if (poses.size() > 0) {
			cout << "input x" << endl;
			string x = text_field.get_str();
			for (auto i : poses) {
				condition.erase(condition.begin() + i);
				condition.insert(i, x);
			}
		}
		condition.erase(condition.begin());
	}

	void run_functions(string& condition) {
		int count_func = count(condition.begin(), condition.end(), 's') + count(condition.begin(), condition.end(), 't') + count(condition.begin(), condition.end(), 'e');

		if (count_func > 0) {
			string func = "";
			for (int i = 0; i < condition.length(); i++) {

				if (((int(condition[i]) >= 48 && int(condition[i]) <= 57) || (int(condition[i]) >= 97 && int(condition[i]) <= 122) || int(condition[i]) == 46 || int(condition[i]) == 34 || condition[i] == '(' ||
					condition[i] == '+' || condition[i] == '-' || condition[i] == '*' || condition[i] == '/' || condition[i] == ')') && func.length() != 0) {

					func.push_back(condition[i]);
				}
				if (count(func.begin(), func.end(), '(') == count(func.begin(), func.end(), ')') && func.length() != 0 && count(func.begin(), func.end(), '(') > 0) {
					int pos = condition.find(func);
					string f = "";
					condition.erase(condition.begin() + pos, condition.begin() + pos + func.length());
					for (int j = 0; j < func.length(); j++) {
						if (func[j] != '(') {
							f.push_back(func[j]);
						}
						else {
							break;
						}
					}
					for (int j = 0; j < f.length(); j++) {
						func.erase(func.begin());
					}
					func.erase(func.begin());
					func.erase(func.end() - 1);
					run_actions_in_brackets(func);
					condition.insert(pos, calculate_func(f, func));
					run_functions(condition);
					break;
				}
				if (func.length() == 0 && (int(condition[i]) >= 97 && int(condition[i]) <= 122)) {
					func.push_back(condition[i]);
				}
			}
		}
		else {
			run_actions_in_brackets(condition);
		}

	}

	void run_actions_in_brackets(string& condition) {
		int count_breackets = count(condition.begin(), condition.end(), '(');
		if (count_breackets > 0) {
			string cond = "";
			for (int i = 0; i < condition.length(); i++) {

				if (((int(condition[i]) >= 48 && int(condition[i]) <= 57) || int(condition[i]) == 46 || int(condition[i]) == 34 || condition[i] == '(' || 
					condition[i] == '+' || condition[i] == '-' || condition[i] == '*' || condition[i] == '/' || condition[i] == ')') && cond.length() != 0) {

					cond.push_back(condition[i]);
				}
				if (count(cond.begin(), cond.end(), '(') == count(cond.begin(), cond.end(), ')') && cond.length() != 0) {

					int pos = condition.find(cond);
					condition.erase(condition.begin() + pos, condition.begin() + pos + cond.length());
					cond.erase(cond.begin());
					cond.erase(cond.end() - 1);
					if (count(cond.begin(), cond.end(), '(') > 0) {
						run_actions_in_brackets(cond);
					}
					run_first_actions(cond);
					condition.insert(pos, cond);
					run_actions_in_brackets(condition);
					break;
				}
				if (cond.length() == 0 && condition[i] == '(') {
					cond.push_back(condition[i]);
				}
			}
		}
		else
		{
			run_first_actions(condition);
		}
	}


	void run_first_actions(string& condition) {
		int count_of_first_operations = count(condition.begin(), condition.end(), '/') + count(condition.begin(), condition.end(), '*');
		
		string litle_cond = "";
		if (count_of_first_operations > 0) {
			bool operation_was_found = false;
			for (int j = 0; j < condition.length(); j++) {

				if ((int(condition[j]) >= 48 && int(condition[j]) <= 57) || int(condition[j]) == 46 || int(condition[j]) == 34) {
					litle_cond.push_back(condition[j]);
				}

				if (operation_was_found && !((int(condition[j + 1]) >= 48 && int(condition[j + 1]) <= 57) || int(condition[j + 1]) == 46 || j == condition.length() || int(condition[j + 1]) == 34)) {
					int pos = condition.find(litle_cond);
					condition.erase(condition.begin() + pos, condition.begin() + pos + litle_cond.length());
					condition.insert(pos, calculate(litle_cond));
					run_first_actions(condition);
					break;
				}

				if (!operation_was_found && !((int(condition[j]) >= 48 && int(condition[j]) <= 57) || int(condition[j]) == 46 || int(condition[j]) == 34)) {
					if (condition[j] == '*' || condition[j] == '/') {
						operation_was_found = true;
						litle_cond.push_back(condition[j]);
					}
					else {
						litle_cond = "";
					}
				}


			}
		}
		else
		{
			run_second_actions(condition);
		}
	}

	void run_second_actions(string& condition) {

		int count_of_second_operations = count(condition.begin(), condition.end(), '-') + count(condition.begin(), condition.end(), '+');

		string litle_cond = "";
		if (count_of_second_operations > 0) {
			bool operation_was_found = false;
			for (int j = 0; j < condition.length(); j++) {

				if ((int(condition[j]) >= 48 && int(condition[j]) <= 57) || int(condition[j]) == 46 || int(condition[j]) == 34) {
					litle_cond.push_back(condition[j]);
				}

				if (operation_was_found && !((int(condition[j + 1]) >= 48 && int(condition[j + 1]) <= 57) || int(condition[j + 1]) == 46 || j == condition.length() || int(condition[j + 1]) == 34)) {
					int pos = condition.find(litle_cond);
					condition.erase(condition.begin() + pos, condition.begin() + pos + litle_cond.length());
					condition.insert(pos, calculate(litle_cond));
					run_second_actions(condition);
					break;
				}

				if (!operation_was_found && !((int(condition[j]) >= 48 && int(condition[j]) <= 57) || int(condition[j]) == 46 || int(condition[j]) == 34)) {
					if (condition[j] == '+' || condition[j] == '-') {
						operation_was_found = true;
						litle_cond.push_back(condition[j]);
					}
					else {
						litle_cond = "";
					}
				}


			}
		}
		else
		{
			res = condition;
		}
	}

	string calculate(string calcuiated_string) {
		float answer;
		vector<float> nums;
		char operation = ' ';
		get_operation(nums, operation, calcuiated_string);
		switch (operation)
		{
		case '+':
			answer = nums[0] + nums[1];
			break;
		case '-':
			answer = nums[0] - nums[1];
			break;
		case '/':
			answer = nums[0] / nums[1];
			break;
		case '*':
			answer = nums[0] * nums[1];
			break;
		}
		if (answer < 0) {
			string res;
			res.push_back('"');
			for (auto i : to_string(answer)) {
				res.push_back(i);
			}
			res.push_back('"');
			res.erase(res.begin() + 1);
			return res;
		}
		return to_string(answer);
	}

	string calculate_func(string func, string num) {
		float answer;
		float arg;
		if (num[0] == '"') {
			num.erase(num.end());
			num.erase(num.begin());
			arg = stof(num) * -1;
		}
		else {
			arg = stof(num);
		}

		switch (func[0])
		{
		case 's':
			answer = sin(arg);
			break;
		case 't':
			answer = tan(arg);
			break;
		case 'c':
			if (func[1] == 'o') {
				answer = cos(arg);
			}
			else
			{
				answer = cos(arg) / sin(arg);
			}
			break;
		case 'e':
			answer = exp(arg);
			break;
		}
		if (answer < 0) {
			string res;
			res.push_back('"');
			for (auto i : to_string(answer)) {
				res.push_back(i);
			}
			res.push_back('"');
			res.erase(res.begin() + 1);
			return res;
		}
		return to_string(answer);
	}

	void get_operation(vector<float>& nums, char& operation, string calcuiated_string) {
		string num;
		for (auto i : calcuiated_string) {
			if ((int(i) >= 48 && int(i) <= 57) || int(i) == 46 || int(i) == 34) {
				num.push_back(i);
			}
			else {
				if (num[0] == '"') {	
					num.erase(num.end() - 1);
					num.erase(num.begin());
					nums.push_back(stof(num) * -1);
					num.erase(num.begin(), num.end());
				}
				else {
				nums.push_back(stof(num));
				num.erase(num.begin(), num.end());
				}
				operation = i;
			}
		}
		if (num[0] == '"') {
			num.erase(num.end());
			num.erase(num.begin());
			nums.push_back(stof(num) * -1);
		}
		else {
			nums.push_back(stof(num));
		}
	}

	void find_negatives(string& condition) {
		for (int i = 0; i < condition.length(); i++) {
			if (condition[i] == '(' && condition[i + 1] == '-') {
				condition[i] = '"';
				condition.erase(condition.begin() + i + 1);
				for (int j = i; j < condition.length(); j++) {
					if (condition[j] == ')') {
						condition[j] = '"';
						break;
					}
				}
			}
		}
	}

};

