#include <algorithm>
#include <iterator>


template<typename T, class _alloc = std::allocator<T>>
class RingBuffer {

public:
    using value_type = T;
    using allocator_type = _alloc;

    using pointer = typename std::allocator_traits<allocator_type>::pointer;
    using size_type = typename std::allocator_traits<allocator_type>::size_type;
    using difference_type = typename std::allocator_traits<allocator_type>::difference_type;


    explicit RingBuffer(const size_type &curr_count = 0, value_type const &val = value_type(),
                        const allocator_type &Al = allocator_type()) :
            begin_of_elems(0), end_of_elems(curr_count + 1), total_volume(curr_count),
            reserved_memory(curr_count * 2 + 31),
            currentAlloc(Al),
            ptr_to_begin(std::allocator_traits<allocator_type>::allocate(currentAlloc, reserved_memory)) {
        if (check_correct_end(end_of_elems) && check_orientation(begin_of_elems, end_of_elems)) {
            for (size_type i = 1; i < end_of_elems; i++)
                manage_memory(currentAlloc, ptr_to_begin + i, val);
        }
    }

    template<class BidirectionalIterator>
    explicit RingBuffer(BidirectionalIterator first_iter, BidirectionalIterator last_iter,
                        const allocator_type &Al = allocator_type()) :
            total_volume(last_iter - first_iter), reserved_memory((last_iter - first_iter) * 2 + 31), begin_of_elems(0),
            end_of_elems(last_iter - first_iter + 1), currentAlloc(Al),
            ptr_to_begin(
                    std::allocator_traits<allocator_type>::allocate(currentAlloc, (last_iter - first_iter) * 2 + 31)) {
        if (!check_orientation(begin_of_elems, end_of_elems)) {
            swap(begin_of_elems, end_of_elems);
        }
        if (check_correct_end(end_of_elems)) {
            for (size_type i = 1; first_iter != last_iter; ++i, ++first_iter)
                manage_memory(currentAlloc, ptr_to_begin + i, *first_iter);
        }
    }

    void manage_memory(allocator_type CurrentAlloc, pointer ptr, value_type const &val = value_type()) {
        std::allocator_traits<allocator_type>::construct(CurrentAlloc, ptr, val);
    }

    void destroy() {
        if (!empty()) {
            for (size_type i = 0; i < total_volume; ++i)
                std::allocator_traits<allocator_type>::destroy(currentAlloc, ptr_to_begin + i);
        }
    }

    template<class ForwardIterator>
    void swap(ForwardIterator &begin, ForwardIterator &end) {
        ForwardIterator &tmp = begin;
        begin = end;
        end = tmp;
    }

    bool check_correct_end(const size_type &end) {
        return (end >= 0);
    }

    bool check_correct_index(size_type index) {
        return index >= 0;
    }

    bool check_orientation(const size_type &begin, const size_type &end) {
        return begin <= end;
    }

    size_type shift_by_index(size_type index) {
        return (begin_of_elems + index + 1) % reserved_memory;
    }

    size_type increment_in_ring(size_type elem) {
        if (check_correct_index(elem))
            return (++elem) % reserved_memory;
    }

    size_type decrement_in_ring(size_type elem) {
        if (check_correct_index(elem)) {
            if (elem) {
                return --elem;
            } else {
                return reserved_memory - 1;
            }
        }
    }

    size_type size() {
        if (total_volume >= 0) return total_volume;

        return 0;
    }

    void push_back(value_type const &val) {
        total_volume++;
        if (total_volume >= reserved_memory) {
            this->resize(reserved_memory * 3 + 1);
        }

        manage_memory(currentAlloc, ptr_to_begin + end_of_elems, val);
        end_of_elems = increment_in_ring(end_of_elems);
    }

    void push_front(value_type const &curr_value) {
        total_volume++;
        if (total_volume >= reserved_memory) {
            this->resize(reserved_memory * 3 + 1);
        }

        manage_memory(currentAlloc, ptr_to_begin + end_of_elems, curr_value);
        begin_of_elems = decrement_in_ring(begin_of_elems);
    }

    void pop_back() {
        if (this->empty()) return;

        end_of_elems = decrement_in_ring(end_of_elems);
        total_volume--;
    }

    class circIterator;

    circIterator begin() {
        return circIterator(ptr_to_begin, total_volume, reserved_memory, 0, increment_in_ring(begin_of_elems));
    }

    circIterator end() {
        return circIterator(ptr_to_begin, total_volume, reserved_memory, total_volume,
                            increment_in_ring(begin_of_elems));
    }

    void pop_front() {
        if (this->empty()) return;

        total_volume--;
        begin_of_elems = increment_in_ring(begin_of_elems);
    };

    bool empty() {
        return !total_volume;
    }

    value_type &operator[](size_type _index) {
        if (check_correct_index(_index)) {
            return *(ptr_to_begin + shift_by_index(_index));
        }
    }

    ~RingBuffer() {
        destroy();
        std::allocator_traits<allocator_type>::deallocate(currentAlloc, ptr_to_begin, reserved_memory);
    }

private:
    size_type total_volume;     // num of elements
    size_type reserved_memory;  // reserved memory
    size_type begin_of_elems;
    size_type end_of_elems;
    pointer ptr_to_begin;       // to begin_of_elems
    allocator_type currentAlloc;

    void resize(size_type new_size) {
        ptr_to_begin = std::allocator_traits<allocator_type>::allocate(currentAlloc, new_size);

        for (size_type i = 0; i < this->size(); ++i)
            manage_memory(currentAlloc, ptr_to_begin + i, (*this)[i]);

        begin_of_elems = new_size - 1;
        end_of_elems = this->size();
        reserved_memory = new_size;
    }

};


template<typename Ty, class Alloc>
class RingBuffer<Ty, Alloc>::circIterator {
private:
    pointer arrPointer;
    size_type total_size;
    size_type totalVolume;
    size_type shift;
    size_type begin_of_elems;

public:
    using value_type = RingBuffer::value_type;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = RingBuffer::difference_type;
    using pointer = RingBuffer::pointer;
    using reference = RingBuffer::value_type &;

    circIterator(pointer ptr_to_data, size_type new_volume, size_type new_total_size, size_type new_shift,
                 size_type begin) :
            arrPointer(ptr_to_data),
            total_size(new_total_size),
            totalVolume(new_volume),
            shift(new_shift),
            begin_of_elems(begin) {};

    circIterator(const circIterator &CircIter) :
            arrPointer(CircIter.arrPointer),
            total_size(CircIter.total_size),
            shift(CircIter.shift),
            begin_of_elems(CircIter.begin_of_elems),
            totalVolume(CircIter.totalVolume) {};

    bool empty() {
        return !totalVolume;
    }

    size_type get_curr_elem() {
        if (this->empty())
            return 0;

        return (begin_of_elems + (shift % totalVolume)) % total_size;
    }

    pointer operator->() const {
        return arrPointer + get_curr_elem();
    }

    reference operator*() const {
        if (totalVolume >= 0) {
            size_type add = begin_of_elems + (shift % totalVolume);
            return *(arrPointer + add % total_size);
        }
    }

    void decrement_this() {
        *this -= 1;
    }

    void increment_this() {
        ++shift;
    }

    size_type increment_shift(size_type elem) {
        return (shift + elem) % totalVolume;
    }

    size_type decrement_shift(difference_type elem) {
        if (shift < elem)
            return totalVolume - (elem % totalVolume);
        else
            return (shift - elem) % totalVolume;
    }

    size_type num_of_pos() {
        return totalVolume + 1;
    }

    difference_type difference_for_p(size_type first, size_type second) {
        return first - second;
    }

    circIterator& operator++() {
        increment_this();
        return *this;
    }

    circIterator& operator--() {
        decrement_this();
        return *this;
    }

    circIterator& operator++(int) {
        increment_this();
        return *this;
    }

    circIterator operator--(int) {
        decrement_this();
        return *this;
    }

    circIterator &operator+=(difference_type curr_shift) {
        shift = increment_shift(curr_shift);
        return *this;
    }

    circIterator &operator-=(difference_type curr_shift) {
        shift = decrement_shift(curr_shift);
        return *this;
    }

    circIterator operator-(difference_type curr_shift) const {
        return circIterator(*this) -= curr_shift;
    }

    difference_type operator-(const circIterator _Right) const {
        auto first = this->shift % (totalVolume + 1);
        auto second = _Right.shift % (totalVolume + 1);
        return first - second;
    }

    reference operator[](difference_type index) const {
        return *(*this + index);
    }

    circIterator operator+(difference_type curr_shift) const {
        return circIterator(*this) += curr_shift;
    }

    bool operator>(const circIterator &it) const {
        return shift > it.shift;
    }

    bool operator<(const circIterator &it) const {
        return shift < it.shift;
    }

    bool operator>=(const circIterator &it) const {
        return shift >= it.shift;
    }

    bool operator<=(const circIterator &it) const {
        return shift <= it.shift;
    }

    bool operator!=(const circIterator &it) const {
        return shift != it.shift;
    }

    bool operator==(const circIterator &it) const {
        return shift == it.shift;
    }
};

