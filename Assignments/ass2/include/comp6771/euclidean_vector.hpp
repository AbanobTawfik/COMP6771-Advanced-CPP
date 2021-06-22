#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <string>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// TODO
	private:
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
		// TODO more if needed
	};
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
