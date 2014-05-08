#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <string>

namespace auth {
  /**
   * Authenticator interface
   */
  class Authenticator {
  public:
    /**
     * Main contract method
     */
    virtual bool authenticate(std::string user, std::string pass) = 0;
    
    virtual ~Authenticator(){};
  };

} // namespace auth

#endif // AUTHENTICATOR_H
