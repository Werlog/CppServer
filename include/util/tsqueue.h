#pragma once

#include <deque>
#include <mutex>

// Thread-safe queue
template<typename T>
class tsqueue
{
public:
	void push_back(const T& value);
	void push_front(const T& value);

	const T& front();
	const T& back();

	T pop_front();
	T pop_back();

	size_t size();
	bool empty();
private:
	std::mutex queueMutex;
	std::deque<T> queue;
};

template<typename T>
inline void tsqueue<T>::push_back(const T& value)
{
	std::scoped_lock lock(queueMutex);
	queue.push_back(value);
}

template<typename T>
inline void tsqueue<T>::push_front(const T& value)
{
	std::scoped_lock lock(queueMutex);
	queue.push_front(value);
}

template<typename T>
inline const T& tsqueue<T>::front()
{
	std::scoped_lock lock(queueMutex);
	return queue.front();
}

template<typename T>
inline const T& tsqueue<T>::back()
{
	std::scoped_lock lock(queueMutex);
	return queue.back();
}

template<typename T>
inline T tsqueue<T>::pop_front()
{
	std::scoped_lock lock(queueMutex);
	auto t = std::move(queue.front());
	queue.pop_front();
	return t;
}

template<typename T>
inline T tsqueue<T>::pop_back()
{
	std::scoped_lock lock(queueMutex);
	auto t = std::move(queue.back());
	queue.pop_back();
	return t;
}

template<typename T>
inline size_t tsqueue<T>::size()
{
	std::scoped_lock lock(queueMutex);
	return queue.size();
}

template<typename T>
inline bool tsqueue<T>::empty()
{
	std::scoped_lock lock(queueMutex);
	return queue.empty();
}
