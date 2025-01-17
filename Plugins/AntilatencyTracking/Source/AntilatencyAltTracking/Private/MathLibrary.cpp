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

#include "MathLibrary.h"

static const FQuat identityFQuat = FQuat(0.f, 0.f, 0.f, 1.f);

FQuat UMathLibrary::MakeFQuat(float x, float y, float z, float w) {
    return FQuat(x, y, z, w);
}

FQuat UMathLibrary::FQuatIdentity() {
    return identityFQuat;
}

FQuat UMathLibrary::FRotatorToFQuat(const FRotator& r) {
    return FQuat(r);
}

FRotator UMathLibrary::FQuatToFRotator(const FQuat& q) {
    return FRotator(q);
}

FQuat UMathLibrary::MultFQuatFQuat(const FQuat& q1, const FQuat& q2) {
    return q1 * q2;
}

FQuat UMathLibrary::InverseFQuat(const FQuat& q) {
    return q.Inverse();
}

FQuat UMathLibrary::FastLerpFQuat(const FQuat& q1, const FQuat& q2, float alpha) {
    return FQuat::FastLerp(q1, q2, alpha);
}

FQuat UMathLibrary::SLerpFQuat(const FQuat& q1, const FQuat& q2, float alpha) {
    return FQuat::Slerp(q1, q2, alpha);
}

FQuat UMathLibrary::NormalizeFQuat(const FQuat& q, float tolerance) {
    FQuat result(q);
    result.Normalize(tolerance);
    return result;
}

float UMathLibrary::FQuatAngularDistance(const FQuat& q1, const FQuat& q2) {
    return q1.AngularDistance(q2);
}
