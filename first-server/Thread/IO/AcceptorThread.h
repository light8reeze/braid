#pragma once
#include "IORingThread.h"
#include "IOUringObject.h"
#include "FirstServerPCH.h"

namespace first {

    class AcceptorThread : public IOURingThread {
        public:
            AcceptorThread(int queue_depth = 1024, int port = 8080);
            virtual ~AcceptorThread();


        public:
            virtual void initialize() override;


        private:
            virtual int routine() override;
            virtual void on_accepted(IOUringObject* client);


        protected:
            socket_fd   listen_fd_ = -1;
            int         port_ = 8080;

			IOUringObject acceptor_object_;

            // TODO: 추후 별도 풀로 분리
			IOUringObject  client_object_[100];
    };
}