#include "../Dogecoin/DogecoinManager.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonUtilities.h"

void UDogecoinManager::CreateNewWallet(FString& NewWalletAddressOutput)
{
    FHttpModule* Http = &FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

    UE_LOG(LogTemp, Warning, TEXT("Sending request to create new wallet"));

    Request->OnProcessRequestComplete().BindUObject(this, &UDogecoinManager::OnCreateWalletResponse);
    Request->SetURL("http://localhost:3000/api/createwallet");  // Updated to API server URL
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/json");

    Request->SetContentAsString("{}");  // Empty body for the POST request

    UE_LOG(LogTemp, Warning, TEXT("Request content: {}"));

    Request->ProcessRequest();

    NewWalletAddressOutput = LastCreatedWalletAddress;
}

void UDogecoinManager::OnCreateWalletResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response->GetResponseCode() == 200)
    {
        FString ResponseString = Response->GetContentAsString();
        UE_LOG(LogTemp, Warning, TEXT("Wallet creation response: %s"), *ResponseString);

        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);
        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            FString WalletAddress = JsonObject->GetStringField("address");
            LastCreatedWalletAddress = WalletAddress;
            OnWalletCreated.Broadcast(WalletAddress);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create wallet. Response Code: %d"), Response->GetResponseCode());
        LastCreatedWalletAddress = "Failed";
        OnWalletCreated.Broadcast("Failed");
    }
}

void UDogecoinManager::CheckWalletBalance(const FString& WalletAddress, FString& BalanceOutput)
{
    FHttpModule* Http = &FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

    Request->OnProcessRequestComplete().BindUObject(this, &UDogecoinManager::OnCheckBalanceResponse);
    Request->SetURL("http://localhost:3000/api/getbalance");  // Updated to API server URL
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/json");

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField("address", WalletAddress);
    JsonObject->SetNumberField("minConfirmations", 0);

    FString Content;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Content);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    Request->SetContentAsString(Content);

    Request->ProcessRequest();

    BalanceOutput = LastWalletBalance;
}

void UDogecoinManager::OnCheckBalanceResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response->GetResponseCode() == 200)
    {
        FString ResponseString = Response->GetContentAsString();
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);
        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            double Balance = JsonObject->GetNumberField("balance");
            LastWalletBalance = FString::SanitizeFloat(Balance);
            OnWalletBalanceChecked.Broadcast(LastWalletBalance);
        }
    }
    else
    {
        LastWalletBalance = "Failed";
        OnWalletBalanceChecked.Broadcast("Failed");
    }
}

void UDogecoinManager::SendDogecoin(const FString& ToAddress, float Amount, FString& TransactionIdOutput, bool& bSuccessOutput)
{
    FHttpModule* Http = &FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

    Request->OnProcessRequestComplete().BindUObject(this, &UDogecoinManager::OnSendDogecoinResponse);
    Request->SetURL("http://localhost:3000/api/senddogecoin");  // Updated to API server URL
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/json");

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField("toAddress", ToAddress);
    JsonObject->SetNumberField("amount", Amount);

    FString Content;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Content);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    Request->SetContentAsString(Content);

    Request->ProcessRequest();

    TransactionIdOutput = LastTransactionId;
    bSuccessOutput = bLastTransactionSuccess;
}

void UDogecoinManager::OnSendDogecoinResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response->GetResponseCode() == 200)
    {
        FString ResponseString = Response->GetContentAsString();
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);
        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            FString TransactionId = JsonObject->GetStringField("txId");
            LastTransactionId = TransactionId;
            bLastTransactionSuccess = true;
            OnDogecoinSent.Broadcast(TransactionId, true);
        }
    }
    else
    {
        LastTransactionId = "Failed";
        bLastTransactionSuccess = false;
        OnDogecoinSent.Broadcast("Failed", false);
    }
}

void UDogecoinManager::GetRecentTransactions(FString& TransactionsOutput)
{
    FHttpModule* Http = &FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

    Request->OnProcessRequestComplete().BindUObject(this, &UDogecoinManager::OnGetTransactionsResponse);
    Request->SetURL("http://localhost:3000/api/gettransactions");  // Updated to API server URL
    Request->SetVerb("GET");
    Request->SetHeader("Content-Type", "application/json");

    Request->ProcessRequest();

    TransactionsOutput = LastTransactionsList;
}

void UDogecoinManager::OnGetTransactionsResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response->GetResponseCode() == 200)
    {
        FString ResponseString = Response->GetContentAsString();
        LastTransactionsList = ResponseString;
        OnTransactionsRetrieved.Broadcast(ResponseString);
    }
    else
    {
        LastTransactionsList = "Failed";
        OnTransactionsRetrieved.Broadcast("Failed");
    }
}

FString UDogecoinManager::GetLastWalletBalance() const
{
    return LastWalletBalance;
}

FString UDogecoinManager::GetLastCreatedWalletAddress() const
{
    return LastCreatedWalletAddress;
}

FString UDogecoinManager::GetLastTransactionId() const
{
    return LastTransactionId;
}

bool UDogecoinManager::GetLastTransactionSuccess() const
{
    return bLastTransactionSuccess;
}

FString UDogecoinManager::GetLastTransactionsList() const
{
    return LastTransactionsList;
}
