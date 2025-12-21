#include <liburing.h>
#include <braid/net/IOOperationSend.h>
#include <braid/net/IOUringObject.h>

namespace braid {
    IOOperationSend::IOOperationSend(std::shared_ptr<IOUringObject>&& io_object, std::span<char>& buffer)
        : IOOperation(std::move(io_object)), buffer_(buffer) {
    }

    void IOOperationSend::request_io(io_uring* ring) {
        io_uring_sqe* sqe = ::io_uring_get_sqe(ring);

        ::io_uring_prep_send(sqe, io_object_->get_socket_fd(), buffer_.data(), buffer_.size(), 0);
        ::io_uring_sqe_set_data(sqe, this);
    }

    void IOOperationSend::handle_io_completion(int result) {
        if (nullptr == io_object_)
            return;

        if (result < 0)
            return;

        io_object_->on_sent(result);
    }

}