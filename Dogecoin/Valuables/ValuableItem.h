#pragma once

#include "CoreMinimal.h"
#include "ValuableObject.h"
#include "ValuableItem.generated.h"

/**
 * Class representing an interactive item with a Dogecoin value.
 */
UCLASS(Blueprintable)
class READYPLAYERDOGE_API AValuableItem : public AValuableObject
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AValuableItem();

    // Item Name for display purposes
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString ItemName;

    // Function to set the item name dynamically
    UFUNCTION(BlueprintCallable, Category = "Item")
    void SetItemName(FString NewName);

    // Function to get the item name
    UFUNCTION(BlueprintCallable, Category = "Item")
    FString GetItemName() const;
};
