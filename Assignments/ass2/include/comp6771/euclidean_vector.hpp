#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <iterator>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace comp6771 {
    class euclidean_vector_error : public std::runtime_error {
    public:
        explicit euclidean_vector_error(std::string const &what)
                : std::runtime_error(what) {}
    };

    class euclidean_vector {
    public:
        euclidean_vector() noexcept;

        explicit euclidean_vector(int) noexcept;

        euclidean_vector(int, double) noexcept;

        euclidean_vector(std::vector<double>::const_iterator,
                         std::vector<double>::const_iterator) noexcept;

        euclidean_vector(std::initializer_list<double>) noexcept;

        euclidean_vector(euclidean_vector const &) noexcept;

        euclidean_vector(euclidean_vector &&) noexcept;

        inline ~euclidean_vector() = default;

        auto operator=(euclidean_vector const &) noexcept -> euclidean_vector &;

        auto operator=(euclidean_vector &&) noexcept -> euclidean_vector &;

        auto operator[](int index) -> double &;

        auto operator[](int index) const -> const double &;

        auto operator+() const noexcept -> euclidean_vector;

        auto operator-() const noexcept -> euclidean_vector;

        auto operator+=(euclidean_vector const &) -> euclidean_vector &;

        auto operator-=(const euclidean_vector &vector) -> euclidean_vector &;

        auto operator*=(double) noexcept -> euclidean_vector &;

        auto operator/=(double) -> euclidean_vector &;

        explicit operator std::vector<double>() const noexcept;

        explicit operator std::list<double>() const noexcept;

        [[nodiscard]] auto at(int) const -> const double &;

        [[nodiscard]] auto at(int) -> double &;

        [[nodiscard]] auto dimensions() const noexcept -> int;

        friend auto operator==(euclidean_vector const &, euclidean_vector const &) noexcept -> bool;

        friend auto operator!=(euclidean_vector const &, euclidean_vector const &) noexcept -> bool;

        friend auto operator+(euclidean_vector const &, euclidean_vector const &) -> euclidean_vector;

        friend auto operator-(euclidean_vector const &, euclidean_vector const &) -> euclidean_vector;

        friend auto operator*(euclidean_vector const &, double) noexcept -> euclidean_vector;

        friend auto operator*(double, euclidean_vector const &) noexcept -> euclidean_vector;

        friend auto operator/(euclidean_vector const &, double) -> euclidean_vector;

        friend auto operator<<(std::ostream &os, euclidean_vector const &vector) noexcept
        -> std::ostream &;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        //                                                                                            //
        //                                                                                            //
        //                                EXTRA CACHE INTERNAL FUNCTIONS                              //
        //                                                                                            //
        //                                                                                            //
        ////////////////////////////////////////////////////////////////////////////////////////////////

        // i implemented this in the source since there is too much code + logic for a header
        void set_cached_norm() const noexcept;

        inline auto check_cached_norm() const noexcept -> double {
            return euclidean_norm_;
        }

    private:
        // ass2 spec requires we use double[]
        // NOLINTNEXTLINE(modernize-avoid-c-arrays)
        std::unique_ptr<double[]> magnitude_;
        int length_;
        // since euclidean norm is always > 0 since its the sqrt of the sum of squares, we just use -1
        // as the default
        mutable double euclidean_norm_;
    };

    auto euclidean_norm(euclidean_vector const &vector) noexcept -> double;

    auto unit(euclidean_vector const &vector) -> euclidean_vector;

    auto dot(euclidean_vector const &vector1, euclidean_vector const &vector2) -> double;

} // namespace comp6771

namespace comp6771_helpers {
    auto convert_to_vector_manually(comp6771::euclidean_vector vector) -> std::vector<double>;
} // namespace comp6771_helpers

#endif // COMP6771_EUCLIDEAN_VECTOR_HPP