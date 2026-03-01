#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "ToalDataAsset_InputConfig.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * FToalInputAction
 *
 * Struct used to map a input action to a gameplay input tag.
 */
USTRUCT(BlueprintType)
struct FToalInputAction
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<const UInputAction> InputAction = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
    FGameplayTag InputTag;
};

/**
 *
 */
UCLASS()
class TOA_LIKE_API UToalDataAsset_InputConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Toal|Pawn")
    const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

    UFUNCTION(BlueprintCallable, Category = "Toal|Pawn")
    const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    // List of input actions used by the owner.  These input actions are mapped to a gameplay tag and must be manually
    // bound.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
    TArray<FToalInputAction> NativeInputActions;

    // List of input actions used by the owner.  These input actions are mapped to a gameplay tag and are automatically
    // bound to abilities with matching input tags.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
    TArray<FToalInputAction> AbilityInputActions;
};
