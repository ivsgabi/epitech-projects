#include <optional>
#include <utility>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <any>
#include "Exceptions.hpp"

#ifndef SPARSEARRAY_HPP
    #define SPARSEARRAY_HPP

namespace ECS {
template <typename Component>
    class SparseArray {
    public:
    using ValueType = std::optional<Component>;  
    using ReferenceType = ValueType&;           
    using ConstReferenceType = const ValueType&;
    using ContainerType = std::vector<ValueType>; // optionally add your allocator template here.
    using SizeType = typename ContainerType::size_type; 
    using Iterator = typename ContainerType::iterator; 
    using ConstIterator = typename ContainerType::const_iterator;
    public:

    SparseArray() = default;

    // copy constructor
    SparseArray(SparseArray const &GivenSparseArray) 
        : _data(GivenSparseArray._data) {}

    // move constructor
    SparseArray(SparseArray&& GivenSparseArray) noexcept
        : _data(std::move(GivenSparseArray._data)) {}

    // destructor
    ~SparseArray() = default;

    //copy assignment operator
    SparseArray& operator=(SparseArray const& GivenSparseArray) {
        if (this != &GivenSparseArray) {
            this->_data = GivenSparseArray._data;
        }
        return *this;
    }

    // move assignment operator
    SparseArray& operator=(SparseArray&& GivenSparseArray) noexcept {
        if (this != &GivenSparseArray) {
            this->_data = std::move(GivenSparseArray._data);
        }
        return *this;
    }

    void clear() {
        _data.clear();
    }

    // data access by index operator
    ReferenceType operator[](size_t idx) {
        return this->_data[idx]; 
    }

    // data access by index operator (read-only)
    ConstReferenceType operator[](size_t idx) const {
        return this->_data[idx];
    }

    // iterators
    Iterator begin() {
        return this->_data.begin();
    }

    ConstIterator begin() const {
        return this->_data.begin();
    }

    ConstIterator cbegin() const {
        return this->_data.cbegin();
    }

    Iterator end() {
        return this->_data.end();
    }

    ConstIterator end() const {
        return this->_data.end();
    }

    ConstIterator cend() const {
        return this->_data.cend();
    }

    // size getter
    SizeType size() const {
        return this->_data.size();
    }

    // insert data at given position | ps: pos -> entity_id
    ReferenceType insert_at(SizeType pos, Component const& comp) {
        if (pos >= this->_data.size()) {
            this->_data.resize(pos + 1);
        }
        this->_data[pos] = comp;
        return this->_data[pos];
    }

    // destoy entity if one already there and create a new one
    template <typename... Params>
    ReferenceType emplace_at(SizeType pos, Params&&... args) {
        if (pos >= this->_data.size()) {
            this->_data.resize(pos + 1);
        }
        auto& allocator = this->_data.get_allocator();
        std::allocator_traits<decltype(allocator)>::destroy(allocator, &this->_data[pos]);
        std::allocator_traits<decltype(allocator)>::construct(allocator, &this->_data[pos], std::forward<Params>(args)...);
        return this->_data[pos];
    }

    // erase a value at a specified index | ps: pos -> entity_id
    void erase(SizeType pos) {
        if (pos >= this->_data.size()) {
            throw SparseArrayExceptions("index out of range");
        }
        this->_data.erase(this->_data.begin() + pos);
    }

    // take a reference to an optional component, and return its index | ps: pos -> entity_id + optional bc it could be empty
    SizeType get_index(ValueType const& value) const {
        auto it = std::find(this->_data.begin(), this->_data.end(), value);
        if (it == this->_data.end()) {
            throw SparseArrayExceptions("error: value not found");
        }
        return std::distance(this->_data.begin(), it);
    }

    // template <typename U>
    // SparseArray<std::any>& operator=(SparseArray<U> const& other);

    //std::addressof

    private:
    ContainerType _data;
};
};
#endif // SPARSEARRAY_HPP