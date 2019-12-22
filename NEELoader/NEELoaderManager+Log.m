//
//  NEELoaderManager+Log.m
//  SnailReader
//
//  Created by F_knight on 2019/4/16.
//  Copyright © 2019 com.netease. All rights reserved.
//

#import "NEELoaderManager+Log.h"
#import <objc/runtime.h>
#import "NEELoaderStore.h"

@interface NEELoaderManager (Extension)

@property (nonatomic, strong) NEELoaderStore *store;

@end

@implementation NEELoaderManager (Log)

- (BOOL)enableLog {
    NSNumber *enable = objc_getAssociatedObject(self, @selector(enableLog));
    if (enable) {
        return [enable boolValue];
    }
    return NO;
}

- (void)setEnableLog:(BOOL)enableLog {
    objc_setAssociatedObject(self, @selector(enableLog), @(enableLog), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (NSMutableDictionary<NSString *,NSMutableArray<NEELoaderEntry *> *> *)functionEntrys {
    return (NSMutableDictionary<NSString *,NSMutableArray<NEELoaderEntry *> *> *)self.store.functionStore;
}

@end
