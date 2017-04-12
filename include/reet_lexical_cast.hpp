/*
 * reet_lexical_cast.hpp
 *
 *  Created on: Apr 13, 2017
 *      Author: ois
 */

#ifndef INCLUDE_REET_LEXICAL_CAST_HPP_
#define INCLUDE_REET_LEXICAL_CAST_HPP_

#include <sstream>

template <typename T, typename FromT> struct serializal {
	static T cast(FromT const& from) {
		std::ostringstream oss;
		oss << from;
		return serializal<T, std::string>::cast(oss.str());
	}
};

template <typename T> struct serializal<T, std::string> {
	static T cast(const std::string& str) {
		std::istringstream iss;
		iss.str(str);
		T var;
		iss >> var;
		return var;
	}
};

template<> struct serializal<std::string, std::string> {
	static std::string cast(const std::string& str) {
		return str;
	}
};

#endif /* INCLUDE_REET_LEXICAL_CAST_HPP_ */
