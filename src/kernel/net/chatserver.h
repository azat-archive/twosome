
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
#include <boost/noncopyable.hpp>

/**
 * Async chat server
 *
 * TODO: singleton
 */
class ChatServer : boost::noncopyable
{
public:
    struct Options
    {
        short port;
        std::string ip;

        Options(short port = 0, std::string ip = "")
            : port(port)
            , ip(ip)
        {}
    };

    ChatServer(const Options &options);
    virtual ~ChatServer();

    void start();

private:
    Options m_options;

    boost::asio::io_service m_socket;
    boost::asio::ip::tcp::acceptor m_acceptor;

    void startAccept();
    void handleAccept(Session* newSession, const boost::system::error_code& error);
};
