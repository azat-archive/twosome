
/**
 * This file is part of the twosome package.
 *
 * (c) Azat Khuzhin <a3at.mail@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */


#include "chatserver.h"
#include "util/log.h"

#include <functional>


namespace PlaceHolders = std::placeholders;
namespace Ip = boost::asio::ip;
namespace Sctp = boost::asio_sctp;


ChatServer::ChatServer(const Options &options)
    : m_options(options)
{
    const Ip::address address = Ip::address::from_string("0.0.0.0");
    m_acceptor = std::unique_ptr<Sctp::ip::sctp::acceptor>(new Sctp::ip::sctp::acceptor(
                                                           m_socket,
                                                           Sctp::ip::sctp::endpoint(address,
                                                                                    options.port)));
    startAccept();
}

void ChatServer::start()
{
    LOG(info) << "Starting server";
    m_socket.run();
}

void ChatServer::startAccept()
{
    SessionPtr newSession(new Session(m_socket, m_room));
    m_acceptor->async_accept(newSession->socket(),
                             std::bind(&ChatServer::handleAccept,
                                       this,
                                       newSession,
                                       PlaceHolders::_1));
}

void ChatServer::handleAccept(SessionPtr newSession, const boost::system::error_code& error)
{
    if (!error) {
        LOG(info) << "Client connected " << newSession;
        newSession->start();
    } else {
        LOG(info) << "Client session error";
    }

    startAccept();
}