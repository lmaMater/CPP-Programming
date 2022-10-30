#include <map>
#include <stack>


template<typename T>
struct BucketManager {
    typedef T* pointer;
    typedef T value_type;

    std::map<pointer, std::size_t> dict;
    pointer *buckets;
    bool *occupancy;
    size_t *currFreeBucket;
    size_t count;

    explicit BucketManager(size_t count = 0) : count(count) {
        occupancy = static_cast<bool *>(calloc(count, sizeof(bool)));
        buckets = static_cast<pointer *>(malloc(count * sizeof(pointer)));

        for (int i = 0; i < count; ++i) {
            dict[buckets[i]] = i;
        }

        currFreeBucket = new size_t(0);
    }

    template<typename U>
    explicit BucketManager(const BucketManager<U> &manager):
            count(manager.count),
            occupancy(manager.occupancy),
            dict(manager.dict),
            currFreeBucket(manager.currFreeBucket),
            buckets(reinterpret_cast<pointer>(manager.buckets)) {}

    BucketManager(const BucketManager &manager) :
            count(manager.count),
            occupancy(manager.occupancy),
            dict(manager.dict),
            currFreeBucket(manager.currFreeBucket),
            buckets(manager.buckets) {}

    ~BucketManager() = default;

    bool ability_get_bucket() {
        if ((*currFreeBucket) >= count || occupancy[*currFreeBucket]) throw std::invalid_argument("Not enough memory");
    }

    bool ability_establish_bucket() {
        if (!*currFreeBucket || occupancy[*currFreeBucket]) throw std::invalid_argument("Not enough memory");
    }

    pointer getBucket() {
        auto new_bucket = find_free_bucket();
        if (new_bucket == nullptr) {
            throw std::invalid_argument("Not enough memory");
        }
        ability_get_bucket(); // out of bucket list
        occupancy[*currFreeBucket] = true;
        dict[buckets[*currFreeBucket]] = *currFreeBucket;
        return (buckets[(*currFreeBucket)++]);
    }

    void establishBucket(pointer p) {
        ability_establish_bucket(); // we should decrement
        buckets[--(*currFreeBucket)] = p;
        occupancy[*currFreeBucket] = false;
        dict[p] = *currFreeBucket;
    }

    pointer find_free_bucket() {
        for (int i = 0; i < count; ++i) {
            if (!occupancy[i]) {
                return buckets[i];
            }
        }
    }
};


