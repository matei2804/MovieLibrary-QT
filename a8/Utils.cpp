#include "Utils.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

std::string trim(const std::string& string)
{
	std::string result(string);
	size_t position = result.find_first_not_of(" ");
	if (position != -1)
		result.erase(0, position);
	position = result.find_last_not_of(" ");
	if (position != std::string::npos)
		result.erase(position + 1);

	return result;
}

vector<string> tokenize(const string& string, char delimiter)
{
	vector <std::string> result;
	stringstream ss(string);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}