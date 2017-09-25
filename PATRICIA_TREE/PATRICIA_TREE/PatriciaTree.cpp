
#include "PatriciaTree.h"

bool PatriciaTree::lookup(std::string string) {

	if (string.length() == 0) { // We have no more characters to try -> we found something
		return isWordEnding;
	}

	// The first string which starts with the same character as my string will suffice
	auto it = std::find_if(strings.begin(), strings.end(), [&](const std::pair<std::string, PatriciaTree>& p) {
		return p.first[0] == string[0];
	});

	if (it == strings.end()) // No child found - return
		return false;

	std::pair<std::string, PatriciaTree>& pair = *it;

	// Found something
	int uncommonIndex = 0, minLen = std::min(string.length(), pair.first.length());

	// Get first uncommon index
	for (; uncommonIndex < minLen && string[uncommonIndex] == pair.first[uncommonIndex]; ++uncommonIndex);

	if (uncommonIndex == minLen && string.length() < pair.first.length()) { 
		// string is a substring of the branch, but not equal to the branch
		return false;
	}

	// Continue search from there
	return pair.second.lookup(string.substr(uncommonIndex));
		
}

void PatriciaTree::insert(std::string string) {

	// The first string which starts with the same character as my string will suffice
	auto it = std::find_if(strings.begin(), strings.end(), [&](const std::pair<std::string, PatriciaTree>& p) {
		return p.first[0] == string[0];
	});

	if (it == strings.end()) { // No children found. Append to root
		PatriciaTree tree{};
		tree.isWordEnding = true;
		strings.push_back(std::make_pair(string, tree));
	}
	else { // Found a child. Find out how long the suffix is
		std::pair<std::string, PatriciaTree>& pair = *it;
		
		int uncommonIndex = 0, minLen = std::min(string.length(), pair.first.length());

		// Get index of first uncommon character
		for (; uncommonIndex < minLen && string[uncommonIndex] == pair.first[uncommonIndex]; ++uncommonIndex); 

		// If the (sub)string is equal to the branch, we have found our insertion point
		if (string.length() == pair.first.length() && uncommonIndex == minLen) {
			isWordEnding = true;
		}

		// If inserting string is larger than branch and contains the branch as a suffix
		else if(string.length() > pair.first.length() && uncommonIndex == minLen) { // Insert rest in next node
			pair.second.insert(string.substr(uncommonIndex));
		}
		else { // They have a common suffix
			std::string substring = string.substr(uncommonIndex);
			if (substring.length() != 0) { // If we have to add a new node
				pair.second.isWordEnding = false;
				pair.second.insert(string.substr(uncommonIndex));
			}
			pair.second.insert(pair.first.substr(uncommonIndex));
			pair.first = pair.first.substr(0, uncommonIndex);
		}
	}
			
}
