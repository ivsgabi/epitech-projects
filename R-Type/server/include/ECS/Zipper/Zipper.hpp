#include "ZipperIterator.hpp"

namespace ECS {
    template <class... Containers>
    class Zipper {
    public:
    using iterator = ZipperIterator<Containers...>;
    using iterator_tuple = typename iterator::iterator_tuple;

    Zipper(Containers &... cs) : _begin(std::make_tuple(cs.begin()...)),
       _end(_compute_end(cs...)),            
       _size(_compute_size(cs...)) {}

    iterator begin() {
        return iterator(_begin, _size);
    }

    iterator end() {
        return iterator(_end, _size);
    }

    private:
    // helper function to know the maximum index of our iterators.
     static size_t _compute_size(Containers &... containers) {
        size_t max_size = 0;

        // each container parcouring and update max size
        auto update_max_size = [&](auto &container) {
            max_size = std::max(max_size, container.size());
        };
        // give max size to all containers
        (update_max_size(containers), ...);
        return max_size;
    }
    // helper function to compute an iterator_tuple that will allow us to build our end iterator.
    static iterator_tuple _compute_end(Containers &... containers) {
        // get ends of all containers
        return std::make_tuple(containers.end()...);
    }

    iterator_tuple _begin;
    iterator_tuple _end;
    size_t _size;
};
};