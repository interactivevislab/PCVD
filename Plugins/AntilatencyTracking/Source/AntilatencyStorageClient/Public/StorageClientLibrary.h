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

/** @addtogroup storageClientModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include <Antilatency.StorageClient.h>

#include "Storage.h"

#include "StorageClientLibrary.generated.h"

/**
 * Provides methods to work with the Antilatency Storage Client library.
 * Do not instantiate this class directly by calling NewObject<UStorageClientLibrary> method,
 * use UStorageClientLibrary::GetLibrary instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYSTORAGECLIENT_API UStorageClientLibrary : public UObject {
    GENERATED_BODY()

public:
    /**
     * Get UStorageClientLibrary instance.
     * @return The UStorageClientLibrary wrapper object. If native Antilatency::StorageClient::ILibrary creation fails, returns nullptr.
     */
    static UStorageClientLibrary* GetLibrary();    

    /**
     * Get the remote storage.
     * @param ipAddress IP address of the remote storage client.
     * @param port Port of the remote storage client.
     * @param result The result storage client wrapper to work with the remote storage.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode GetRemoteStorage(const FString& ipAddress, const int32 port, UStorage*& result) const;

    /**
     * Get the local storage client.
     * @param result The result storage client wrapper to work with the local storage.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode GetLocalStorage(UStorage*& result) const;

    /**
     * Check if UStorageClientLibrary has been initialized properly (the native Antilatency::StorageClient::ILibrary is not nullptr).
     * @return True if object is initialized properly, otherwise false.
     */
    bool IsValid() const;

private:
    /** Pointer to native storage client library object */
    mutable Antilatency::StorageClient::ILibrary _library;

    void Init(Antilatency::StorageClient::ILibrary library);
};

/** @} */