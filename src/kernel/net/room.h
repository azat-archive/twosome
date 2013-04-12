
/**
 * This file is part of the twosome package.
 *
 * (c) Azat Khuzhin <a3at.mail@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#pragma once


#include "participant.h"
#include "util/log.h"

#include <boost/noncopyable.hpp>
#include <set>
#include <functional>
#include <algorithm>


class Room : boost::noncopyable
{
public:
    explicit Room() {}

    void join(ParticipantPtr participant)
    {
        LOG(info) << "Add participant, already connected " << m_participants.size();
        m_participants.insert(participant);
    }

    void leave(ParticipantPtr participant)
    {
        m_participants.erase(participant);
    }

    void deliver(const std::string& message)
    {
        std::for_each(m_participants.begin(), m_participants.end(),
                      std::bind(&Participant::deliver,
                                std::placeholders::_1,
                                message));
    }

private:
    std::set<ParticipantPtr> m_participants;
};