#define BUF_LEN 256
#include <typeinfo>

class NetworkError : public std::exception {
   private:
    char msg_error[BUF_LEN];

   public:
    explicit NetworkError(const char* fmt, ...) noexcept;
    virtual const char* what() const noexcept;
    virtual ~NetworkError() noexcept;
};
