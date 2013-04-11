
/**
 * This file is part of the twosome package.
 *
 * (c) Azat Khuzhin <a3at.mail@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */


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
    ioService.run();

    return EXIT_SUCCESS;
}