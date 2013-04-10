
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

ChatServer::ChatServer(const Options &options)
    : m_options(options)
    , m_acceptor(m_socket, Ip::tcp::endpoint(Ip::tcp::v4(), options.port))
{
    startAccept();
}

ChatServer::~ChatServer()
{
}

void ChatServer::start()
{
    LOG(info) << "Starting server";
    m_socket.run();
}

void ChatServer::startAccept()
{
    Session* newSession = new Session(m_socket);
    m_acceptor.async_accept(newSession->socket(),
                            std::bind(&ChatServer::handleAccept,
                                      this,
                                      newSession,
                                      PlaceHolders::_1));
}

void ChatServer::handleAccept(Session* newSession, const boost::system::error_code& error)
{
    if (!error) {
        LOG(info) << "Client connected " << newSession;
        newSession->start();
    } else {
        LOG(info) << "Client session error";
        delete newSession;
    }

    startAccept();
}
