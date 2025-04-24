#include <tuple>
#include <iterator>


namespace ECS {
    template <class... Containers>
    class ZipperIterator {
    template <class Container>
    using iterator_t = decltype(std::declval<Container>().begin()); // return begin iterator type of passed container

    template <class Container> // iterator reference
    using it_reference_t = typename iterator_t<Container>::reference;

    public:
        using value_type = std::tuple<it_reference_t<Containers>&...>; // std::tuple of references to componants sparse arrays
        using reference = value_type;
        using pointer = void;  // no ptr for it
        using difference_type = size_t; 
        using iterator_category = std::input_iterator_tag;  // iterator type indication
        using iterator_tuple = std::tuple<iterator_t<Containers>...>;  // iterators tuple for each container

        // If we want ZipperIterator to be built by zipper only.
        // friend containers::zipper<Containers...>;

        ZipperIterator(iterator_tuple const &it_tuple, size_t max) : _current(it_tuple), _max(max), _idx(0) {}
        ZipperIterator(ZipperIterator const &z) : _current(z._current), _max(z._max), _idx(z._idx) {}

        ZipperIterator& operator++() {
            if (_idx < _max) {
                _idx++;
                incr_all(std::make_index_sequence<sizeof...(Containers)>{});
            }
            return *this;
        }

        ZipperIterator operator++(int) {
            ZipperIterator temp = *this;  // current it copy
            while (_idx < _max) {
                _idx++;
                incr_all(std::make_index_sequence<sizeof...(Containers)>{});
            }
            return temp;  // return copy before ++
        }

        value_type operator*() {
            return to_value(_seq);
        }
        value_type operator->() {
            return to_value(_seq);
        }

        friend bool operator==(ZipperIterator const &lhs, ZipperIterator const& rhs) {
            return lhs._idx == rhs._idx; // check if lhs index == rhs index (return true of false based on this ope)
        }

        friend bool operator !=(ZipperIterator const &lhs, ZipperIterator const& rhs) {
            return !(lhs == rhs); // it value check, if not equal, true is returned
        }

    private:
        // Increment every iterator at the same time. It also skips to the next
        // value if one of the pointed to std::optional does not contains a value.
        template <size_t... Is>
        void incr_all(std::index_sequence<Is...>) {
            (..., ++std::get<Is>(_current));  // increment all iterators in the tuple
        }
        
        // check if every std::optional are set.
        template<size_t... Is>
        bool all_set(std::index_sequence<Is...>) {
            size_t indices[] = {Is...};  // indices for each container
            bool result = true;

            for (size_t i = 0; i < sizeof...(Is); ++i) {
                if (!std::get<indices[i]>(_current).has_value()) {  // check if the value at _current[indices[i]] is set
                    result = false;
                    break;
                }
            }
            return result;
        }

        // return a tuple of references to components.
        template<size_t... Is>
        value_type to_value(std::index_sequence<Is...>) {
            return std::tuple<it_reference_t<Containers>...>(
                (*std::get<Is>(_current))...
            );
        }
       
        private: 
        iterator_tuple _current;
        size_t _max;
        size_t _idx;
        static constexpr std::index_sequence_for<Containers...> _seq{};
};
};
