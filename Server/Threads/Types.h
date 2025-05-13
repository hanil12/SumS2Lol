#pragma once

using int8			= __int8;
using int16			= __int16;
using int32			= int;
using int64			= __int64;

using uint8			= unsigned __int8;
using uint16		= unsigned __int16;
using uint32		= unsigned int;
using uint64		= unsigned __int64;

using Mutex =  std::mutex;
using ConditionV = std::condition_variable;
using UniqueLock = std::unique_lock<Mutex>;
using LockGuard = std::lock_guard<Mutex>;

template <typename T>
using TArray = std::vector<T>;

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