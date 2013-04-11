
/**
 * This file is part of the twosome package.
 *
 * (c) Azat Khuzhin <a3at.mail@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#pragma once


#include "session.h"

#include <string>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio_sctp/ip/sctp.hpp>

#include <boost/noncopyable.hpp>


/**
 * Async chat client
 */
class ChatClient : boost::noncopyable
{
public:
    struct Options
    {
        std::string port;
        std::string ip;

        Options(std::string port = "", std::string ip = "")
            : port(port)
            , ip(ip)
        {}
    };

    ChatClient(const Options &options, boost::asio::io_service& ioService);

    void send(const std::string& message);
    void close();

private:
    Options m_options;
    char m_readBuffer[Session::MAX_BUFFER_LENGTH];
    char m_writeBuffer[Session::MAX_BUFFER_LENGTH];

    boost::asio::io_service &m_ioService;
    boost::asio_sctp::ip::sctp::socket m_socket;

    void handleConnect(const boost::system::error_code& error);
    void handleRead(const boost::system::error_code& error);
    void handleWrite(const boost::system::error_code& error);
};