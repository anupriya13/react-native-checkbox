/**
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 *
 * @format
 */

import NativeCheckboxModule from './NativeCheckboxModule';

/**
 * Simple multiply function for testing TurboModule connection.
 * @param a First number
 * @param b Second number
 * @returns Product of a and b
 */
export async function multiply(a: number, b: number): Promise<number> {
  if (!NativeCheckboxModule) {
    throw new Error('NativeCheckboxModule is not available');
  }
  return NativeCheckboxModule.multiply(a, b);
}

// Export the native component and its types
export {default as RNCCheckbox} from './RNCCheckboxNativeComponent';
export type {RNCCheckboxNativeProps} from './RNCCheckboxNativeComponent';

// Re-export the native module for direct access
export {default as NativeCheckboxModule} from './NativeCheckboxModule';
export type {Spec as NativeCheckboxModuleSpec} from './NativeCheckboxModule';
