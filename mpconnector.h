#ifndef MPCONNECTOR_H
#define MPCONNECTOR_H
#include <winsock2.h>
#include <ws2tcpip.h>
#include <exception>


/**
 * Mission Planner socket wrapper
 */
class MPConnector
{
public:
    MPConnector();
    ~MPConnector();

    /**
     * Data from the Mission Planner
     */
    struct MPData {
        double altitude;
        double latitude;
        double longitude;
    };

    /**
     * Socket initialization
     * @param serverName the MP hostname
     * @param port
     */
    void connect(const char *serverName, int port) throw (std::exception);

    /**
     * Query the Mission Planner for metadata.
     * This is a blocking call
     * @return the metadata
     */
    struct MPData getData() throw (std::exception);

private:
    SOCKET socket;
};

#endif // MPCONNECTOR_H
