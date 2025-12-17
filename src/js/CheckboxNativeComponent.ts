/**
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License.
 *
 * @format
 */

'use strict';

import type {HostComponent} from 'react-native';
import {Platform} from 'react-native';
import type {RNCCheckboxNativeProps} from './RNCCheckboxNativeComponent';

// Re-export the native props type
export type {RNCCheckboxNativeProps as NativeProps};

let CheckboxNativeComponent: HostComponent<RNCCheckboxNativeProps>;

if (Platform.OS === 'windows') {
  // Use the Windows-specific native component with codegen
  CheckboxNativeComponent = require('./RNCCheckboxNativeComponent').default;
} else if (Platform.OS === 'android') {
  CheckboxNativeComponent = require('./AndroidCheckBoxNativeComponent').default;
} else {
  CheckboxNativeComponent = require('./IOSCheckBoxNativeComponent').default;
}

export default CheckboxNativeComponent;
