/**
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License.
 *
 * @format
 */

'use strict';

import type {TurboModule} from 'react-native';
import {TurboModuleRegistry} from 'react-native';

export interface Spec extends TurboModule {
  // Multiply two numbers and return the result
  multiply(a: number, b: number): Promise<number>;
}

export default TurboModuleRegistry.get<Spec>('Checkbox') as Spec | null;
