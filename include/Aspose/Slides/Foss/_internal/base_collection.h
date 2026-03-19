// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Aspose Pty Ltd

#pragma once

#include <cstddef>
#include <iterator>

namespace Aspose::Slides::Foss::Internal {

/// Index-based random-access iterator for BaseCollection-derived types.
///
/// @tparam Collection The concrete collection type (must provide operator[]).
/// @tparam ValueType  The element type returned by operator[].
template <typename Collection, typename ValueType>
class BaseCollectionIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = ValueType;
    using difference_type   = std::ptrdiff_t;
    using pointer           = ValueType*;
    using reference         = ValueType&;

    BaseCollectionIterator() = default;
    BaseCollectionIterator(Collection* coll, std::size_t index)
        : collection_(coll), index_(index) {}

    reference operator*() const { return (*collection_)[index_]; }
    pointer operator->() const { return &(*collection_)[index_]; }

    reference operator[](difference_type n) const { return (*collection_)[index_ + n]; }

    BaseCollectionIterator& operator++() { ++index_; return *this; }
    BaseCollectionIterator operator++(int) { auto tmp = *this; ++index_; return tmp; }
    BaseCollectionIterator& operator--() { --index_; return *this; }
    BaseCollectionIterator operator--(int) { auto tmp = *this; --index_; return tmp; }

    BaseCollectionIterator& operator+=(difference_type n) { index_ += n; return *this; }
    BaseCollectionIterator& operator-=(difference_type n) { index_ -= n; return *this; }

    friend BaseCollectionIterator operator+(BaseCollectionIterator it, difference_type n) {
        it += n; return it;
    }
    friend BaseCollectionIterator operator+(difference_type n, BaseCollectionIterator it) {
        it += n; return it;
    }
    friend BaseCollectionIterator operator-(BaseCollectionIterator it, difference_type n) {
        it -= n; return it;
    }
    friend difference_type operator-(const BaseCollectionIterator& a,
                                     const BaseCollectionIterator& b) {
        return static_cast<difference_type>(a.index_) -
               static_cast<difference_type>(b.index_);
    }

    friend bool operator==(const BaseCollectionIterator& a,
                           const BaseCollectionIterator& b) {
        return a.index_ == b.index_;
    }
    friend bool operator!=(const BaseCollectionIterator& a,
                           const BaseCollectionIterator& b) {
        return a.index_ != b.index_;
    }
    friend bool operator<(const BaseCollectionIterator& a,
                          const BaseCollectionIterator& b) {
        return a.index_ < b.index_;
    }
    friend bool operator<=(const BaseCollectionIterator& a,
                           const BaseCollectionIterator& b) {
        return a.index_ <= b.index_;
    }
    friend bool operator>(const BaseCollectionIterator& a,
                          const BaseCollectionIterator& b) {
        return a.index_ > b.index_;
    }
    friend bool operator>=(const BaseCollectionIterator& a,
                           const BaseCollectionIterator& b) {
        return a.index_ >= b.index_;
    }

private:
    Collection* collection_ = nullptr;
    std::size_t index_ = 0;
};

/// CRTP base class providing common collection operations.
///
/// Concrete subclasses must implement:
///   - `std::size_t size() const noexcept`
///   - `Element& operator[](std::size_t index)`
///   - `const Element& operator[](std::size_t index) const`
///
/// In return they get:
///   - `length()` — mirrors size(), analogous to .NET ICollection.Count
///   - `begin()` / `end()` — index-based iterators for range-for
///   - `contains()` — membership test (pointer identity then equality)
///
/// @tparam Derived The concrete collection class (CRTP parameter).
/// @tparam Element The element type stored in the collection.
template <typename Derived, typename Element>
class BaseCollection {
public:
    using iterator       = BaseCollectionIterator<Derived, Element>;
    using const_iterator = BaseCollectionIterator<const Derived, const Element>;

    /// Returns the number of elements. Read-only.
    [[nodiscard]] std::size_t length() const noexcept {
        return self().size();
    }

    /// Returns an iterator to the first element.
    [[nodiscard]] iterator begin() noexcept {
        return iterator(&self(), 0);
    }

    /// Returns an iterator past the last element.
    [[nodiscard]] iterator end() noexcept {
        return iterator(&self(), self().size());
    }

    /// Returns a const iterator to the first element.
    [[nodiscard]] const_iterator begin() const noexcept {
        return const_iterator(&self(), 0);
    }

    /// Returns a const iterator past the last element.
    [[nodiscard]] const_iterator end() const noexcept {
        return const_iterator(&self(), self().size());
    }

    /// Tests whether an element is in the collection.
    ///
    /// Checks pointer identity first, then falls back to equality comparison.
    /// @param item The element to search for.
    /// @return true if the element is found.
    [[nodiscard]] bool contains(const Element& item) const {
        const auto& d = self();
        for (std::size_t i = 0; i < d.size(); ++i) {
            const auto& elem = d[i];
            if (&elem == &item || elem == item) {
                return true;
            }
        }
        return false;
    }

protected:
    BaseCollection() = default;
    ~BaseCollection() = default;
    BaseCollection(const BaseCollection&) = default;
    BaseCollection(BaseCollection&&) = default;
    BaseCollection& operator=(const BaseCollection&) = default;
    BaseCollection& operator=(BaseCollection&&) = default;

private:
    [[nodiscard]] Derived& self() noexcept {
        return static_cast<Derived&>(*this);
    }
    [[nodiscard]] const Derived& self() const noexcept {
        return static_cast<const Derived&>(*this);
    }
};

} // namespace Aspose::Slides::Foss::Internal
