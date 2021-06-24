#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <iterator>
#include <vector>
#include <list>
#include <unordered_map>

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

        auto operator=(euclidean_vector const &) -> euclidean_vector &;

        auto operator=(euclidean_vector &&) -> euclidean_vector &;

        auto operator[](int index) -> double &;

        auto operator[](int index) const -> const double &;

        auto operator+() -> euclidean_vector;

        auto operator-() -> euclidean_vector;

        auto operator+=(euclidean_vector const &) -> euclidean_vector &;

        auto operator-=(const euclidean_vector &vector) -> euclidean_vector &;

        auto operator*=(double) -> euclidean_vector &;

        auto operator/=(double) -> euclidean_vector &;

        explicit operator std::vector<double>() const;

        explicit operator std::list<double>() const;

        [[nodiscard]] auto at(int) const -> const double &;

        [[nodiscard]] auto at(int) -> double &;

        [[nodiscard]] auto dimensions() const -> int;

        friend auto operator==(euclidean_vector const &, euclidean_vector const &) -> bool;

        friend auto operator!=(euclidean_vector const &, euclidean_vector const &) -> bool;

        friend auto operator+(euclidean_vector const &, euclidean_vector const &) -> euclidean_vector;

        friend auto operator-(euclidean_vector const &, euclidean_vector const &) -> euclidean_vector;

        friend auto operator*(euclidean_vector const &, double) -> euclidean_vector;

        friend auto operator*(double, euclidean_vector const &) -> euclidean_vector;

        friend auto operator/(euclidean_vector const &, double) -> euclidean_vector;

        friend std::ostream &operator<<(std::ostream &os, euclidean_vector const &vector);

        template<typename EuclideanVector>
        struct container_hash {
            std::size_t operator()(euclidean_vector const &vector) const {
                size_t h = 7;
                h = 31 * h + std::hash<int>{}(vector.length_);
                for(auto i = vector.magnitude_.get(); i != vector.magnitude_.get() + vector.length_; ++i){
                    h = 31 * h + std::hash<double>{}(*i);
                }
                return h;
            }
        };
        inline static auto cache = std::unordered_map<euclidean_vector, double, container_hash<euclidean_vector>>();

    private:
        // ass2 spec requires we use double[]
        // NOLINTNEXTLINE(modernize-avoid-c-arrays)
        std::unique_ptr<double[]> magnitude_;
        int length_;
        //int size;
        // TODO more if needed
        template<typename> friend struct container_hash;
    };
    // hash method used from the default java hashcode (used in previous assignments)
    // reference: https://www.baeldung.com/java-hashcode




    auto euclidean_norm(euclidean_vector const &vector) -> double;

    auto unit(euclidean_vector const &vector) -> euclidean_vector;

    auto dot(euclidean_vector const &vector1, euclidean_vector const &vector2) -> double;

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
