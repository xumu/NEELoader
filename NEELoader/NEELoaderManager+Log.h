//
//  NEELoaderManager+Log.h
//  SnailReader
//
//  Created by F_knight on 2019/4/16.
//  Copyright © 2019 com.netease. All rights reserved.
//

#import "NEELoaderManager.h"

NS_ASSUME_NONNULL_BEGIN

@class NEELoaderEntry;

@interface NEELoaderManager (Log)

/* 日志开关 Default NO */
@property (nonatomic, assign) BOOL enableLog;

@property (nonatomic, strong, readonly) NSMutableDictionary<NSString *, NSMutableArray<NEELoaderEntry *> *> *functionEntrys;

@end

NS_ASSUME_NONNULL_END
