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

/** @addtogroup hardwareExtensionInterfaceModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "DeviceNetwork.h"
#include "DeviceNetworkTypes.h"
#include "HardwareExtensionInterfaceCotask.h"

#include <Antilatency.HardwareExtensionInterface.h>
#include <Antilatency.HardwareExtensionInterface.Interop.h>

#include "HardwareExtensionInterfaceLibrary.generated.h"

/** 
 * Provides methods to work with Antilatency Hardware Extension Interface library.
 * Do not instantiate this class directly by calling NewObject<UHardwareExtensionInterfaceLibrary> method,
 * use UHardwareExtensionInterfaceLibrary::GetLibrary instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYHARDWAREEXTENSIONINTERFACE_API UHardwareExtensionInterfaceLibrary : public UObject {
    GENERATED_BODY()

public:
    /** @return UHardwareExtensionInterfaceLibrary library object */
    static UHardwareExtensionInterfaceLibrary* GetLibrary();

	/** Start Hardware Extension Interface task on node. */
    Antilatency::InterfaceContract::ExceptionCode StartHardwareExtensionInterfaceTask(const UDeviceNetwork* network, const FAdnNode& node, UHardwareExtensionInterfaceCotask*& result) const;

    /** Check if node supports Hardware Extension Interface task */
    Antilatency::InterfaceContract::ExceptionCode IsSupported(const UDeviceNetwork* network, const FAdnNode& node, bool& result) const;

    /** Get list of currently connected nodes that supports Hardware Extension Interface task */
    Antilatency::InterfaceContract::ExceptionCode FindSupportedNodes(const UDeviceNetwork* network, TArray<FAdnNode>& result) const;

    /** @return true if library initialized properly */
    bool IsValid() const;

private:
    mutable Antilatency::HardwareExtensionInterface::ILibrary _library;

    Antilatency::HardwareExtensionInterface::ICotaskConstructor GetCotaskConstructor() const;
};

/** @} */