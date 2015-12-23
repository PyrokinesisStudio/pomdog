// Copyright (c) 2013-2015 mogemimi. Distributed under the MIT license.

#pragma once

#include "Pomdog/Signals/detail/ForwardDeclarations.hpp"
#include "Pomdog/Signals/Connection.hpp"
#include "Pomdog/Basic/Export.hpp"

namespace Pomdog {

class POMDOG_EXPORT ScopedConnection final {
private:
    Connection connection;

public:
    ScopedConnection() = default;
    ScopedConnection(ScopedConnection const&) = delete;
    ScopedConnection(ScopedConnection &&) = default;

    ScopedConnection(Connection const& connection);
    ScopedConnection(Connection && connection);

    ~ScopedConnection();

    ScopedConnection & operator=(ScopedConnection const&) = delete;
    ScopedConnection & operator=(ScopedConnection &&) = default;

    ScopedConnection & operator=(Connection const& c);
    ScopedConnection & operator=(Connection && c);

    void Disconnect();
};

} // namespace Pomdog
