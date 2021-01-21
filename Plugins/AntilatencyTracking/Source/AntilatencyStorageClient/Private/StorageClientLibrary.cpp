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

#include "StorageClientLibrary.h"
#include "IAntilatencyStorageClientModule.h"

#include "StorageClientLog.h"
#include <ExceptionCheck.h>

UStorageClientLibrary* UStorageClientLibrary::GetLibrary() {
    auto module = IAntilatencyStorageClientModule::Get();
    auto library = module.GetNativeLibrary();

    if (library == nullptr) {
        return nullptr;
    }

    auto result = NewObject<UStorageClientLibrary>();
    result->Init(library);
    return result;
}

void UStorageClientLibrary::Init(Antilatency::StorageClient::ILibrary library) {
    _library = library;
}

Antilatency::InterfaceContract::ExceptionCode UStorageClientLibrary::GetRemoteStorage(const FString& ipAddress, const int32 port, UStorage*& result) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::StorageClient::IStorage nativeStorage;
    auto exception = _library.getRemoteStorage(TCHAR_TO_UTF8(*ipAddress), port, nativeStorage);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);
    if (nativeStorage == nullptr) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::InterfaceContract::LongBool storageExists;
    exception = nativeStorage.exists(storageExists);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);
    if (!storageExists) {
        STORAGECLIENT_LOG(Warning, TEXT("Failed to connect to remote storage."));
        return Antilatency::InterfaceContract::ExceptionCode::UnknownFailure;
    }

    result = UStorage::CreateStorage(nativeStorage);    
    return Antilatency::InterfaceContract::ExceptionCode::Ok;
}

Antilatency::InterfaceContract::ExceptionCode UStorageClientLibrary::GetLocalStorage(UStorage*& result) const {
    result = nullptr;

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::StorageClient::IStorage nativeStorage;
    auto exception = _library.getLocalStorage(nativeStorage);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);
    if (nativeStorage == nullptr) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::InterfaceContract::LongBool storageExists;
    exception = nativeStorage.exists(storageExists);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);
    if (!storageExists) {
        STORAGECLIENT_LOG(Warning, TEXT("Failed to connect to local storage."));
        return Antilatency::InterfaceContract::ExceptionCode::UnknownFailure;
    }

    result = UStorage::CreateStorage(nativeStorage);
    return Antilatency::InterfaceContract::ExceptionCode::Ok;
}

bool UStorageClientLibrary::IsValid() const {
    if (_library == nullptr) {
        STORAGECLIENT_LOG(Warning, TEXT("Antilatency Storage Client library is nullptr."));
        return false;
    }

    return true;
}
