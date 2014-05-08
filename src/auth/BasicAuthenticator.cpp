#include "Authenticator.hpp"

namespace auth {
  class BasicAuthenticator : public Authenticator {
  public:
    bool authenticate(std::string user, std::string pass) {
      return true;
    }
  };
}
