#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ValuableObject.generated.h"

/**
 * A base class for any object that can hold a Dogecoin value.
 */
UCLASS(Blueprintable)
class READYPLAYERDOGE_API AValuableObject : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AValuableObject();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Property to store the object's Dogecoin value
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dogecoin")
    float DogecoinValue;

    // Function to set the Dogecoin value dynamically
    UFUNCTION(BlueprintCallable, Category = "Dogecoin")
    void SetDogecoinValue(float NewValue);

    // Function to get the Dogecoin value
    UFUNCTION(BlueprintCallable, Category = "Dogecoin")
    float GetDogecoinValue() const;
};
