# ReadyPlayerDoge Documentation

## Overview

**ReadyPlayerDoge** is a game featuring Dogecoin-based in-game transactions, player wallet management, and inventory tracking. The game incorporates a custom non-custodial Dogecoin wallet, implemented via Unreal Engine C++ and a Node.js API that interacts with a Dogecoin node.

---

## Project Components

### 1. **RPDGameInstance** (`RPDGameInstance.h` and `RPDGameInstance.cpp`)

#### Description
`RPDGameInstance` manages player-specific data and transaction handling, such as Dogecoin balance, transaction history, wallet creation, and Dogecoin sending functionality.

#### Properties
- **DogecoinBalance** (`float`): Tracks the player's Dogecoin balance.
- **WalletAddress** (`FString`): Stores the player’s current Dogecoin address.
- **EncryptedPrivateKey** (`FString`): Stores the encrypted private key for the Dogecoin wallet.
- **TransactionHistory** (`TArray<FTransactionRecord>`): Records transaction history for the player’s Dogecoin transactions.

#### Functions
- **Init()**: Initializes the game instance and sets default values for the wallet.
- **GenerateNewWallet(Passphrase)**: Creates a new Dogecoin wallet, encrypts the private key, and assigns a unique Dogecoin address to `WalletAddress`.
- **LoadWallet(Passphrase)**: Loads an existing wallet using the stored encrypted private key.
- **SendDogecoin(ToAddress, Amount)**: Sends Dogecoin to a specified address if the player has sufficient funds.
- **GetWalletAddress()**: Returns the player's Dogecoin wallet address.
- **AddTransactionRecord(TxID, Amount, Address, bIsSent)**: Adds a transaction to the `TransactionHistory`.
- **GetDogecoinBalance()**: Retrieves the current Dogecoin balance of the player.

---

### 2. **ReadyPlayerDogeGameMode** (`ReadyPlayerDogeGameMode.h` and `ReadyPlayerDogeGameMode.cpp`)

#### Description
`ReadyPlayerDogeGameMode` handles game-specific rules and player interactions, such as managing transactions and updating the HUD with Dogecoin balance information.

#### Properties
- **GameInstanceRef** (`URPDGameInstance*`): A reference to the `RPDGameInstance` used for Dogecoin balance management and transaction handling.

#### Functions
- **BeginPlay()**: Called when the game starts, this function sets up `GameInstanceRef` and logs the player’s starting Dogecoin balance.
- **ProcessTransaction(Amount)**: Processes transactions by adding or subtracting the specified `Amount` from the player's balance. It updates the HUD after each transaction.
- **GetPlayerBalance()**: Retrieves the player’s current Dogecoin balance from the `RPDGameInstance`.
- **UpdateHUD()**: Updates the HUD with the player's current Dogecoin balance.

---

### 3. **InventoryCore** (`InventoryCore.h` and `InventoryCore.cpp`)

#### Description
`InventoryCore` manages the player's in-game inventory, including item storage, item retrieval, and Dogecoin-valued item tracking.

#### Properties
- **InventorySlots** (`TArray<FInventorySlot>`): Holds all inventory slots available for the player.
- **GridWidth** and **GridHeight** (`int32`): Define the inventory grid dimensions.

#### Functions
- **InitializeInventory(Width, Height)**: Initializes the inventory grid with custom dimensions.
- **AddItemToSlot(Item, X, Y)**: Adds an item to a specified inventory slot if it's available.
- **RemoveItemFromSlot(X, Y)**: Removes an item from a specified slot.
- **GetItemFromSlot(X, Y)**: Retrieves an item from a specified slot.
- **AddItemToFirstAvailableSlot(Item)**: Adds an item to the first available slot.
- **ProcessTransaction(DogecoinAmount, isPurchase)**: Handles item transactions involving Dogecoin.

---

### 4. **InventoryUI** (`InventoryUI.h` and `InventoryUI.cpp`)

#### Description
`InventoryUI` handles the display and management of the player's inventory through the HUD.

#### Properties
- **InventoryGrid** (`UUniformGridPanel*`): The UI element where inventory slots are displayed.
- **ItemNameText**, **ItemValueText**, **ItemIconImage** (`UTextBlock*`, `UImage*`): UI elements for displaying item details.

#### Functions
- **InitializeInventory()**: Populates the inventory grid in the UI.
- **UpdateInventoryDisplay()**: Updates the UI to reflect the current inventory.
- **DisplayItemDetails(Item)**: Displays item details when selected.

---

### 5. **Node.js Dogecoin API** (`RPDAPI.js`)

#### Description
A Node.js server that interfaces between the game and a Dogecoin node, handling key wallet operations such as address generation, balance checking, and sending Dogecoin.

#### Routes
- **GET `/`**: Confirms the API server is running.
- **POST `/api/getnewaddress`**: Generates a new Dogecoin receiving address.
- **POST `/api/getbalance`**: Returns the balance of a specified Dogecoin address.
- **POST `/api/senddogecoin`**: Sends Dogecoin from the wallet to a specified address.
- **POST `/api/gettransactions`**: Lists recent transactions.
- **POST `/api/getwalletinfo`**: Provides general wallet information.

#### Environment Variables
- **DOGECOIN_NODE_HOST**: Host of the Dogecoin node.
- **DOGECOIN_NODE_PORT**: Port used by the Dogecoin node.
- **DOGECOIN_RPC_USER** and **DOGECOIN_RPC_PASSWORD**: Credentials for Dogecoin node RPC.
- **DOGECOIN_WALLET**: Optional, for specifying a specific wallet when using multi-wallet.

---

### 6. **Additional Modules and Files**

#### Crypter
The `Crypter` module is responsible for encrypting and decrypting wallet private keys to ensure security.

---

### Usage

1. **Initializing a Wallet**: On game start, `RPDGameInstance` will either create a new wallet or load an existing one.
2. **Transactions**: Use `ProcessTransaction` in `ReadyPlayerDogeGameMode` to handle Dogecoin balance changes.
3. **Updating the HUD**: The game mode automatically updates the HUD to reflect any balance changes.
4. **Inventory**: Manage inventory items with `InventoryCore` and view items in `InventoryUI`.

---

### Notes

- Ensure the Dogecoin node is running and accessible via the Node.js API server.
- Wallet encryption requires a passphrase for enhanced security.

---

This documentation covers the main classes, functions, and system interactions in the ReadyPlayerDoge project. Future additions and feature expansions can build on these core systems.
