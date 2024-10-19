#pragma once

#include "CoreMinimal.h"
#include "ValuableObject.h"
#include "ValuableMesh.generated.h"

/**
 * Class representing a static mesh object with a Dogecoin value.
 */
UCLASS(Blueprintable)
class READYPLAYERDOGE_API AValuableMesh : public AValuableObject
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AValuableMesh();

protected:
    // Static mesh component for the object
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    class UStaticMeshComponent* MeshComponent;

public:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Function to set the static mesh
    UFUNCTION(BlueprintCallable, Category = "Mesh")
    void SetMesh(UStaticMesh* NewMesh);
};
