#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <Interfaces/IHttpRequest.h>
#include "DogecoinManager.generated.h"

/**
 * Delegate signatures for broadcasting results
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWalletBalanceChecked, const FString&, Balance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWalletCreated, const FString&, NewWalletAddress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDogecoinSent, const FString&, TransactionId, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTransactionsRetrieved, const FString&, Transactions);

/**
 * Dogecoin Manager for handling interactions with the Dogecoin network
 */
UCLASS()
class READYPLAYERDOGE_API UDogecoinManager : public UGameInstance
{
    GENERATED_BODY()

public:
    // Functions to interact with the Dogecoin network with output parameters
    UFUNCTION(BlueprintCallable, Category = "Dogecoin")
    void CheckWalletBalance(const FString& WalletAddress, FString& BalanceOutput);

    UFUNCTION(BlueprintCallable, Category = "Dogecoin")
    void CreateNewWallet(FString& NewWalletAddressOutput);

    UFUNCTION(BlueprintCallable, Category = "Dogecoin")
    void SendDogecoin(const FString& ToAddress, float Amount, FString& TransactionIdOutput, bool& bSuccessOutput);

    UFUNCTION(BlueprintCallable, Category = "Dogecoin")
    void GetRecentTransactions(FString& TransactionsOutput);

    // Functions to get the last results for Blueprint-Pure access
    UFUNCTION(BlueprintPure, Category = "Dogecoin")
    FString GetLastWalletBalance() const;

    UFUNCTION(BlueprintPure, Category = "Dogecoin")
    FString GetLastCreatedWalletAddress() const;

    UFUNCTION(BlueprintPure, Category = "Dogecoin")
    FString GetLastTransactionId() const;

    UFUNCTION(BlueprintPure, Category = "Dogecoin")
    bool GetLastTransactionSuccess() const;

    UFUNCTION(BlueprintPure, Category = "Dogecoin")
    FString GetLastTransactionsList() const;

    // Delegates for broadcasting results
    UPROPERTY(BlueprintAssignable, Category = "Dogecoin")
    FOnWalletBalanceChecked OnWalletBalanceChecked;

    UPROPERTY(BlueprintAssignable, Category = "Dogecoin")
    FOnWalletCreated OnWalletCreated;

    UPROPERTY(BlueprintAssignable, Category = "Dogecoin")
    FOnDogecoinSent OnDogecoinSent;

    UPROPERTY(BlueprintAssignable, Category = "Dogecoin")
    FOnTransactionsRetrieved OnTransactionsRetrieved;

private:
    // Private helper functions to handle HTTP responses
    void OnCheckBalanceResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    void OnCreateWalletResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    void OnSendDogecoinResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    void OnGetTransactionsResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    // Variables to store the last results
    FString LastWalletBalance;
    FString LastCreatedWalletAddress;
    FString LastTransactionId;
    bool bLastTransactionSuccess;
    FString LastTransactionsList;
};
