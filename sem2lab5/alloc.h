#include <iostream>
#include <exception>
#include <memory>
#include "BucketManager.h"


template<typename T, int BucketSize = 1024, int BucketCount = 1024>
class PoolAllocator {
public:
    typedef size_t size_type;
    typedef T *pointer;
    typedef T value_type;

    template<typename U>
    struct rebind {
        typedef PoolAllocator<U, BucketSize, BucketCount> other;
    };

    pointer buffer;             // // pointer to begin of allocated memory
    size_type num_of_buckets;   // num of buckets
    size_t size_of_bucket;      // size_of_bucket of bucket
    size_t num_of_free_buckets{}; // num_of_free_buckets
    BucketManager<value_type> *bucketManager;

    explicit PoolAllocator(size_type BS = BucketSize, size_type BC = BucketCount) :
            num_of_buckets(BC), num_of_free_buckets(BC), size_of_bucket(BS),
            bucketManager(new BucketManager<value_type>(BC)),
            buffer(static_cast<pointer>(calloc(BC, BS))) {
        auto buckets_curr = static_cast<pointer *>(malloc(BC * sizeof(pointer)));
        for (int i = 0; i < num_of_buckets; ++i) {
            buckets_curr[i] = buffer + i * size_of_bucket / sizeof(value_type);
        }
        bucketManager->buckets = buckets_curr;
    }

    template<typename U>
    explicit PoolAllocator(const PoolAllocator<U, BucketSize, BucketCount> &Al):
            buffer(reinterpret_cast<pointer>(Al.buffer)),
            num_of_free_buckets(Al.num_of_free_buckets),
            size_of_bucket(Al.size_of_bucket),
            num_of_buckets(Al.num_of_buckets),
            bucketManager(reinterpret_cast<BucketManager<T> *>(Al.bucketManager)) {}


    PoolAllocator(const PoolAllocator &alloc) :
            buffer(alloc.buffer),
            num_of_free_buckets(alloc.num_of_free_buckets),
            size_of_bucket(alloc.size_of_bucket),
            num_of_buckets(alloc.num_of_buckets),
            bucketManager(alloc.bucketManager) {}

    void check_correct_size(size_type n) {
        if (n > size_of_bucket) {
            throw std::invalid_argument(" request is bigger than size_of_bucket of chunk ");
        }
    }

    bool exists_free_bucket() {
        return num_of_free_buckets > 0;
    }

    pointer allocate(size_type n) {
        check_correct_size(n);

        if (exists_free_bucket()) {
            num_of_free_buckets -= 1;
            return bucketManager->getBucket();
        }
    }

    void deallocate(pointer p, size_type n) noexcept {
        num_of_free_buckets += 1;
        bucketManager->establishBucket(p);
    }

    ~PoolAllocator() = default;
};