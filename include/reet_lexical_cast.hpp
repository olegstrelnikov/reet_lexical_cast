/*
 * reet_lexical_cast.hpp
 *
 *  Created on: Apr 13, 2017
 *      Author: ois
 */

#ifndef INCLUDE_REET_LEXICAL_CAST_HPP_
#define INCLUDE_REET_LEXICAL_CAST_HPP_

#include <cstddef>
#include <sstream>

namespace reet {

template <typename T, typename FromT> struct impl {
	static T lexical_cast(FromT const& from);
};

//from basic string
template <typename T, typename FromT> struct impl<T, std::basic_string<FromT> > {
	static T lexical_cast(std::basic_string<FromT> const& from) {
		std::basic_istringstream<FromT> iss(from);
		T t;
		iss >> t;
		return t;
	}
};

//to basic sting
template <typename T, typename FromT> struct impl<std::basic_string<T>, FromT> {
	static std::basic_string<T> lexical_cast(FromT const& from) {
		std::basic_ostringstream<T> oss;
		oss << from;
		return oss.str();
	}
};

//identity
template <typename T> struct impl<T, T> {
	static T lexical_cast(T const& t) {
		return t;
	}
};

template <typename T, typename FromT> T lexical_cast(FromT const& from) {
	return impl<T, FromT>::lexical_cast(from);
}

//from C string
template <typename T, typename FromT> T lexical_cast(FromT const* from) {
	return lexical_cast<T>(std::basic_string<FromT>(from));
}

//from range of characters
template <typename T, typename FromT> T lexical_cast(FromT const* from, std::size_t n) {
	return lexical_cast<T>(std::basic_string<FromT>(from, n));
}

} //namespace reet

#endif /* INCLUDE_REET_LEXICAL_CAST_HPP_ */
