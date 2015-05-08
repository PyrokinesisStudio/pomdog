// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_CONNECTIONLIST_EF8910DE_HPP
#define POMDOG_CONNECTIONLIST_EF8910DE_HPP

#include "ScopedConnection.hpp"
#include "Pomdog/Basic/Export.hpp"
#include <vector>
#include <utility>

namespace Pomdog {

class POMDOG_EXPORT ConnectionList {
    std::vector<ScopedConnection> connections;

public:
    template <typename...Args, typename Func>
    void Connect(Signal<void(Args...)> & signal, Func && func)
    {
        auto connection = signal.Connect(std::forward<Func>(func));
        connections.push_back(std::move(connection));
    }

    void Disconnect()
    {
        connections.clear();
    }
};

} // namespace Pomdog

#endif // POMDOG_CONNECTIONLIST_EF8910DE_HPP