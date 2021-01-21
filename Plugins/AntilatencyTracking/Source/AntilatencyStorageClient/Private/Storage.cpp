// Copyright 2020, ALT LLC. All Rights Reserved.
// This file is part of Antilatency SDK.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://www.antilatency.com/eula
// You may not use this file except in compliance with the License.
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Storage.h"

#include "StorageClientLog.h"

#include <ExceptionCheck.h>

UStorage* UStorage::CreateStorage(const Antilatency::StorageClient::IStorage& native) {
    if (native == nullptr) {
        STORAGECLIENT_LOG(Warning, TEXT("Antilatency Storage is nullptr"));
        return nullptr;
    }

    auto result = NewObject<UStorage>();
    result->Init(native);
    return result;
}


void UStorage::Init(Antilatency::StorageClient::IStorage native) {
    _native = native;
}


Antilatency::InterfaceContract::ExceptionCode UStorage::Read(const FString& group, const FString& key, FString& result) const {
    result.Empty();

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    std::string nativeValue;
    auto exception = _native.read(TCHAR_TO_UTF8(*group), TCHAR_TO_UTF8(*key), nativeValue);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

    result = { nativeValue.c_str() };
    return exception;
}


Antilatency::InterfaceContract::ExceptionCode UStorage::Write(const FString& group, const FString& key, const FString& data) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    auto exception = _native.write(TCHAR_TO_UTF8(*group), TCHAR_TO_UTF8(*key), TCHAR_TO_UTF8(*data));
    ANTILATENCY_EXCEPTION_CHECK(_native, exception);

    return exception;
}


Antilatency::InterfaceContract::ExceptionCode UStorage::Remove(const FString& group, const FString& key) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    auto exception = _native.remove(TCHAR_TO_UTF8(*group), TCHAR_TO_UTF8(*key));
    ANTILATENCY_EXCEPTION_CHECK(_native, exception);

    return exception;
}


Antilatency::InterfaceContract::ExceptionCode UStorage::Next(const FString& group, const FString& key, FString& result) const {
    result.Empty();

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    std::string nativeValue;
    auto exception = _native.next(TCHAR_TO_UTF8(*group), TCHAR_TO_UTF8(*key), nativeValue);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

    result = { nativeValue.c_str() };
    return exception;
}


bool UStorage::IsValid() const {
    if (_native == nullptr) {
        STORAGECLIENT_LOG(Warning, TEXT("Antilatency Storage is nullptr"));
        return false;
    }

    return true;
}