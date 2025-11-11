#pragma	once
#include <atomic>

namespace first {

	class Node {
	public:
		Node() = default;
		virtual ~Node() = default;


	public:
		Node* next = nullptr;
	};

	class ConcurrentStack {
	public:
		ConcurrentStack() : head_(nullptr) {}
		~ConcurrentStack() = default;


	public:
		bool push(Node* newNode);
		Node* pop();
		Node* flush();


	private:
		std::atomic<Node*> head_;
	};
}