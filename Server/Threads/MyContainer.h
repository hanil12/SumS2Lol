#pragma once

#include "Allocator.h"

#include <vector>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>

// Multi Thread Data Structure
#include "Lock_Based_Stack.h"

using namespace std;

template <typename T>
using Vector = std::vector<T, STLAllocator<T>>;

template <typename KTy, typename VTy>
using UMap = std::unordered_map<KTy, VTy, hash<KTy>, equal_to<KTy>, STLAllocator<pair<const KTy,VTy>>>;

template<typename KTy, typename VTy>
using Map = std::map<KTy, VTy, less<KTy>, STLAllocator<pair<const KTy, VTy>>>;

template<typename T, typename Pred = less<T>>
using Set = std::set<T, less<T>, STLAllocator<T>>;

template<typename T>
using Deque = std::deque<T, STLAllocator<T>>;

template <typename T>
using Stack = std::stack<T, Deque<T>>;

template <typename T>
using Queue = std::queue<T, Deque<T>>;

template <typename T, typename Container = Vector<T>, typename Pred = less<typename Container::value_type>>
using PriorityQueue = std::priority_queue<T, Vector<T>, Pred>;

using String = basic_string<char, char_traits<char>, STLAllocator<char>>;
using WString = basic_string<wchar_t, char_traits<wchar_t>, STLAllocator<wchar_t>>;