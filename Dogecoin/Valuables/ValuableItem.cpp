#include "ValuableItem.h"

// Sets default values
AValuableItem::AValuableItem()
{
    // Default values for item properties
    ItemName = TEXT("Unknown Item");
}

// Function to set item name dynamically
void AValuableItem::SetItemName(FString NewName)
{
    ItemName = NewName;
}

// Function to get the current item name
FString AValuableItem::GetItemName() const
{
    return ItemName;
}
