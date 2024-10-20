# Features of the Updated Code

## 1. Interactable Valuable Objects

**Functionality:** Players can interact with `ValuableObject` instances in the game world.

**Behavior:** When the player interacts with a `ValuableObject`, it is added to their inventory, and the object is destroyed from the world.

**Logging:** The action is logged, providing feedback in the output log.

---

## 2. Player Inventory System

**Class:** `AInventoryCore` manages the player's inventory.

**Structure:** Implements a grid-based inventory system with configurable `GridWidth` and `GridHeight`.

**Slot Management:**

- **Add Items:** `AddItemToSlot` adds items to specific slots.
- **Remove Items:** `RemoveItemFromSlot` removes items from slots.
- **Retrieve Items:** `GetItemFromSlot` retrieves items from specific slots.
- **Check Availability:** `IsSlotAvailable` checks if a slot is free.

---

## 3. Valuable Object Properties and Methods

### Properties:

- **`DogecoinValue`:** Represents the value of the object in Dogecoin.
- **`Dimensions`:** The size of the object for inventory placement.
- **`MeshComponent`:** Visual representation of the object.
- **`ObjectMaterial`:** Material or texture applied to the object.

### Methods:

- **`SetDogecoinValue`:** Dynamically sets the value.
- **`GetDogecoinValue`:** Retrieves the current value.
- **`SetObjectMaterial`:** Changes the object's material dynamically.
- **`Use`:** Defines what happens when the object is used.
- **`OnInteract`:** Handles the interaction logic with the player.

---

## 4. Player Character Enhancements

- **Inventory Integration:** The player character now holds a reference to the `PlayerInventory`, allowing seamless interaction with the inventory system.
- **Plane Control:** Spawns a `PlaneControl` actor for additional gameplay mechanics (as per your existing code).
- **Input Handling:** The character handles various input actions, including movement, looking, jumping, and interacting with the plane.

---

## 5. Inventory UI Framework

**Class:** `UInventoryUI` serves as the base for the inventory user interface.

**Functions:**

- **`UpdateInventoryDisplay`:** Updates the UI to reflect the current inventory state.
- **`DisplayItemDetails`:** Shows details about a selected item.
- **`PopulateInventoryGrid`:** Fills the UI grid with inventory items.

**Status:** These functions are set up for further implementation, possibly in Blueprints.

---

## 6. Error Handling and Logging

- **Comprehensive Checks:** The code includes null checks and logs warnings or errors when operations fail.
- **Debugging Aid:** Logging statements throughout the code help trace execution flow and identify issues during testing.

---
