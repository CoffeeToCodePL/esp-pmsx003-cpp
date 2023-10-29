/*
 * Copyright (c) 2023 Michał Łubiński <mlubinski@coffeetocode.pl>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef ESP_PMSX003_CPP_PROTOCOL_H
#define ESP_PMSX003_CPP_PROTOCOL_H

#include <cstdint>
#include <array>
#include <optional>

namespace PMSx003 {
  namespace Protocol {
    constexpr uint8_t START_BYTE_1 = 0x42;
    constexpr uint8_t START_BYTE_2 = 0x4D;
    constexpr size_t FRAME_IN_LENGTH = 32;
    constexpr size_t FRAME_OUT_LENGTH = 7;

    using FrameIn = std::array<uint8_t, FRAME_IN_LENGTH>;
    using FrameOut = std::array<uint8_t, FRAME_OUT_LENGTH>;

    struct Measurement
    {
      uint16_t pm1_0_cf1;         /* PM1.0 concentration unit ug/m3 (CF=1, standard particle) */
      uint16_t pm2_5_cf1;         /* PM2.5 concentration unit ug/m3 (CF=1, standard particle) */
      uint16_t pm10_cf1;          /* PM10 concentration unit ug/m3 (CF=1, standard particle) */
      uint16_t pm1_0_atmospheric; /* PM1.0 concentration unit (under atmospheric environment) */
      uint16_t pm2_5_atmospheric; /* PM2.5 concentration unit (under atmospheric environment) */
      uint16_t pm10_atmospheric;  /* PM10 concentration unit (under atmospheric environment) */
      uint16_t particles_0_3um;   /* Number of particles with diameter beyond 0.3um in 0.1L of air */
      uint16_t particles_0_5um;   /* Number of particles with diameter beyond 0.5um in 0.1L of air */
      uint16_t particles_1um;     /* Number of particles with diameter beyond 1um in 0.1L of air */
      uint16_t particles_2_5um;   /* Number of particles with diameter beyond 2.5um in 0.1L of air */
      uint16_t particles_5um;     /* Number of particles with diameter beyond 5um in 0.1L of air */
      uint16_t particles_10um;    /* Number of particles with diameter beyond 10um in 0.1L of air */
    };

    enum class Mode : uint8_t
    {
      Active = 0x00,
      Passive = 0x01
    };

    enum class SleepState : uint8_t
    {
      Sleep = 0x00,
      WakeUp = 0x01
    };

    enum class Command : uint8_t
    {
      Read = 0xE2,
      ChangeMode = 0xE1,
      SleepSet = 0xE4
    };

    std::optional<Measurement> parseIncomingFrame(const FrameIn& frame);
    FrameOut createCommand(const Command command, const uint16_t data);
  }
}

#endif // ESP_PMSX003_CPP_PROTOCOL_H
