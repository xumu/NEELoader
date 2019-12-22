//
//  NEELoaderManager.h
//  SnailReader
//
//  Created by F_knight on 2019/4/15.
//  Copyright © 2019 com.netease. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NEELoaderAnnotation.h"


/**
 * NEE_EXPORT_FUNCTION(usage, stage_key, args)
 *
 * @param USAGE 用户标识符
 * @param STAGE_KEY 执行标识符
 *
 * 例：
 *
 * NEE_EXPORT_FUNCTION(@"LaunchingItemA", @"Stage_key_A", NSArray *args) {
 *    arg1 = args.firstObject;
 *    NSLog(@"%@", arg1);
 * }
 *
 */
#define NEE_EXPORT_FUNCTION(USAGE, STAGE_KEY,...) _NEE_EXPORT_FUNCTION_CONVENIENCE(NEE_CATEGORY_PREFIX_DEFAULT, NEE_MODULE_PREFIX_DEFAULT, USAGE, STAGE_KEY, __VA_ARGS__)


/**
 * NEE_LOADER_EXECUTE(stage_key, arg1, agr2, ...)
 *
 * @param STAGE_KEY 执行标识符
 * @param ARG 入参
 *
 * 例:
 *
 * NEE_LOADER_EXECUTE(@"Stage_key_A", @"arg1")
 *
 */
#define NEE_LOADER_EXECUTE(...) _NEE_LOADER_EXECUTE(__VA_ARGS__)

/**
 * NEE_EXPORT_ENV(@"AppID", @"12345678")
 *
 * @param key key
 * @param value value
 *
 */
#define NEE_EXPORT_ENV(key, value) _NEE_EXPORT_ENV(NEE_CATEGORY_PREFIX_DEFAULT, NEE_MODULE_PREFIX_DEFAULT, NEE_NAME_PREFIX_DEFAULT, key, value)

/**
 * NSString *appID = NEE_GET_ENV(@"AppID")
 *
 * @param key key
 * @return value
 *
 */
#define NEE_GET_ENV(key) _NEE_GET_ENV(key)

NS_ASSUME_NONNULL_BEGIN

@interface NEELoaderManager : NSObject

+ (instancetype)shareInstance;

- (NSString *)env:(NSString *)key;

- (void)execute:(NSString *)stageKey args:(NSArray *)args;

@end

NS_ASSUME_NONNULL_END
