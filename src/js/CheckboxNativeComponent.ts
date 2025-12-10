// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

'use strict';

import type {ViewProps, ColorValue, HostComponent} from 'react-native';
import type {BubblingEventHandler} from 'react-native/Libraries/Types/CodegenTypes';
import {Platform} from 'react-native';
import codegenNativeComponent from 'react-native/Libraries/Utilities/codegenNativeComponent';

type CheckBoxEvent = Readonly<{
  value: boolean;
}>;

export interface NativeProps extends ViewProps {
  disabled?: boolean;
  value?: boolean;
  tintColor?: ColorValue;
  onCheckColor?: ColorValue;
  onTintColor?: ColorValue;
  onFillColor?: ColorValue;
  onChange?: BubblingEventHandler<CheckBoxEvent>;
}

let CheckboxNativeComponent: HostComponent<NativeProps>;

// Windows uses requireNativeComponent with static view config
if (Platform.OS === 'windows') {
  // @ts-ignore requireNativeComponent typing
  const {requireNativeComponent} = require('react-native');
  // Provide a static view config to avoid dynamic lookup in new architecture
  CheckboxNativeComponent = requireNativeComponent('Checkbox', {
    nativeOnly: {
      onChange: true,
    }
  });
} else {
  CheckboxNativeComponent = codegenNativeComponent<NativeProps>('WindowsCheckBoxComponent') as HostComponent<NativeProps>;
}

export default CheckboxNativeComponent;
