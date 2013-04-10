
/**
 * This file is part of the twosome package.
 *
 * (c) Azat Khuzhin <a3at.mail@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include "kernel/net/chatserver.h"

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
    /**
     * TODO: add options
     */

    ChatServer server(ChatServer::Options(8765));
    server.start();

    return EXIT_SUCCESS;
}
