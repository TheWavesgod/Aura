// Copyright Terren 


#include "CharacterClassInfo.h"


FCharacterClassDefaultInfo UCharacterClassInfo::GetCharacterDefault(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}
