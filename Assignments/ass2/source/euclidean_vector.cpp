// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

namespace comp6771 {
    // Implement solution here

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                            //
    //                                                                                            //
    //                                    Section 1: Constructors                                 //
    //                                                                                            //
    //                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////

    euclidean_vector::euclidean_vector() noexcept
            : length_{1}
            , euclidean_norm_{-1} {
        magnitude_ = std::make_unique<double[]>(static_cast<size_t>(length_));
        magnitude_[0] = 0;
    }

    euclidean_vector::euclidean_vector(const int size) noexcept
            : length_{size}
            , euclidean_norm_{-1} {
        magnitude_ = std::make_unique<double[]>(static_cast<size_t>(length_));
        std::fill_n(magnitude_.get(), length_, 0);
    }

    euclidean_vector::euclidean_vector(const int size, const double initial_value) noexcept
            : euclidean_vector(size) {
        std::fill_n(magnitude_.get(), length_, initial_value);
    }

    euclidean_vector::euclidean_vector(const std::vector<double>::const_iterator begin,
                                       const std::vector<double>::const_iterator end) noexcept
            : euclidean_vector(static_cast<int>(std::distance(begin, end))) {
        std::copy(begin, end, magnitude_.get());
    }

    euclidean_vector::euclidean_vector(const std::initializer_list<double> initialiser_list) noexcept
            : euclidean_vector(static_cast<int>(initialiser_list.size())) {
        std::copy(initialiser_list.begin(), initialiser_list.end(), magnitude_.get());
    }

    euclidean_vector::euclidean_vector(const euclidean_vector& vector) noexcept
            : euclidean_vector(vector.length_) {
        std::copy(vector.magnitude_.get(), vector.magnitude_.get() + length_, magnitude_.get());
    }

    euclidean_vector::euclidean_vector(euclidean_vector&& vector_reference) noexcept
            : magnitude_{std::move(vector_reference.magnitude_)}
            , length_{vector_reference.length_}
            , euclidean_norm_{vector_reference.euclidean_norm_} {
        vector_reference.length_ = 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                            //
    //                                                                                            //
    //                                    Section 2: OPERATORS                                    //
    //                                                                                            //
    //                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////

    euclidean_vector& euclidean_vector::operator=(const euclidean_vector& vector) noexcept {
        length_ = vector.length_;
        euclidean_norm_ = vector.euclidean_norm_;
        magnitude_ = std::make_unique<double[]>(static_cast<size_t>(length_));
        std::copy(vector.magnitude_.get(), vector.magnitude_.get() + length_, magnitude_.get());
        return *this;
    }

    auto euclidean_vector::operator=(euclidean_vector&& vector) noexcept -> euclidean_vector& {
        length_ = vector.length_;
        magnitude_ = std::move(vector.magnitude_);
        vector.euclidean_norm_ = -1;
        vector.length_ = 0;
        euclidean_norm_ = vector.euclidean_norm_;
        return *this;
    }

    auto euclidean_vector::operator[](const int index) -> double& {
        assert(index < length_ and index >= 0);
        euclidean_norm_ = -1;
        return magnitude_[static_cast<size_t>(index)];
    }

    auto euclidean_vector::operator[](const int index) const -> const double& {
        assert(index < length_ and index >= 0);
        return magnitude_[static_cast<size_t>(index)];
    }

    auto euclidean_vector::operator+() const noexcept -> euclidean_vector {
        return euclidean_vector(*this);
    }

    auto euclidean_vector::operator-() const noexcept -> euclidean_vector {
        auto negated_vector = euclidean_vector(*this);
        std::transform(negated_vector.magnitude_.get(),
                       negated_vector.magnitude_.get() + negated_vector.length_,
                       negated_vector.magnitude_.get(),
                       [](auto x) { return -x; });
        return negated_vector;
    }

    auto euclidean_vector::operator+=(const euclidean_vector& vector) -> euclidean_vector& {
        if (length_ != vector.length_) {
            throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(length_) + ") and RHS ("
                                         + std::to_string(vector.length_) + ") do not match");
        }
        auto index = 0;
        std::transform(magnitude_.get(), magnitude_.get() + length_, magnitude_.get(), [&](double x) {
            return x + vector[index++];
        });
        euclidean_norm_ = -1;
        return *this;
    }

    auto euclidean_vector::operator-=(const euclidean_vector& vector) -> euclidean_vector& {
        euclidean_norm_ = -1;
        auto vector_copy = euclidean_vector(vector);
        return *this += -1 * vector_copy;
    }

    auto euclidean_vector::operator*=(const double scale) noexcept -> euclidean_vector& {
        std::transform(magnitude_.get(), magnitude_.get() + length_, magnitude_.get(), [&](double x) {
            return x * scale;
        });

        euclidean_norm_ = (scale == 1 or scale == -1) ? euclidean_norm_ : -1;

        return *this;
    }

    auto euclidean_vector::operator/=(const double scale) -> euclidean_vector& {
        if (scale == 0) {
            throw euclidean_vector_error("Invalid vector division by 0");
        }

        euclidean_norm_ = (scale == 1 or scale == -1) ? euclidean_norm_ : -1;

        return *this *= 1 / scale;
    }

    euclidean_vector::operator std::vector<double>() const noexcept {
        auto vector = std::vector<double>(static_cast<size_t>(length_));
        std::copy(magnitude_.get(), magnitude_.get() + length_, vector.begin());
        return vector;
    }

    euclidean_vector::operator std::list<double>() const noexcept {
        auto list = std::list<double>(static_cast<size_t>(length_));
        std::copy(magnitude_.get(), magnitude_.get() + length_, list.begin());
        return list;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                            //
    //                                                                                            //
    //                             Section 3: MEMBER FUNCTIONS                                    //
    //                                                                                            //
    //                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////

    auto euclidean_vector::at(const int index) const -> const double& {
        if (index >= length_ or index < 0) {
            throw euclidean_vector_error("Index " + std::to_string(index) + " is out of bounds!");
        }
        return magnitude_[static_cast<size_t>(index)];
    }

    auto euclidean_vector::at(const int index) -> double& {
        if (index >= length_ or index < 0) {
            throw euclidean_vector_error("Index " + std::to_string(index) + " is out of bounds!");
        }
        euclidean_norm_ = -1;
        return magnitude_[static_cast<size_t>(index)];
    }

    auto euclidean_vector::dimensions() const noexcept -> int {
        return length_;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                            //
    //                                                                                            //
    //                                      Section 4: FRIENDS                                    //
    //                                                                                            //
    //                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // we don't want to check if euclidean norms are equal since its only changed from -1
    // once its called the get_euclidean_norm, so we check all other fields are equal
    auto operator==(const euclidean_vector& vector1, const euclidean_vector& vector2) noexcept
    -> bool {
        return vector1.length_ == vector2.length_
               && std::equal(vector1.magnitude_.get(),
                             vector1.magnitude_.get() + vector1.length_,
                             vector2.magnitude_.get(),
                             vector2.magnitude_.get() + vector2.length_);
    }

    auto operator!=(const euclidean_vector& vector1, const euclidean_vector& vector2) noexcept
    -> bool {
        return !(vector1 == vector2);
    }

    auto operator+(const euclidean_vector& vector1, const euclidean_vector& vector2)
    -> euclidean_vector {
        auto sum_vector = euclidean_vector(vector1);
        sum_vector += vector2;
        sum_vector.euclidean_norm_ = -1;
        return sum_vector;
    }

    auto operator-(const euclidean_vector& vector1, const euclidean_vector& vector2)
    -> euclidean_vector {
        auto sum_vector = euclidean_vector(vector1);
        sum_vector -= vector2;
        sum_vector.euclidean_norm_ = -1;
        return sum_vector;
    }

    auto operator*(const euclidean_vector& vector, double scale) noexcept -> euclidean_vector {
        auto multiple_vector = euclidean_vector(vector);
        multiple_vector *= scale;
        multiple_vector.euclidean_norm_ = -1;
        return multiple_vector;
    }

    auto operator*(double scale, const euclidean_vector& vector) noexcept -> euclidean_vector {
        return vector * scale;
    }

    auto operator/(const euclidean_vector& vector, double scale) -> euclidean_vector {
        auto division_vector = euclidean_vector(vector);
        division_vector /= scale;
        division_vector.euclidean_norm_ = -1;
        return division_vector;
    }

    auto operator<<(std::ostream& os, const euclidean_vector& vector) noexcept -> std::ostream& {
        os << "[";
        for (int i = 0; i < vector.length_ - 1; ++i) {
            os << vector.magnitude_[static_cast<size_t>(i)] << " ";
        }
        if (vector.length_ > 0) {
            os << vector.magnitude_[static_cast<size_t>(vector.length_ - 1)];
        }
        os << "]";
        return os;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                            //
    //                                                                                            //
    //                            Section 5: Utility Functions                                    //
    //                                                                                            //
    //                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // had to make it a friend to follow the specifcation for caching the norm, requiring access to
    // the norm stored in cache, and modification
    auto euclidean_norm(euclidean_vector const& vector) noexcept -> double {
        auto cached_norm = vector.euclidean_norm_;
        if (cached_norm != -1 && cached_norm >= 0) {
            return cached_norm;
        }
        // compute and cache, might aswell use magnitude_ instead of casting to vector since its a
        // friend anyway
        auto euclidean_norm = std::sqrt(std::inner_product(vector.magnitude_.get(),
                                                           vector.magnitude_.get() + vector.length_,
                                                           vector.magnitude_.get(),
                                                           0.0));
        vector.euclidean_norm_ = euclidean_norm;
        // return either 0 if length 0 or the cached result we computed above
        return euclidean_norm;
    }

    auto unit(const euclidean_vector& vector) -> euclidean_vector {
        if (vector.dimensions() == 0) {
            throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit "
                                         "vector");
        }
        auto e_norm = euclidean_norm(vector);
        if (e_norm == 0) {
            throw euclidean_vector_error("euclidean_vector with zero euclidean normal does not have a "
                                         "unit vector");
        }
        return euclidean_vector(vector) / e_norm;
    }

    auto dot(euclidean_vector const& vector1, euclidean_vector const& vector2) -> double {
        if (vector1.dimensions() != vector2.dimensions()) {
            throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(vector1.dimensions())
                                         + ") and RHS (" + std::to_string(vector2.dimensions())
                                         + ") do not match");
        }
        return vector1.dimensions() == 0
               ? 0
               : std::inner_product(vector1.magnitude_.get(),
                                    vector1.magnitude_.get() + vector1.length_,
                                    vector2.magnitude_.get(),
                                    0.0);
    }
} // namespace comp6771