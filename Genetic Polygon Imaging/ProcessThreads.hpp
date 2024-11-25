/*****************************************************************//**
 * @file   ProcessThreads.hpp
 * @brief  Threads for genetic algorithm steps.
 * 
 * Contains threads that will execute the different stages of the
 * genetic algorithm. Specifically, selection, crossover, evaluation
 * and mutation.
 * 
 * Also provides a threadsafe queue which will be used by the threads
 * to communicate.
 * 
 * @author Thomas Johnson
 * @date   November 2024
 *********************************************************************/
#pragma once

#include <thread>
#include <mutex>
#include <queue>

#include "Solution.hpp"


/**
 * @class Queue<T>.
 * @brief A thread safe wrapper of std::queue.
 * 
 * Allows pushing and popping of items in a threadsafe manner.
 * Threads that try to pop an empty queue will block until an item is
 * put into the queue.
 */
template <typename T>
class Queue {
public:
	Queue() {};
	~Queue() {};

	void push(T item);
	T pop();

private:
	std::mutex queueLock;
	std::condition_variable waiters;
	std::queue<T> queue;
};


template <typename T>
class Thread {
public:
	Thread(void (*func)(T&), Queue<T>* in) : func(func), in(in), out(out) {}
	virtual	~Thread() { delete out; }

	void start();
	void close();

private:
	void run();

	Queue<T>* in;
	Queue<T>* out;

	void (*func)(T&);

	std::thread thread;
	bool running = false;
};

class SelectThread {
public:
	SelectThread(Solution(*selectFunc)(Solution));
	~SelectThread();

private:
};


class MutateThread {

};


class CrossoverThread {

};


class EvaluationThread {

};



