#pragma once

#include "CoreMinimal.h"

#include <type_traits>

#include <Antilatency.InterfaceContract.h>

 #define ANTILATENCY_EXCEPTION_CHECK(interfaceObject, exceptionValue) \
{ \
    static_assert(std::is_base_of<Antilatency::InterfaceContract::IUnsafe, decltype(interfaceObject)>::value, "Type mismatch for interace object"); \
    static_assert(std::is_same<decltype(exceptionValue), Antilatency::InterfaceContract::ExceptionCode>::value, "Type mismatch for exception"); \
    if(exceptionValue != Antilatency::InterfaceContract::ExceptionCode::Ok) { \
        auto exceptionInterface = interfaceObject.queryInterface<Antilatency::InterfaceContract::IExceptionData>(); \
        if(exceptionInterface == nullptr) { \
            UE_LOG(LogTemp, Error, TEXT("Failed to read exception message")); \
        }else{ \
            auto msg = exceptionInterface.getMessage(); \
            UE_LOG(LogTemp, Warning, TEXT("%s"), UTF8_TO_TCHAR(msg.c_str())); \
        } \
    } \
}

/** Check for exception and RETURN FALSE if something going wrong */
#define ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(interfaceObject, exceptionValue) \
{ \
    static_assert(std::is_base_of<Antilatency::InterfaceContract::IUnsafe, decltype(interfaceObject)>::value, "Type mismatch for interace object"); \
    static_assert(std::is_same<decltype(exceptionValue), Antilatency::InterfaceContract::ExceptionCode>::value, "Type mismatch for exception"); \
    if(exceptionValue != Antilatency::InterfaceContract::ExceptionCode::Ok) { \
        auto exceptionInterface = interfaceObject.queryInterface<Antilatency::InterfaceContract::IExceptionData>(); \
        if(exceptionInterface == nullptr) { \
            UE_LOG(LogTemp, Error, TEXT("Failed to read exception message")); \
        }else{ \
            auto msg = exceptionInterface.getMessage(); \
            UE_LOG(LogTemp, Warning, TEXT("%s"), UTF8_TO_TCHAR(msg.c_str())); \
        } \
        return exceptionValue; \
    } \
}
