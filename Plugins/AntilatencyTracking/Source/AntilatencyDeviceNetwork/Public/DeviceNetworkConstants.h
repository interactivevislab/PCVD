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
#include "Kismet/BlueprintFunctionLibrary.h"

#include "DeviceNetworkTypes.h"

#include "DeviceNetworkConstants.generated.h"

/**
 *
 */
UCLASS()
class ANTILATENCYDEVICENETWORK_API UDeviceNetworkConstantsLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:

    /**
     * @return The predefined FUsbDeviceType structure that matches all Antilatency devices.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|DeviceNetwork|Constants|USB Device Type")
    static FUsbDeviceType AntilatencyUsbDeviceType();

    /**
     * @return The predefined FUsbDeviceType structure that matches all Antilatency devices with legacy vendor ID.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|DeviceNetwork|Constants|USB Device Type")
    static FUsbDeviceType AntilatencyUsbDeviceTypeLegacy();

    /**
     * Get the null node, that can be used as invalid node. Also, calling nodeGetParent on USB node will return null node.
     * @return The null node.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|DeviceNetwork|Constants|Node")
    static FAdnNode NullNode();

    /**
     * The predefined key to get the hardware version property value from the node.
     * @return The hardware version property key.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|DeviceNetwork|Constants|Property Key")
    static FString HardwareVersionKey();

    /**
     * The predefined key to get the hardware name property value from the node.
     * @return The hardware name property key.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|DeviceNetwork|Constants|Property Key")
    static FString HardwareNameKey();

    /**
     * The predefined key to get the software version property value from the node.
     * @return The software version property key.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|DeviceNetwork|Constants|Property Key")
    static FString FirmwareVersionKey();

    /**
     * The predefined key to get the hardware version property value from the node.
     * @return The hardware version property key.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|DeviceNetwork|Constants|Property Key")
    static FString FirmwareNameKey();

    /**
     * The predefined key to get the hardware serial number property value from the node.
     * @return The hardware serial number property key.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|DeviceNetwork|Constants|Property Key")
    static FString HardwareSerialNumberKey();

    /**
     * The predefined key to get the tag property value from the node.
     * @return The tag property key.
     */
    UFUNCTION(BlueprintPure, Category = "Antilatency|DeviceNetwork|Constants|Property Key")
    static FString TagKey();   
};

/** @} */