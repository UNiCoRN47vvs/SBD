#pragma once

#include "CoreMinimal.h"
//-----------------------------------------------------------------------------------------------------------
//проверка на нульпоинтер и оповещение в случае нульпоинтера
#if !UE_BUILD_SHIPPING
#define CHECK_PTR(Ptr)\
       if (!(Ptr)) {\
           UE_LOG(LogTemp, Warning, TEXT("Null pointer in function %s, line %d"),\
               *FString(__FUNCTION__), __LINE__);\
           return;}
#else
#define CHECK_PTR(Ptr)\
         if (!(Ptr)) {\
            return;}
#endif
//-----------------------------------------------------------------------------------------------------------
//#if !UE_BUILD_SHIPPING
#define CHECK_WEAK_PTR(Ptr)\
       if (!Ptr.IsValid()) {\
           UE_LOG(LogTemp, Warning, TEXT("Null pointer in function %s, line %d"),\
               *FString(__FUNCTION__), __LINE__);\
           return;}
//#else
//#define CHECK_PTR(Ptr)\
//         if (!(Ptr)) {\
//            return;}
//#endif
//-----------------------------------------------------------------------------------------------------------
#define ALARM_LOG \
      UE_LOG(LogTemp, Warning, TEXT("Null pointer in function %s, line %d"), \
               *FString(__FUNCTION__), __LINE__);

//-----------------------------------------------------------------------------------------------------------
#define CHECK_CAST(Variable, Class, Object) \
     if(!(Variable))  {\
         Variable = Cast<Class>(Object);\
         CHECK_PTR(Variable)\
     };
//-----------------------------------------------------------------------------------------------------------
#define PTR(Ptr) \
           if (!(Ptr)) {\
           UE_LOG(LogTemp, Warning, TEXT("Null pointer in function %s, line %d"),\
               *FString(__FUNCTION__), __LINE__);\
           return;}\
           Ptr
//-----------------------------------------------------------------------------------------------------------
#define TIME_SPENT_START \
   double TimeSpentStart = 0.0; \
   double TimeSpentEnd = 0.0; \
   double TimeSpentResult = 0.0; \
   TimeSpentStart = FPlatformTime::Seconds(); \
//-----------------------------------------------------------------------------------------------------------
#define TIME_SPENT_END \
   TimeSpentEnd = FPlatformTime::Seconds(); \
   TimeSpentResult = TimeSpentEnd - TimeSpentStart; \
   UE_LOG(LogTemp, Warning, TEXT(" --\\-- TIME SPENT SECONDS: %f --\\--"), TimeSpentResult);
//-----------------------------------------------------------------------------------------------------------
#define DEBUG_MESSAGE(Time, String) \
      if(GEngine) GEngine->AddOnScreenDebugMessage(-1, Time, FColor::Blue, String);
//-----------------------------------------------------------------------------------------------------------
#define ENUM_TO_TEXT(Value, Class, TextValue) \
      const UEnum* enumPtr = StaticEnum<Class>(); \
     enumPtr  ? TextValue = enumPtr->GetDisplayNameTextByValue(static_cast<int64>(Value)) : TextValue = FText::FromString("Unknown");

#pragma region Public Beta
//Character

#define Public_Beta_Character_Block \
         /*if (saveData->DemoCount >= 2000) { \
            UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true); } \
         else { \
            saveData->DemoCount += 1; } \
 \
         if (saveData->UnixTime > FDateTime::UtcNow().ToUnixTimestamp()) \
         { \
            UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true); \
         } \
         else \
         { \
            saveData->UnixTime = FDateTime::UtcNow().ToUnixTimestamp(); \
         } \*/


//Controller

#define Public_Beta_Controller_Block \
    /*FTimerHandle timerHandle = {}; \
    GetWorld()->GetTimerManager().SetTimer(timerHandle, [this](){ \
             FTimerHandle betaHandle = {}; \
             int64 unixTime = FDateTime::UtcNow().ToUnixTimestamp(); \
             if (unixTime <= 1754056800 || unixTime >= 1754244000) { \
             GetWorld()->GetTimerManager().SetTimer(betaHandle, [this](){ \
                UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit, true);\
             }, FMath::RandRange(5.0f, 30.0f), false); }\
         }, 10.0f, true); \*/

#pragma endregion
