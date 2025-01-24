// Copyright Terren 

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

protected:
	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;
	
	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<class UCameraComponent> Camera;
};
