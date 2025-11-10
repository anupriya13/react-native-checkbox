// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

'use strict';

import type {ViewProps, ColorValue, HostComponent} from 'react-native';
import type {BubblingEventHandler} from 'react-native/Libraries/Types/CodegenTypes';
import codegenNativeComponent from 'react-native/Libraries/Utilities/codegenNativeComponent';

type CheckBoxEvent = Readonly<{
  target: number;
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

export default codegenNativeComponent<NativeProps>('Checkbox') as HostComponent<NativeProps>;
