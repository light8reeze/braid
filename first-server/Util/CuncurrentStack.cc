#include "CurrentStack.h"

namespace first {
	
	bool ConcurrentStack::push(Node* newNode) {
		Node* oldHead = head_.load(std::memory_order_relaxed);

		do {
			newNode->next = oldHead;
		} while (!head_.compare_exchange_weak(oldHead, newNode,
			std::memory_order_release,
			std::memory_order_relaxed));

		return true;
	}
	
	Node* ConcurrentStack::pop() {
		Node* oldHead = head_.load(std::memory_order_acquire);

		while (oldHead != nullptr) {
			Node* nextNode = oldHead->next;

			if (head_.compare_exchange_weak(oldHead, nextNode,
				std::memory_order_acquire,
				std::memory_order_relaxed)) {
				return oldHead;
			}
		}

		return nullptr;
	}

	Node* ConcurrentStack::flush() {
		return head_.exchange(nullptr, std::memory_order_acquire);
	}
}