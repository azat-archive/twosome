
/**
 * This file is part of the twosome package.
 *
 * (c) Azat Khuzhin <a3at.mail@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */


#include "chatclient.h"
#include "util/log.h"

#include <functional>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>


namespace PlaceHolders = std::placeholders;
namespace Ip = boost::asio::ip;
namespace Sctp = boost::asio_sctp;


ChatClient::ChatClient(const Options &options, boost::asio::io_service &ioService)
    : m_options(options)
    , m_ioService(ioService)
    , m_socket(ioService)
{
    Sctp::ip::sctp::resolver resolver(ioService);
    Sctp::ip::sctp::resolver_query query(options.ip, options.port);

    connectAsyncNext(resolver.resolve(query));
}

void ChatClient::send(const std::string& message)
{
    boost::asio::async_write(m_socket,
                             boost::asio::buffer(message.c_str(), message.size()),
                             std::bind(&ChatClient::handleWrite, this,
                                       PlaceHolders::_1));
}

void ChatClient::close()
{
    LOG(info) << "Leaving";
    m_socket.close();
}

void ChatClient::handleConnect(const boost::system::error_code& error,
                               Sctp::ip::sctp::resolver_iterator iterator)
{
    if (error) {
        LOG(info) << "Connect error";
        close();
        connectAsyncNext(iterator);
        return;
    }

    boost::asio::async_read(m_socket,
                            boost::asio::buffer(m_readBuffer, Session::MAX_BUFFER_LENGTH),
                            std::bind(&ChatClient::handleRead, this,
                                      PlaceHolders::_1));
}

void ChatClient::connectAsyncNext(Sctp::ip::sctp::resolver_iterator iterator)
{
    m_socket.async_connect(*iterator,
                           std::bind(&ChatClient::handleConnect, this,
                                      PlaceHolders::_1, ++iterator));
}

void ChatClient::handleRead(const boost::system::error_code& error)
{
    if (error) {
        LOG(info) << "Read error";
        close();
        return;
    }

    writeOutputPrompt();
    std::cout << m_readBuffer
              << std::endl << std::flush;
}

void ChatClient::handleWrite(const boost::system::error_code& error)
{
    if (error) {
        LOG(info) << "Write error";
        close();
        return;
    }

    boost::asio::async_write(m_socket,
                             boost::asio::buffer(m_writeBuffer, Session::MAX_BUFFER_LENGTH),
                             std::bind(&ChatClient::handleWrite, this,
                                       PlaceHolders::_1));
}