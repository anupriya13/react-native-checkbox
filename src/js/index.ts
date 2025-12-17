/**
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License.
 *
 * @format
 */

'use strict';

// Export the default CheckBox component based on platform
export {default} from './CheckboxNativeComponent';

// Export the TurboModule (for native module access if needed)
export {default as NativeCheckboxModule} from './NativeCheckboxModule';

// Export the Windows-specific native component spec
export {default as RNCCheckboxNativeComponent} from './RNCCheckboxNativeComponent';
export type {RNCCheckboxNativeProps} from './RNCCheckboxNativeComponent';

// Export the platform-specific CheckBox components
export {default as CheckBoxWindows} from './CheckBox.windows';
export type {Props as CheckBoxWindowsProps} from './CheckBox.windows';
