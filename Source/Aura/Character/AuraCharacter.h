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
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	/** Combat Interface **/
	virtual int32 GetPlayerLevel() const override;
	/** End Combat Interface **/
	
protected:
	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;
	
	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<class UCameraComponent> Camera;

private:
	virtual void InitAbilityActorInfo() override;
};
