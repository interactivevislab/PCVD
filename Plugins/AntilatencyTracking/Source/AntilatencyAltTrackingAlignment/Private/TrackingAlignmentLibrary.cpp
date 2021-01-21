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

#include "TrackingAlignmentLibrary.h"
#include "IAntilatencyTrackingAlignmentModule.h"
#include "TrackingAlignmentLog.h"

#include <ExceptionCheck.h>

UTrackingAlignmentLibrary* UTrackingAlignmentLibrary::GetLibrary() {
    auto module = IAntilatencyTrackingAlignmentModule::Get();
    auto library = module.GetNativeLibrary();

    if (library == nullptr) {
        return nullptr;
    }

    auto result = NewObject<UTrackingAlignmentLibrary>();
    result->Init(library);
    return result;
}

void UTrackingAlignmentLibrary::Init(Antilatency::TrackingAlignment::ILibrary& library) {
    _library = library;
}

Antilatency::InterfaceContract::ExceptionCode UTrackingAlignmentLibrary::CreateTrackingAlignment(const FQuat& initialARelativeToB, const float initialTimeBAheadOfA, UTrackingAlignment*& result) const {
    result = {};

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

	Antilatency::Math::doubleQ nativeInitialARelativeToB = { 
		double{initialARelativeToB.Y}, 
		double{initialARelativeToB.Z}, 
		double{initialARelativeToB.X}, 
		double{initialARelativeToB.W} 
	};

	Antilatency::TrackingAlignment::ITrackingAlignment native;
	auto exception = _library.createTrackingAlignment(nativeInitialARelativeToB, double{ initialTimeBAheadOfA }, native);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);

	result = UTrackingAlignment::CreateTrackingAlignment(native);
	
	return exception;
}

bool UTrackingAlignmentLibrary::IsValid() const {
    if (_library == nullptr) {
        TRACKINGALIGNMENT_LOG(Warning, TEXT("Library is null"));
        return false;
    }
    return true;
}