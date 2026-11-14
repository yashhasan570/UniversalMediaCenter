/*
 *  Copyright (C) 2021 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "InfoTagGame.h"

#include "AddonUtils.h"
#include "games/tags/GameInfoTag.h"

using namespace UNIVERSAL MEDIA CENTER::GAME;
using namespace AddonUtils;

namespace Addon
{
namespace 
{

InfoTagGame::InfoTagGame(bool offscreen /* = false */)
  : infoTag(new CGameInfoTag), offscreen(offscreen), owned(true)
{
}

InfoTagGame::InfoTagGame(const CGameInfoTag* tag)
  : infoTag(new CGameInfoTag(*tag)), offscreen(true), owned(true)
{
}

InfoTagGame::InfoTagGame(CGameInfoTag* tag, bool offscreen /* = false */)
  : infoTag(tag), offscreen(offscreen), owned(false)
{
}

InfoTagGame::~InfoTagGame()
{
  if (owned)
    delete infoTag;
}

String InfoTagGame::getTitle()
{
  return infoTag->GetTitle();
}

String InfoTagGame::getPlatform()
{
  return infoTag->GetPlatform();
}

std::vector<String> InfoTagGame::getGenres()
{
  return infoTag->GetGenres();
}

String InfoTagGame::getPublisher()
{
  return infoTag->GetPublisher();
}

String InfoTagGame::getDeveloper()
{
  return infoTag->GetDeveloper();
}

String InfoTagGame::getOverview()
{
  return infoTag->GetOverview();
}

unsigned int InfoTagGame::getYear()
{
  return infoTag->GetYear();
}

String InfoTagGame::getGameClient()
{
  return infoTag->GetGameClient();
}

String InfoTagGame::getOriginalTitle()
{
  return infoTag->GetOriginalTitle();
}

float InfoTagGame::getRating()
{
  return infoTag->GetRating();
}

unsigned int InfoTagGame::getPlayers()
{
  return infoTag->GetPlayers();
}

String InfoTagGame::getAgeRating()
{
  return infoTag->GetAgeRating();
}

String InfoTagGame::getTrailer()
{
  return infoTag->GetTrailer();
}

std::vector<String> InfoTagGame::getTags()
{
  return infoTag->GetTags();
}

void InfoTagGame::setTitle(const String& title)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  setTitleRaw(infoTag, title);
}

void InfoTagGame::setPlatform(const String& platform)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  setPlatformRaw(infoTag, platform);
}

void InfoTagGame::setGenres(const std::vector<String>& genres)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  setGenresRaw(infoTag, genres);
}

void InfoTagGame::setPublisher(const String& publisher)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  setPublisherRaw(infoTag, publisher);
}

void InfoTagGame::setDeveloper(const String& developer)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  setDeveloperRaw(infoTag, developer);
}

void InfoTagGame::setOverview(const String& overview)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  setOverviewRaw(infoTag, overview);
}

void InfoTagGame::setYear(unsigned int year)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  setYearRaw(infoTag, year);
}

void InfoTagGame::setGameClient(const String& gameClient)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  setGameClientRaw(infoTag, gameClient);
}

void InfoTagGame::setOriginalTitle(const String& originalTitle)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  infoTag->SetOriginalTitle(originalTitle);
}

void InfoTagGame::setRating(float rating)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  infoTag->SetRating(rating);
}

void InfoTagGame::setPlayers(unsigned int players)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  infoTag->SetPlayers(players);
}

void InfoTagGame::setAgeRating(const String& ageRating)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  infoTag->SetAgeRating(ageRating);
}

void InfoTagGame::setTrailer(const String& trailer)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  infoTag->SetTrailer(trailer);
}

void InfoTagGame::setTags(const std::vector<String>& tags)
{
  AddonUtils::GuiLock lock(languageHook, offscreen);
  infoTag->SetTags(tags);
}

void InfoTagGame::setTitleRaw(UNIVERSAL MEDIA CENTER::GAME::CGameInfoTag* infoTag, const String& title)
{
  infoTag->SetTitle(title);
}

void InfoTagGame::setPlatformRaw(UNIVERSAL MEDIA CENTER::GAME::CGameInfoTag* infoTag, const String& platform)
{
  infoTag->SetPlatform(platform);
}

void InfoTagGame::setGenresRaw(UNIVERSAL MEDIA CENTER::GAME::CGameInfoTag* infoTag, const std::vector<String>& genres)
{
  infoTag->SetGenres(genres);
}

void InfoTagGame::setPublisherRaw(UNIVERSAL MEDIA CENTER::GAME::CGameInfoTag* infoTag, const String& publisher)
{
  infoTag->SetPublisher(publisher);
}

void InfoTagGame::setDeveloperRaw(UNIVERSAL MEDIA CENTER::GAME::CGameInfoTag* infoTag, const String& developer)
{
  infoTag->SetDeveloper(developer);
}

void InfoTagGame::setOverviewRaw(UNIVERSAL MEDIA CENTER::GAME::CGameInfoTag* infoTag, const String& overview)
{
  infoTag->SetOverview(overview);
}

void InfoTagGame::setYearRaw(UNIVERSAL MEDIA CENTER::GAME::CGameInfoTag* infoTag, unsigned int year)
{
  infoTag->SetYear(year);
}

void InfoTagGame::setGameClientRaw(UNIVERSAL MEDIA CENTER::GAME::CGameInfoTag* infoTag, const String& gameClient)
{
  infoTag->SetGameClient(gameClient);
}

} // namespace 
} // namespace Addon
