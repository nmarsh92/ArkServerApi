#pragma once
DECLARE_HOOK(APrimalDinoCharacter_Die, bool, APrimalDinoCharacter*, float, FDamageEvent*, AController*, AActor*);
DECLARE_HOOK(AShooterCharacter_Die, bool, AShooterCharacter*, float, FDamageEvent*, AController*, AActor*);


void InitHooks()
{
	if (DinoKillsEnabled) ArkApi::GetHooks().SetHook("APrimalDinoCharacter.Die", &Hook_APrimalDinoCharacter_Die, reinterpret_cast<LPVOID*>(&APrimalDinoCharacter_Die_original));
	if (PlayerKillsEnabled) ArkApi::GetHooks().SetHook("AShooterCharacter.Die", &Hook_AShooterCharacter_Die, reinterpret_cast<LPVOID*>(&AShooterCharacter_Die_original));
}

void RemoveHooks()
{
	if (DinoKillsEnabled) ArkApi::GetHooks().DisableHook("APrimalDinoCharacter.Die", &Hook_APrimalDinoCharacter_Die);
	if (PlayerKillsEnabled) ArkApi::GetHooks().DisableHook("AShooterCharacter.Die", &Hook_AShooterCharacter_Die);
}


const FString GetDinoName(APrimalDinoCharacter* Dino)
{
	FString DinoName;
	Dino->GetDinoDescriptiveName(&DinoName);

	int32 Index = 0;
	if (DinoName.FindLastChar('-', Index))
	{
		DinoName = DinoName.RightChop(Index + 2);
		if (DinoName.FindLastChar('(', Index)) DinoName.RemoveAt(Index);
		if (DinoName.FindLastChar(')', Index)) DinoName.RemoveAt(Index);
	}
	return DinoName;
}

void NotifyDeath(const FString& KillerName, const FString& KillerTribe, const FString& KillerDinoName, const FString& VictimName, const FString& VictimTribe, const FString& WeaponName, UTexture2D* WeaponIcon, float Distance, bool IsPlayer)
{
	const bool isKillerDino = !KillerDinoName.IsEmpty();
	switch (DisplayType)
	{
	case 0:
		if (Distance != 0)
		{

			if (isKillerDino) ArkApi::GetApiUtils().SendNotificationToAll(DisplayColour, DisplayScale, DisplayDelay, WeaponIcon, (IsPlayer ? Messages[6].c_str() : Messages[7].c_str()), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"KillerDinoName", *FString("(" + KillerDinoName + ")")), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName), fmt::arg(L"Distance", trunc_decs(Distance, 2)));
			else ArkApi::GetApiUtils().SendNotificationToAll(DisplayColour, DisplayScale, DisplayDelay, WeaponIcon, (IsPlayer ? Messages[4].c_str() : Messages[5].c_str()), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName), fmt::arg(L"WeaponName", *WeaponName), fmt::arg(L"Distance", trunc_decs(Distance, 2)));
		}
		else
		{
			if (isKillerDino) ArkApi::GetApiUtils().SendNotificationToAll(DisplayColour, DisplayScale, DisplayDelay, WeaponIcon, (IsPlayer ? Messages[2].c_str() : Messages[3].c_str()), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"KillerDinoName", *FString("(" + KillerDinoName + ")")), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName));
			else ArkApi::GetApiUtils().SendNotificationToAll(DisplayColour, DisplayScale, DisplayDelay, WeaponIcon, (IsPlayer ? Messages[0].c_str() : Messages[1].c_str()), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName), fmt::arg(L"WeaponName", *WeaponName));
		}
		break;
	case 1:
		if (Distance != 0) ArkApi::GetApiUtils().SendNotificationToAll(DisplayColour, DisplayScale, DisplayDelay, WeaponIcon, (IsPlayer ? Messages[6].c_str() : Messages[7].c_str()), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"KillerDinoName", *(isKillerDino ? FString("(" + KillerDinoName + ")") : FString(""))), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName), fmt::arg(L"Distance", trunc_decs(Distance, 2)));
		else ArkApi::GetApiUtils().SendNotificationToAll(DisplayColour, DisplayScale, DisplayDelay, WeaponIcon, (IsPlayer ? Messages[2].c_str() : Messages[3].c_str()), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"KillerDinoName", *(isKillerDino ? FString("(" + KillerDinoName + ")") : FString(""))), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName));
		break;
	case 2:
		if (Distance != 0)
		{
			if (isKillerDino) ArkApi::GetApiUtils().SendNotificationToAll(DisplayColour, DisplayScale, DisplayDelay, WeaponIcon, (IsPlayer ? Messages[6].c_str() : Messages[7].c_str()), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"KillerDinoName", *FString("(" + KillerDinoName + ")")), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName), fmt::arg(L"Distance", trunc_decs(Distance, 2)));
			else ArkApi::GetApiUtils().SendNotificationToAll(DisplayColour, DisplayScale, DisplayDelay, WeaponIcon, (IsPlayer ? Messages[4].c_str() : Messages[5].c_str()), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName), fmt::arg(L"WeaponName", *WeaponName), fmt::arg(L"Distance", trunc_decs(Distance, 2)));
		}
		else
		{
			if (isKillerDino) ArkApi::GetApiUtils().SendNotificationToAll(DisplayColour, DisplayScale, DisplayDelay, WeaponIcon, (IsPlayer ? Messages[2].c_str() : Messages[3].c_str()), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"KillerDinoName", *FString("(" + KillerDinoName + ")")), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName));
			else ArkApi::GetApiUtils().SendNotificationToAll(DisplayColour, DisplayScale, DisplayDelay, WeaponIcon, (IsPlayer ? Messages[0].c_str() : Messages[1].c_str()), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName), fmt::arg(L"WeaponName", *WeaponName));
		}
		break;
	}

	if (DisplayInChatbox)
	{
		if (Distance != 0)
		{
			if (isKillerDino) ArkApi::GetApiUtils().SendChatMessageToAll(ServerName, fmt::format(L"<RichColor Color=\"{}, {}, {}, {}\">{}</>", DisplayColour.R, DisplayColour.G, DisplayColour.B, DisplayColour.A, (IsPlayer ? Messages[6].c_str() : Messages[7].c_str())).c_str(), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"KillerDinoName", *FString("(" + KillerDinoName + ")")), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName), fmt::arg(L"Distance", trunc_decs(Distance, 2)));
			else ArkApi::GetApiUtils().SendChatMessageToAll(ServerName, fmt::format(L"<RichColor Color=\"{}, {}, {}, {}\">{}</>", DisplayColour.R, DisplayColour.G, DisplayColour.B, DisplayColour.A, (IsPlayer ? Messages[4].c_str() : Messages[5].c_str())).c_str(), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName), fmt::arg(L"WeaponName", *WeaponName), fmt::arg(L"Distance", trunc_decs(Distance, 2)));
		}
		else
		{
			if (isKillerDino) ArkApi::GetApiUtils().SendChatMessageToAll(ServerName, fmt::format(L"<RichColor Color=\"{}, {}, {}, {}\">{}</>", DisplayColour.R, DisplayColour.G, DisplayColour.B, DisplayColour.A, (IsPlayer ? Messages[2].c_str() : Messages[3].c_str())).c_str(), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"KillerDinoName", *FString("(" + KillerDinoName + ")")), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName));
			else ArkApi::GetApiUtils().SendChatMessageToAll(ServerName, fmt::format(L"<RichColor Color=\"{}, {}, {}, {}\">{}</>", DisplayColour.R, DisplayColour.G, DisplayColour.B, DisplayColour.A, (IsPlayer ? Messages[0].c_str() : Messages[1].c_str())).c_str(), fmt::arg(L"KillerTribe", *(KillerTribe.IsEmpty() ? FString("") : FString("[" + KillerTribe + "]"))), fmt::arg(L"KillerName", *KillerName), fmt::arg(L"VictimTribe", *(VictimTribe.IsEmpty() ? FString("") : FString("[" + VictimTribe + "]"))), fmt::arg(L"VictimName", *VictimName), fmt::arg(L"WeaponName", *WeaponName));
		}
	}
}

void LogDeath(AShooterCharacter* _this, float KillingDamage, FDamageEvent* DamageEvent, AController* Killer, AActor* DamageCauser) {
	
}

void RequestCallback(bool success, std::string response)
{
	//
}

void PostToDiscord(const FString& KillerName, const FString& KillerTribe, const FString& KillerDinoName, const FString& VictimName, const FString& VictimTribe, const FString& WeaponName, UTexture2D* WeaponIcon, float Distance, bool IsPlayer) {
	const bool isKillerDino = !KillerDinoName.IsEmpty();
	FString text = "";

	text = ServerName + ": Player " + VictimName + " [" + VictimTribe + "]" + " was killed by " + KillerName + " [" + KillerTribe + "]";

	if (isKillerDino) {
		text.Append(" with a " + KillerDinoName);
	}
	else {
		text.Append(" with a " + WeaponName);
	}

	//if (Distance > 0) {
	//	text.Append(" (");
	//	text.Append(FString(std::to_string(trunc_decs(Distance, 2))));
	//	text.Append("m)");
	//}

	AShooterGameMode* GameMode = ArkApi::GetApiUtils().GetShooterGameMode();

	AGameState* GameState = GameMode->GameStateField();

	AShooterGameState* ShooterGameState = static_cast<AShooterGameState*>(GameState);
	nlohmann::json my_json = {
			  {"content", text.ToString().c_str() }
	};

	ShooterGameState->HTTPPostRequest(DiscordWebhookURL, FString(ArkApi::Tools::Utf8Decode(my_json.dump().c_str())));

}

bool _cdecl Hook_AShooterCharacter_Die(AShooterCharacter* _this, float KillingDamage, FDamageEvent* DamageEvent, AController* Killer, AActor* DamageCauser)
{
	if (_this && _this->PlayerStateField() && Killer && !Killer->IsLocalController() && Killer->IsA(AShooterPlayerController::StaticClass()))
	{
		AShooterPlayerController* KillerShooterController = static_cast<AShooterPlayerController*>(Killer);
		if (KillerShooterController && KillerShooterController->PlayerStateField() && KillerShooterController->GetPlayerCharacter() && (DisplaySameTribeKills || _this->TargetingTeamField() != KillerShooterController->GetPlayerCharacter()->TargetingTeamField()))
		{
			FString KillerDinoName, WeaponName = "Punch";
			UTexture2D* WeaponIcon = nullptr;

			if (KillerShooterController->GetPlayerCharacter()->CurrentWeaponField() && KillerShooterController->GetPlayerCharacter()->CurrentWeaponField()->AssociatedPrimalItemField())
			{
				if (DisplayType != 2) WeaponIcon = KillerShooterController->GetPlayerCharacter()->CurrentWeaponField()->AssociatedPrimalItemField()->ItemIconField();

				KillerShooterController->GetPlayerCharacter()->CurrentWeaponField()->AssociatedPrimalItemField()->GetItemName(&WeaponName, false, true, nullptr);
			}

			if (KillerShooterController->GetPlayerCharacter()->GetRidingDino())
				KillerDinoName = GetDinoName(KillerShooterController->GetPlayerCharacter()->GetRidingDino());

			float Distance = 0;
			if (DisplayDistance) Distance = (FVector::Distance((_this->RootComponentField() ? _this->RootComponentField()->RelativeLocationField() : FVector(0, 0, 0)), (KillerShooterController->GetPlayerCharacter()->RootComponentField() ? KillerShooterController->GetPlayerCharacter()->RootComponentField()->RelativeLocationField() : FVector(0, 0, 0))) / 220);
			NotifyDeath(ArkApi::GetApiUtils().GetCharacterName(KillerShooterController), KillerShooterController->GetPlayerCharacter()->TribeNameField(), KillerDinoName, _this->PlayerNameField(), _this->TribeNameField(), WeaponName, WeaponIcon, Distance, true);
			/*	if (StoreInDB) {
					LogDeath(_this, KillingDamage, DamageEvent, Killer, DamageCauser);
				}*/

			if (UseDiscordWebhook) {
				PostToDiscord(ArkApi::GetApiUtils().GetCharacterName(KillerShooterController), KillerShooterController->GetPlayerCharacter()->TribeNameField(), KillerDinoName, _this->PlayerNameField(), _this->TribeNameField(), WeaponName, WeaponIcon, Distance, true);
			}
			
			//possible code to get location, would need to add params for location webhook etc
	/*		FVector* groundLocation;
			FVector* offsetUp;
			FVector* offsetDown;
			if (KillerShooterController->GetPlayerCharacter()->GetGroundLocation(groundLocation, offsetUp, offsetDown)) 
			{
			};*/

		}
	}
	return AShooterCharacter_Die_original(_this, KillingDamage, DamageEvent, Killer, DamageCauser);
}

bool _cdecl Hook_APrimalDinoCharacter_Die(APrimalDinoCharacter* Dino, float KillingDamage, FDamageEvent* DamageEvent, AController* Killer, AActor* DamageCauser)
{
	if (Dino && !Dino->bIsBaby().Get() && Dino->TargetingTeamField() > 49999 && Killer && !Killer->IsLocalController() && Killer->IsA(AShooterPlayerController::StaticClass()))
	{
		AShooterPlayerController* KillerShooterController = static_cast<AShooterPlayerController*>(Killer);
		if (KillerShooterController && KillerShooterController->PlayerStateField() && KillerShooterController->GetPlayerCharacter() && (DisplaySameTribeKills || Dino->TargetingTeamField() != KillerShooterController->GetPlayerCharacter()->TargetingTeamField()))
		{
			FString DinoName, KillerDinoName, WeaponName = "Punch";
			UTexture2D* WeaponIcon = nullptr;

			DinoName = GetDinoName(Dino);

			if (KillerShooterController->GetPlayerCharacter()->CurrentWeaponField() && KillerShooterController->GetPlayerCharacter()->CurrentWeaponField()->AssociatedPrimalItemField())
			{
				if (DisplayType != 2) WeaponIcon = KillerShooterController->GetPlayerCharacter()->CurrentWeaponField()->AssociatedPrimalItemField()->ItemIconField();

				KillerShooterController->GetPlayerCharacter()->CurrentWeaponField()->AssociatedPrimalItemField()->GetItemName(&WeaponName, false, true, nullptr);
			}

			if (KillerShooterController->GetPlayerCharacter()->GetRidingDino())
				KillerDinoName = GetDinoName(KillerShooterController->GetPlayerCharacter()->GetRidingDino());

			float Distance = 0;
			if (DisplayDistance) Distance = (FVector::Distance((Dino->RootComponentField() ? Dino->RootComponentField()->RelativeLocationField() : FVector(0, 0, 0)), (KillerShooterController->GetPlayerCharacter()->RootComponentField() ? KillerShooterController->GetPlayerCharacter()->RootComponentField()->RelativeLocationField() : FVector(0, 0, 0))) / 220);
			NotifyDeath(ArkApi::GetApiUtils().GetCharacterName(KillerShooterController), KillerShooterController->GetPlayerCharacter()->TribeNameField(), KillerDinoName, DinoName, Dino->TribeNameField(), WeaponName, WeaponIcon, Distance, false);
		}
	}
	return APrimalDinoCharacter_Die_original(Dino, KillingDamage, DamageEvent, Killer, DamageCauser);
}

