#pragma once
#include <Windows.h>
#include "API\ARK\Ark.h"
#include "Requests.h"

bool PlayerKillsEnabled, DinoKillsEnabled, DisplayInChatbox, DisplaySameTribeKills, DisplayDistance, UseDiscordWebhook;
int DisplayType;
float DisplayScale, DisplayDelay;
FLinearColor DisplayColour;
FString ServerName, DiscordWebhookURL;
std::wstring Messages[8];

const float trunc_decs(const float& f, int decs)
{
	int i1 = static_cast<int>(floor(f));
	float rmnd = f - i1;
	int i2 = static_cast<int>(rmnd * pow(10, decs));
	float f1 = static_cast<float>(i2 / pow(10, decs));
	return i1 + f1;
}