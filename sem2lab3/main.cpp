#include <iostream>
#include <vector>
#include "CircBuffer.h"
#include "algo.h"

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


bool is_odd(int a) {
    return a % 2;
}

int main() {
    std::vector<std::string> test_results;

    // test 1
    std::vector<int> my_vec = {2, 9, 8, 11, 4};
    RingBuffer<int> buf(my_vec.begin(), my_vec.end());
    buf.pop_front();

    add_test_result(test_results, buf[0] == 9);

    for (int i = 0; i < 10; ++i) {
        buf.push_back(i);
    }
    for (int i = 0; i < 5; ++i) {
        buf.pop_back();
    }

    // test 2
    add_test_result(test_results, buf[7] == 3);

    // test 3
    add_test_result(test_results, *buf.begin() == 9);

    // test 4
    add_test_result(test_results, buf.size() == 9);

    // test 5
    std::sort(buf.begin(), buf.end());

    add_test_result(test_results, buf[0] == 0);


    // test 6
    std::vector<int> my_vec_2 = {1, 2, 3, 4, 5};
    RingBuffer<int> bf(my_vec_2.begin(), my_vec_2.end());
    bf.pop_back();
    auto it_ = --bf.begin();

    add_test_result(test_results, *it_ == 4);


    // test 7
    it_ -= 2;
    add_test_result(test_results, *it_ == 2);

    // test 8
    it_ += 3;
    add_test_result(test_results, *it_ == 1);


    // test 9
    std::vector<int> my_vect = {1, 4, 3, 5, 6, 7};
    RingBuffer<int> n_buf(my_vect.begin(), my_vect.end());

    add_test_result(test_results, algo::isPalindrome(n_buf.begin(), n_buf.end(), is_odd) == 1);

    std::sort(n_buf.begin(), n_buf.end(), std::greater<int>());

    for (int i = 0; i < n_buf.size(); i++) {
        std::cout << n_buf[i] << ' ';
    }

    print_test_results(test_results);
    return 0;
}