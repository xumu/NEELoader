//
//  NEELoaderStore.h
//  SnailReader
//
//  Created by F_knight on 2019/4/15.
//  Copyright © 2019 com.netease. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NEELoaderEntry.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NEEEntryType) {
    NEEEntryTypeFunc = 1,
    NEEEntryTypeENV,
};

@interface NEELoaderEntryExt : NEELoaderEntry

@property (nonatomic, assign, readonly) NEEEntryType type;

@property (nonatomic, copy, readonly, nullable) NSString *envValue;
@property (nonatomic, readonly, nullable) void *imp;
@property (nonatomic, assign, readonly) int argsCount;

- (instancetype)initWithCategory:(NSString *)category module:(NSString *)module name:(NSString *)name stageKey:(NSString *)stageKey value:(void *)value encoding:(char *)encoding;

@end


@interface NEELoaderStore : NSObject

@property (nonatomic, strong) NSMutableDictionary<NSString *, NSMutableArray<NEELoaderEntryExt *> *> *functionStore;
@property (nonatomic, strong) NSMutableDictionary<NSString *, NEELoaderEntryExt *> *envStore;

- (void)addItem:(NEELoaderEntryExt *)item;


@end

NS_ASSUME_NONNULL_END
