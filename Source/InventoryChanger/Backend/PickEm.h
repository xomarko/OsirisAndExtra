#pragma once

#include <cstdint>
#include <map>

#include <SDK/Constants/Tournament.h>
#include <SDK/Constants/TournamentTeam.h>

namespace inventory_changer::backend
{

    class PickEm {
    public:
        struct PickPosition {
            Tournament tournament;
            std::uint16_t group;
            std::uint8_t indexInGroup;

            friend auto operator<=>(const PickPosition&, const PickPosition&) = default;
        };

        void pick(PickPosition position, TournamentTeam team)
        {
            picks[position] = team;
        }

        [[nodiscard]] TournamentTeam getPickedTeam(PickPosition position) const
        {
            if (const auto pick = picks.find(position); pick != picks.end())
                return pick->second;
            return TournamentTeam::None;
        }

        [[nodiscard]] const auto& getPicks() const noexcept
        {
            return picks;
        }

        void clear() noexcept
        {
            picks.clear();
        }

    private:
        std::map<PickPosition, TournamentTeam> picks;
    };

}