#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

// forward declarations
class UCapsuleComponent;
class USkeletalMeshComponent;

UCLASS()
class ULTGAMEDEVCOURSE_API ABird : public APawn
{
	GENERATED_BODY()

public:
	ABird();

	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* capsuleCollider;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* skeletalMesh;
};
