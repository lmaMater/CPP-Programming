#include <stack>

namespace algo {
    template<typename ForwardIterator, typename Func>
    bool all(ForwardIterator first, ForwardIterator last, Func f) {
        bool ans = true;
        while (first != last) {
            if (!f(*first))
                ans = false;
            first++;
        }
        return ans;
    }

    template<typename ForwardIterator, typename Func>
    bool any(ForwardIterator first, ForwardIterator last, Func f) {
        bool ans = true;
        while (first != last) {
            if (f(*first))
                ans = false;
            first++;
        }
        return ans;
    }

    template<typename ForwardIterator, typename Func>
    bool none(ForwardIterator first, ForwardIterator last, Func f) {
        bool ans = true;
        while (first != last) {
            if (f(*first))
                ans = false;
            first++;
        }
        return ans;
    }

    template<typename ForwardIterator, typename Func>
    bool contains(ForwardIterator first, ForwardIterator last, Func f) {
        bool exists = false;
        while (first != last) {
            if (f(*first)) {
                if (exists)
                    return false;
                exists = true;
            }
            first++;
        }
        return exists;
    }

    template<typename ForwardIterator, typename Func>
    bool is_sorted(ForwardIterator first, ForwardIterator last, Func f) {
        bool ans = true;
        auto curr = f(*first);
        while (first != last) {
            if (f(*first) < curr)
                ans = false;
            curr = f(*first);
            first++;
        }
        return ans;
    }


    template<typename ForwardIterator, typename T>
    ForwardIterator findBackward(ForwardIterator first, ForwardIterator last, T val) {
        ForwardIterator ans = last;
        while (first != last) {
            if (*first == val)
                ans = first;
            first++;
        }

        return ans;
    }

    template<class ForwardIterator, typename Func>
    bool isPalindrome(const ForwardIterator first, const ForwardIterator last, Func f) {
        std::stack<ForwardIterator> st;
        bool ans = true;

        ForwardIterator tmp = first;
        for (ForwardIterator it = first; it != last; ++it) {
            st.push(it);
        }
        while (tmp != last) {
            if (f(*tmp) != f(*st.top()))
                ans = false;
            st.pop();
            tmp++;
        }

        return ans;
    }

}
