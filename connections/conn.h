#include <cstddef>
#include <sys/syslog.h>
#ifndef CONN_H
#define CONN_H
enum ConnStatus {
    INACCESSIBLE = -999
};
enum class OperationType {
    Read,
    Write 
};

class Conn {
public:
    virtual bool read(void *buf, size_t count) = 0;
    virtual bool write(void *buf, size_t count) = 0;
    virtual ~Conn() = default;
};

#endif
