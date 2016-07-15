#pragma once

#include <ModuleConfiguration.hpp>
#include <core/mw/CoreModule.hpp>


class Module:
   public core::mw::CoreModule
{
public:
   static bool
   initialize();


   Module();
   virtual ~Module() {}
};
