// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>

namespace comp6771 {
    // Implement solution here
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                            //
    //                                                                                            //
    //                                    Section 1: Constructors                                 //
    //                                                                                            //
    //                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    euclidean_vector::euclidean_vector() noexcept {
        length_ = 1;
        magnitude_ = std::make_unique<double[]>(length_);
        magnitude_[0] = 0;
    }

    euclidean_vector::euclidean_vector(int size) noexcept {
        length_ = size;
        magnitude_ = std::make_unique<double[]>(length_);
        std::fill_n(magnitude_.get(), length_, 0);
    }

    euclidean_vector::euclidean_vector(int size, double initial_value) noexcept:
            euclidean_vector(size) {
        std::fill_n(magnitude_.get(), length_, initial_value);
    }

    euclidean_vector::euclidean_vector(std::vector<double>::const_iterator begin,
                                       std::vector<double>::const_iterator end) noexcept:
            euclidean_vector(static_cast<int>(distance(begin, end))) {
        std::copy(begin, end, magnitude_.get());
    }

    euclidean_vector::euclidean_vector(std::initializer_list<double> initialiser_list) noexcept:
            euclidean_vector(static_cast<int>(initialiser_list.size())) {
        std::copy(initialiser_list.begin(), initialiser_list.end(), magnitude_.get());
    }

    euclidean_vector::euclidean_vector(const euclidean_vector &vector) noexcept:
            euclidean_vector(vector.length_) {
        std::copy(vector.magnitude_.get(), vector.magnitude_.get() + length_, magnitude_.get());
    }

    euclidean_vector::euclidean_vector(euclidean_vector &&vector_reference) noexcept:
            magnitude_{std::move(vector_reference.magnitude_)}, length_{vector_reference.length_} {
        vector_reference.length_ = 0;
    }

    euclidean_vector &euclidean_vector::operator=(const euclidean_vector &vector) {
        length_ = vector.length_;
        magnitude_ = std::make_unique<double[]>(length_);
        std::copy(vector.magnitude_.get(), vector.magnitude_.get() + length_, magnitude_.get());
        return *this;
    }

    auto euclidean_vector::operator=(euclidean_vector &&vector) -> euclidean_vector & {
        length_ = vector.length_;
        magnitude_ = std::move(vector.magnitude_);
        vector.length_ = 0;
        return *this;
    }

    auto euclidean_vector::operator[](int index) -> double & {
        if (index >= length_ or index < 0) {
            throw euclidean_vector_error("Index" + std::to_string(index) + " is out of bounds!\n");
        }
        return magnitude_[index];
    }

    auto euclidean_vector::operator[](int index) const -> const double & {
        if (index >= length_ or index < 0) {
            throw euclidean_vector_error("Index" + std::to_string(index) + " is out of bounds!\n");
        }
        return magnitude_[index];
    }

    auto euclidean_vector::operator+() -> euclidean_vector {
        return euclidean_vector(*this);
    }

    auto euclidean_vector::operator-() -> euclidean_vector {
        auto negated_vector = euclidean_vector(*this);
        std::for_each(negated_vector.magnitude_.get(), negated_vector.magnitude_.get() + negated_vector.length_,
                      [](double x) {
                          return -x;
                      });
        return negated_vector;
    }

    auto euclidean_vector::operator+=(const euclidean_vector &vector) -> euclidean_vector & {
        if (length_ != vector.length_) {
            throw euclidean_vector_error(
                    "Dimensions of LHS(" + std::to_string(length_) + ") and RHS (" + std::to_string(vector.length_) +
                    ") do not match\n");
        }
        auto index = 0;
        std::transform(magnitude_.get(), magnitude_.get() + length_, magnitude_.get(), [&](double x) {
            return x + vector[index++];
        });
        return *this;
    }

    auto euclidean_vector::operator-=(const euclidean_vector &vector) -> euclidean_vector & {
        if (length_ != vector.length_) {
            throw euclidean_vector_error(
                    "Dimensions of LHS(" + std::to_string(length_) + ") and RHS (" + std::to_string(vector.length_) +
                    ") do not match\n");
        }
        auto index = 0;
        std::transform(magnitude_.get(), magnitude_.get() + length_, magnitude_.get(), [&](double x) {
            return x - vector[index++];
        });
        return *this;
    }

    auto euclidean_vector::operator*=(double scale) -> euclidean_vector & {
        std::transform(magnitude_.get(), magnitude_.get() + length_, magnitude_.get(), [&](double x) {
            return x * scale;
        });
        return *this;
    }

    auto euclidean_vector::operator/=(double scale) -> euclidean_vector & {
        if (scale == 0) {
            throw euclidean_vector_error("Invalid vector division by 0");
        }
        std::transform(magnitude_.get(), magnitude_.get() + length_, magnitude_.get(), [&](double x) {
            return x / scale;
        });
        return *this;
    }

    euclidean_vector::operator std::vector<double>() const {
        auto vector = std::vector<double>(length_);
        std::copy(magnitude_.get(), magnitude_.get() + length_, vector.begin());
        return vector;
    }

    euclidean_vector::operator std::list<double>() const {
        auto list = std::list<double>(length_);
        std::copy(magnitude_.get(), magnitude_.get() + length_, list.begin());
        return list;
    }

    auto euclidean_vector::at(int index) const -> const double & {
        this[index];
    }

    auto euclidean_vector::at(int index) -> double & {
        return reinterpret_cast<double &>(this[index]);
    }

    auto euclidean_vector::dimensions() const -> int {
        return length_;
    }

    auto operator==(const euclidean_vector &vector1, const euclidean_vector &vector2) -> bool {
        return vector1.length_ == vector2.length_ &&
               std::equal(vector1.magnitude_.get(), vector1.magnitude_.get() + vector1.length_,
                          vector2.magnitude_.get(), vector2.magnitude_.get() + vector2.length_);
    }

    auto operator!=(const euclidean_vector &vector1, const euclidean_vector &vector2) -> bool {
        return !(vector1 == vector2);
    }

    auto operator+(const euclidean_vector &vector1, const euclidean_vector &vector2) -> euclidean_vector {
        auto sum_vector = euclidean_vector(vector1);
        sum_vector += vector2;
        return sum_vector;
    }

    auto operator-(const euclidean_vector &vector1, const euclidean_vector &vector2) -> euclidean_vector {
        auto sum_vector = euclidean_vector(vector1);
        sum_vector -= vector2;
        return sum_vector;
    }

    auto operator*(const euclidean_vector &vector, double scale) -> euclidean_vector {
        auto multiple_vector = euclidean_vector(vector);
        multiple_vector *= scale;
        return multiple_vector;
    }

    auto operator*(double scale, const euclidean_vector &vector) -> euclidean_vector {
        return vector * scale;
    }

    auto operator/(const euclidean_vector &vector, double scale) -> euclidean_vector {
        auto division_vector = euclidean_vector(vector);
        division_vector /= scale;
        return division_vector;
    }

    std::ostream &operator<<(std::ostream &os, const euclidean_vector &vector) {
        os << "[";
        for (int i = 0; i < vector.length_ - 1; ++i) {
            os << vector.magnitude_[i] << " ";
        }
        os << vector.magnitude_[vector.length_ - 1] << "]";
        return os;
    }

    auto euclidean_norm(euclidean_vector const &vector) -> double {
        auto found_cache = comp6771::cache.find(vector);
        if(found_cache != comp6771::cache.end()){
            return found_cache->second;
        }
        auto vector_casted = static_cast<std::vector<double>>(vector);
        auto euclidean_norm = std::sqrt(
                std::accumulate(vector_casted.begin(), vector_casted.end(), 0.0,
                                [](double sum, double x) { return sum + x * x; }));
        comp6771::cache.emplace(vector, euclidean_norm);
        return vector.dimensions() == 0 ? 0 : euclidean_norm;
    }

    auto unit(const euclidean_vector &vector) -> euclidean_vector {
        if (vector.dimensions() == 0) {
            throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit vector");
        }
        auto e_norm = euclidean_norm(vector);
        if (e_norm == 0) {
            throw euclidean_vector_error("euclidean_vector with zero euclidean normal does not have a unit vector");
        }
        return euclidean_vector(vector) / e_norm;
    }

    auto dot(euclidean_vector const &vector1, euclidean_vector const &vector2) -> double {
        if (vector1.dimensions() != vector2.dimensions()) {
            throw euclidean_vector_error(
                    "Dimensions of LHS(" + std::to_string(vector1.dimensions()) + ") and RHS (" +
                    std::to_string(vector2.dimensions()) +
                    ") do not match\n");
        }
        auto index = 0;
        auto casted_vector1 = static_cast<std::vector<double>>(vector1);
        auto casted_vector2 = static_cast<std::vector<double>>(vector2);
        return vector1.dimensions() == 0 ? 0 : std::accumulate(casted_vector1.begin(), casted_vector1.end(), 0,
                                                               [&](double sum, double value) {
                                                                   return sum + (value) * casted_vector2.at(index++);
                                                               });
//        return euclidean_vector(vector) / e_norm;
    }


} // namespace comp6771