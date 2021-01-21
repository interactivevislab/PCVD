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

/** @addtogroup altTrackingModule
 *  @{
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include <StorageClientLibrary.h>

#include <Antilatency.Alt.Tracking.h>

#include "AltEnvironment.generated.h"

/** The UE wrapper for the Antilatency tracking environment (IR markers pattern). */
UCLASS(BlueprintType)
class ANTILATENCYALTTRACKING_API UAltEnvironment : public UObject {
    GENERATED_BODY()

public:
    /** Create UAltEnvironment instance using a environment from the Antilatency Service that is marked as default.*/
    static UAltEnvironment* CreateEnvironment();

    /**
     * Create UAltEnvironment instance using the environment code.
     * @param code The environment code (serialized value).
     */
    static UAltEnvironment* CreateEnvironmentUsingCode(const FString& code);

    /**
     *  Create UAltEnvironment instance using a environment from the Antilatency Service with provided name.
     * @param name The name of the environment.
     */
    static UAltEnvironment* CreateEnvironmentUsingName(const FString& name);

    /**
     * Get the pointer to the native Antilatency::Alt::Tracking::IEnvironment object.
     * @return The native Antilatency::Alt::Tracking::IEnvironment object.
     */
    Antilatency::Alt::Tracking::IEnvironment GetNative() const;

    /**
     * Get environment's markers coordinates.
     * @param result The result array of FVector coordinates that represents environment IR markers positions.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode GetMarkers(TArray<FVector>& result) const;

    /**
     * Is current environment is mutable (IR markers pattern is not constantly defined).
     * @param result True if environment is mutable, otherwise false.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode IsMutable(bool& result) const;

    /**
     * Get mutable environment update id: every time when the tracking corrects markers positions, the environment update id will be incremented.
     * @param result Current mutable environment update id.
     * @return ExceptionCode::Ok if the method execution is successfull, otherwise returns the appropriate error code.
     */
    Antilatency::InterfaceContract::ExceptionCode GetUpdateId(int32& result) const;

    /** @return true if the environment has been initialized properly */
    bool IsValid() const;

private:
    /** A pointer to the native environment object */
    mutable Antilatency::Alt::Tracking::IEnvironment _native;

    static Antilatency::InterfaceContract::ExceptionCode GetEnvironmentCode(const FString& name, FString& result);
};

/** @} */