#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class ErrorFinder
{
public:
	vector<string> funcs = {"cos(", "sin(", "exp(", "tan(", "tg(", "ctg(", "x"};
	vector<string> opers = { "+", "-", "*", "/", "."};
	vector<string> funcs_for_check;
	vector<string> opers_for_check;
	string condition;

	string find_errors() {
		find_funcs();
		find_opers();
		if (count(condition.begin(), condition.end(), '(') != count(condition.begin(), condition.end(), ')')) {
			return "error with brackets";
		}
		if (!check_funcs()) {
			return "error with functions";
		}
		if (!check_opers()) {
			return "error with operations";
		}
		return "";
	}

	bool check_funcs() {
		
		for (auto i : funcs_for_check) {
			if (find(funcs.begin(), funcs.end(), i) == funcs.end()) {
				return false;
			}
		}
		return true;
	}

	bool check_opers() {
		for (auto i : opers_for_check) {
			if (find(opers.begin(), opers.end(), i) == opers.end()) {
				return false;
			}
		}
		return true;
	}

	

	void find_funcs() {
		string func = "";
		for (auto i : condition) {
			if ((int(i) >= 97 && int(i) <= 122) || i == '(') {
				if (i == '(' && func.length() > 0) {
					func.push_back(i);
					funcs_for_check.push_back(func);
					func = "";
				}
				if (int(i) >= 97 && int(i) <= 122) {
					func.push_back(i);
				}

			}
			else
			{
				if (func.length() > 0) {
					funcs_for_check.push_back(func);
					func = "";
				}
			}
			
		}
		if (func.length() > 0) {
			funcs_for_check.push_back(func);
		}
	}

	void find_opers() {
		string oper = "";
		for (auto i : condition) {
			if (!(int(i) >= 97 && int(i) <= 122) && i != '(' && i != ')' && !(int(i) >= 48 && int(i) <= 57)) {
				oper.push_back(i);
			}
			else
			{
				if (oper.length() > 0) {
					opers_for_check.push_back(oper);
					oper = "";
				}
			}
		}
	}

	ErrorFinder(string cond) {
		condition = cond;
	}
};

