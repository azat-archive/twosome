
/**
 * This file is part of the twosome package.
 *
 * (c) Azat Khuzhin <a3at.mail@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#pragma once

#include "participant.h"
#include "room.h"

#include <boost/asio/io_service.hpp>
#include <boost/asio_sctp/ip/sctp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>


/**
 * Session handler for ChatServer
 */
class Session
    : public Participant
    , public boost::enable_shared_from_this<Session>
{
public:
    enum Constants
    {
        MAX_BUFFER_LENGTH = 1 << 10 /* 1024 */
    };

    Session(boost::asio::io_service& socket);

    void start();
    virtual void deliver(const std::string& message);

    boost::asio_sctp::ip::sctp::socket& socket()
    {
        return m_socket;
    }


private:
    boost::asio_sctp::ip::sctp::socket m_socket;
    char m_buffer[MAX_BUFFER_LENGTH];
    Room m_room;

    void asyncRead();
    void asyncWrite(const std::string& message);
    void handleRead(const boost::system::error_code& error, size_t bytesTransferred);
    void handleWrite(const boost::system::error_code& error);
};