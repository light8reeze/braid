#include <braid/service/Service.h>
#include <memory>

int main() {

  auto game_service = braid::ServiceBuilder<braid::Service>::create_builder()
          .set_address("", 4832)
          .set_backlog(4096)
          .set_thread_count(16)
          .set_session_count(100)
          .build();

  game_service->initialize();

  game_service->run();

  return 0;
}