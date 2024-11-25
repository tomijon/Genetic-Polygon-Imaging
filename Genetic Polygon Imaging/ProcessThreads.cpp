#include "ProcessThreads.hpp"


template <typename T>
void Queue<T>::push(T item) {
	std::unique_lock<std::mutex> mut(queueLock);
	queue.push(item);
	waiters.notify_one();
}


template <typename T>
T Queue<T>::pop() {
	T item;
	std::unique_lock<std::mutex> mut(queueLock);
	waiters.wait(mut, [] { return !queue.empty(); });

	item = queue.front();
	queue.pop();
	return item;
}


template <typename T>
void Thread<T>::start() {
	if (!running) {
		running = true;
		thread = std::thread(run);
	}
}


template <typename T>
void Thread<T>::run() {
	while (running) {
		T item = in->pop();
		func(item);
		out->push(item);
	}
}


template <typename T>
void Thread<T>::close() {
	running = false;
	if (thread.joinable()) thread.join();
}


