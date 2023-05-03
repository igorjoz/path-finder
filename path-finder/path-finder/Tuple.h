#pragma once


#include <iostream>

template <typename... Types>
class Tuple;

template <>
class Tuple<> {};

template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : private Tuple<Tail...> {
public:
    Tuple() = default;

	
    Tuple(const Head& head, const Tail&... tail) : Tuple<Tail...>(tail...), head_(head) {}

	
    Head& head() {
        return head_;
    }

	
    Tuple<Tail...>& tail() {
        return *this;
    }

	
	const Head& head() const {
		return head_;
	}

	
	template <int index>
	auto& get() {
		if constexpr (index == 0) {
			return head_;
		}
		else {
			return Tuple<Tail...>::template get<index - 1>();
		}
	}


	template <typename T>
	auto& get() {
		if constexpr (std::is_same_v<T, Head>) {
			return head_;
		}
		else {
			return Tuple<Tail...>::template get<T>();
		}
	}

	
	template <int index>
	const auto& get() const {
		if constexpr (index == 0) {
			return head_;
		}
		else {
			return Tuple<Tail...>::template get<index - 1>();
		}
	}

	
private:
    Head head_;
};
