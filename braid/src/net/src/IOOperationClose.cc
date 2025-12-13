#include <braid/net/IOOperationClose.h>

namespace braid {
    IOOperationClose::IOOperationClose(std::shared_ptr<IOUringObject>&& io_object) 
        : IOOperation(std::move(io_object)) {
    }

    void IOOperationClose::request_io(io_uring* ring) {
        ::shutdown(io_object_->get_socket_fd(), SHUT_RDWR);

        struct io_uring_sqe* sqe = io_uring_get_sqe(ring);
        ::io_uring_prep_close(sqe, io_object_->get_socket_fd());
        ::io_uring_sqe_set_data(sqe, this);
        ::io_uring_submit(ring);
    }

    void IOOperationClose::handle_io_completion(int result) {}
}