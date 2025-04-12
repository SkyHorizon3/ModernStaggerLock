#pragma once

// clib
#include <RE/Skyrim.h>
#include <REL/Relocation.h>
#include <SKSE/SKSE.h>

// winnt
#include <ShlObj_core.h>

using namespace std::literals;
using namespace REL::literals;

// Version
#include "Plugin.h"

// DKUtil
#include "DKUtil/Logger.hpp"

#define DLLEXPORT extern "C" [[maybe_unused]] __declspec(dllexport)