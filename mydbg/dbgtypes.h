
#ifndef DBG_TYPES_H
#define DBG_TYPES_H

#include "core.h"

template<class T> struct is_vector {
	static bool const value = false;
};
template<class T> struct is_vector<std::vector<T> > {
	static bool const value = true;
};

template<class T> struct is_map {
	static bool const value = false;
};

template<class T1, class T2> struct is_map<std::map<T1, T2> > {
	static bool const value = true;
};

template <typename T>
std::string _to_string(const T& value) {
	if constexpr (std::is_same<T, bool>::value) {
		return value ? "true" : "false";
	} else if constexpr (std::is_arithmetic<T>::value) {
		return std::to_string(value);
	} else if constexpr (std::is_same<T, std::string>::value || std::is_same<T, const std::string&>::value) {
		return value;

	} else if constexpr (std::is_same<T, std::vector<bool>>::value) {
		std::string ret = "[ ";
		for (size_t i = 0; i < value.size(); i++) {
			if (i != 0) ret += ", ";
			ret += (value[i]) ? "true" : "false";
		}
		return ret + " ]";
	} else if constexpr (is_vector<T>::value) {
		std::string ret = "[ ";
		for (size_t i = 0; i < value.size(); i++) {
			if (i != 0) ret += ", ";
			ret += _to_string(value[i]);
		}
		return ret + " ]";

	} else if constexpr (is_map<T>::value) {
		auto it = value.begin();
		std::string ret = "[ ";
		while (it != value.end()) {
			if (it != value.begin()) ret += ", ";
			ret += _to_string(it->first) + " : " + _to_string(it->second);
			it++;
		}
		return ret + " ]";
	} else if constexpr (std::is_same<T, const char*>::value) {
		return value;
	}
	// don't return anything here as it may throw compiler error if any type were missed.
}


#endif // DBG_TYPES_H