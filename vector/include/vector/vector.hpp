#ifndef _MyVector_HPP_
#define _MyVector_HPP_

#include <iostream>
#include <type_traits>
#include <memory>

template <typename T, typename Allocate = std::allocator<T>>
class MyVector
{
private:
	T* data_;
	size_t size_;
	size_t capacity_;
	Allocate alloc_;
public:

	using iterator = T*;

	using const_iterator = const T*;

	MyVector() noexcept: size_(0), capacity_(0), data_(nullptr), alloc_(Allocate()) {}

	explicit MyVector(const Allocate& alloc) noexcept : size_(0), capacity_(0), alloc_(alloc){}

	explicit MyVector(size_t count, const Allocate& alloc = Allocate()) : size_(count), capacity_(count), alloc_(alloc)
	{
		data_ = std::allocator_traits<Allocate>::allocate(alloc_, count);
		try
		{
			for (size_t i = 0; i < count; i++)
			{
				std::allocator_traits<Allocate>::construct(alloc_, data_ + i);
			}
		}
		catch (...)
		{
			std::allocator_traits<Allocate>::deallocate(alloc_, data_, count);
			throw;
		}
	}

	template<typename InputIt>
	MyVector(InputIt first, InputIt last, const Allocate& alloc = Allocate()) : alloc_(alloc)
	{
		size_t count = std::distance(first, last), i = 0;
		capacity_ = count;
		size_ = count;
		data_ = std::allocator_traits<Allocate>::allocate(alloc_, count);
		try
		{
			for (auto it = first; it != last; ++it, ++i)
			{
				std::allocator_traits<Allocate>::construct(alloc_, data_ + i, *it);
			}
		}
		catch (...)
		{
			std::allocator_traits<Allocate>::deallocate(alloc_, data_, count);
			throw;
		}
	}

	constexpr MyVector(size_t count, const T& value, const Allocate& alloc = Allocate()) : size_(count), capacity_(count), alloc_(alloc)
	{
		data_ = std::allocator_traits<Allocate>::allocate(alloc_, count);
		try
		{
			for (size_t i = 0; i < count; i++)
			{
				std::allocator_traits<Allocate>::construct(alloc_, data_ + i, value);
			}
		}
		catch (...)
		{
			std::allocator_traits<Allocate>::deallocate(alloc_, data_, count);
			throw;
		}
	}

	MyVector(std::initializer_list<T> l, const Allocate& alloc = Allocate()) : MyVector(std::make_move_iterator(l.begin()), 
																						std::make_move_iterator(l.end()), alloc)
	{
	}

	MyVector(const MyVector<T, Allocate>& v) : MyVector(v.begin(), v.end(), std::allocator_traits<Allocate>::select_on_container_copy_construction(v.alloc_))
	{
	}

	MyVector<T, Allocate>& operator = (const MyVector<T, Allocate>& v)
	{
		if (std::allocator_traits<Allocate>::propagate_on_container_copy_assignment::value && alloc_ != v.alloc_)
		{
			for (size_t i = 0; i < size_; i++)
			{
				std::allocator_traits<Allocate>::destroy(alloc_, data_ + i);
			}
			std::allocator_traits<Allocate>::deallocate(alloc_, data_, capacity_);
			size_ = 0, capacity_ = 0;
			alloc_ = v.alloc_;
		}
		size_t i = 0;
		try 
		{
			reserve(v.size_);
			for (; i < v.size_; i++)
			{
				std::allocator_traits<Allocate>::construct(alloc_, data_ + i, v[i]);
			}
			capacity_ = v.capacity_;
			size_ = v.size_;
		}
		catch (...)
		{
			for (size_t j  = 0; j < i; j++)
			{
				std::allocator_traits<Allocate>::destroy(alloc_, data_ + j);
			}
			std::allocator_traits<Allocate>::deallocate(alloc_, data_, v.size_);
		}
		return *this;
	}

	MyVector(MyVector<T, Allocate>&& v) noexcept : size_(v.size()), capacity_(v.capacity()), data_(v.data_), alloc_(std::move(v.alloc_))
	{
		v.capacity_ = 0;
		v.size_ = 0;
		v.data_ = nullptr;
	}

	MyVector(MyVector<T, Allocate>&& v, const Allocate& alloc) noexcept : size_(v.size()), capacity_(v.capacity()), alloc_(alloc)
	{
		if (alloc != v.alloc_)
		{
			MyVector vv(std::make_move_iterator(v.begin()), std::make_move_iterator(v.end()), alloc);
			swap(vv);
		} 
		else
		{
			swap(v);
		}
	}

	MyVector<T, Allocate>& operator = (MyVector<T, Allocate>&& v) noexcept
	{
		if (std::allocator_traits<Allocate>::propagate_on_container_move_assignment::value && alloc_ != v.alloc_)
		{
			for (size_t i = 0; i < size_; i++)
			{
				std::allocator_traits<Allocate>::destroy(alloc_, data_ + i);
			}
			std::allocator_traits<Allocate>::deallocate(alloc_, data_, capacity_);
			alloc_ = std::move(v.alloc_);
			reserve(v.size_);
			for (size_t i = 0; i < v.size_; i++)
			{
				std::allocator_traits<Allocate>::construct(alloc_, data_ + i, std::move(v[i]));
			}
			size_ = v.size_;
		}
		else
		{
			data_ = v.data_;
			size_ = v.size_;
			capacity_ = v.capacity_;
		}
		v.data_ = nullptr;
		v.size_ = 0;
		v.capacity_ = 0;
		return *this;
	}

	MyVector<T, Allocate> operator = (std::initializer_list<T> l)
	{
		size_ = 0, capacity_ = 0;
		size_t i = 0;
		try
		{
			reserve(l.size());
			for (auto it = l.begin(), ite = l.end(); it != ite; ++it, ++i)
			{
				std::allocator_traits<Allocate>::construct(alloc_, data_ + i, *it);
			}
			size_ = l.size();
		}
		catch (...)
		{
			for (size_t j = 0; j < i; j++)
			{
				std::allocator_traits<Allocate>::destroy(alloc_, data_ + j);
			}
			std::allocator_traits<Allocate>::deallocate(alloc_, data_, l.size());
		}
		return *this;
	}

	~MyVector()
	{
		clear();
		std::allocator_traits<Allocate>::deallocate(alloc_, data_, capacity_);
	}

	void clear() noexcept
	{
		for (size_t i = 0; i < size_; i++)
		{
			std::allocator_traits<Allocate>::destroy(alloc_, data_ + i);
		}
		size_ = 0;
	}

	size_t size() const
	{
		return size_;
	}

	size_t capacity() const
	{
		return capacity_;
	}

	void reserve(size_t n)
	{
		if (n < capacity_) return;
		size_t i = 0;
		T* new_data = std::allocator_traits<Allocate>::allocate(alloc_, n);
		try
		{
			for (; i < size_; i++)
			{
				std::allocator_traits<Allocate>::construct(alloc_, new_data + i, std::move_if_noexcept(data_[i]));
			}
		}
		catch (...)
		{
			for (size_t k = 0; k < i; ++k)
			{
				std::allocator_traits<Allocate>::destroy(alloc_, new_data + k);
			}
			std::allocator_traits<Allocate>::deallocate(alloc_, new_data, n);
			throw;
		}
		for (size_t k = 0; k < size_; ++k)
		{
			std::allocator_traits<Allocate>::destroy(alloc_, data_ + k);
		}
		std::allocator_traits<Allocate>::deallocate(alloc_, data_, capacity_);
		data_ = new_data;
		capacity_ = n;
	}

	void resize(size_t n, const T& value = T())
	{
		if (n < size_)
		{
			for (size_t j = n; j < size_; j++)
			{
				std::allocator_traits<Allocate>::destroy(alloc_, data_ + j);
			}
			size_ = n;
			return;
		}
		reserve(n);
		size_t i = size_;
		try
		{
			for (; i < n; i++)
			{
				std::allocator_traits<Allocate>::construct(alloc_, data_ + i, value);
			}
		}
		catch (...)
		{
			for (size_t j = 0; j < i; j++)
			{
				std::allocator_traits<Allocate>::destroy(alloc_, data_ + j);
			}
			std::allocator_traits<Allocate>::deallocate(alloc_, data_, n);
			throw;
		}
	}

	template<typename... Args>
	void emplace_back(Args&&...args)
	{
		if (capacity_ == size_)
		{
			reserve(2 * size_);
		}
		std::allocator_traits<Allocate>::construct(alloc_, data_ + size_, std::forward<Args>(args)...);
		++size_;
	}

	void push_back(const T& value)
	{
		emplace_back(value);
	}

	void push_back(T&& value)
	{
		emplace_back(std::move(value));
	}

	void pop_back() noexcept
	{
		std::allocator_traits<Allocate>::destroy(alloc_, data_ + size_);
		size_--;
	}

	void insert(const int index, T&& value)
	{
		if (index >= size_ || index < 0)
		{
			throw std::out_of_range("Incorrect index\n");
		}
		emplace_back(std::move(value));
		for (size_t i = size_; i > index; i--)
		{
			std::swap(data_[i], data_[i - 1]);
		}
	}

	void swap(MyVector<T, Allocate>& v) noexcept
	{
		if (std::allocator_traits<Allocate>::propagate_on_container_swap::value && alloc_ != v.alloc_)
		{
			std::swap(alloc_, v.alloc_);
		}
		std::swap(data_, v.data_);
		std::swap(size_, v.size_);
		std::swap(capacity_, v.capacity_);
	}

	T& front()
	{
		return data_[0];
	}

	T& back()
	{
		if (empty)
		{
			return data_[size_ - 1];
		}
		throw std::out_of_range("Vector is empty\n");
	}

	T* data()
	{
		return &data_[0];
	}

	bool empty()
	{
		return size_ == 0;
	}

	T& operator[](const int index)
	{
		return data_[index];
	}

	const T& operator [] (const int index) const
	{
		return data_[index];
	}


	T& at(const int index)
	{
		if (index < 0 || index >= size_)
		{
			throw std::out_of_range("Incorrect index\n");
		}
		return data_[index];
	}

	const T& at(const int index) const
	{
		if (index < 0 || index >= size_)
		{
			throw std::out_of_range("Incorrect index\n");
		}
		return data_[index];
	}


	iterator begin()
	{
		return data_;
	}

	const iterator begin() const
	{
		return data_;
	}

	const iterator cbegin() const
	{
		return data_;
	}

	iterator end()
	{
		return data_ + size_;
	}

	const iterator end() const
	{
		return data_ + size_;
	}

	const iterator cend() const
	{
		return data_ + size_;
	}

};

#endif

