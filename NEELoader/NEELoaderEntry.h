//
//  NEELoaderEntry.h
//  SnailReader
//
//  Created by F_knight on 2019/4/15.
//  Copyright © 2019 com.netease. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NEELoaderEntry : NSObject

@property (nonatomic, copy) NSString *category;
@property (nonatomic, copy) NSString *module;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *stage_key;
@property (nonatomic, assign) void *value;
@property (nonatomic, assign) char *encoding;
@property (nonatomic, assign) void *info;

@property (nonatomic, copy, readonly) NSString *identify;

- (instancetype)initWithCategory:(NSString *)category module:(NSString *)module name:(NSString *)name stage_key:(NSString *)stage_key;

- (instancetype)initWithName:(NSString *)name stage_key:(NSString *)stage_key;


@end

NS_ASSUME_NONNULL_END
