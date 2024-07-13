#pragma once
#include <cstddef>


/// <summary>
/// latest offsets from hazdumper https://github.com/frk1/hazedumper/blob/master/csgo.hpp
/// </summary>


// whats "ptrdiff_t"? pointer difference?

constexpr ::std::ptrdiff_t dwLocalPlayer = 0xDEB99C;
constexpr ::std::ptrdiff_t dwEntityList = 0x4E0102C;
constexpr ::std::ptrdiff_t dwForceJump = 0x52BCD88;
constexpr ::std::ptrdiff_t dwSetClanTag = 0x8DAB0;

// knife bot
constexpr ::std::ptrdiff_t dwForceAttack = 0x322EE98;
constexpr ::std::ptrdiff_t dwForceAttack2 = 0x322EEA4;

// scope removals
constexpr ::std::ptrdiff_t m_bIsScoped = 0x9974;
constexpr ::std::ptrdiff_t dwZoomSensitivityRatioPtr = 0xDF53B8;
constexpr ::std::ptrdiff_t m_hViewModel = 0x3308;
constexpr ::std::ptrdiff_t m_zoomLevel = 0x33E0; 

// glow esp
constexpr ::std::ptrdiff_t dwGlowObjectManager = 0x535BAD0;
constexpr ::std::ptrdiff_t m_iGlowIndex = 0x10488;

// fuck is this
constexpr ::std::ptrdiff_t m_iHealth = 0x100;
