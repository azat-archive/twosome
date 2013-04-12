
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
#include <boost/asio/read_until.hpp>


namespace PlaceHolders = std::placeholders;
namespace Ip = boost::asio::ip;
namespace Sctp = boost::asio_sctp;


ChatClient::ChatClient(const Options &options, boost::asio::io_service &ioService)
    : m_options(options)
    , m_messageBuffer(Session::MAX_BUFFER_LENGTH)
    , m_inputBuffer(Session::MAX_BUFFER_LENGTH)
    , m_input(ioService, ::dup(STDIN_FILENO))
    , m_output(ioService, ::dup(STDOUT_FILENO))
    , m_ioService(ioService)
    , m_socket(ioService)
{
    Sctp::ip::sctp::resolver resolver(ioService);
    Sctp::ip::sctp::resolver_query query(options.ip, options.port);

    connectAsyncNext(resolver.resolve(query));
}

void ChatClient::send(const std::string& message)
{
    m_ioService.post(std::bind(&ChatClient::asyncWrite, this, message));
}

void ChatClient::close()
{
    LOG(info) << "Leaving";
    m_socket.close();
    m_input.close();
    m_output.close();
}

void ChatClient::handleConnect(const boost::system::error_code& error,
                               Sctp::ip::sctp::resolver_iterator iterator)
{
    LOG(info) << "ChatClient::handleConnect";
    if (error) {
        LOG(info) << "Connect error";
        close();
        connectAsyncNext(iterator);
        return;
    }

    asyncRead();
    asyncReadFromStdin();
}

void ChatClient::connectAsyncNext(Sctp::ip::sctp::resolver_iterator iterator)
{
    m_socket.async_connect(*iterator,
                           std::bind(&ChatClient::handleConnect, this,
                                      PlaceHolders::_1, ++iterator));
}

void ChatClient::handleRead(const boost::system::error_code& error,
                            size_t length)
{
    LOG(info) << "ChatClient::handleRead";
    if (error) {
        LOG(info) << "Read error";
        close();
        return;
    }

    m_messageBuffer.sgetn(m_buffer, length);
    writeOutputPrompt();
    std::cout << m_buffer << std::endl << std::flush;

    asyncRead();
}

void ChatClient::handleReadInput(const boost::system::error_code& error,
                                 size_t length)
{
    LOG(info) << "ChatClient::handleReadInput";
    if (error) {
        close();
        return;
    }

    m_inputBuffer.sgetn(m_buffer, length);
    asyncWrite(m_buffer);
}

void ChatClient::handleWrite(const boost::system::error_code& error)
{
    LOG(info) << "ChatClient::handleWrite";
    if (error) {
        LOG(info) << "Write error";
        close();
        return;
    }

    asyncReadFromStdin();
}

void ChatClient::asyncRead()
{
    boost::asio::async_read_until(m_socket, m_messageBuffer, '\n',
                                  std::bind(&ChatClient::handleRead, this,
                                            PlaceHolders::_1, PlaceHolders::_2));
}

void ChatClient::asyncReadFromStdin()
{
    writeInputPrompt();
    boost::asio::async_read_until(m_input, m_inputBuffer, '\n',
                                  std::bind(&ChatClient::handleReadInput, this,
                                            PlaceHolders::_1, PlaceHolders::_2));
}

void ChatClient::asyncWrite(const std::string& message)
{
    boost::asio::async_write(m_socket,
                             boost::asio::buffer(message.c_str(), message.size()),
                             std::bind(&ChatClient::handleWrite, this,
                                       PlaceHolders::_1));
}