#pragma once

// Semaphore

// UObject
// Wrapper Class
class RefCountable
{
public:
	RefCountable() : _refCount(1) {}
	virtual ~RefCountable() {}

	int32 AddRef() { return _refCount.fetch_add(1); }
	int32 ReleaseRef()
	{
		_refCount.fetch_sub(1);

		if (_refCount == 0)
		{
			delete this;
		}

		return _refCount;
	}

private:
	atomic<int32> _refCount;
};

template <typename T>
class TSharedPtr
{
public:
	TSharedPtr() {}
	TSharedPtr(T* ptr) { _ptr = ptr; }

	TSharedPtr(const TSharedPtr& other) { Set(other._ptr); }
	TSharedPtr(TSharedPtr&& rv) { _ptr = rv._ptr; rv._ptr = nullptr; }

	~TSharedPtr() { Release(); }

	// 상속관계에서의 복사생성자
	template<typename U>
	TSharedPtr(const TSharedPtr<U>& child) { Set(static_cast<T*>(child._ptr)); }

	// 연산자 오버로딩
	TSharedPtr& operator=(const TSharedPtr& other)
	{
		if (_ptr != other._ptr)
		{
			Release();
			Set(other._ptr);
		}

		return *this;
	}

	TSharedPtr& operator=(TSharedPtr&& rv)
	{
		Release();
		_ptr = rv._ptr;
		rv._ptr = nullptr;

		return *this;
	}
	 
	bool operator==(const TSharedPtr& other) const { return _ptr == other._ptr; }
	bool operator!=(const TSharedPtr& other) const { return _ptr!=other._ptr; }
	bool operator==(T* ptr) const { return _ptr == ptr; }
	bool operator!=(T* ptr) const { return _ptr != ptr; }
	T* operator*() { return _ptr; }
	const T* operator*() const { return _ptr; }
	T* operator->() { return _ptr; }
	const T* operator->() const { return _ptr; }

	bool IsNull() { return _ptr == nullptr; }


private:
	void Set(T* ptr)
	{
		_ptr = ptr;
		if (_ptr)
		{
			_ptr->AddRef();
		}
	}

	void Release()
	{
		if (_ptr != nullptr)
		{
			_ptr->ReleaseRef();
			_ptr = nullptr;
		}
	}

private:
	// RefCountable을 상속받는 클래스 T
	T* _ptr = nullptr;
};

