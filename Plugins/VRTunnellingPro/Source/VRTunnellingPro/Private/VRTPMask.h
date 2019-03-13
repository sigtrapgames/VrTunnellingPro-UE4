
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VRTPMask.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UVRTPMask : public UActorComponent
{
	GENERATED_BODY()

public:
	UVRTPMask();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

};
