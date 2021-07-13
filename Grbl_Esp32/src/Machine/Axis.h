#pragma once

/*
    Part of Grbl_ESP32
    2021 -  Stefan de Bruijn, Mitch Bradley

    Grbl_ESP32 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Grbl_ESP32 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Grbl_ESP32.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../Configuration/Configurable.h"
#include "Gang.h"
#include "Homing.h"

namespace Motors {
    class Motor;
}

namespace Machine {
    class Axis : public Configuration::Configurable {
    public:
        Axis() {
            for (int i = 0; i < MAX_NUMBER_GANGED; ++i) {
                _gangs[i] = nullptr;
            }
        }
        static const int MAX_NUMBER_GANGED = 2;

        Gang*   _gangs[MAX_NUMBER_GANGED];
        Homing* _homing = nullptr;

        float _stepsPerMm   = 320.0f;
        float _maxRate      = 1000.0f;
        float _acceleration = 25.0f;
        float _maxTravel    = 200.0f;
        bool  _softLimits   = false;
        Endstops* _endstops     = nullptr;

        // Configuration system helpers:
        void group(Configuration::HandlerBase& handler) override;
        void afterParse() override;

        // Checks if a motor matches this axis:
        bool hasMotor(const Motors::Motor* const motor) const;

        ~Axis();
    };
}
