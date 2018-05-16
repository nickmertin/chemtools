#ifndef CHEMTOOLS_VAR_ARRAY_H
#define CHEMTOOLS_VAR_ARRAY_H


#include <cstdlib>
#include <vector>
#include "exception.h"

namespace utils {
    template<class T, size_t N_max>
    class var_array final {
    private:
        std::vector<T> data;

    public:
        class iterator final : std::iterator<std::random_access_iterator_tag, T> {
        private:
            var_array<T, N_max> *array;
            size_t index;

            const static size_t end = static_cast<size_t>(-1);

            iterator(var_array<T, N_max> *array, size_t index) : array(array), index(index) {}

            friend class var_array<T, N_max>;

        public:
            iterator() noexcept : array(nullptr), index(end) {}

            bool operator==(const iterator &rhs) const noexcept {
                return array == rhs.array && index == rhs.index;
            }

            bool operator!=(const iterator &rhs) const noexcept {
                return !(rhs == *this);
            }

            bool operator<(const iterator &rhs) const noexcept {
                return index < rhs.index;
            }

            bool operator>(const iterator &rhs) const noexcept {
                return rhs < *this;
            }

            bool operator<=(const iterator &rhs) const noexcept {
                return !(rhs < *this);
            }

            bool operator>=(const iterator &rhs) const noexcept {
                return !(*this < rhs);
            }

            iterator &operator++() {
                if (index == end)
                    throw EX_ITERATOR;
                if (++index >= N_max)
                    index = end;
                return *this;
            }

            iterator &operator--() {
                if (index == 0)
                    throw EX_ITERATOR;
                if (index == end) {
                    if (!array)
                        throw EX_ITERATOR;
                    index = array->data.size() - 1;
                }
                else
                    --index;
                return *this;
            }

            T &operator*() {
                if (index == end)
                    throw EX_ITERATOR;
                while (array->data.size() <= index)
                    array->data.push_back({});
                return array->data[index];
            }

            T *operator->() {
                return &**this;
            }

            const T &operator*() const {
                if (index == end || array->data.size() <= index)
                    throw EX_ITERATOR;
                return array->data[index];
            }

            const T *operator->() const {
                return &**this;
            }

            iterator operator+(size_t offset) {
                if (index == end || index + offset >= N_max)
                    throw EX_ITERATOR;
                return {array, index + offset};
            }

            iterator operator-(size_t offset) {
                return *this + -offset;
            }

            const iterator operator+(size_t offset) const {
                if (index == end || index + offset >= N_max)
                    throw EX_ITERATOR;
                return {array, index + offset};
            }

            const iterator operator-(size_t offset) const {
                return *this + -offset;
            }

            iterator &operator+=(size_t offset) {
                *this = *this + offset;
            }

            iterator &operator-=(size_t offset) {
                *this += -offset;
            }

            T &operator[](size_t offset) {
                return *(*this + offset);
            }

            const T &operator[](size_t offset) const {
                return *(*this + offset);
            }
        };

        explicit var_array(size_t length) : data(length) {
            if (length > N_max)
                throw(EX_BOUNDS);
        }

        var_array(std::initializer_list<T> list) : data(list) {
            if (list.size() > N_max)
                throw(EX_BOUNDS);
        }

        T &operator[](size_t i) noexcept {
            return data[i];
        }

        const T &operator[](size_t i) const noexcept {
            return data[i];
        }

        size_t size() const noexcept {
            return data.size();
        }

        void push_back(const T &value) {
            if (data.size() >= N_max)
                throw(EX_BOUNDS);
            data.push_back(value);
        }

        T pop_back() {
            if (data.empty())
                throw(EX_ITERATOR);
            return data.pop_back();
        }

        iterator begin() noexcept {
            return data.empty() ? end() : iterator{this, 0};
        }

        iterator end() noexcept {
            return {this, iterator::end};
        }
    };
}


#endif //CHEMTOOLS_VAR_ARRAY_H
