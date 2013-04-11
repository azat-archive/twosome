
/**
 * This file is part of the twosome package.
 *
 * (c) Azat Khuzhin <a3at.mail@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#pragma once

#include <string>
#include <memory>
#include <boost/noncopyable.hpp>


class Participant : boost::noncopyable
{
public:
    virtual ~Participant() {}
    virtual void deliver(const std::string& message) = 0;
};

/**
 * Write wrapper for std::shared_ptr and shared_from_this(),
 * and avoid using boost::shared_ptr()
 */
typedef std::shared_ptr<Participant> ParticipantPtr;