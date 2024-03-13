#include <map>
#include <set>
#include <list>
#include <array>
#include <deque>
#include <string>
#include <vector>
#include <cassert>
#include <utility>
#include <string_view>
#include <forward_list>
#include <unordered_map>
#include <unordered_set>
#include <initializer_list>

#include "sos/predicates/is_empty.hpp"


using namespace std::string_literals;
using namespace std::string_view_literals;

using sos::predicates::is_empty, sos::predicates::is_not_empty;


static void is_empty_succeeds_with_empty_string() noexcept {
    assert(        is_empty(""s));
    assert(not is_not_empty(""s));

    static_assert(        is_empty(""sv));
    static_assert(not is_not_empty(""sv));
}

static consteval void is_empty_succeeds_with_empty_initializer_list() noexcept {
    static_assert(        is_empty(std::initializer_list<int>{}));
    static_assert(not is_not_empty(std::initializer_list<int>{}));
}

static void is_empty_succeeds_with_empty_sequence_container() noexcept {
    static constexpr std::vector<int> vec;
    static_assert(        is_empty(vec));
    static_assert(not is_not_empty(vec));

    static constexpr std::array<int, 0> array;
    static_assert(        is_empty(array));
    static_assert(not is_not_empty(array));

    std::list<int> list;
    assert(        is_empty(list));
    assert(not is_not_empty(list));

    std::deque<int> deque;
    assert(        is_empty(deque));
    assert(not is_not_empty(deque));

    std::forward_list<int> flist;
    assert(        is_empty(flist));
    assert(not is_not_empty(flist));
}

static void is_empty_succeeds_with_empty_associative_container() noexcept {
    std::set<int> set;
    assert(        is_empty(set));
    assert(not is_not_empty(set));

    std::multiset<int> mset;
    assert(        is_empty(mset));
    assert(not is_not_empty(mset));

    std::map<int, int> map;
    assert(        is_empty(map));
    assert(not is_not_empty(map));

    std::multimap<int, int> mmap;
    assert(        is_empty(mmap));
    assert(not is_not_empty(mmap));
}

static void is_empty_succeeds_with_empty_unordered_associative_container() noexcept {
    std::unordered_set<int> uset;
    assert(        is_empty(uset));
    assert(not is_not_empty(uset));

    std::unordered_multiset<int> umset;
    assert(        is_empty(umset));
    assert(not is_not_empty(umset));

    std::unordered_map<int, int> umap;
    assert(        is_empty(umap));
    assert(not is_not_empty(umap));

    std::unordered_multimap<int, int> ummap;
    assert(        is_empty(ummap));
    assert(not is_not_empty(ummap));
}


static void is_empty_fails_with_populated_string() noexcept {
    assert(not is_empty("string"s));
    assert(is_not_empty("string"s));

    static_assert(not is_empty("string_view"sv));
    static_assert(is_not_empty("string_view"sv));
}

static consteval void is_empty_fails_with_positive_extent_array() noexcept {
    constexpr int array[10]{};
    static_assert(not is_empty(array));
    static_assert(is_not_empty(array));

    constexpr int matrix[10][10]{};
    static_assert(not is_empty(matrix));
    static_assert(is_not_empty(matrix));
}

static consteval void is_empty_fails_with_populated_initializer_list() noexcept {
    static_assert(not is_empty(std::initializer_list<int>{1}));
    static_assert(is_not_empty(std::initializer_list<int>{1}));
}

static void is_empty_fails_with_populated_sequence_container() noexcept {
    static_assert(not is_empty(std::vector{1, 2, 3}));
    static_assert(is_not_empty(std::vector{1, 2, 3}));

    static constexpr std::array array{1, 2, 3};
    static_assert(not is_empty(array));
    static_assert(is_not_empty(array));

    std::list list{1, 2, 3};
    assert(not is_empty(list));
    assert(is_not_empty(list));

    std::deque deque{1, 2, 3};
    assert(not is_empty(deque));
    assert(is_not_empty(deque));

    std::forward_list flist{1, 2, 3};
    assert(not is_empty(flist));
    assert(is_not_empty(flist));
}

static void is_empty_fails_with_populated_associative_container() noexcept {
    std::set set{0};
    assert(not is_empty(set));
    assert(is_not_empty(set));

    std::multiset mset{0};
    assert(not is_empty(mset));
    assert(is_not_empty(mset));

    std::map map{std::pair{0, 0}};
    assert(not is_empty(map));
    assert(is_not_empty(map));

    std::multimap mmap{std::pair{0, 0}};
    assert(not is_empty(mmap));
    assert(is_not_empty(mmap));
}

static void is_empty_fails_with_populated_unordered_associative_container() noexcept {
    std::unordered_set uset{-1};
    assert(not is_empty(uset));
    assert(is_not_empty(uset));

    std::unordered_multiset umset{-1};
    assert(not is_empty(umset));
    assert(is_not_empty(umset));

    std::unordered_map umap{std::pair{-1, 1U}};
    assert(not is_empty(umap));
    assert(is_not_empty(umap));

    std::unordered_multimap ummap{std::pair{-1, 1U}};
    assert(not is_empty(ummap));
    assert(is_not_empty(ummap));
}


int main() {
    is_empty_succeeds_with_empty_string();
    is_empty_succeeds_with_empty_initializer_list();
    is_empty_succeeds_with_empty_sequence_container();
    is_empty_succeeds_with_empty_associative_container();
    is_empty_succeeds_with_empty_unordered_associative_container();

    is_empty_fails_with_populated_string();
    is_empty_fails_with_positive_extent_array();
    is_empty_fails_with_populated_initializer_list();
    is_empty_fails_with_populated_sequence_container();
    is_empty_fails_with_populated_associative_container();
    is_empty_fails_with_populated_unordered_associative_container();
}
