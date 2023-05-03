#pragma once


#include "String.h"
#include "Resources.h"


namespace std {
    template<>
    struct hash<String> {
        size_t operator()(const String& key) const {
            return hash<String>{}(key.getCString());
        }
    };
}


template <typename T>
class UnorderedMap {
public:
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<String, T>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        iterator() = default;

        iterator(typename std::vector<std::list<std::pair<String, T>>>::iterator outer_it,
            typename std::list<std::pair<String, T>>::iterator inner_it)
            : m_outer_it(outer_it), m_inner_it(inner_it) {}

        iterator& operator++() {
            ++m_inner_it;
            if (m_inner_it == m_outer_it->end()) {
                ++m_outer_it;
                while (m_outer_it != m_buckets_end && m_outer_it->empty()) {
                    ++m_outer_it;
                }
                if (m_outer_it != m_buckets_end) {
                    m_inner_it = m_outer_it->begin();
                }
            }
            return *this;
        }

        reference operator*() const {
            return *m_inner_it;
        }

        pointer operator->() {
            return &(*m_inner_it);
        }

        friend bool operator==(const iterator& a, const iterator& b) {
            return a.m_outer_it == b.m_outer_it && a.m_inner_it == b.m_inner_it;
        }

        friend bool operator!=(const iterator& a, const iterator& b) {
            return a.m_outer_it != b.m_outer_it || a.m_inner_it != b.m_inner_it;
        }

    private:
        typename std::vector<std::list<std::pair<String, T>>>::iterator m_outer_it;
        typename std::list<std::pair<String, T>>::iterator m_inner_it;
        //static typename std::vector<std::list<std::pair<String, T>>>::iterator m_buckets_end;
		static typename std::vector<std::list<std::pair<String, T>>>::iterator m_buckets_end;
    };

    iterator begin() noexcept {
        auto outer_it = m_buckets.begin();
        while (outer_it != m_buckets.end() && outer_it->empty()) {
            ++outer_it;
        }
        auto inner_it = outer_it != m_buckets.end() ? outer_it->begin() : typename std::list<std::pair<String, T>>::iterator();
        return iterator(outer_it, inner_it);
    }

    iterator end() noexcept {
        return iterator(m_buckets.end(), typename std::list<std::pair<String, T>>::iterator());
    }
    
    
    UnorderedMap(size_t bucket_count = 16, double max_load_factor = 0.75)
        : m_buckets(bucket_count), m_size(0), m_max_load_factor(max_load_factor) {
    }

    void insert(const String& key, const T& value) {
        check_load_factor_and_resize();
        size_t idx = hash_function(key) % m_buckets.size();
        for (auto& pair : m_buckets[idx]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        m_buckets[idx].emplace_back(key, value);
        ++m_size;
    }

    T& operator[](const String& key) {
        size_t idx = hash_function(key) % m_buckets.size();
        for (auto& pair : m_buckets[idx]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw std::out_of_range("Key not found in MyUnorderedMap");
    }

    bool contains(const String& key) const {
        size_t idx = hash_function(key) % m_buckets.size();
        for (const auto& pair : m_buckets[idx]) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    iterator find(const String& key) {
        size_t idx = hash_function(key) % m_buckets.size();
        for (auto it = m_buckets[idx].begin(); it != m_buckets[idx].end(); ++it) {
            if (it->first == key) {
                return iterator(m_buckets.begin() + idx, it);
            }
        }
        return end();
    }

    T& at(const String& key) {
        size_t idx = hash_function(key) % m_buckets.size();
        for (auto& pair : m_buckets[idx]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw std::out_of_range("Key not found in MyUnorderedMap");
    }

private:
    void check_load_factor_and_resize() {
        if (static_cast<double>(m_size) / m_buckets.size() >= m_max_load_factor) {
            size_t new_bucket_count = m_buckets.size() * 2;
            std::vector<std::list<std::pair<String, T>>> new_buckets(new_bucket_count);
            for (const auto& bucket : m_buckets) {
                for (const auto& pair : bucket) {
                    size_t idx = hash_function(pair.first) % new_bucket_count;
                    new_buckets[idx].emplace_back(pair);
                }
            }
            m_buckets.swap(new_buckets);
        }
    }

    size_t hash_function(const String& key) const {
        std::hash<String> hasher;
        return hasher(key);
    }

    std::vector<std::list<std::pair<String, T>>> m_buckets;
    size_t m_size;
    double m_max_load_factor;
};

template <typename T>
typename std::vector<std::list<std::pair<String, T>>>::iterator UnorderedMap<T>::iterator::m_buckets_end = typename std::vector<std::list<std::pair<String, T>>>::iterator();