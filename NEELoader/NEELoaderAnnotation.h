//
//  NEELoaderAnnotation.h
//  SnailReader
//
//  Created by F_knight on 2019/4/15.
//  Copyright © 2019 com.netease. All rights reserved.
//

#ifndef NEELoaderAnnotation_h
#define NEELoaderAnnotation_h

#import "NEEMetamacors.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef __unsafe_unretained NSString *NEE_Unsafe_String;
    
typedef struct {
    NEE_Unsafe_String *category;
    NEE_Unsafe_String *module;
    NEE_Unsafe_String *name;
    NEE_Unsafe_String *stage_key;
    void *value;
    char **encoding;
    void *info;
} nee_entry;
    
__attribute__((used)) static id _nee_wrap_arg(void *value, char *encoding) {
/**
 * C++编译 和 OC环境下 nil 和 Nil 都正常
 * C++编译环境下传入NULL, 处理会异常, 宏会展开为 __null, encode 为 encode(long) "q"
 */
  __auto_type nilType = nil;
  //  https://nshipster.com/type-encodings/
    if (strcmp(encoding, @encode(BOOL)) == 0) {
        return @(*(BOOL *) value);
    } else if (strcmp(encoding, @encode(float)) == 0) {
        return @(*(float *) value);
    } else if (strcmp(encoding, @encode(double)) == 0) {
        return @(*(double *) value);
    } else if (strcmp(encoding, @encode(short)) == 0) {
        return @(*(short *) value);
    } else if (strcmp(encoding, @encode(unsigned short)) == 0) {
        return @(*(unsigned short *) value);
    } else if (strcmp(encoding, @encode(int)) == 0) {
        return @(*(int *)value);
    } else if (strcmp(encoding, @encode(unsigned int)) == 0) {
        return @(*(unsigned int *)value);
    } else if (strcmp(encoding, @encode(long)) == 0) {
        return @(*(long *)value);
    } else if (strcmp(encoding, @encode(unsigned long)) == 0) {
        return @(*(unsigned long *)value);
    } else if (strcmp(encoding, @encode(long long)) == 0) {
        return @(*(long long *)value);
    } else if (strcmp(encoding, @encode(unsigned long long)) == 0) {
        return @(*(unsigned long long *)value);
    } else if (strcmp(encoding, @encode(NSInteger)) == 0) {
        return @(*(NSInteger *)value);
    } else if (strcmp(encoding, @encode(NSUInteger)) == 0) {
        return @(*(NSUInteger *)value);
    } else if (strcmp(encoding, @encode(id)) == 0) {
#if __has_feature(objc_arc)
        return *(id __weak *)value;
#else
        return *(id __unsafe_unretained  *)value;
#endif
    } else if (strcmp(encoding, @encode(__typeof__(nilType))) == 0) {
        return nil;
    } else {
        NSCAssert(NO, @"Unknown encoding %s . Value was %p.", encoding, value);
        return nil;
    }
}

#define NEESegmentName "__DATA"
#define NEESectionName "NEELoader"
#define NEEncodingFUNC "__FUNC__"
#define NEEncodingENV "__ENV__"
    
#define NEE_CATEGORY_PREFIX_DEFAULT @"NEE_CATEGORY" //category
#define NEE_MODULE_PREFIX_DEFAULT @"NEE_MODULE" //module
#define NEE_NAME_PREFIX_DEFAULT @"NEE_NAME" //name

#define NEE_FUNC_CATEGORY_PREFIX           __nee_func_category_
#define NEE_FUNC_MODULE_PREFIX             __nee_func_module_
#define NEE_FUNC_NAME_PREFIX               __nee_func_name_
#define NEE_FUNC_KEY_PREFIX                __nee_func_key_
#define NEE_FUNC_PTR_PREFIX                __nee_func_ptr_
#define NEE_FUNC_DECLARE_NAME_PREFIX       __nee_func_declare_name_
#define NEE_FUNC_ENCODING_PREFIX           __nee_func_encoding_
#define NEE_FUNC_ENTRY_PREFIX              __nee_func_entry_
#define NEE_FUNC_INFO_ENTRY_PREFIX         __nee_func_info_entry_
    
#define NEE_ENV_CATEGORY_PREFIX            __nee_env_category_
#define NEE_ENV_MODULE_PREFIX              __nee_env_module_
#define NEE_ENV_NAME_PREFIX                __nee_env_name_
#define NEE_ENV_KEY_PREFIX                 __nee_env_key_
#define NEE_ENV_VALUE_PREFIX               __nee_env_value_
#define NEE_ENV_ENCODING_PREFIX            __nee_env_encoding_
#define NEE_ENV_ENTRY_PREFIX               __nee_env_entry_
    
#define __NEECONCAT2_(X, Y) X ## Y
#define __NEECONCAT3_(X, Y, Z) X ## Y ## Z
    
#define __NEECONCAT(X, ...) \
    metamacro_if_eq(1, metamacro_argcount(__VA_ARGS__))\
    (__NEECONCAT2_(X, __VA_ARGS__))\
    (__NEECONCAT3_(X, __VA_ARGS__))


/* Func */
#define _NEE_VOID_FUNC(...) _NEE_VOID_FUNC_COUNT_DISPATCH(__VA_ARGS__)
    
#define _NEE_VOID_FUNC_COUNT_DISPATCH(counter, CMD, ...) \
  metamacro_if_eq(1, metamacro_argcount(__VA_ARGS__))\
    (CMD(0, counter, __VA_ARGS__))\
    (metamacro_if_eq(2, metamacro_argcount(__VA_ARGS__))\
      (CMD(1, counter, __VA_ARGS__))\
      (CMD(1, counter, __VA_ARGS__))\
    )
    
#define _NEE_FUNC_COUNT_DECLARE(args_count, counter, ...) \
  __attribute__((used)) static int __NEECONCAT(NEE_FUNC_INFO_ENTRY_PREFIX, counter) = args_count; \
  metamacro_if_eq(0, args_count) \
   (_NEE_FUNC_COUNT_0(counter, __VA_ARGS__)) \
   (_NEE_FUNC_COUNT(args_count, counter, __VA_ARGS__))
    
#define _NEE_FUNC_COUNT_IMP(args_count, counter, ...) \
  metamacro_if_eq(0, args_count) \
   (_NEE_FUNC_COUNT_0(counter, __VA_ARGS__)) \
   (_NEE_FUNC_COUNT(args_count, counter, __VA_ARGS__))
    
#define _NEE_FUNC_COUNT_0(counter, ...) \
_NEE_DECLARE_VOID_FUNC(__NEECONCAT(NEE_FUNC_DECLARE_NAME_PREFIX, counter), void)
    
#define _NEE_FUNC_COUNT(args_count, counter, stage_key, ...) \
_NEE_VOID_FUNC_COUNT_INTERNAL(counter, args_count, __VA_ARGS__)
    
#define _NEE_VOID_FUNC_COUNT_INTERNAL(counter, arg_count, ...) \
_NEE_DECLARE_VOID_FUNC(__NEECONCAT(NEE_FUNC_DECLARE_NAME_PREFIX, counter), __VA_ARGS__)
    
#define _NEE_DECLARE_VOID_FUNC(name, ...) static void name(__VA_ARGS__)
    
/* Attribute */
#define _NEE_EXPORT_ENV_INTERNAL(category, module, name, suffix, stage_key, value) \
/* store the loader entry data in the binary at compile time. */ \
__attribute__((used)) static NEE_Unsafe_String __NEECONCAT(NEE_ENV_CATEGORY_PREFIX, suffix) = category; \
__attribute__((used)) static NEE_Unsafe_String __NEECONCAT(NEE_ENV_MODULE_PREFIX, suffix) = module; \
__attribute__((used)) static NEE_Unsafe_String __NEECONCAT(NEE_ENV_NAME_PREFIX, suffix) = name; \
__attribute__((used)) static NEE_Unsafe_String __NEECONCAT(NEE_ENV_KEY_PREFIX, suffix) = stage_key; \
__attribute__((used)) static void * __NEECONCAT(NEE_ENV_VALUE_PREFIX, suffix) = value; \
__attribute__((used)) static char * __NEECONCAT(NEE_ENV_ENCODING_PREFIX, suffix) = (char *)NEEncodingENV; \
__attribute__((used)) __attribute__((section (NEESegmentName "," NEESectionName))) static nee_entry __NEECONCAT(NEE_ENV_ENTRY_PREFIX, suffix) = { \
&__NEECONCAT(NEE_ENV_CATEGORY_PREFIX, suffix), \
&__NEECONCAT(NEE_ENV_MODULE_PREFIX, suffix), \
&__NEECONCAT(NEE_ENV_NAME_PREFIX, suffix), \
&__NEECONCAT(NEE_ENV_KEY_PREFIX, suffix), \
&__NEECONCAT(NEE_ENV_VALUE_PREFIX, suffix), \
&__NEECONCAT(NEE_ENV_ENCODING_PREFIX, suffix), \
NULL,\
}; \

#define _NEE_EXPORT_FUNCTION_ATTRIBUTE_INTERNAL(category, module, name, suffix, function, stage_key, ...) \
/* store the loader entry data in the binary at compile time. */ \
__attribute__((used)) static NEE_Unsafe_String __NEECONCAT(NEE_FUNC_CATEGORY_PREFIX, suffix) = category; \
__attribute__((used)) static NEE_Unsafe_String __NEECONCAT(NEE_FUNC_MODULE_PREFIX, suffix) = module; \
__attribute__((used)) static NEE_Unsafe_String __NEECONCAT(NEE_FUNC_NAME_PREFIX, suffix) = name; \
__attribute__((used)) static NEE_Unsafe_String __NEECONCAT(NEE_FUNC_KEY_PREFIX, suffix) = stage_key; \
__attribute__((used)) static void * __NEECONCAT(NEE_FUNC_PTR_PREFIX, suffix) = function; \
__attribute__((used)) static char * __NEECONCAT(NEE_FUNC_ENCODING_PREFIX, suffix) = (char *)NEEncodingFUNC;
    
    
#define _NEE_EXPORT_FUNCTION_ENTRY_INTERNAL_2(suffix) \
__attribute__((used)) __attribute__((section (NEESegmentName "," NEESectionName))) static nee_entry __NEECONCAT(NEE_FUNC_ENTRY_PREFIX, suffix) = { \
&__NEECONCAT(NEE_FUNC_CATEGORY_PREFIX, suffix), \
&__NEECONCAT(NEE_FUNC_MODULE_PREFIX, suffix), \
&__NEECONCAT(NEE_FUNC_NAME_PREFIX, suffix), \
&__NEECONCAT(NEE_FUNC_KEY_PREFIX, suffix), \
&__NEECONCAT(NEE_FUNC_PTR_PREFIX, suffix), \
&__NEECONCAT(NEE_FUNC_ENCODING_PREFIX, suffix), \
&__NEECONCAT(NEE_FUNC_INFO_ENTRY_PREFIX, suffix),\
}; \

/* Func Setter & Getter*/
#define _NEE_EXPORT_FUNCTION_INTERNAL(category, module, name, counter, function, stage_key, ...) \
_NEE_EXPORT_FUNCTION_ATTRIBUTE_INTERNAL(category, module, name, counter, function, stage_key) \
_NEE_EXPORT_FUNCTION_ENTRY_INTERNAL_2(counter)
    
#define _NEE_EXPORT_FUNCTION_CONVENIENCE_INTERNAL(category, module, name, counter, ...) \
_NEE_VOID_FUNC(counter, _NEE_FUNC_COUNT_DECLARE, __VA_ARGS__); \
_NEE_EXPORT_FUNCTION_INTERNAL(category, module, name, counter, __NEECONCAT(NEE_FUNC_DECLARE_NAME_PREFIX, counter), __VA_ARGS__) \
_NEE_VOID_FUNC(counter, _NEE_FUNC_COUNT_IMP, __VA_ARGS__)

#define _NEE_EXPORT_FUNCTION_CONVENIENCE(category, module, name, ...) \
_NEE_EXPORT_FUNCTION_CONVENIENCE_INTERNAL(category, module, name, __COUNTER__, __VA_ARGS__)


#define _NEE_WRAP_VALUE(index, arg, ...) \
metamacro_if_eq(0, index) \
(__auto_type nee_call_key = arg;) \
({ \
__auto_type __NEECONCAT(nee_arg, index) = arg; \
__auto_type __NEECONCAT(nee_arg_type, index) = (char *)@encode(__typeof__(__NEECONCAT(nee_arg, index))); \
id __NEECONCAT(nee_wraped_arg, index) = _nee_wrap_arg(&__NEECONCAT(nee_arg, index), __NEECONCAT(nee_arg_type, index)); \
[nee_args_array addObject:__NEECONCAT(nee_wraped_arg, index) ?: [NSNull null]]; \
}) \
    
#define _NEE_LOADER_EXECUTE(...) {\
__auto_type nee_args_array = [NSMutableArray array]; \
metamacro_foreach(_NEE_WRAP_VALUE, ,__VA_ARGS__) \
[[NEELoaderManager shareInstance] execute:nee_call_key args:nee_args_array]; \
}
    
/* ENV Setter & Getter*/
#define _NEE_EXPORT_ENV(category, module, name, stage_key, value) \
_NEE_EXPORT_ENV_INTERNAL(category, module, name, __COUNTER__, stage_key, value)
   
#define _NEE_GET_ENV(key) [[NEELoaderManager shareInstance] env:key];
    
#ifdef __cplusplus
}
#endif

#endif /* NEELoaderAnnotation_h */
