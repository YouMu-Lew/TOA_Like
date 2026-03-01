#pragma once

#include "CoreMinimal.h"
#include "Characters/ToalBaseCharacter.h"
#include "Engine/DataAsset.h"

#include "ToalHeroCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UToalDataAsset_InputConfig;
struct FInputActionValue;

/**
 *
 */
UCLASS()
class TOA_LIKE_API AToalHeroCharacter : public AToalBaseCharacter
{
    GENERATED_BODY()

public:
    AToalHeroCharacter();

    //~ Begin AActor interface
    virtual void BeginPlay() override;
    //~ End AActor interface

protected:
    //~ Begin APawn Interface.
    virtual void PossessedBy(AController* NewController) override;
    //~ End APawn Interface

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    void Input_Move(const FInputActionValue& InputActionValue);
    void Input_LookMouse(const FInputActionValue& InputActionValue);
    void Input_LookStick(const FInputActionValue& InputActionValue);

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Toal|Character", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UToalDataAsset_InputConfig> InputConfigDataAsset;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Toal|Camera", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Toal|Character", Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> FollowCamera;
};
