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

/** @addtogroup bracerModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BracerCotask.h"
#include "DeviceNetwork.h"
#include "DeviceNetworkTypes.h"

#include <Antilatency.Bracer.h>

#include "BracerLibrary.generated.h"

/** 
 * Provides methods to work with Antilatency Bracer library.
 * Do not instantiate this class directly by calling NewObject<UBracerLibrary> method,
 * use UBracerLibrary::GetLibrary instead.
 */
UCLASS(BlueprintType)
class ANTILATENCYBRACER_API UBracerLibrary : public UObject {
    GENERATED_BODY()

public:
    /** @return bracer library object */
    static UBracerLibrary* GetLibrary();

    

    Antilatency::InterfaceContract::ExceptionCode StartBracerTask(const UDeviceNetwork* network, const FAdnNode& node, UBracerCotask*& result) const;

    /** Check if node supports bracer task */
    Antilatency::InterfaceContract::ExceptionCode IsSupported(const UDeviceNetwork* network, const FAdnNode& node, bool& result) const;

    /** Get list of currently connected nodes that supports bracer task */
    Antilatency::InterfaceContract::ExceptionCode FindSupportedNodes(const UDeviceNetwork* network, TArray<FAdnNode>& result) const;

    /** @return true if library initialized properly */
    bool IsValid() const;

private:
    /** Pointer to native bracer library object */
    mutable Antilatency::Bracer::ILibrary _library;

    Antilatency::Bracer::ICotaskConstructor GetCotaskConstructor() const;
	
    void Init(Antilatency::Bracer::ILibrary& library);
};

/** @} */