#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "CustomCharacter.generated.h"

// forward declarations
class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ULTGAMEDEVCOURSE_API ACustomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACustomCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* LookAction;
	
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	
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
