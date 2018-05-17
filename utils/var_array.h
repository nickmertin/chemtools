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
        typedef T value_type;

        class iterator final : public std::iterator<std::random_access_iterator_tag, T> {
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
                if (++index >= array->size())
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

            T &operator*() const {
                if (index == end)
                    throw EX_ITERATOR;
                while (array->data.size() <= index)
                    array->data.push_back(T());
                return array->data[index];
            }

            T *operator->() const {
                return &**this;
            }

            iterator operator+(size_t offset) const {
                return {array, index == end || index + offset >= array->size() ? end : -offset > index ? 0 : index + offset};
            }

            iterator operator-(size_t offset) const {
                return *this + -offset;
            }

            iterator &operator+=(size_t offset) {
                *this = *this + offset;
            }

            iterator &operator-=(size_t offset) {
                *this += -offset;
            }

            T &operator[](size_t offset) const {
                return *(*this + offset);
            }
        };

        class const_iterator final : public std::iterator<std::input_iterator_tag, T> {
        private:
            const var_array<T, N_max> *array;
            size_t index;

            const static size_t end = static_cast<size_t>(-1);

            const_iterator(const var_array<T, N_max> *array, size_t index) : array(array), index(index) {}

            friend class var_array<T, N_max>;

        public:
            const_iterator() noexcept : array(nullptr), index(end) {}

            bool operator==(const const_iterator &rhs) const noexcept {
                return array == rhs.array && index == rhs.index;
            }

            bool operator!=(const const_iterator &rhs) const noexcept {
                return !(rhs == *this);
            }

            bool operator<(const const_iterator &rhs) const noexcept {
                return index < rhs.index;
            }

            bool operator>(const const_iterator &rhs) const noexcept {
                return rhs < *this;
            }

            bool operator<=(const const_iterator &rhs) const noexcept {
                return !(rhs < *this);
            }

            bool operator>=(const const_iterator &rhs) const noexcept {
                return !(*this < rhs);
            }

            const_iterator &operator++() {
                if (index == end)
                    throw EX_ITERATOR;
                if (++index >= array->size())
                    index = end;
                return *this;
            }

            const_iterator &operator--() {
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

            const T &operator*() const {
                if (index == end || array->data.size() <= index)
                    throw EX_ITERATOR;
                return array->data[index];
            }

            const T *operator->() const {
                return &**this;
            }

            const_iterator operator+(size_t offset) const {
                return {array, index == end || index + offset >= array->size() ? end : -offset > index ? 0 : index + offset};
            }

            const_iterator operator-(size_t offset) const {
                return *this + -offset;
            }

            const_iterator &operator+=(size_t offset) {
                *this = *this + offset;
            }

            const_iterator &operator-=(size_t offset) {
                *this += -offset;
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

        var_array() : var_array({}) {}

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

        const_iterator cbegin() const noexcept {
            return data.empty() ? cend() : const_iterator{this, 0};
        }

        const_iterator cend() const noexcept {
            return {this, const_iterator::end};
        }

        const_iterator begin() const noexcept {
            return cbegin();
        }

        const_iterator end() const noexcept {
            return cend();
        }
    };
}


#endif //CHEMTOOLS_VAR_ARRAY_H
