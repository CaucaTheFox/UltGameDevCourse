#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Bird.generated.h"

// forward declarations
class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ULTGAMEDEVCOURSE_API ABird : public APawn
{
	GENERATED_BODY()

public:
	ABird();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* MoveAction;
	
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& value);
	
private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* capsuleCollider;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* skeletalMesh;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* cameraBoom;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera;
};


