#include "StdAfx.h"
#include "PythonCharacterManager.h"
#include "PythonBackground.h"
#include "PythonPlayer.h"
#include "PythonGuild.h"
#include "fmt/fmt.h"

namespace Discord
{
	constexpr auto DiscordClientID = "1100557026179952740";

	using DCDATA = std::pair<std::string, std::string>;

	inline void ReplaceStringInPlace(std::string& subject, const std::string& search,
		const std::string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
	}
	inline void capitalizeWord(std::string& str)
	{
		bool canCapitalize = true;
		for (auto& c : str)
		{
			if (isalpha(c))
			{
				if (canCapitalize)
				{
					c = std::toupper(c);
					canCapitalize = false;
				}
			}
			else
				canCapitalize = true;
		}
	}

	/*NAME*/
	inline DCDATA GetNameData()
	{
		auto MapName = "Shinsoo Empire";
		auto pInstance = CPythonCharacterManager::Instance().GetMainInstancePtr();
		if (!pInstance)
			return { "","" };

		auto EmpireID = pInstance->GetEmpireID();
		switch (EmpireID)
		{
		case 2:
			MapName = "Chunjo Empire";
			break;
		case 3:
			MapName = "Jinno Empire";
		}

		/*CH Name*/
		std::string GuildName;
		CPythonGuild::Instance().GetGuildName(CPythonPlayer::Instance().GetGuildID(), &GuildName);
		auto CHName = fmt::format("Lv. {} - {} {}", CPythonPlayer::Instance().GetStatus(POINT_LEVEL), CPythonPlayer::Instance().GetName(), GuildName);

		return { MapName, CHName };
	}

	/*RACE*/
	inline DCDATA GetRaceData()
	{
		auto pInstance = CPythonCharacterManager::Instance().GetMainInstancePtr();
		if (!pInstance)
			return { "","" };

		auto RACENUM = pInstance->GetRace();

		/*Image*/
		auto EmpireImage = "race_" + std::to_string(RACENUM);

		/*Name*/
		auto EmpireName = "Warrior";
		switch (RACENUM)
		{
		case NRaceData::JOB_ASSASSIN:
		case NRaceData::JOB_ASSASSIN + 4:
			EmpireName = "Assassin";
			break;
		case NRaceData::JOB_SURA:
		case NRaceData::JOB_SURA + 4:
			EmpireName = "Sura";
			break;
		case NRaceData::JOB_SHAMAN:
		case NRaceData::JOB_SHAMAN + 4:
			EmpireName = "Shaman";
			break;
#if defined(ENABLE_WOLFMAN_CHARACTER)
		case NRaceData::JOB_WOLFMAN + 4:
			EmpireName = "Lycan";
#endif
		}
		return { EmpireImage , EmpireName };
	}

	/*EMPIRE*/
	inline DCDATA GetEmpireData()
	{
		/*Image*/
		auto RaceImage = "logo";
		/*Name*/
		auto RaceName = "Zenaris";

		return { RaceImage, RaceName };
	}
}
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
