/*
 * test.cpp
 *
 *  Created on: Apr 21, 2017
 *      Author: ois
 */

#include <iostream>

#include <reet_lexical_cast.hpp>

int main() {
	std::string const str5 = reet::lexical_cast<std::string>(5);
	const char* const str10 = "10";
	int const n10 = reet::lexical_cast<int>(str10);
	unsigned const u20 = reet::lexical_cast<unsigned>("20");
	double const pi3_14 = reet::lexical_cast<double>("3.1415926", 4);
	std::string const True = "1";
	bool const b1 = reet::lexical_cast<bool>(True);
	std::cout << str5 << " " << n10 << " " << u20 << " " << pi3_14 << " " << b1 << "\n";
	return 0;
}

