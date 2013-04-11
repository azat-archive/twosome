
/**
 * This file is part of the twosome package.
 *
 * (c) Azat Khuzhin <a3at.mail@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */


#include <boost/thread.hpp>
#include <functional>

#include "kernel/net/chatclient.h"
#include "kernel/net/session.h"


int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
    /**
     * TODO: add options
     */

    boost::asio::io_service ioService;
    ChatClient client(ChatClient::Options("8765"), ioService);

    // TODO: Replace by std::bind()
    boost::thread clientThread(boost::bind(&boost::asio::io_service::run,
                                           &ioService));

    char message[Session::MAX_BUFFER_LENGTH];
    while (ChatClient::writeInputPrompt()
           && std::cin.getline(message, Session::MAX_BUFFER_LENGTH + 1)) {
        client.send(message);
    }

    client.close();
    clientThread.join();

    return EXIT_SUCCESS;
}