export * from './CheckBox';

// Export the native component and its types (for Windows/New Architecture)
export {default as RNCCheckbox} from './RNCCheckboxNativeComponent';
export type {RNCCheckboxNativeProps} from './RNCCheckboxNativeComponent';

// Re-export the native module for direct access
export {default as NativeCheckboxModule} from './NativeCheckboxModule';
export type {Spec as NativeCheckboxModuleSpec} from './NativeCheckboxModule';
