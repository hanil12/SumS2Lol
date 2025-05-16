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
using TArray = std::vector<T, STLAllocator<T>>;

template <typename KTy, typename VTy>
using TMap = std::unordered_map<KTy, VTy>;

template<typename KTy, typename VTy>
using TRedBlackTree = std::map<KTy, VTy>;

template<typename T, typename Pred = less<T>>
using Set = std::set<T>;

template <typename T>
using Atomic = std::atomic<T>;

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T>
using WeakPtr = std::weak_ptr<T>;