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

/** @addtogroup deviceNetworkModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include <Antilatency.DeviceNetwork.h>

#include "DeviceNetwork.h"

#include "DeviceNetworkLibrary.generated.h"

/**
 * Antilatency Device Network library Log Level
 */
UENUM(BlueprintType)
enum class EDeviceNetworkLogLevel : uint8 {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Critical,
    Off
};

/**
 * Provides methods to work with Device Network library.
 * Do not instantiate this class directly by calling NewObject<UDeviceNetworkLibrary> method,
 * use UDeviceNetworkLibrary::GetLibrary instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYDEVICENETWORK_API UDeviceNetworkLibrary : public UObject {
    GENERATED_BODY()

public:
    /**
     * Get UDeviceNetworkLibrary instance.
     * @return The UDeviceNetworkLibrary wrapper object. If native Antilatency::DeviceNetwork::ILibrary creation fails, returns nullptr.
     */
    static UDeviceNetworkLibrary* GetLibrary();

    /**
     * Create the device network to work with Antilatency devices.
     * @param usbDeviceTypes The array of the USB devices identifiers that will be used by network.
     * @param result The pointer to the created UDeviceNetwork instance.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode CreateNetwork(const TArray<FUsbDeviceType>& usbDeviceTypes, UDeviceNetwork*& result) const;

    /**
     * Get the Antilatency Device Network library version.
     * @param result The Antilatency Device Network library version.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode GetVersion(FString& result) const;

    /**
     * Set the log verbosity level for Antilatency Device Network library.
     * @param level The verbosity level to set.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode SetLogLevel(const EDeviceNetworkLogLevel& level) const;

    /**
     * Check if UDeviceNetworkLibrary has been initialized properly (the native Antilatency::DeviceNetwork::ILibrary is not nullptr).
     * @return True if object is initialized properly, otherwise false.
     */
    bool IsValid() const;

private:
    /** Pointer to native Device Network library object */
    mutable Antilatency::DeviceNetwork::ILibrary _library;

    void Init(Antilatency::DeviceNetwork::ILibrary library);
};

/** @} */