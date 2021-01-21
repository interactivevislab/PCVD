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

using System;
using System.IO;

namespace UnrealBuildTool.Rules {
    public class AntilatencyStorageClient : ModuleRules {

        public AntilatencyStorageClient(ReadOnlyTargetRules Target) : base(Target) {
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

            string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", ".."));
            string BinaryDirectory = Path.Combine(BaseDirectory, "ThirdParty", "Antilatency", "Bin", Target.Platform.ToString());
            string HeadersDirectory = Path.Combine(BaseDirectory, "ThirdParty", "Antilatency", "Include");

            string PublicInclude = Path.Combine(BaseDirectory, "Source", "AntilatencyStorageClient", "Public");
            string PrivateInclude = Path.Combine(BaseDirectory, "Source", "AntilatencyStorageClient", "Private");

            PublicIncludePathModuleNames.AddRange(
                new string[] {
                    "Launch",
                    "Core"
                }
            );

            PublicIncludePaths.AddRange(
                new string[] {
                    HeadersDirectory
                }
            );

            /*PrivateIncludePaths.AddRange(
                new string[] { }
            );*/

            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "Projects",
                    "AntilatencyDeviceNetwork"
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {}
            );

            DynamicallyLoadedModuleNames.AddRange(
                new string[] {}
            );

            if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64) {
                var storageClientLibraryPath = Path.Combine(BinaryDirectory, "AntilatencyStorageClient.dll");

#if UE_4_19_OR_LATER
                RuntimeDependencies.Add(storageClientLibraryPath);
#else
                RuntimeDependencies.Add(new RuntimeDependency(storageClientLibraryPath));
#endif
            } else if (Target.Platform == UnrealTargetPlatform.Android) {
                string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                string AplPath = Path.Combine(PluginPath, "AntilatencyStorageClient_APL.xml");
#if UE_4_19_OR_LATER
				AdditionalPropertiesForReceipt.Add("AndroidPlugin", AplPath);
#else
                AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", AplPath));
#endif
            } else {
                throw new NotImplementedException("NOT IMPLEMENTED YET FOR PLATFORM " + Target.Platform.ToString());
            }
        }
    }
}
