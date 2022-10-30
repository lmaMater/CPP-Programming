#include "alloc.h"
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <unordered_map>
#include <ctime>


void add_test_result(std::vector<std::string> &results, bool res) {
    if (res) {
        results.emplace_back("ok");
    } else {
        results.emplace_back("wrong");
    }
}

void print_test_results(std::vector<std::string> &results) {
    std::cout << "-- test results --\n";
    for (int i = 0; i < results.size(); ++i) {
        std::cout << "test " << i + 1 << ": " << results[i] << '\n';
    }
}

template<class Alloc>
int count_time(std::deque<int, Alloc> list1) {
    int n = 5000, iters = 1000;
    int start_time = clock();
    for (int j = 0; j < iters; ++j) {
        for (int i = 0; i < n; ++i) {
            list1.push_back(i);
            list1.push_back(i);
            list1.pop_back();
            list1.pop_back();
        }
        for (int i = 0; i < n; ++i) {
            list1.push_back(i);
        }
        for (int i = 0; i < n; ++i) {
            list1.pop_back();
        }
    }
    return clock() - start_time;
}


struct Point {
    int x;
    int y;

    bool operator==(const Point &a) const {
        return (a.x == x && a.y == y);
    }
};


int main() {
    std::vector<std::string> test_relults;

// unordered_map
    std::unordered_map<int, Point, std::hash<int>, std::equal_to<>, PoolAllocator<std::pair<int, Point>>> m;
    for (int i = 0; i < 10; ++i) {
        m.insert({i, {i, i}});
    }

    // test 1
    add_test_result(test_relults, m[5] == Point{5, 5});

    // test 2
    add_test_result(test_relults, m.find(15) == m.end());

// map
    std::map<int, int, std::less<>, PoolAllocator<std::pair<int, int>>> my;
    for (int i = 5; i < 16; ++i) {
        my.insert({i, i});
    }
    for (int i = 1; i < 10; ++i) {
        my.insert({i, i});
    }

    // test 3
    add_test_result(test_relults, my.find(6) != my.end());

    // test 4
    add_test_result(test_relults, my.size() == 15);

// vector
    std::vector<int, PoolAllocator<int>> a;
    a.reserve(10);
    for (int i = 0; i < 10; ++i)
        a.push_back(i);
    for (int i = 0; i < 10; ++i)
        a.pop_back();

    // test 5
    add_test_result(test_relults, a.empty());

    // test 6
    for (int i = 0; i < 10; ++i)
        a.push_back(i);

    add_test_result(test_relults, a[6] == 6);

// deque
    std::deque<int, PoolAllocator<int>> deq;
    for (int i = 0; i < 1000; ++i) deq.push_back(i);
    for (int i = 0; i < 100; ++i) deq.pop_front();

    // test 7
    add_test_result(test_relults, deq[0] == 100);

    // test 8
    add_test_result(test_relults, deq.size() == 900);

// list
    std::list<int> arr;
    for (int i = 0; i < 10; ++i)
        arr.push_back(i);

    for (int i = 0; i < 9; ++i)
        arr.pop_back();

    // test 9
    add_test_result(test_relults, arr.size() == 1);

// test time
    std::deque<int, std::allocator<int>> list1;
    std::cout << "standard allocator - " << count_time(list1) << '\n';

    std::deque<int, PoolAllocator<int>> list2;
    std::cout << "Custom Allocator - " << count_time(list2) << "\n\n";

    print_test_results(test_relults);

    return 0;
}