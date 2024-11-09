# 🐾 ReadyPlayerDoge

## 🎮 **Game Overview**

**ReadyPlayerDoge** is a sandbox, open-world game that combines player creativity, crafting, exploration, and an integrated Dogecoin economy. Inspired by games like **Minecraft** and **Space Engineers**, it allows players to gather resources, craft items, build structures, and trade within a persistent in-game economy. The game also integrates real-world Dogecoin transactions, making it possible to earn and spend Dogecoin while playing.

---

## 🛠️ **Key Game Features**
- **Dogecoin Economy**:
  - Players can purchase, sell, and trade in-game items using Dogecoin.
  - Integrated blockchain functionality to exchange in-game Dogecoin for real-world Dogecoin and vice versa.
  - Potential for **play-to-earn** mechanics.

- **Crafting & Building**:
  - Modular crafting system where players can design custom objects by connecting nodes in 3D space.
  - Create and customize structures using collected resources.

- **Open World & Exploration**:
  - Explore a vast game world filled with resources, valuable objects, and secrets.
  - Use tools and items to mine, build, and craft your way through the environment.

- **Inventory & Quick Slots**:
  - Manage resources, crafting materials, and tools using a grid-based inventory system.
  - Quick slots for easy access to frequently used items during gameplay.

---

## 🛠️ **Inventory System Overview**

### 1. Inventory Core
- **Class**: `AInventoryCore`
  - Manages inventory operations, including adding/removing items, swapping slots, and transactions.
  - Uses a **grid-based** system for inventory slots (e.g., 10x10 grid).

### 2. Inventory Slot
- **Struct**: `FInventorySlot`
  - Represents slots in the inventory with support for stacking items.

### 3. Inventory UI
- **Class**: `UInventoryUI`
  - Handles the user interface for inventory management.

### 4. Quick Slots Component
- **Class**: `UQuickSlotsComponent`
  - Manages quick access slots for frequently used items.

### 5. Valuable Object
- **Class**: `AValuableObject`
  - Represents collectible items in the game world.

---

## 💰 **Transaction Manager**
- **Class**: `UTransactionManager`
  - Handles HTTP requests for real-world Dogecoin transactions.

### **Functions**:
```cpp
void ProcessPurchase(AValuableObject* Item, APlayerController* PlayerController);
void ProcessSale(AValuableObject* Item, APlayerController* PlayerController);
```

---

## 📦 **Project Structure**
```
ReadyPlayerDoge/
├── InventoryCore/
│   ├── InventoryCore.cpp
│   ├── InventoryCore.h
│   ├── InventoryManager.cpp
│   ├── InventoryManager.h
│   ├── InventorySlot.cpp
│   ├── InventorySlot.h
│   ├── InventorySlotWidget.cpp
│   ├── InventorySlotWidget.h
│   ├── InventoryUI.cpp
│   ├── InventoryUI.h
│   ├── QuickSlotsComponent.cpp
│   ├── QuickSlotsComponent.h
│   ├── TransactionManager.cpp
│   ├── TransactionManager.h
│   ├── ValuableObject.cpp
│   └── ValuableObject.h
├── PlaneControl/
│   ├── PlaneControl.cpp
│   ├── PlaneControl.h
└── ReadyPlayerDogeCharacter.cpp
```

---


## 🚀 **Gameplay Instructions**

### Inventory Management
- **Opening Inventory**: Press the designated key to toggle the inventory UI.
- **Adding Items**: Pick up items in the world, which will be added to the inventory automatically.
- **Quick Slots**: Assign frequently used items to quick slots for easy access.

### Dogecoin Transactions
- **Purchasing**: Use the in-game shop to buy items using Dogecoin.
- **Selling**: Sell valuable objects to earn Dogecoin, which can be converted to real-world Dogecoin.

---

## 👾 **Controls**

| Action                     | Key/Button     |
|----------------------------|-----------------|
| Open/Close Inventory       | `I`            |
| Use Quick Slot 1           | `1`            |
| Use Quick Slot 2           | `2`            |
| Use Quick Slot 3           | `3`            |
| Pick Up Item               | `E`            |
| Jump                       | `Space`        |
| Move                       | `WASD`         |
| Look Around                | Mouse Movement |

---

## 🤖 **Technical Details**

### Inventory System Implementation
The inventory system uses a **grid-based** approach, where each item occupies a slot in a 2D array. Items can be stacked if they share the same `ItemID` and are marked as stackable.

#### Example Code Snippet:
```cpp
bool AInventoryCore::AddItemToSlot(AValuableObject* Item, int32 X, int32 Y, int32 Quantity)
{
    if (!Item) return false;
    int32 Index = GetSlotIndex(X, Y);
    if (InventorySlots.IsValidIndex(Index))
    {
        if (InventorySlots[Index].Item == nullptr || InventorySlots[Index].Item == Item)
        {
            InventorySlots[Index].AddItem(Item, Quantity);
            OnInventoryUpdated.Broadcast();
            return true;
        }
    }
    return false;
}
```

### Dogecoin Integration
The game integrates with a Dogecoin node via `UTransactionManager`. It sends HTTP requests to process purchases and sales using real Dogecoin.

#### Example Code Snippet:
```cpp
void UTransactionManager::ProcessPurchase(AValuableObject* Item, APlayerController* PlayerController)
{
    if (!Item || !PlayerController) return;
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("ItemName"), Item->GetDisplayName());
    JsonObject->SetNumberField(TEXT("DogecoinValue"), Item->GetDogecoinValue());
    
    FString ContentJson;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentJson);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

    FString Url = FString(TEXT("http://localhost:3000/api/purchase"));
    SendTransactionRequest(Url, ContentJson);
}
```

---

## 📝 **Contributors**
- **TheDogeBird** - Lead Developer
