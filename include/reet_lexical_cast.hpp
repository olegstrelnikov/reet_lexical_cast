/*
 * reet_lexical_cast.hpp
 *
 *  Created on: Apr 13, 2017
 *  Author: Oleg Strelnikov
 */

#ifndef INCLUDE_REET_LEXICAL_CAST_HPP_
#define INCLUDE_REET_LEXICAL_CAST_HPP_

#include <cstddef>
#include <sstream>
#include <locale>

namespace reet {

	namespace impl {

	template <typename T, typename CharT>
	T from_istringstream(std::basic_istringstream<CharT>& istream) {
		T t;
		istream >> t;
		return t;
	}

	template <typename T, typename CharT>
	std::basic_string<CharT> to_string(std::basic_ostringstream<CharT>& ostream, T const& from) {
		ostream << from;
		return ostream.str();
	}

	template <typename T, typename FromT> struct from_to_string {
		static T cast(FromT const& from);
		static T cast(FromT const& from, std::locale);
	};

	//from std::basic_string
	template <typename T, typename CharT> struct from_to_string<T, std::basic_string<CharT> > {
		static T cast(std::basic_string<CharT> const& from) {
			std::basic_istringstream<CharT> iss(from);
			return from_istringstream<T>(iss);
		}
		static T cast(std::basic_string<CharT> const& from, std::locale const& l) {
			std::basic_istringstream<CharT> iss(from);
			iss.imbue(l);
			iss.setf(std::ios_base::boolalpha);
			return from_istringstream<T>(iss);
		}
	};

	//to std::basic_sting
	template <typename CharT, typename FromT> struct from_to_string<std::basic_string<CharT>, FromT> {
		static std::basic_string<CharT> cast(FromT const& from) {
			std::basic_ostringstream<CharT> oss;
			return to_string(oss, from);
		}
		static std::basic_string<CharT> cast(FromT const& from, std::locale const& l) {
			std::basic_ostringstream<CharT> oss;
			oss.imbue(l);
			oss.setf(std::ios_base::boolalpha);
			return to_string(oss, from);
		}
	};

	//identity std::basic_string to std::basic_string
	template <typename CharT> struct from_to_string<std::basic_string<CharT>, std::basic_string<CharT> > {
		static std::basic_string<CharT> cast(std::basic_string<CharT> const& t) {
			return t;
		}
	};

	} //namespace impl

template <typename T, typename FromT> T lexical_cast(FromT const& from) {
	return impl::from_to_string<T, FromT>::cast(from);
}

template <typename T, typename FromT> T lexical_cast(FromT const& from, std::locale const& l) {
	return impl::from_to_string<T, FromT>::cast(from, l);
}

//from C string
template <typename T, typename CharT> T lexical_cast(CharT const* from) {
	return lexical_cast<T>(std::basic_string<CharT>(from));
}

template <typename T, typename CharT> T lexical_cast(CharT const* from, std::locale const& l) {
	return lexical_cast<T>(std::basic_string<CharT>(from), l);
}

//from range of characters
template <typename T, typename CharT> T lexical_cast(CharT const* from, std::size_t n) {
	return lexical_cast<T>(std::basic_string<CharT>(from, n));
}

template <typename T, typename CharT> T lexical_cast(CharT const* from, std::size_t n, std::locale const& l) {
	return lexical_cast<T>(std::basic_string<CharT>(from, n), l);
}

} //namespace reet

#endif /* INCLUDE_REET_LEXICAL_CAST_HPP_ */
