// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/ToalDataAsset_InputConfig.h"

#include "ToalInputComponent.generated.h"

/**
 *
 */
UCLASS()
class TOA_LIKE_API UToalInputComponent : public UEnhancedInputComponent
{
    GENERATED_BODY()

public:
    template <class UserClass, typename FuncType>
    void BindNativeAction(const UToalDataAsset_InputConfig* InputConfig, const FGameplayTag& InputTag,
                          ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound = false);
};

template <class UserClass, typename FuncType>
inline void UToalInputComponent::BindNativeAction(const UToalDataAsset_InputConfig* InputConfig,
                                                  const FGameplayTag& InputTag, ETriggerEvent TriggerEvent,
                                                  UserClass* Object, FuncType Func, bool bLogIfNotFound)
{

    check(InputConfig);

    if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
    {
        BindAction(IA, TriggerEvent, Object, Func);
    }
}
