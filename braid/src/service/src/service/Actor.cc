#include <braid/service/Actor.h>
#include <braid/service/ServiceSession.h>

namespace braid {
    void Actor::request_send(ObjectPtr<SendBuffer> send_buffer) {
        if (nullptr != session_)
            session_->request_send(send_buffer);
    }

    void Actor::request_close() {
        if (nullptr != session_)
            session_->request_close();
    }

    void Actor::on_closed() {
        session_.reset();
    }
}