#pragma once

#include <string>
#include <vector>
#include <algorithm>

class PatriciaTree {

private:

	std::vector<std::pair<std::string, PatriciaTree>> strings;

	bool isWordEnding;

public:

	PatriciaTree() : strings{}, isWordEnding{ false } { }

	bool lookup(std::string string);

	void insert(std::string string);

};
