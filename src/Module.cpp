/* COPYRIGHT (c) 2016-2017 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <core/mw/Middleware.hpp>
#include <core/mw/transport/RTCANTransport.hpp>

#include <core/snippets/CortexMxFaultHandlers.h>

#include <core/hw/EXT.hpp>
#include <core/hw/GPIO.hpp>
#include <core/hw/IWDG.hpp>
#include <core/os/Thread.hpp>

#include <Module.hpp>

// LED
using LED_PAD = core::hw::Pad_<core::hw::GPIO_F, LED_PIN>;
static LED_PAD _led;

// GPIO
static core::hw::Pad_<core::hw::GPIO_A, 11> _d1;
static core::hw::Pad_<core::hw::GPIO_A, 10> _d2;
static core::hw::Pad_<core::hw::GPIO_A, 8>  _d3;
static core::hw::Pad_<core::hw::GPIO_A, 9>  _d4;
static core::hw::Pad_<core::hw::GPIO_B, 7>  _d5;
static core::hw::Pad_<core::hw::GPIO_B, 6>  _d6;
static core::hw::Pad_<core::hw::GPIO_B, 4>  _d7;
static core::hw::Pad_<core::hw::GPIO_B, 5>  _d8;

static core::hw::Pad_<core::hw::GPIO_A, 7> _a1;
static core::hw::Pad_<core::hw::GPIO_A, 6> _a2;
static core::hw::Pad_<core::hw::GPIO_A, 5> _a3;
static core::hw::Pad_<core::hw::GPIO_A, 4> _a4;
static core::hw::Pad_<core::hw::GPIO_A, 0> _a5;
static core::hw::Pad_<core::hw::GPIO_A, 1> _a6;
static core::hw::Pad_<core::hw::GPIO_A, 3> _a7;
static core::hw::Pad_<core::hw::GPIO_A, 2> _a8;

static core::hw::Pad_<core::hw::GPIO_A, 12> _pwr1_4;
static core::hw::Pad_<core::hw::GPIO_C, 15> _pwr5_8;


// MODULE DEVICES
core::hw::Pad& Module::d1 = _d1;
core::hw::Pad& Module::d2 = _d2;
core::hw::Pad& Module::d3 = _d3;
core::hw::Pad& Module::d4 = _d4;
core::hw::Pad& Module::d5 = _d5;
core::hw::Pad& Module::d6 = _d6;
core::hw::Pad& Module::d7 = _d7;
core::hw::Pad& Module::d8 = _d8;

core::hw::Pad& Module::a1 = _a1;
core::hw::Pad& Module::a2 = _a2;
core::hw::Pad& Module::a3 = _a3;
core::hw::Pad& Module::a4 = _a4;
core::hw::Pad& Module::a5 = _a5;
core::hw::Pad& Module::a6 = _a6;
core::hw::Pad& Module::a7 = _a7;
core::hw::Pad& Module::a8 = _a8;


// SYSTEM STUFF
static core::os::Thread::Stack<1024> management_thread_stack;
static core::mw::RTCANTransport      rtcantra(&RTCAND1);

core::mw::Middleware
core::mw::Middleware::instance(
    ModuleConfiguration::MODULE_NAME
);


RTCANConfig rtcan_config = {
    1000000, 100, 60
};


Module::Module()
{}

bool
Module::initialize()
{
    FAULT_HANDLERS_ENABLE(true);

    static bool initialized = false;

    if (!initialized) {
        core::mw::CoreModule::initialize();

        core::mw::Middleware::instance.initialize(name(), management_thread_stack, management_thread_stack.size(), core::os::Thread::LOWEST);
        rtcantra.initialize(rtcan_config, canID());
        core::mw::Middleware::instance.start();

        _pwr1_4.setMode(core::hw::Pad::Mode::OUTPUT_OPENDRAIN);
        _pwr5_8.setMode(core::hw::Pad::Mode::OUTPUT_OPENDRAIN);

        initialized = true;
    }

    return initialized;
} // Board::initialize

void Module::setPower14(bool on) {
	_pwr1_4.write(!on);
}

void Module::setPower58(bool on) {
	_pwr5_8.write(!on);
}

// ----------------------------------------------------------------------------
// CoreModule STM32FlashConfigurationStorage
// ----------------------------------------------------------------------------
#include <core/snippets/CoreModuleSTM32FlashConfigurationStorage.hpp>
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// CoreModule HW specific implementation
// ----------------------------------------------------------------------------
#include <core/snippets/CoreModuleHWSpecificImplementation.hpp>
// ----------------------------------------------------------------------------
