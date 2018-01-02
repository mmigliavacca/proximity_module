/* COPYRIGHT (c) 2016-2018 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */
 
#pragma once

#include <ModuleConfiguration.hpp>
#include <core/mw/CoreModule.hpp>

namespace core {
namespace hw {
class Pad;
class EXTChannel;
}
}

class Module:
    public core::mw::CoreModule
{
public:
// --- DEVICES ----------------------------------------------------------------
    static core::hw::Pad& d1;
    static core::hw::Pad& d2;
    static core::hw::Pad& d3;
    static core::hw::Pad& d4;
    static core::hw::Pad& d5;
    static core::hw::Pad& d6;
    static core::hw::Pad& d7;
    static core::hw::Pad& d8;

    static core::hw::Pad& a1;
    static core::hw::Pad& a2;
    static core::hw::Pad& a3;
    static core::hw::Pad& a4;
    static core::hw::Pad& a5;
    static core::hw::Pad& a6;
    static core::hw::Pad& a7;
    static core::hw::Pad& a8;

    static void
    setPower14(
        bool on
    );

    static void
    setPower58(
        bool on
    );


// ----------------------------------------------------------------------------

    static bool
    initialize();


    Module();
    virtual ~Module() {}
};
