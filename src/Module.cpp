/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <core/mw/Middleware.hpp>

#include "ch.h"
#include "hal.h"

#include <core/hw/GPIO.hpp>
#include <core/os/Thread.hpp>
#include <Module.hpp>


using LED_PAD = core::hw::Pad_<core::hw::GPIO_F, GPIOF_LED>;
static LED_PAD _led;

static THD_WORKING_AREA(wa_info, 1024);
static core::mw::RTCANTransport rtcantra(RTCAND1);

RTCANConfig rtcan_config = {
   1000000, 100, 60
};

#ifndef CORE_MODULE_NAME
#define CORE_MODULE_NAME "proximity"
#endif

core::mw::Middleware core::mw::Middleware::instance(CORE_MODULE_NAME, "BOOT_" CORE_MODULE_NAME);

Module::Module()
{}

bool
Module::initialize()
{
//	CORE_ASSERT(core::mw::Middleware::instance.is_stopped()); // TODO: capire perche non va...

   static bool initialized = false;

   if (!initialized) {
      halInit();
      chSysInit();

      core::mw::Middleware::instance.initialize(wa_info, sizeof(wa_info), core::os::Thread::LOWEST);
      rtcantra.initialize(rtcan_config);
      core::mw::Middleware::instance.start();

      initialized = true;
   }

   return initialized;
} // Board::initialize

// Leftover from CoreBoard (where LED_PAD cannot be defined
void
core::mw::CoreModule::Led::toggle()
{
   _led.toggle();
}

void
core::mw::CoreModule::Led::write(
   unsigned on
)
{
   _led.write(on);
}
