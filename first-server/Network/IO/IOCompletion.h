
struct io_uring;
struct io_uring_cqe;
class IOUringObject;
namespace first {

	class IOCompletion {
	public:
		NON_COPYABLE(IOCompletion);

		IOCompletion(io_uring* ring, io_uring_cqe* cqe);
		IOCompletion(IOCompletion&& io_completion) noexcept;
		~IOCompletion();


	public:
		IOUringObject* get_completed_object() const { return completed_object_; }
		int get_result() const { return cqe_ ? cqe_->res : -1; }
		

	private:
		io_uring*		ring_ = nullptr;
		io_uring_cqe*	cqe_ = nullptr;
		IOUringObject*  completed_object_ = nullptr;
	};
}